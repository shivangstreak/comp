from typing import List
from dataclasses import dataclass
from PlayingPiece import PlayingPiece

# @dataclass
# class PlayingPiece:
#     pieceType: str

class Board:
    def __init__(self, size: int):
        self.size = size
        self.board = [[None] * size for _ in range(size)]

    def addPiece(self, row: int, column: int, playingPiece: PlayingPiece) -> bool:
        if self.board[row][column] is not None:
            return False
        self.board[row][column] = playingPiece
        return True

    def getFreeCells(self) -> List[tuple[int, int]]:
        freeCells = []
        for i in range(self.size):
            for j in range(self.size):
                if self.board[i][j] is None:
                    freeCells.append((i, j))
        return freeCells

    def printBoard(self):
        for i in range(self.size):
            for j in range(self.size):
                if self.board[i][j] is not None:
                    print(self.board[i][j].pieceType + "   ", end="")
                else:
                    print("    ", end="")
                print(" | ", end="")
            print()
