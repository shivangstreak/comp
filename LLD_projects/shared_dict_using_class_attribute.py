class MyClass:
    shared_dict = {}  # Class attribute

    def __init__(self, key, value):
        self.key = key
        self.value = value
        MyClass.shared_dict[key] = value

# Creating objects and adding elements to the shared dictionary
obj1 = MyClass("key1", "value1")
obj2 = MyClass("key2", "value2")

# Accessing the shared dictionary from any object
print(obj1.shared_dict)  # Output: {'key1': 'value1', 'key2': 'value2'}
print(obj2.shared_dict)  # Output: {'key1': 'value1', 'key2': 'value2'}
