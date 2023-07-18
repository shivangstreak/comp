from constants import City, SeatCategory
from MovieController import MovieController
from TheatreController import TheatreController
from Booking import Booking
from Theatre import Theatre
from Screen import Screen
from Movie import Movie
from Seat import Seat
from Show import Show

class BookMyShow:
    def __init__(self):
        self.movieController = MovieController()
        self.theatreController = TheatreController()

    def createBooking(self, userCity, movieName):
        movies = self.movieController.getMoviesByCity(userCity)
        interestedMovie = None

        for movie in movies:
            if movie.getMovieName() == movieName:
                interestedMovie = movie
                break

        showsTheatreWise = self.theatreController.getAllShow(interestedMovie, userCity)
        entry = next(iter(showsTheatreWise.items()), None)

        if entry is not None:
            theatre, runningShows = entry
            interestedShow = runningShows[0]
            seatNumber = 30
            bookedSeats = interestedShow.getBookedSeatIds()

            if seatNumber not in bookedSeats:
                bookedSeats.append(seatNumber)
                booking = Booking()
                myBookedSeats = [screenSeat for screenSeat in interestedShow.getScreen().getSeats() if screenSeat.getSeatId() == seatNumber]
                booking.setBookedSeats(myBookedSeats)
                booking.setShow(interestedShow)
            else:
                print("Seat already booked. Please try again.")
                return

            print("Booking successful.")
        else:
            print("No shows available for the selected movie in your city.")

    def initialize(self):
        self.createMovies()
        self.createTheatre()

    def createTheatre(self):
        avengerMovie = self.movieController.getMovieByName("AVENGERS")
        baahubali = self.movieController.getMovieByName("BAAHUBALI")

        inoxTheatre = Theatre()
        inoxTheatre.setTheatreId(1)
        inoxTheatre.setScreen(self.createScreen())
        inoxTheatre.setCity(City.Bangalore)
        inoxShows = []
        inoxMorningShow = self.createShows(1, inoxTheatre.getScreen()[0], avengerMovie, 8)
        inoxEveningShow = self.createShows(2, inoxTheatre.getScreen()[0], baahubali, 16)
        inoxShows.append(inoxMorningShow)
        inoxShows.append(inoxEveningShow)
        inoxTheatre.setShows(inoxShows)

        pvrTheatre = Theatre()
        pvrTheatre.setTheatreId(2)
        pvrTheatre.setScreen(self.createScreen())
        pvrTheatre.setCity(City.Delhi)
        pvrShows = []
        pvrMorningShow = self.createShows(3, pvrTheatre.getScreen()[0], avengerMovie, 13)
        pvrEveningShow = self.createShows(4, pvrTheatre.getScreen()[0], baahubali, 20)
        pvrShows.append(pvrMorningShow)
        pvrShows.append(pvrEveningShow)
        pvrTheatre.setShows(pvrShows)

        self.theatreController.addTheatre(inoxTheatre, City.Bangalore)
        self.theatreController.addTheatre(pvrTheatre, City.Delhi)

    def createScreen(self):
        screens = []
        screen1 = Screen()
        screen1.setScreenId(1)
        screen1.setSeats(self.createSeats())
        screens.append(screen1)
        return screens

    def createShows(self, showId, screen, movie, showStartTime):
        show = Show()
        show.setShowId(showId)
        show.setScreen(screen)
        show.setMovie(movie)
        show.setShowStartTime(showStartTime)
        return show

    def createSeats(self):
        seats = []

        for i in range(40):
            seat = Seat()
            seat.setSeatId(i)
            seat.setSeatCategory(SeatCategory.SILVER)
            seats.append(seat)

        for i in range(40, 70):
            seat = Seat()
            seat.setSeatId(i)
            seat.setSeatCategory(SeatCategory.GOLD)
            seats.append(seat)

        for i in range(70, 100):
            seat = Seat()
            seat.setSeatId(i)
            seat.setSeatCategory(SeatCategory.PLATINUM)
            seats.append(seat)

        return seats

    def createMovies(self):
        avengers = Movie()
        avengers.setMovieId(1)
        avengers.setMovieName("AVENGERS")
        avengers.setMovieDuration(128)

        baahubali = Movie()
        baahubali.setMovieId(2)
        baahubali.setMovieName("BAAHUBALI")
        baahubali.setMovieDuration(180)

        self.movieController.addMovie(avengers, City.Bangalore)
        self.movieController.addMovie(avengers, City.Delhi)
        self.movieController.addMovie(baahubali, City.Bangalore)
        self.movieController.addMovie(baahubali, City.Delhi)


if __name__ == "__main__":
    bookMyShow = BookMyShow()
    bookMyShow.initialize()
    bookMyShow.createBooking(City.Bangalore, "BAAHUBALI")
    bookMyShow.createBooking(City.Bangalore, "BAAHUBALI")
