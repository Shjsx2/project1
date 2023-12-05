import asyncio
import websockets

async def receive(websocket):
    while True:
        msg = await websocket.recv()
        print(f"<<< {msg}")

async def main():
    async with websockets.serve(receive, "localhost", 8080):
        await asyncio.Future()  # run forever

if __name__ == "__main__":
    asyncio.run(main())