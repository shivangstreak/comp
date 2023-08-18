from System import System
from AllocationStrategy import GenderBased, HighCapapcity
if __name__ == "__main__":
    # Initialize system object
    system = System()

    # initialize Students
    s1 = system.register("Akhilesh", "Male", "Student") #Student1
    s2 = system.register("Komal", "Female", "Student") #Student2
    s3 = system.register("Rajnish", "Female", "Student")  #Student3
    s4 = system.register("Mayuri", "Female", "Student") #Student4
    print(s1, s2, s3, s4)

    # Enrol students to particular subjects
    system.enroll(s1.id, "IIT")
    system.enroll(s2.id, "IIT")
    system.enroll(s3.id, "NEET")
    system.enroll(s4.id, "IIT")

    # initialize Admins
    a1 = system.register("Kamesh", "Male", "Admin") # Admin 1
    a2 = system.register("M", "Male", "Admin") # Admin 2

    b1 = system.create_batch(a1.id, capacity=3, batch_stream="IIT", timing = "Morning")
    b2 = system.create_batch(a1.id, capacity=2, batch_stream="NEET", timing="Evening")
    b3 = system.create_batch(a1.id, capacity=3, batch_stream="IIT", timing="Evening")

    print("Following batches were made")

    print(b1, b2, b3)

    # Define all types of strategy taken

    gender_based_strategy_object = GenderBased()
    higher_capacity_based_strategy_object = HighCapapcity()

    print(system.allocate_batch(a2.id, s2.id, gender_based_strategy_object))

    print(system.allocate_batch(a2.id, s4.id, higher_capacity_based_strategy_object))
    print(system.allocate_batch(a2.id, s1.id, higher_capacity_based_strategy_object))
    print(system.allocate_batch(a2.id, s3.id, higher_capacity_based_strategy_object))
