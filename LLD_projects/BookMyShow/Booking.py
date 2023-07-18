#
# Booking has Seats , Show and payment
#
class Booking:
    def __init__(self):
        self.show = None
        self.bookedSeats = []
        self.payment = None

    def getShow(self):
        return self.show

    def setShow(self, show):
        self.show = show

    def getBookedSeats(self):
        return self.bookedSeats

    def setBookedSeats(self, bookedSeats):
        self.bookedSeats = bookedSeats

    def getPayment(self):
        return self.payment

    def setPayment(self, payment):
        self.payment = payment
