class Message:
    def __init__(self, message_id, sender, content, recipient, multimedia):
        self.__message_id = message_id
        self.__sender = sender
        self.__content = content
        self.__recipent = []
        self.__multimedia = []

    # user here refers to a list of users
    def add_recipent(self, user):
        pass


class FriendRequest:
    def __init__(self, recipent, sender, status, request_sent, request_status_modified):
        self.__recipient = recipent
        self.__sender = sender
        self.__status = status
        self.__request_sent = request_sent
        self.__request_status_modified = request_status_modified

    def accept_request(self, user):
        pass

    def reject_request(self, user):
        pass