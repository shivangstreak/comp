class Profile:
  def __init__(self, gender, profile_picture, cover_photo):
    self.__gender = gender
    self.__profile_picture = profile_picture
    self.__cover_photo = cover_photo
    self.__friends = []
    self.__users_followed = [];
    self.__pages_followed = [];
    self.__groups_joined = [];
    self.__work_experience = [];
    self.__education_info = [];
    self.__places = [];

  def add_work_experience(self, work):
    pass
  def add_education(self, education):
    pass
  def add_place(self, place):
    pass
  def add_profile_picture(self, image):
    pass
  def add_cover_photo(self, image):
    pass
  def add_gender(self, gender):
    pass

class Work:
  def __init__(self, title, company, location, description, start_date, end_date):
    self.__title = title
    self.__company = company
    self.__location = location
    self.__description = description
    self.__start_date = start_date
    self.__end_date = end_date

class Places:
  def __init__(self, name):
    self.__name = name

class Education:
  def __init__(self, school, degree, description, start_date, end_date):
    self.__school = school
    self.__degree = degree
    self.__description = description
    self.__start_date = start_date
    self.__end_date = end_date