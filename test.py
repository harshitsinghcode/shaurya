import shaurya_hft
import time
import sys

MULTICAST_IP = "239.0.0.1"
MULTICAST_PORT = 30001
TEST_DURATION = 120 

def run_dashboard():
    print("==================================================")
    print("   SHAURYA HFT ENGINE - REAL-TIME MONITOR         ")
    print("==================================================")
    
    print(f"[PYTHON] Initializing Shaurya Engine...")
    engine = shaurya_hft.Engine()

    print(f"[PYTHON] Connecting to Multicast Feed {MULTICAST_IP}:{MULTICAST_PORT}...")
    engine.start(MULTICAST_IP, MULTICAST_PORT)
    
    print(f"[PYTHON] Engine Running. Monitoring for {TEST_DURATION} seconds...")
    print("-" * 50)

    min_seen = float('inf')
    max_seen = 0.0
    packets_detected = False

    try:
        for i in range(TEST_DURATION):
            time.sleep(1)
            
            latency = engine.get_latency()

            if latency > 0:
                packets_detected = True
                min_seen = min(min_seen, latency)
                max_seen = max(max_seen, latency)
                status_msg = f"| BEST: {min_seen} us"
            else:
                status_msg = "| (WAITING FOR DATA...)"

            print(f"[TIME {i:03}s] Current Latency: {latency:6.2f} us {status_msg}")

    except KeyboardInterrupt:
        print("\n[PYTHON] Monitoring Interrupted by User.")

    finally:
        print("-" * 50)
        print("[PYTHON] Stopping C++ Engine...")
        engine.stop()
        
        if packets_detected:
            print(f"\n=== SESSION SUMMARY ===")
            print(f"MIN Latency: {min_seen} us")
            print(f"MAX Latency: {max_seen} us")
        else:
            print("\n[WARNING] No data packets were detected. Did you run the Bridge?")
            
        print("==================================================")

if __name__ == "__main__":
    run_dashboard()