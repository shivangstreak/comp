from abc import ABC, abstractmethod

# Define Strategy
class AllocationStrategy(ABC):
    @abstractmethod
    # It returns in which batch student got allocated in
    def allocate(self, student, batches):
        pass

class GenderBased(AllocationStrategy):
    def allocate(self, student, batches):
        if student.gender == 'Female':
            for timing in ['Morning', 'Noon', 'Evening']:
                for batch in batches:
                    if batch.timing == timing and batch.can_allocate(student):
                        return batch
        return None


class HighCapapcity(AllocationStrategy):
    def allocate(self, student, batches):
        for batch in sorted(batches, key=lambda x: -x.capacity):
            if batch.can_allocate(student):
                return batch
        return None