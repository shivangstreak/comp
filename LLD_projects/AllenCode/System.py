from Batch import Batch
from AllocationStrategy import AllocationStrategy
from User import User

class System:
    def __init__(self):
        self.users = []
        self.batches = []

    # create a user and add users in the system
    def register(self, name, gender, user_type):
        user = User(name=name, gender=gender, user_type=user_type)
        self.users.append(user)
        return user

    # create a batch and add to system
    def create_batch(self, admin_id, capacity, batch_stream, timing):
        admin = next((user for user in self.users if user.id == admin_id and user.user_type == 'Admin'), None)
        if admin:
            batch = Batch(admin = admin, capacity=capacity, batch_stream=batch_stream, timing=timing)
            self.batches.append(batch)
            return batch
        return None

    # Following solid principle 'L' here
    def allocate_batch(self, admin_id, student_id, strategy: AllocationStrategy):
        admin = next((user for user in self.users if user.id == admin_id and user.user_type == 'Admin'), None)
        # no admin found can not allocate to batch
        if not admin:
            return None
        student = next((user for user in self.users if user.id == student_id and user.user_type == 'Student'), None)
        if not student or not student.stream:
            return None
        return strategy.allocate(student, self.batches)

    def enroll(self, user_id, stream):
        user = next((user for user in self.users if user.id == user_id and user.user_type == 'Student'), None)
        if user:
            user.stream = stream
            return True
        return False

