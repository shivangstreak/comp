from abc import ABCMeta,abstractmethod


class IPerson(metaclass=ABCMeta):

    @abstractmethod
    def person_method(self):
        """ Interface Method """


class Student(IPerson):
    def __init__(self):
        self.name = "Student name"

    def person_method(self):
        print("I am a Student")


class Teacher(IPerson):
    def __init__(self):
        self.name = "Teacher name"

    def person_method(self):
        print("I am a Teacher")


class PersonFactory:
    @staticmethod
    def build_person(person_type):
        if person_type == "Student":
            return Student()
        if person_type == "Teacher":
            return Teacher()
        print("Invalid Type")
        return -1

if __name__ == "__main__":
    # Type Student or Teacher in inputs
    type = input("What type of person do you want to create ? \n")
    person = PersonFactory.build_person(type)
    person.person_method()


#Please watch https://www.youtube.com/watch?v=s_4ZrtQs8Do for more understanding of factory pattern

