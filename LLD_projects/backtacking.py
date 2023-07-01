def chaining(songs, start_song):
    # create a map of songs where the last word of title is the key
    song_map = {}
    for song in songs:
        last_word = song.split()[-1]
        if last_word not in song_map:
            song_map[last_word] = []
        song_map[last_word].append(song)

    # define a helper function to perform depth-first search
    def dfs(song, path):
        nonlocal longest_path
        # check if the current path is longer than the longest path found so far
        if len(path) > len(longest_path):
            longest_path = path.copy()
        # get the first word of the current song
        first_word = song.split()[0]
        # if there are any songs that end with this word, explore them
        if first_word in song_map:
            for next_song in song_map[first_word]:
                if next_song not in path:
                    path.append(next_song)
                    dfs(next_song, path)
                    path.pop()  # backtrack

    longest_path = [start_song]
    dfs(start_song, longest_path)
    return longest_path



songs = [
    "Down By the River",
    "River of Dreams",
    "Take me to the River",
    "Dreams",
    "Blues Hand Me Down",
    "Forever Young",
    "American Dreams",
    "All My Love",
    "Cantaloop",
    "Take it All",
    "Love is Forever",
    "Young American",
    "Every Breath You Take",
]
start_song = "Every Breath You Take"
print(chaining(songs, start_song))




