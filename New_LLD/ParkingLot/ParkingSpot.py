from enum import Enum

class SpotType(Enum):
    MOTORCYCLE = 1
    CAR = 2
    LARGE = 3

class ParkingSpot:
    def __init__(self, id: str, spot_type: SpotType):
        self._id = id
        self._spot_type = spot_type

    def get_spot_type(self) -> SpotType:
        return self._spot_type

    def get_id(self) -> str:
        return self._id
