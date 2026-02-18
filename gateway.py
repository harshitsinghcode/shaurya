import asyncio
import websockets
import json
import socket


async def binance_1s_stream(conn, loop):
    url = "wss://stream.binance.com:9443/ws/btcusdt@miniTicker"
    print("[BINANCE] Linked to Live 1-Second Ticker...")
    
    tick_count = 0

    while True:
        try:
            async with websockets.connect(url) as ws:
                print("[BINANCE] Stream Active! Routing 1-Tick/Sec to C++ Engine...\n")
                async for msg in ws:
                    data = json.loads(msg)
                    
                    if 'c' in data:
                        tick_count += 1
                        price = float(data['c'])

                        if tick_count % 15 == 0:
                            print(f"\n[GATEWAY] INJECTING FAT FINGER ANOMALY ($250,000) TO TEST FPGA...\n")
                            price = 250000.00
                        
                        fix = f"8=FIX.4.2\x0135=X\x0149=BINANCE\x0155=BTCUSDT\x01269=0\x01270={price:.2f}\x01"
                        
                        await loop.sock_sendall(conn, fix.encode())
                        
        except Exception as e:
            print(f"[BINANCE] Connection reset. Reconnecting... ({e})")
            await asyncio.sleep(1)

def start_tcp_server():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(('0.0.0.0', 5000))
    server.listen(1)
    
    print("\n=======================================================")
    print(" [GATEWAY] Live Binance API (1-Tick/Sec Demo Mode)")
    print(" [GATEWAY] Listening on Port 5000...")
    print("=======================================================")
    print(" Waiting for Shaurya Engine to connect...\n")
    
    conn, addr = server.accept()
    print(f"\n[>>>] Shaurya Engine Connected from {addr}!")
    return conn

async def main():
    loop = asyncio.get_event_loop()
    conn = start_tcp_server()
    try:
        await binance_1s_stream(conn, loop)
    except KeyboardInterrupt:
        print("\n[GATEWAY] Shutting down.")
        conn.close()

if __name__ == "__main__":
    asyncio.run(main())