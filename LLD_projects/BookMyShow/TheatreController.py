from constants import City

# TheatreController has Theatre

class TheatreController:
    def __init__(self):
        self.cityVsTheatre = {}
        self.allTheatre = []

    def addTheatre(self, theatre, city):
        self.allTheatre.append(theatre)
        theatres = self.cityVsTheatre.get(city, [])
        theatres.append(theatre)
        self.cityVsTheatre[city] = theatres

    def getAllShow(self, movie, city):
        theatreVsShows = {}
        theatres = self.cityVsTheatre.get(city, [])

        for theatre in theatres:
            givenMovieShows = []
            shows = theatre.getShows()

            for show in shows:
                if show.getMovie().getMovieId() == movie.getMovieId():
                    givenMovieShows.append(show)

            if givenMovieShows:
                theatreVsShows[theatre] = givenMovieShows

        return theatreVsShows
