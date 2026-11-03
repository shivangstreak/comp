import threading
import time
from abc import ABC, abstractmethod
from collections import defaultdict, deque
from dataclasses import dataclass


@dataclass(frozen=True)
class Rule:
    algorithm: str
    limit: int
    window_seconds: float


class RateLimiter(ABC):  # Strategy
    @abstractmethod
    def allow(self, client_id: str) -> bool:
        pass


class TokenBucketLimiter(RateLimiter):
    def __init__(self, rule: Rule):
        self.capacity = rule.limit
        self.refill_rate = rule.limit / rule.window_seconds
        self.buckets = {}  # client_id -> (tokens, last_refill_time)
        self.lock = threading.Lock()

    def allow(self, client_id: str) -> bool:
        with self.lock:
            now = time.monotonic()
            tokens, last_refill_time = self.buckets.get(
                client_id, (self.capacity, now)
            )

            elapsed = now - last_refill_time
            tokens = min(self.capacity, tokens + elapsed * self.refill_rate)

            allowed = tokens >= 1
            if allowed:
                tokens -= 1

            self.buckets[client_id] = (tokens, now)
            return allowed


class SlidingWindowLogLimiter(RateLimiter):
    def __init__(self, rule: Rule):
        self.limit = rule.limit
        self.window_seconds = rule.window_seconds
        self.logs = defaultdict(deque)  # client_id -> request timestamps
        self.lock = threading.Lock()

    def allow(self, client_id: str) -> bool:
        with self.lock:
            now = time.monotonic()
            log = self.logs[client_id]

            while log and log[0] <= now - self.window_seconds:
                log.popleft()

            if len(log) < self.limit:
                log.append(now)
                return True
            return False


class RateLimiterFactory:
    @staticmethod
    def create(rule: Rule) -> RateLimiter:
        if rule.algorithm == "token_bucket":
            return TokenBucketLimiter(rule)
        if rule.algorithm == "sliding_window_log":
            return SlidingWindowLogLimiter(rule)
        raise ValueError(f"Unknown algorithm: {rule.algorithm}")


class RateLimiterService:
    def __init__(self, rules: dict[str, Rule]):
        # One limiter is created for each API at startup
        self.limiters = {
            api: RateLimiterFactory.create(rule)
            for api, rule in rules.items()
        }

    def allow(self, client_id: str, api: str) -> bool:
        limiter = self.limiters.get(api)
        if limiter is None:
            return True  # This API has no rate limit
        return limiter.allow(client_id)


if __name__ == "__main__":
    rules = {
        "/search": Rule("token_bucket", limit=3, window_seconds=60),
        "/login": Rule("sliding_window_log", limit=5, window_seconds=60),
    }

    service = RateLimiterService(rules)

    print([service.allow("user-1", "/search") for _ in range(5)])
    # [True, True, True, False, False]