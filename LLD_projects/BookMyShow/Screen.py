
#
# Screen has seats
#
class Screen:
    def __init__(self):
        self.screenId = 0
        self.seats = []

    def getScreenId(self):
        return self.screenId

    def setScreenId(self, screenId):
        self.screenId = screenId

    def getSeats(self):
        return self.seats

    def setSeats(self, seats):
        self.seats = seats
