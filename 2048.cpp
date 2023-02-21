/*
 * 2048 console game
 */

#include <iostream>
#include <cstdlib>

const int BOARD_SIZE = 4;

const char UP = 'w';
const char LEFT = 'a';
const char RIGHT = 'd';
const char DOWN = 's';
const char QUIT = 'q';

/*
 * the gameboard
 */
int board[BOARD_SIZE][BOARD_SIZE];

/*
 * copy of the gameboard for change comparison
 */
int _board[BOARD_SIZE][BOARD_SIZE];

/*
 * Class
 */
class Game {
    public:
        Game();
        ~Game();
        void Play();

    private:
        /*
	 * Variables  
	 */
        int score;

        //Functions    
        void InitializeBoard();    
        void PrintBoard();   
        void CommandLoop();    
        void AddTile();
        void UpdateScore();
        void ShiftLeft();
        void ShiftRight();
        void ShiftUp();
        void ShiftDown();   
        bool BoardFull();
        bool CanMerge(); 
        bool GameOver();                                                                                                                            
};

Game::Game() {}

Game::~Game() {}

/*
 * Place two tiles randomly on the board to start the game - either 2s or 4s
 * Otherwise, the tiles will remain 0 value
 */
void Game::InitializeBoard() {
    srand(time(NULL));
    score = 0;

    std::cout << "\n\tWelcome to 2048!" << std::endl;
    //ask user if they want to read the rules?

	// initialize board with 0s
	for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				board[i][j] = 0;
		}
	}

    int a = rand() % BOARD_SIZE;
    int b = rand() % BOARD_SIZE;
    int r = rand() % 10;
    while (a == b) {
        b = rand() % BOARD_SIZE;
    }

	// fill board with two 2s or 4s - 80% 4 / 20% 2,
  	for (int i = 0; i < BOARD_SIZE; i++) {
    	for (int j = 0; j < BOARD_SIZE; j++) {
      		if (board[i][j] == 0) {
      			r = rand() % 10;
      			if (r >= 8) {
      				board[a][b] = 4;
                    board[b][a] = 4;
      			} else {
      				board[a][b] = 2;
                    board[b][a] = 2;
      			}
      		}
    	}
  	}
}

/*
 * print board
 * format spacing around integers on board up to 5 digits
 */
void Game::PrintBoard(){
	for (int x = 0; x < BOARD_SIZE; x++) {
        std::cout << "+------+------+------+------+" << std::endl;
		for (int y = 0; y < BOARD_SIZE; y++) {
			std::cout << "|";
            if (board[x][y] < 10) {
                std::cout << "   " << board[x][y] << "  ";
            }
            else if (board[x][y] >= 10 && board[x][y] < 100) {
                std::cout << "  " << board[x][y] << "  ";
            } 
            else if (board[x][y] >= 100 && board[x][y] < 1000) {
                std::cout << "  " << board[x][y] << " ";
            }
            else if (board[x][y] >= 1000 && board[x][y] < 10000) {
               std::cout << " " << board[x][y] << " ";
            }
            else {
                std::cout << " " << board[x][y];
            }
		}
		std::cout << "|" << std::endl;
	}
    std::cout << "+------+------+------+------+" << std::endl;

}

/*
 * Get user input a/w/s/d/q to shift board or quit
 */
void Game::CommandLoop() {
    char user_choice;
    do {
        std::cout << "Press: (a):left (d):right (w):up (s):down (q): quit " << std::endl;
        std::cin >> user_choice;
        std::cin.ignore();
        if (user_choice == LEFT) {
            ShiftLeft();
            UpdateScore();
            PrintBoard();
        }
        else if (user_choice == RIGHT) {
            ShiftRight();
            UpdateScore();
            PrintBoard();
        }
        else if (user_choice == UP) {
            ShiftUp();
            UpdateScore();
            PrintBoard();
        }
        else if (user_choice == DOWN) {
            ShiftDown();
            UpdateScore();
            PrintBoard();
        }
        else if (user_choice == QUIT) {
            exit(0);
        }
        else {
            std::cout << "Command not recognized. Please try again." << std::endl;
            std::cin.clear();
        }
    } while (user_choice != QUIT);
    std::cout << "\nGame Over." << std::endl;
}

/*                                                                                                                                                                
 * Output score function                                                                                                                                   
 */
void Game::UpdateScore() {
  std::cout << "Score: " << score << std::endl;
}

/*
 * add one tile to a random empty position on the board
 */
void Game::AddTile() {
    srand(time(NULL));
    int num_empty = 0;

    for (int i = 0; i < BOARD_SIZE; i++) { //check for empty spots                                                                                                  
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                num_empty++;
            }
        }
    }

    /* 
     * from empty positions, randomly generate an index     
     */
    int empty_position = rand() % num_empty;                                                                 
    num_empty = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            // if space is empty 
            if (board[i][j] == 0) {                                                                                                                
                if (empty_position == num_empty) {
                    int r = rand() % 10;
                    if (r >= 9) {
                        board[i][j] = 4;
                    }
                    else {
                        board[i][j] = 2;
                    }
                }
                num_empty++;
            } 
        }
    }
}

/*                                                                                                                                                                
 * Shift tile with value to left if: tile to left is empty / 0                                                                                                    
 * Merge value if tile to left is of equal value                                                                                                                  
 */
void Game::ShiftLeft() {
  bool moved = false;
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int col = 0; col < BOARD_SIZE; col++) {
        for (int curr_col = col + 1; curr_col < BOARD_SIZE; curr_col++) {
          if ((board[row][col] == 0) and (board[row][curr_col] != 0) and (curr_col < BOARD_SIZE)) {
            board[row][col] = board[row][curr_col];
            board[row][curr_col] = 0;
            moved = true;
        }
      }
    }
  }
  /*
   * merge tiles LEFT
   */
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int col = 0; col < BOARD_SIZE; col++) {
      for (int curr_col = col + 1; curr_col < BOARD_SIZE; curr_col++) {
        if ((board[row][col] != 0) and (board[row][col] == board[row][curr_col]) and (curr_col < BOARD_SIZE)) {
            board[row][col] += board[row][col + 1];
            board[row][col + 1] = 0;
            score += board[row][col];
        }
      }
    }
  }
  if (moved == true) {
    AddTile();
  }
}

/*                                                                                                                                                                
 * Shift tile with value right if: tile to right is empty / 0                                                                                                     
 * Merge value if tile to right is of equal value                                                                                                                 
 */
void Game::ShiftRight() {
  bool moved = false;
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int col = BOARD_SIZE - 1; col >= 0; col--) {
      for (int curr_col = col - 1; curr_col >= 0; curr_col--) {
        if ((board[row][col] == 0) and (board[row][curr_col] != 0) and (curr_col >= 0)) {
          board[row][col] = board[row][curr_col];
          board[row][curr_col] = 0;
          moved = true;
        }
      }
    }
  }
  /*
   * merge tiles RIGHT 
   */
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int col = BOARD_SIZE; col >= 0; col--) {
      for (int curr_col = col - 1; curr_col >= 0; curr_col--) {
        if ((board[row][col] != 0) and (board[row][col] == board[row][curr_col]) and (curr_col >= 0)) {
           board[row][col] += board[row][curr_col];
           board[row][curr_col] = 0;
           score += board[row][col];
        }
      }
    }
  }
  if (moved == true) {
    AddTile();
  }
}

/*                                                                                                                                                                
 * While tile + 1 is empty and tile has value, move to tile + 1                                                                                                   
 * For up and down, columns are the outer for loop                                                                                                                
 */
void Game::ShiftUp() {
  bool moved = false;
  for (int col = 0; col < BOARD_SIZE; col++) {
    for (int row = 0; row < BOARD_SIZE; row++) {
       for (int curr_col = col + 1; curr_col < BOARD_SIZE; curr_col++) {
         if ((board[col][row] == 0) and (board[curr_col][row] != 0)) {
           board[col][row] = board[curr_col][row];
           board[curr_col][row] = 0;
           moved = true;
        }
      }
    }
  }
  /*
   * merge tiles UP
   */
  for (int col = 0; col < BOARD_SIZE; col++) {
    for (int row = 0; row < BOARD_SIZE; row++) {
      for (int curr_col = col + 1; curr_col < BOARD_SIZE; curr_col++) {
        if ((board[col][row] != 0) and (board[col][row] == board[curr_col][row])) {
          board[col][row] += board[curr_col][row];
          board[curr_col][row] = 0;
          score += board[col][row];
        }
      }
    }
  }
  if (moved == true) {
    AddTile();
  }
}

/*                                                                                                                                                                
 * Shift down if tile below is empty and current tile has value                                                                                                   
 */
void Game::ShiftDown() {
  bool moved = false;
  for (int col = BOARD_SIZE - 1; col >= 0; col--) {
    for (int row = 0; row < BOARD_SIZE; row++) {
      for (int curr_col = col - 1; curr_col >= 0; curr_col--) {
        if ((board[col][row] == 0) and (board[curr_col][row] != 0) and (curr_col >= 0)) {
          board[col][row] = board[curr_col][row];
          board[curr_col][row] = 0;
          moved = true;
        }
      }
    }
  }
  /* 
   * merge tiles DOWN
   */
  for (int col = BOARD_SIZE - 1; col >= 0; col--) {
    for (int row = 0; row < BOARD_SIZE; row++) {
      for (int curr_col = col - 1; curr_col >= 0; curr_col--) {
        if ((board[col][row] != 0) and (board[curr_col][row] == board[col][row]) and (curr_col >= 0)) {
          board[col][row] += board[curr_col][row];
          board[curr_col][row] = 0;
          score += board[col][row];
        }
      }
    }
  }
  if (moved == true) {
    AddTile();
  }
}

/*                                                                                                                                                                
 * Check if board is full of tiles with value                                                                                                                     
 */
bool Game::BoardFull() {
  int num_empty = 0;
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == 0) {
        num_empty++;
      }
    }
  }

  if (num_empty == 0) {
    return true;
  } else {
    return false;
  }
}

/*                                                                                                                                                                
 * Checks if there are any tile of equal value next to each other                                                                                                 
 * When board is full?                                                                                                                                            
 */
bool Game::CanMerge() {
  /*
   * check left        
   */
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int col = 0; col < BOARD_SIZE; col++) {
      for (int curr_col = col + 1; curr_col < BOARD_SIZE; curr_col++) {
        if ((board[row][col] != 0) and (board[row][col] == board[row][curr_col]) and (curr_col < BOARD_SIZE)) {
          return true;
        }
      }
    }
  }
  //check right                                                                                                                                                   
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int col = BOARD_SIZE; col >= 0; col--) {
      for (int curr_col = col - 1; curr_col >= 0; curr_col--) {
        if ((board[row][col] != 0) and (board[row][col] == board[row][curr_col]) and (curr_col >= 0)) {
          return true;
        }
      }
    }
  }
  /* 
   * check up
   */
  for (int col = 0; col < BOARD_SIZE; col++) {
    for (int row = 0; row < BOARD_SIZE; row++) {
      for (int curr_col = col + 1; curr_col < BOARD_SIZE; curr_col++) {
        if ((board[col][row] != 0) and (board[col][row] == board[curr_col][row])) {
          return true;
        }
      }
    }
  }
  /* 
   * check down  
   */
  for (int col = BOARD_SIZE - 1; col >= 0; col--) {
    for (int row = 0; row < BOARD_SIZE; row++) {
      for (int curr_col = col - 1; curr_col >= 0; curr_col--) {
        if ((board[col][row] != 0) and (board[curr_col][row] == board[col][row]) and (curr_col >= 0)) {
          return true;
        }
      }
    }
  }
  return false;
}

/*                                                                                                                                                                
 * End game conditions: over if no empty spots, no merges possible  or score 2048                                                                                 
 */
bool Game::GameOver() {
  if ((BoardFull() == true) && (CanMerge() == false)) {
    return true;
  } else if (score == 2048) {
    return true;
  } else {
    return false;
  }
  if (true) {
    std::cout << "Board Full. Game Over!" << std::endl;
    return 1;
  }
}

void Game::Play() {
    InitializeBoard();
    PrintBoard();
    while (GameOver() == false) {
        CommandLoop();
    }
}

int main() {
    Game aGame;
    aGame.Play();
    return 0;
}
