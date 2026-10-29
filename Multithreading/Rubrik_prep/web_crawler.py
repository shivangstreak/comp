from threading import Thread, Lock
from collections import deque

class Solution:
    def crawl(self, startUrl: str, htmlParser: 'HtmlParser') -> List[str]:
        def hostname(url):
            return url.split('/')[2]

        domain = hostname(startUrl)
        q = deque([startUrl])
        seen = {startUrl}
        lock = Lock()

        def parser(curr):
            urls = htmlParser.getUrls(curr)        # slow call: OUTSIDE the lock
            for u in urls:
                if hostname(u) != domain:
                    continue
                lock.acquire()
                try:
                    if u in seen:                  # check + add together
                        continue
                    seen.add(u)
                    q.append(u)
                finally:
                    lock.release()

        while q:
            workers = []
            for _ in range(len(q)):
                t = Thread(target=parser, args=(q.popleft(),))
                t.start()
                workers.append(t)
            for t in workers:
                t.join()

        return list(seen)