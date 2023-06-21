from abc import ABC, abstractmethod

class Search(ABC):
  def search_users(self, name):
    pass
  def search_groups(self, name):
    pass
  def search_pages(self, name):
    pass
  def search_posts(self, keywords):
    pass

class SearchCatalog(Search):
  def __init__(self):
    self.__user_names = {}
    self.__group_names = {}
    self.__page_titles = {}
    self.__posts = {}

  def add_new_user(self, user):
    pass
  def add_new_group(self, group):
    pass
  def add_new_page(self, page):
    pass
  def add_new_post(self, post):
    pass

  def search_users(self, name):
    # functionality
    pass
  def search_groups(self, name):
    # functionality
    pass
  def search_pages(self, name):
    # functionality
    pass
  def search_posts(self, keywords):
    # functionality
    pass