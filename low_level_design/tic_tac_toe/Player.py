from PlayingPiece import PlayingPiece
class Player:
    def __init__(self, name, playingPiece):
        self.name = name
        self.playingPiece = playingPiece

    def getName(self):
        return self.name

    def setName(self, name):
        self.name = name

    def getPlayingPiece(self):
        return self.playingPiece

    def setPlayingPiece(self, playingPiece):
        self.playingPiece = playingPiece