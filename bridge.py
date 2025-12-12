import asyncio
import websockets
import json
import socket
import time

TCP_HOST = "127.0.0.1"
TCP_PORT = 5000
RUN_DURATION = 1800  # 30 Minutes

SOURCES = [
    {"name": "BINANCE",  "url": "wss://stream.binance.com:9443/ws/btcusdt@trade"},
    {"name": "COINBASE", "url": "wss://ws-feed.exchange.coinbase.com"},
    {"name": "BITSTAMP", "url": "wss://ws.bitstamp.net"}
]

async def forward_to_engine(writer, fix_msg):
    try:
        writer.write(fix_msg.encode())
        await writer.drain()
    except Exception as e:
        print(f"[TCP ERROR] {e}")

async def stream_binance(writer):
    url = SOURCES[0]["url"]
    async for websocket in websockets.connect(url):
        try:
            print(f"[CONNECT] Connected to {SOURCES[0]['name']}")
            while True:
                msg = await websocket.recv()
                data = json.loads(msg)
                price = data['p']
                fix = f"8=FIX.4.2\x0135=X\x0149=BINANCE\x0155=BTCUSDT\x01269=0\x01270={price}\x01"
                await forward_to_engine(writer, fix)
        except Exception:
            continue

async def stream_coinbase(writer):
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
                    await forward_to_engine(writer, fix)
        except Exception:
            continue

async def stream_bitstamp(writer):
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
                    await forward_to_engine(writer, fix)
        except Exception:
            continue

async def main():
    server = await asyncio.start_server(handle_client, TCP_HOST, TCP_PORT)
    addr = server.sockets[0].getsockname()
    print(f"[GATEWAY] Multi-Source Bridge listening on {addr}")
    print(f"[GATEWAY] Test Duration: {RUN_DURATION / 60} Minutes")

    async with server:
        await server.serve_forever()

async def handle_client(reader, writer):
    print("[GATEWAY] Shaurya Engine Connected! Starting Streams...")
    
    tasks = [
        asyncio.create_task(stream_binance(writer)),
        asyncio.create_task(stream_coinbase(writer)),
        asyncio.create_task(stream_bitstamp(writer))
    ]

    await asyncio.sleep(RUN_DURATION)
    
    print("\n[GATEWAY] 30 Minutes Complete. Stopping Test...")
    writer.close()
    await writer.wait_closed()
    
    for task in tasks:
        task.cancel()

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass