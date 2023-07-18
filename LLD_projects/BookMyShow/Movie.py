class Movie:
    def __init__(self):
        self.movieId = 0
        self.movieName = ""
        self.movieDurationInMinutes = 0
        # other details like Genre, Language, etc.

    def getMovieId(self):
        return self.movieId

    def setMovieId(self, movieId):
        self.movieId = movieId

    def getMovieName(self):
        return self.movieName

    def setMovieName(self, movieName):
        self.movieName = movieName

    def getMovieDuration(self):
        return self.movieDurationInMinutes

    def setMovieDuration(self, movieDuration):
        self.movieDurationInMinutes = movieDuration
