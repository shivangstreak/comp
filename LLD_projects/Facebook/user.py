from abc import ABC, abstractmethod
from page_function_by_user import PageFunctionsByUser

class Admin:
    def block_user(self, user):
        pass

    def unblock_user(self, user):
        pass

    def enable_page(self, page):
        pass

    def disable_page(self, page):
        pass

    def delete_group(self, group):
        pass

    def change_group_privacy(self, group):
        pass


class Person(ABC):
    def __init__(self, name, address, email, phone, account):
        self.__name = name
        self.__address = address
        self.__email = email
        self.__phone = phone
        self.__account = account


# Will be using only one interface example
class User(Person, PageFunctionsByUser):
    def __init__(self, name, address, email, phone, account, user_id, date_of_joining, is_admin, profile):
        self.__name = name
        self.__user_id = user_id;
        self.__date_of_joining = date_of_joining
        self.__profile = profile
        # The following lists contain the pages and groups that a user is admin of
        self.__pages_admin = []
        self.__groups_admin = []
        super().__init__(name, address, email, phone, account)

    def send_message(self, message):
        pass

    def send_recommendation(self, page, group, user):
        pass

    def send_friend_request(self, user):
        pass

    def unfriend_user(self, user):
        pass

    def block_user(self, user):
        pass

    def follow_user(self, user):
        pass

    # The functions of the different interfaces will be present here
    def create_page(self, name):
        # functionality
        pass

    def like_page(self, page):
        # functionality
        pass

    def follow_page(self, page):
        # functionality
        pass

    def unLike_page(self, page):
        # functionality
        pass

    def unFollow_page(self, page):
        # functionality
        pass

    def share_page(self, page):
        # functionality
        pass