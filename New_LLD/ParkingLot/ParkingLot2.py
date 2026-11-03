import time
import uuid
from abc import ABC, abstractmethod
from enum import Enum
from typing import Dict, List, Optional, Set

MILLIS_PER_HOUR = 60 * 60 * 1000


class VehicleType(Enum):
    MOTORCYCLE = "motorcycle"
    CAR = "car"
    LARGE = "large"


class SpotType(Enum):
    MOTORCYCLE = "motorcycle"
    CAR = "car"
    LARGE = "large"


class ParkingSpot:
    def __init__(self, spot_id: str, spot_type: SpotType):
        self._id = spot_id
        self._spot_type = spot_type

    def get_id(self) -> str:
        return self._id

    def get_spot_type(self) -> SpotType:
        return self._spot_type


class Ticket:
    def __init__(
        self,
        ticket_id: str,
        spot_id: str,
        vehicle_type: VehicleType,
        entry_time: int,
    ):
        self._id = ticket_id
        self._spot_id = spot_id
        self._vehicle_type = vehicle_type
        self._entry_time = entry_time

    def get_id(self) -> str:
        return self._id

    def get_spot_id(self) -> str:
        return self._spot_id

    def get_vehicle_type(self) -> VehicleType:
        return self._vehicle_type

    def get_entry_time(self) -> int:
        return self._entry_time


def billable_hours(entry_time: int, exit_time: int) -> int:
    """Return the parked duration, rounded up to the next full hour."""
    duration_millis = exit_time - entry_time
    return -(-duration_millis // MILLIS_PER_HOUR)


class FeeStrategy(ABC):
    @abstractmethod
    def compute_fee(self, ticket: Ticket, exit_time: int) -> int:
        """Return the fee in cents."""


class HourlyFeeStrategy(FeeStrategy):
    def __init__(self, hourly_rate_cents: int):
        self._hourly_rate_cents = hourly_rate_cents

    def compute_fee(self, ticket: Ticket, exit_time: int) -> int:
        hours = billable_hours(ticket.get_entry_time(), exit_time)
        return hours * self._hourly_rate_cents


class VehicleTypeFeeStrategy(FeeStrategy):
    def __init__(self, rates_cents: Dict[VehicleType, int]):
        self._rates_cents = rates_cents

    def compute_fee(self, ticket: Ticket, exit_time: int) -> int:
        hours = billable_hours(ticket.get_entry_time(), exit_time)
        return hours * self._rates_cents[ticket.get_vehicle_type()]


class FlatFeeStrategy(FeeStrategy):
    def __init__(self, flat_fee_cents: int):
        self._flat_fee_cents = flat_fee_cents

    def compute_fee(self, ticket: Ticket, exit_time: int) -> int:
        return self._flat_fee_cents


class ParkingLot:
    def __init__(self, spots: List[ParkingSpot], fee_strategy: FeeStrategy):
        self._spots = spots
        self._active_tickets: Dict[str, Ticket] = {}
        self._occupied_spot_ids: Set[str] = set()
        self._fee_strategy = fee_strategy

    def enter(self, vehicle_type: VehicleType) -> Ticket:
        spot = self._find_available_spot(vehicle_type)
        if spot is None:
            raise Exception(f"No available spots for vehicle type {vehicle_type}")

        self._occupied_spot_ids.add(spot.get_id())

        ticket_id = str(uuid.uuid4())
        entry_time = int(time.time() * 1000)
        ticket = Ticket(ticket_id, spot.get_id(), vehicle_type, entry_time)

        self._active_tickets[ticket_id] = ticket

        return ticket

    def exit(self, ticket_id: str) -> int:
        if ticket_id is None or ticket_id == "":
            raise Exception("Invalid ticket ID")

        ticket = self._active_tickets.get(ticket_id)
        if ticket is None:
            raise Exception("Ticket not found or already used")

        exit_time = int(time.time() * 1000)
        fee = self._fee_strategy.compute_fee(ticket, exit_time)

        self._occupied_spot_ids.discard(ticket.get_spot_id())
        del self._active_tickets[ticket_id]

        return fee

    def _find_available_spot(self, vehicle_type: VehicleType) -> Optional[ParkingSpot]:
        required_spot_type = self._map_vehicle_type_to_spot_type(vehicle_type)

        for spot in self._spots:
            if (
                spot.get_id() not in self._occupied_spot_ids
                and spot.get_spot_type() == required_spot_type
            ):
                return spot

        return None

    def _map_vehicle_type_to_spot_type(self, vehicle_type: VehicleType) -> SpotType:
        if vehicle_type == VehicleType.MOTORCYCLE:
            return SpotType.MOTORCYCLE
        if vehicle_type == VehicleType.CAR:
            return SpotType.CAR
        if vehicle_type == VehicleType.LARGE:
            return SpotType.LARGE
        raise Exception("Unknown vehicle type")