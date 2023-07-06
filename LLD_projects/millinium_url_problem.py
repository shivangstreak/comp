import requests


def bestUniversityByCountry(country):
    base_url = "https://jsonmock.hackerrank.com/api/universities"
    page = 1
    max_rank = float('-inf')
    best_university = ""

    while True:
        url = f"{base_url}?page={page}"
        response = requests.get(url)
        data = response.json()

        for entry in data["data"]:
            if entry["location"]["country"] == country and int(entry["rank_display"]) > max_rank:
                max_rank = int(entry["rank_display"])
                best_university = entry["university"]

        total_pages = data["total_pages"]
        if page >= total_pages:
            break

        page += 1

    return best_university
