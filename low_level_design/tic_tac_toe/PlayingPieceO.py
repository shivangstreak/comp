from PlayingPiece import PlayingPiece
from Constants import PieceType

class PlayingPieceO(PlayingPiece):
    def __init__(self):
        super().__init__(PieceType.O)
