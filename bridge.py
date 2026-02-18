import asyncio
import websockets
import json
import socket

# C:\Users\Admin\shaurya\bridge.py

SOURCES = [
    {"name": "BINANCE",  "url": "wss://stream.binance.com:9443/ws/btcusdt@trade"},
    {"name": "COINBASE", "url": "wss://ws-feed.exchange.coinbase.com"},
    {"name": "BITSTAMP", "url": "wss://ws.bitstamp.net"}
]

global_ticks = 0

async def send_to_cpp(conn, loop, fix_msg):
    global global_ticks
    global_ticks += 1
    
    # --- DEMO FEATURE: Inject Anomaly every 30 ticks to trigger FPGA ---
    if global_ticks % 30 == 0:
        print("\n[GATEWAY] INJECTING FAT FINGER ANOMALY ($250,000) TO TEST FPGA...\n")
        fix_msg = "8=FIX.4.2\x0135=X\x0149=ANOMALY\x0155=BTCUSDT\x01269=0\x01270=250000.00\x01"

    try:
        await loop.sock_sendall(conn, fix_msg.encode())
    except Exception as e:
        pass # Ignore if C++ disconnects

async def stream_binance(conn, loop):
    url = SOURCES[0]["url"]
    while True:
        try:
            async with websockets.connect(url) as ws:
                print(f"[CONNECT] Connected to {SOURCES[0]['name']}")
                async for msg in ws:
                    data = json.loads(msg)
                    price = data['p']
                    fix = f"8=FIX.4.2\x0135=X\x0149=BINANCE\x0155=BTCUSDT\x01269=0\x01270={price}\x01"
                    await send_to_cpp(conn, loop, fix)
                    await asyncio.sleep(0.1) # Throttle to prevent Windows buffer overflow
        except Exception:
            await asyncio.sleep(1)

async def stream_coinbase(conn, loop):
    url = SOURCES[1]["url"]
    while True:
        try:
            async with websockets.connect(url) as ws:
                await ws.send(json.dumps({"type": "subscribe", "product_ids": ["BTC-USD"], "channels": ["ticker"]}))
                print(f"[CONNECT] Connected to {SOURCES[1]['name']}")
                async for msg in ws:
                    data = json.loads(msg)
                    if 'price' in data:
                        price = data['price']
                        fix = f"8=FIX.4.2\x0135=X\x0149=COINBASE\x0155=BTCUSD\x01269=0\x01270={price}\x01"
                        await send_to_cpp(conn, loop, fix)
                        await asyncio.sleep(0.1)
        except Exception:
            await asyncio.sleep(1)

async def stream_bitstamp(conn, loop):
    url = SOURCES[2]["url"]
    while True:
        try:
            async with websockets.connect(url) as ws:
                sub_msg = {"event": "bts:subscribe", "data": {"channel": "live_trades_btcusd"}}
                await ws.send(json.dumps(sub_msg))
                print(f"[CONNECT] Connected to {SOURCES[2]['name']}")
                async for msg in ws:
                    data = json.loads(msg)
                    if 'data' in data and 'price' in data['data']:
                        price = data['data']['price']
                        fix = f"8=FIX.4.2\x0135=X\x0149=BITSTAMP\x0155=BTCUSD\x01269=0\x01270={price}\x01"
                        await send_to_cpp(conn, loop, fix)
                        await asyncio.sleep(0.1)
        except Exception:
            await asyncio.sleep(1)

def start_tcp_server():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(('0.0.0.0', 5000))
    server.listen(1)
    print("\n=======================================================")
    print(" [GATEWAY] Multi-Exchange Live Aggregator (TCP Mode)")
    print(" [GATEWAY] Listening on Port 5000...")
    print("=======================================================")
    print(" Waiting for Shaurya Engine to connect...\n")
    conn, addr = server.accept()
    print(f"\n[>>>] Shaurya Engine Connected from {addr}!\n")
    return conn

async def main():
    # 1. Start TCP Server and wait for C++
    conn = start_tcp_server()
    loop = asyncio.get_event_loop()

    # 2. Start streaming from all 3 exchanges simultaneously
    tasks = [
        asyncio.create_task(stream_binance(conn, loop)),
        asyncio.create_task(stream_coinbase(conn, loop)),
        asyncio.create_task(stream_bitstamp(conn, loop))
    ]

    try:
        await asyncio.gather(*tasks)
    except KeyboardInterrupt:
        print("\n[GATEWAY] Shutting down.")
        conn.close()

if __name__ == "__main__":
    asyncio.run(main())