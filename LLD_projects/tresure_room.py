def filter_rooms(treasure_rooms, instructions):
    # Store the instructions in a dict for efficient lookup
    instruct_dict = {i[0]: i[1] for i in instructions}

    # Count the number of pointers to each room
    pointer_count = {}
    for _, destination in instructions:
        pointer_count[destination] = pointer_count.get(destination, 0) + 1

    # Filter rooms by the given conditions
    result = []
    for room, destination in instruct_dict.items():
        if destination in treasure_rooms and pointer_count.get(room, 0) >= 2:
            result.append(room)

    return result


instructions_1 = [
    ["jasmin", "tulip"],
    ["lily", "tulip"],
    ["tulip", "tulip"],
    ["rose", "rose"],
    ["violet", "rose"],
    ["sunflower", "violet"],
    ["daisy", "violet"],
    ["iris", "violet"]
]

instructions_2 = [
    ["jasmin", "tulip"],
    ["lily", "tulip"],
    ["tulip", "violet"],
    ["violet", "violet"]
]

treasure_rooms_1 = ["lily", "tulip", "violet", "rose"]
treasure_rooms_2 = ["lily", "jasmin", "violet"]
treasure_rooms_3 = ["violet"]

print(filter_rooms(treasure_rooms_1, instructions_1))    # => ["tulip", "violet"]
print(filter_rooms(treasure_rooms_2, instructions_1))    # => []
print(filter_rooms(treasure_rooms_3, instructions_2))    # => [tulip]
