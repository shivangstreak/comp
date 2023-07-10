import asyncio

async def fetch_data(url):
    print(f"Fetching data from {url}")
    await asyncio.sleep(1)  # Simulating network delay
    print(f"Data fetched from {url}")

async def main():
    # Create a list of tasks
    tasks = [
        asyncio.create_task(fetch_data("https://api.example.com/data1")),
        asyncio.create_task(fetch_data("https://api.example.com/data2")),
        asyncio.create_task(fetch_data("https://api.example.com/data3")),
    ]

    # Wait for all tasks to complete
    await asyncio.gather(*tasks)

asyncio.run(main())
