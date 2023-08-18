# Batch class has Students

class Batch:
    next_id = 1

    def __init__(self, admin, capacity, batch_stream, timing):
        self.id = f'B{Batch.next_id}'
        Batch.next_id +=1
        self.admin = admin
        self.capacity = capacity
        self.batch_stream = batch_stream
        self.timing = timing
        # Bascially list of student object in this batch
        self.students = []

    def __str__(self):
        return self.id

    # This function will be responsible for student addition in this batch
    def allocate(self, student):
        if self.can_allocate(student):
            self.students.append(student)
            return True
        return False

    # Check if this student can be allocated in this batch
    def can_allocate(self, student):
        if self.batch_stream == student.stream and len(self.students) < self.capacity:
            return True
        return False
