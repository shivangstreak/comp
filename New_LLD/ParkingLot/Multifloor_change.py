class ParkingLot:
    - floors: List < ParkingFloor >
    - activeTickets: Map < String, Ticket >
    - hourlyRateCents


class ParkingFloor:
    - floorNumber
    - spots: List < ParkingSpot >

    + getAvailableSpotCount(spotType) -> int
    + findAvailableSpot(spotType) -> ParkingSpot


findAvailableSpot(vehicleType)
requiredType = mapVehicleTypeToSpotType(vehicleType)

for floor in floors
    spot = floor.findAvailableSpot(requiredType)
    if spot != null
        return spot
return null



#
# But with 10 floors, you might want smarter allocation. You could even use a Strategy pattern to implement different allocation strategies based on occupancy or time of day.
# 1. Fill lower floors first — Keeps customers closer to the entrance/exit. This is what the simple iteration does.
# 2. Balance across floors — Spread vehicles evenly so no single floor gets congested. Track spot counts per floor and prefer floors with more availability.
# 3. Proximity to destination — In a mall garage, different floors might be closer to different stores. If someone says "I'm going to the food court," assign them to floor 4 which connects directly.


findAvailableSpot(vehicleType)
requiredType = mapVehicleTypeToSpotType(vehicleType)

// Find
floor
with most available spots of this type
bestFloor = null
maxAvailable = 0

for floor in floors
    available = floor.getAvailableSpotCount(requiredType)
    if available > maxAvailable
        maxAvailable = available
        bestFloor = floor

if bestFloor == null
    return null
return bestFloor.findAvailableSpot(requiredType)


class AllocationStrategy(ABC):
    @abstractmethod
    def find_spot(self, floors: List[ParkingFloor], spot_type: SpotType) -> Optional[ParkingSpot]:
        pass


class FirstAvailableStrategy(AllocationStrategy):
    def find_spot(self, floors, spot_type):
        for floor in floors:
            spot = floor.find_available_spot(spot_type)
            if spot is not None:
                return spot
        return None


class MostAvailableStrategy(AllocationStrategy):
    def find_spot(self, floors, spot_type):
        best_floor = max(
            floors,
            key=lambda floor: floor.get_available_spot_count(spot_type),
            default=None,
        )
        if best_floor is None:
            return None
        return best_floor.find_available_spot(spot_type)


lot = ParkingLot(floors, HourlyFeeStrategy(500), MostAvailableStrategy())

def _find_available_spot(self, vehicle_type):
    required_type = self._map_vehicle_type_to_spot_type(vehicle_type)
    return self._allocation_strategy.find_spot(self._floors, required_type)