import threading
import time
from abc import ABC, abstractmethod
from collections import deque
from dataclasses import dataclass
from enum import Enum, auto
from typing import Callable, Optional


class AlgorithmType(Enum):
    TOKEN_BUCKET = auto()
    SLIDING_WINDOW_LOG = auto()


@dataclass(frozen=True)
class Request:
    client_id: str
    api: str
    tier: str


@dataclass(frozen=True)
class Rule:
    id: str
    algorithm: AlgorithmType
    max_requests: int
    window_seconds: float

    def __post_init__(self):
        if self.max_requests <= 0 or self.window_seconds <= 0:
            raise ValueError("Limit and window must be positive")


class Clock(ABC):
    @abstractmethod
    def now(self) -> float:
        pass


class SystemClock(Clock):
    def now(self) -> float:
        # Monotonic time isn't affected by system clock changes
        return time.monotonic()


class RateLimiter(ABC):  # Strategy
    @abstractmethod
    def allow(self, client_id: str) -> bool:
        pass


class RuleRepository(ABC):
    @abstractmethod
    def find(self, api: str, tier: str) -> Optional[Rule]:
        pass


class InMemoryRuleRepository(RuleRepository):
    def __init__(self, rules: dict[tuple[str, str], Rule]):
        self._rules = rules

    def find(self, api: str, tier: str) -> Optional[Rule]:
        return self._rules.get((api, tier))


class Bucket:
    def __init__(self, tokens: float, last_refill_time: float):
        self.tokens = tokens
        self.last_refill_time = last_refill_time
        self.lock = threading.Lock()


class TokenBucketLimiter(RateLimiter):
    def __init__(self, rule: Rule, clock: Clock):
        self._capacity = rule.max_requests
        self._refill_per_second = rule.max_requests / rule.window_seconds
        self._clock = clock
        self._buckets: dict[str, Bucket] = {}
        self._registry_lock = threading.Lock()

    def _get_bucket(self, client_id: str) -> Bucket:
        with self._registry_lock:
            if client_id not in self._buckets:
                self._buckets[client_id] = Bucket(
                    self._capacity, self._clock.now()
                )
            return self._buckets[client_id]

    def allow(self, client_id: str) -> bool:
        bucket = self._get_bucket(client_id)

        # Lock per client so that clients don't block each other
        with bucket.lock:
            now = self._clock.now()
            elapsed = max(0.0, now - bucket.last_refill_time)
            bucket.tokens = min(
                self._capacity,
                bucket.tokens + elapsed * self._refill_per_second,
            )
            bucket.last_refill_time = now

            if bucket.tokens >= 1:
                bucket.tokens -= 1
                return True
            return False


class RequestLog:
    def __init__(self):
        self.timestamps: deque[float] = deque()
        self.lock = threading.Lock()


class SlidingWindowLogLimiter(RateLimiter):
    def __init__(self, rule: Rule, clock: Clock):
        self._max_requests = rule.max_requests
        self._window_seconds = rule.window_seconds
        self._clock = clock
        self._logs: dict[str, RequestLog] = {}
        self._registry_lock = threading.Lock()

    def _get_log(self, client_id: str) -> RequestLog:
        with self._registry_lock:
            if client_id not in self._logs:
                self._logs[client_id] = RequestLog()
            return self._logs[client_id]

    def allow(self, client_id: str) -> bool:
        log = self._get_log(client_id)

        with log.lock:
            now = self._clock.now()
            window_start = now - self._window_seconds

            while log.timestamps and log.timestamps[0] <= window_start:
                log.timestamps.popleft()

            if len(log.timestamps) < self._max_requests:
                log.timestamps.append(now)
                return True
            return False


class RateLimiterFactory:
    def __init__(self, clock: Clock):
        self._clock = clock
        self._creators: dict[
            AlgorithmType, Callable[[Rule, Clock], RateLimiter]
        ] = {
            AlgorithmType.TOKEN_BUCKET: TokenBucketLimiter,
            AlgorithmType.SLIDING_WINDOW_LOG: SlidingWindowLogLimiter,
        }

    def create(self, rule: Rule) -> RateLimiter:
        creator = self._creators.get(rule.algorithm)
        if creator is None:
            raise ValueError(f"Unsupported algorithm: {rule.algorithm}")
        return creator(rule, self._clock)


class RateLimiterService:  # Facade
    def __init__(self, rules: RuleRepository, factory: RateLimiterFactory):
        self._rules = rules
        self._factory = factory
        self._limiters: dict[str, RateLimiter] = {}
        self._lock = threading.Lock()

    def _get_limiter(self, rule: Rule) -> RateLimiter:
        with self._lock:
            if rule.id not in self._limiters:
                self._limiters[rule.id] = self._factory.create(rule)
            return self._limiters[rule.id]

    def allow(self, request: Request) -> bool:
        rule = self._rules.find(request.api, request.tier)
        if rule is None:
            return True  # No rule means this API isn't rate limited

        return self._get_limiter(rule).allow(request.client_id)


if __name__ == "__main__":
    rule = Rule("search-free-v1", AlgorithmType.TOKEN_BUCKET, 3, 60)
    repository = InMemoryRuleRepository({("/search", "free"): rule})
    service = RateLimiterService(
        repository,
        RateLimiterFactory(SystemClock()),
    )

    request = Request("user-1", "/search", "free")
    print([service.allow(request) for _ in range(5)])
    # [True, True, True, False, False]