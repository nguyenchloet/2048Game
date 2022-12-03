// simplified 2048 game
#include <iostream>
#include <cstdlib>

const int BOARD_SIZE = 4;

const char UP = 'w';
const char LEFT = 'a';
const char RIGHT = 'd';
const char DOWN = 's';
const char QUIT = 'q';

// the gameboard
int board[BOARD_SIZE][BOARD_SIZE];

// copy of the gameboard for change comparison
int _board[BOARD_SIZE][BOARD_SIZE];

class Game {
    public:
        Game();
        ~Game();
        void Play();

    private:
        //Variables                                                                                                                                               

        //Functions    
        void InitializeBoard();    
        void PrintBoard();   
        void CommandLoop();    
        void AddTile();                                                                                                                                
};

Game::Game() {}

Game::~Game() {}

// place two tiles randomly on the board to start the game - either 2s or 4s
// otherwise, the tiles will remain 0 value
void Game::InitializeBoard() {
    srand(time(NULL));
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

void Game::PrintBoard(){
    // print board
    // format spacing around integers on board up to 5 digits
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

void Game::CommandLoop() {
    char user_choice;
    do {
        std::cout << "Press: (w):up (a):left (d):right (s):down (q): quit " << std::endl;
        std::cin >> user_choice;
        std::cin.ignore();
        if (user_choice == LEFT) {
            //shift_left();
            //update_score();
            AddTile();
            PrintBoard();
        }
        else if (user_choice == RIGHT) {
            //shift_right();
            //update_score();
            AddTile();
            PrintBoard();
        }
        else if (user_choice == UP) {
            //shift_up();
            //update_score();
            AddTile();            
            PrintBoard();
        }
        else if (user_choice == DOWN) {
            //shift_down();
            //update_score();
            AddTile();
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

// add one tile to a random empty position on the board
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

    //from empty positions, randomly generate an index     
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

void Game::Play() {
    InitializeBoard();
    PrintBoard();
    CommandLoop();
}

int main() {
    Game aGame;
    aGame.Play();
    return 0;
}