from enum import Enum

class VehicleType(Enum):
    MOTORCYCLE = 1
    CAR = 2
    LARGE = 3

class Ticket:
    def __init__(self, id: str, spot_id: str, vehicle_type: VehicleType, entry_time: int):
        self._id = id
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
