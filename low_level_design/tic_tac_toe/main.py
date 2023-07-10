from TicTacToeGame import TicTacToeGame

if __name__ == "__main__":
    game = TicTacToeGame()
    game.initializeGame()
    print("game winner is:", game.startGame())
