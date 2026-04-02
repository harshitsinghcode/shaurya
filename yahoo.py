"""Standalone real-price exchange for the existing Shaurya engine.

Previous mock-only approach kept here as reference:

# messages = [
#     '8=FIX.4.2|35=X|55=AAPL|269=0|270=150.50|',
#     '8=FIX.4.2|35=X|55=GOOGL|269=0|270=2800.10|',
# ]
# for raw in messages:
#     send(raw)

This script listens on localhost:5000, accepts the Shaurya engine,
fetches a real stock price from a public HTTP endpoint, formats it as a
FIX-like tick, and streams it to the engine.
"""

from __future__ import annotations

import argparse
import json
import socket
import time
import urllib.error
import urllib.request
from datetime import datetime

DEFAULT_HOST = "127.0.0.1"
DEFAULT_PORT = 5000
DEFAULT_SYMBOL = "KLA"
DEFAULT_INTERVAL_SECONDS = 1.0
DEFAULT_ITERATIONS = 20
DEFAULT_SPIKE_THRESHOLD_MS = 50.0
YAHOO_CHART_URL = "https://query1.finance.yahoo.com/v8/finance/chart/{symbol}?interval=1m&range=1d"


def fetch_real_stock_price(symbol: str) -> float:
    url = YAHOO_CHART_URL.format(symbol=symbol)
    request = urllib.request.Request(
        url,
        headers={
            "User-Agent": "Mozilla/5.0",
            "Accept": "application/json",
        },
    )
    with urllib.request.urlopen(request, timeout=10) as response:
        payload = json.loads(response.read().decode("utf-8"))

    result = payload["chart"]["result"][0]
    quote = result["indicators"]["quote"][0]

    for key in ("close", "open", "high", "low"):
        series = quote.get(key) or []
        if series and series[-1] is not None:
            return float(series[-1])

    raise RuntimeError(f"No price data returned for {symbol}")


from datetime import datetime, timezone

def build_fix_message(symbol: str, price: float, side: str = "0") -> str:
    # Use timezone-aware datetime to fix the deprecation warning
    timestamp = datetime.now(timezone.utc).strftime("%Y%m%d-%H:%M:%S.%f")[:-3]
    
    # We use pipes (|) instead of \x01 to match your old mock, 
    # and add \n at the end so the C++ TCP socket knows the message is over!
    return (
        f"8=FIX.4.2|35=X|49=REALFEED|55={symbol}|269={side}"
        f"|270={price:.2f}|52={timestamp}|\n"
    )


def accept_engine_client(host: str, port: int) -> socket.socket:
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((host, port))
    server.listen(1)
    print(f"[INJECTOR] Listening on {host}:{port}")
    conn, addr = server.accept()
    print(f"[INJECTOR] Engine connected from {addr[0]}:{addr[1]}")
    server.close()
    return conn


def inject_message(conn: socket.socket, message: str) -> float:
    start = time.perf_counter()
    conn.sendall(message.encode("utf-8"))
    return (time.perf_counter() - start) * 1000.0


def main() -> int:
    parser = argparse.ArgumentParser(description="Fetch real stock prices and inject them into Shaurya.")
    parser.add_argument("--symbol", default=DEFAULT_SYMBOL, help="Stock symbol to fetch, e.g. AAPL")
    parser.add_argument("--host", default=DEFAULT_HOST, help="Exchange host to bind")
    parser.add_argument("--port", type=int, default=DEFAULT_PORT, help="Target exchange port")
    parser.add_argument("--iterations", type=int, default=DEFAULT_ITERATIONS, help="Number of ticks to inject")
    parser.add_argument("--interval", type=float, default=DEFAULT_INTERVAL_SECONDS, help="Seconds between injections")
    parser.add_argument("--spike-threshold-ms", type=float, default=DEFAULT_SPIKE_THRESHOLD_MS, help="Latency threshold to flag")
    args = parser.parse_args()

    print(f"[INJECTOR] Binding exchange on {args.host}:{args.port}")
    print(f"[INJECTOR] Symbol: {args.symbol}")

    try:
        conn = accept_engine_client(args.host, args.port)
    except OSError as exc:
        print(f"[INJECTOR] Socket error while binding: {exc}")
        return 1

    with conn:
        try:
            for index in range(args.iterations):
                price = fetch_real_stock_price(args.symbol)
                fix_message = build_fix_message(args.symbol, price)
                latency_ms = inject_message(conn, fix_message)
                spike = " <== LATENCY SPIKE" if latency_ms >= args.spike_threshold_ms else ""
                print(
                    f"[INJECTOR] {index + 1}/{args.iterations} {args.symbol}={price:.2f} "
                    f"sent in {latency_ms:.2f} ms{spike}"
                )

                if index + 1 < args.iterations:
                    time.sleep(args.interval)
        except urllib.error.URLError as exc:
            print(f"[INJECTOR] HTTP error fetching {args.symbol}: {exc}")
            return 1
        except (socket.timeout, ConnectionError, OSError) as exc:
            print(f"[INJECTOR] Socket error: {exc}")
            return 1
        except Exception as exc:
            print(f"[INJECTOR] Unexpected error: {exc}")
            return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
