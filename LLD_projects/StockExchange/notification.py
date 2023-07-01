from abc import ABC, abstractmethod

class Notification(ABC):
  def __init__(self, notification_id, creation_date, content):
    self.__notification_id = notification_id
    self.__creation_date = creation_date
    self.__content = content

  @abstractmethod
  def send_notification(self):
    None

class SmsNotification(Notification):
  def __init__(self, notification_id, creation_date, content, phone_number):
    super().__init__(notification_id, creation_date, content)
    self.__phone_number = phone_number

  def send_notification(self):
    # functionality
    pass

class EmailNotification(Notification):
  def __init__(self, notification_id, creation_date, content, email):
    super().__init__(notification_id, creation_date, content)
    self.__email = email

  def send_notification(self):
    # functionality