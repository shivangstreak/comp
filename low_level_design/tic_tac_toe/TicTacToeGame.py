from Board import Board
from PlayingPieceO import PlayingPieceO
from PlayingPieceX import PlayingPieceX
from Player import Player

from collections import deque

class TicTacToeGame:
    def initializeGame(self):
        # Creating 2 Players
        self.players = deque()
        crossPiece = PlayingPieceX()
        player1 = Player("Player1", crossPiece)

        noughtsPiece = PlayingPieceO()
        player2 = Player("Player2", noughtsPiece)

        self.players.append(player1)
        self.players.append(player2)

        # Initialize Board
        self.gameBoard = Board(3)

    def startGame(self):
        noWinner = True
        while noWinner:
            # Take out the player whose turn is and also put the player in the list back
            playerTurn = self.players.popleft()

            # Get the free space from the board
            self.gameBoard.printBoard()
            freeSpaces = self.gameBoard.getFreeCells()
            if not freeSpaces:
                noWinner = False
                continue

            # Read the user input
            print("Player:", playerTurn.name, "Enter row,column: ")
            s = input()
            values = s.split(",")
            inputRow = int(values[0])
            inputColumn = int(values[1])

            # Place the piece
            pieceAddedSuccessfully = self.gameBoard.addPiece(inputRow, inputColumn, playerTurn.playingPiece)
            if not pieceAddedSuccessfully:
                # Player cannot insert the piece into this cell, player has to choose another cell
                print("Incorrect position chosen, try again")
                self.players.appendleft(playerTurn)
                continue
            self.players.append(playerTurn)

            winner = self.isThereWinner(inputRow, inputColumn, playerTurn.playingPiece.pieceType)
            if winner:
                return playerTurn.name

        return "tie"

    def isThereWinner(self, row, column, pieceType):
        rowMatch = True
        columnMatch = True
        diagonalMatch = True
        antiDiagonalMatch = True

        # Need to check in row
        for i in range(self.gameBoard.size):
            if self.gameBoard.board[row][i] is None or self.gameBoard.board[row][i].pieceType != pieceType:
                rowMatch = False

        # Need to check in column
        for i in range(self.gameBoard.size):
            if self.gameBoard.board[i][column] is None or self.gameBoard.board[i][column].pieceType != pieceType:
                columnMatch = False

        # Need to check diagonals
        for i in range(self.gameBoard.size):
            if self.gameBoard.board[i][i] is None or self.gameBoard.board[i][i].pieceType != pieceType:
                diagonalMatch = False

        # Need to check anti-diagonals
        for i in range(self.gameBoard.size):
            if self.gameBoard.board[i][self.gameBoard.size - i - 1] is None or self.gameBoard.board[i][self.gameBoard.size - i - 1].pieceType != pieceType:
                antiDiagonalMatch = False

        return rowMatch or columnMatch or diagonalMatch or antiDiagonalMatch
