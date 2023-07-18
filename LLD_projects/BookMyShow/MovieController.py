from constants import City
from Movie import Movie

# MovieController has Movie
class MovieController:
    def __init__(self):
        self.cityVsMovies = {}
        self.allMovies = []

    def addMovie(self, movie, city):
        self.allMovies.append(movie)
        movies = self.cityVsMovies.get(city, [])
        movies.append(movie)
        self.cityVsMovies[city] = movies

    def getMovieByName(self, movieName):
        for movie in self.allMovies:
            if movie.getMovieName() == movieName:
                return movie
        return None

    def getMoviesByCity(self, city):
        return self.cityVsMovies.get(city, [])

    # Implement removeMovie, updateMovie, and CRUD operations based on Movie ID
    # based on your specific requirements
