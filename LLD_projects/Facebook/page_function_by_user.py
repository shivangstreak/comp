from abc import ABC, abstractmethod

class PageFunctionsByUser(ABC):
  def create_page(self, name):
    pass
  def share_page(self, page):
    pass
  def like_page(self, page):
    pass
  def follow_page(self, page):
    pass
  def unLike_page(self, page):
    pass
  def unFollow_page(self, page):
    pass

class GroupFunctions(ABC):
  def add_user(self, user):
    pass
  def delete_user(self, user):
    pass
  def notify_user(self, user):
    pass

  def create_group(self, name):
    pass
  def join_group(self, group):
    pass
  def leave_group(self, group):
    pass
  def send_group_invite(self, group):
    pass

class PostFunctionsByUser(ABC):
  def create_post(self, content):
    pass
  def share_post(self, post):
    pass
  def comment_on_post(self, post):
    pass
  def like_post(self, post):
    pass

class CommentFunctionsByUser(ABC):
  def create_comment(self, post, content):
    pass
  def like_comment(self, comment):
    pass