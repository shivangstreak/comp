class User:
    next_id = 1

    # user_type can be of two types
    # 'Admin' or 'Student'
    def __init__(self, name, gender, user_type):
        self.id = f'{user_type}{User.next_id}'
        User.next_id+=1
        self.name = name
        self.gender = gender
        self.user_type = user_type
        self.stream = None

    def __str__(self):
        return self.id