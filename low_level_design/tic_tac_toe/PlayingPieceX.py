from PlayingPiece import PlayingPiece
from Constants import PieceType

class PlayingPieceX(PlayingPiece):
    def __init__(self):
        super().__init__(PieceType.X)
