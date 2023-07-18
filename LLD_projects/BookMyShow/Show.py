from Movie import Movie
from Screen import Screen

#
# Show has Movie
# Show has Screen
# Show contains seat
#

class Show:
    def __init__(self):
        self.showId = 0
        self.movie = None
        self.screen = None
        self.showStartTime = 0
        self.bookedSeatIds = []

    def getShowId(self):
        return self.showId

    def setShowId(self, showId):
        self.showId = showId

    def getMovie(self):
        return self.movie

    def setMovie(self, movie):
        self.movie = movie

    def getScreen(self):
        return self.screen

    def setScreen(self, screen):
        self.screen = screen

    def getShowStartTime(self):
        return self.showStartTime

    def setShowStartTime(self, showStartTime):
        self.showStartTime = showStartTime

    def getBookedSeatIds(self):
        return self.bookedSeatIds

    def setBookedSeatIds(self, bookedSeatIds):
        self.bookedSeatIds = bookedSeatIds
