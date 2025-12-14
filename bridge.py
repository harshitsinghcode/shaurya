import asyncio
import websockets
import json
import socket

MULTICAST_GROUP = "239.0.0.1"
MULTICAST_PORT = 30001
RUN_DURATION = 120 

SOURCES = [
    {"name": "BINANCE",  "url": "wss://stream.binance.com:9443/ws/btcusdt@trade"},
    {"name": "COINBASE", "url": "wss://ws-feed.exchange.coinbase.com"},
    {"name": "BITSTAMP", "url": "wss://ws.bitstamp.net"}
]

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 2)

def send_multicast(fix_msg):
    try:
        sock.sendto(fix_msg.encode(), (MULTICAST_GROUP, MULTICAST_PORT))
    except Exception as e:
        print(f"[ERROR] UDP Send Failed: {e}")

async def stream_binance():
    url = SOURCES[0]["url"]
    async for websocket in websockets.connect(url):
        try:
            print(f"[CONNECT] Connected to {SOURCES[0]['name']}")
            while True:
                msg = await websocket.recv()
                data = json.loads(msg)
                price = data['p']
                fix = f"8=FIX.4.2\x0135=X\x0149=BINANCE\x0155=BTCUSDT\x01269=0\x01270={price}\x01"
                send_multicast(fix)
        except Exception:
            await asyncio.sleep(1)
            continue

async def stream_coinbase():
    url = SOURCES[1]["url"]
    async for websocket in websockets.connect(url):
        try:
            await websocket.send(json.dumps({
                "type": "subscribe",
                "product_ids": ["BTC-USD"],
                "channels": ["ticker"]
            }))
            print(f"[CONNECT] Connected to {SOURCES[1]['name']}")
            while True:
                msg = await websocket.recv()
                data = json.loads(msg)
                if 'price' in data:
                    price = data['price']
                    fix = f"8=FIX.4.2\x0135=X\x0149=COINBASE\x0155=BTCUSD\x01269=0\x01270={price}\x01"
                    send_multicast(fix)
        except Exception:
            await asyncio.sleep(1)
            continue

async def stream_bitstamp():
    url = SOURCES[2]["url"]
    async for websocket in websockets.connect(url):
        try:
            sub_msg = {
                "event": "bts:subscribe",
                "data": {"channel": "live_trades_btcusd"}
            }
            await websocket.send(json.dumps(sub_msg))
            print(f"[CONNECT] Connected to {SOURCES[2]['name']}")
            while True:
                msg = await websocket.recv()
                data = json.loads(msg)
                if 'data' in data and 'price' in data['data']:
                    price = data['data']['price']
                    fix = f"8=FIX.4.2\x0135=X\x0149=BITSTAMP\x0155=BTCUSD\x01269=0\x01270={price}\x01"
                    send_multicast(fix)
        except Exception:
            await asyncio.sleep(1)
            continue

async def main():
    print(f"[GATEWAY] Starting Multi-Exchange UDP Broadcast to {MULTICAST_GROUP}:{MULTICAST_PORT}")
    print(f"[GATEWAY] Aggregating Liquidity from Binance, Coinbase, Bitstamp...")

    tasks = [
        asyncio.create_task(stream_binance()),
        asyncio.create_task(stream_coinbase()),
        asyncio.create_task(stream_bitstamp())
    ]

    await asyncio.sleep(RUN_DURATION)
    
    print("\n[GATEWAY] Test Duration Complete. Stopping...")
    for task in tasks:
        task.cancel()

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("Gateway Stopped.")