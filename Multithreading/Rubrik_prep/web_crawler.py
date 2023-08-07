# """
# This is HtmlParser's API interface.
# You should not implement it, or speculate about its implementation
# """
#class HtmlParser(object):
#    def getUrls(self, url):
#        """
#        :type url: str
#        :rtype List[str]
#        """
# https://leetcode.com/problems/web-crawler-multithreaded/
from threading import Thread
class Solution:
    def crawl(self, startUrl: str, htmlParser: 'HtmlParser') -> List[str]:
        # Using BFS
        q = [startUrl]
        seen = set()
        seen.add(startUrl)

        def hostname(url):
            return url.split('/')[2]
        domain = hostname(startUrl)

        def parser(curr):
            for u in htmlParser.getUrls(curr):
                if u not in seen and hostname(u) == domain:
                    q.append(u)
                    seen.add(u)

        while q:
            workers = []
            for _ in range(len(q)):
                top = q.pop(0)
                thread = Thread(target=parser, args = (top, ))
                thread.start()
                workers.append(thread)
            for t in workers:
                t.join()

        return list(seen)