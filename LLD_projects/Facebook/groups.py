class GroupFunctions:
  def add_user(self, user):
    pass
  def delete_user(self, user):
    pass
  def notify_user(self, user):
    pass

class Group(GroupFunctions):
  def __init__(self, group_id, name, description, cover_photo, total_users, is_private):
    self.__group_id = group_id
    self.__name = name
    self.__description = description
    self.__cover_photo = cover_photo
    self.__total_users = total_users
    self.__is_private = is_private
    self.__users = []

  def add_user(self, user):
    # functionality
    pass

  def delete_user(self, user):
    # functionality
    pass

  def notify_user(self, user):
    # functionality
    pass

  def update_description(self, description):
    pass

  def add_cover_photo(self, image):
    pass