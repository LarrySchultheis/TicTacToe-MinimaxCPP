//Larry Schultheis
//Tic tac toe minimax agent

#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int terminal_test(vector<vector<int>>& board);
bool checkSpace(vector<vector<int>>& board, int row, int col);
void aiMove(vector<vector<int>>& board, int goFirst);
void oppoMove(vector<vector<int>>& board, int goFirst);
pair<int, int> minimax_decision(vector<vector<int>>& board);
int max_value(vector<vector<int>>& board);
int min_value(vector<vector<int>>& board);
void printBoard(vector<vector<int>>& board, int row, int column);
bool gameOver(vector<vector<int>>& board, int row, int column);
void showTemplate();

const int EMPTY = 0;
const int PLAYX = 1;
const int PLAYO = 2;

int wentFirst;


int main()
{
	// randomize seed for generating random numbers
	srand((unsigned)time(NULL));

	int row = 3;
	int column = 3;

	bool play = true;
	char playAgain = 'y';

	while (play)
	{
		// declare and initialize the board
		vector<vector<int>> board(row, vector<int>(column, EMPTY));

		//goFirst = 1 for AI
		//goFirst = 0 for opponent 

		cout << "Who's going first? (0 for player, 1 for AI)" << endl;
		cin >> wentFirst;
		cout << ((wentFirst == 1) ? "You are O's" : "You are X's") << endl;
		cout << "Pick squares using this template: \n" << endl;
		showTemplate();
		system("pause");

		printBoard(board, row, column);

		while (true)
		{
			if (wentFirst == 0)
			{
				//Opponent
				oppoMove(board, wentFirst);
				if (gameOver(board, row, column))
					break;
				printBoard(board, row, column);
				aiMove(board, wentFirst);
				if (gameOver(board, row, column))
					break;
				printBoard(board, row, column);
			}
			else if (wentFirst == 1)
			{
				//AI
				aiMove(board, wentFirst);
				if (gameOver(board, row, column))
					break;
				printBoard(board, row, column);
				oppoMove(board, wentFirst);
				if (gameOver(board, row, column))
					break;
				printBoard(board, row, column);
			}
			else
			{
				cerr << "Invalid number for variable 'goFirst'" << endl;
			}
		}

		cout << "Would you like to play again? (y/n)" << endl;
		cin >> playAgain;

		play = (playAgain == 'y' || playAgain == 'Y');
	}



	cerr << endl;
	cout.flush();
	system("pause");
	return 0;
}

bool gameOver(vector<vector<int>>& board, int row, int column)
{
	int gameCheck = terminal_test(board);
	bool over = false;
	if (gameCheck == -1)
	{
		//oppo wins
		cerr << "Opponent has won" << endl;
		system("pause");
		over = true;
	}
	else if (gameCheck == 0)
	{
		//tie
		cerr << "The game is a tie" << endl;
		system("pause");
		over = true;
	}
	else if (gameCheck == 1)
	{
		//ai wins
		cerr << "AI has won" << endl;
		system("pause");
		over = true;
	}
	else if (gameCheck == 3)
	{
		//game not over
		cerr << "The game is not finished" << endl;
		over = false;

	}
	else
	{
		//invalid value
		cerr << "Invalid return value from terminal_test()" << endl;
		over = true;
	}
	printBoard(board, row, column);
	return over;
}

// checks the current board for a winner
// Returns the current state of the board:
// 1 = AI wins, -1 = opponent wins
// 0 = tie, 3 = game not finished
int terminal_test(vector<vector<int>>& board)
{
	int row = board.size();
	int column = board[0].size();

	bool aiWin = false, oppoWin = false, gameOver = true;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (board[i][j] == EMPTY)
			{
				//if there are still empty spaces the game may not be over
				gameOver = false;
			}
		}
	}

	//check rows
	for (int i = 0; i < row; i++)
	{
		if (board[i][0] == PLAYX && board[i][1] == PLAYX && board[i][2] == PLAYX)
		{
			if (wentFirst == 0)
				oppoWin = true;
			else if (wentFirst == 1)
				aiWin = true;
			break;
		}

		if (board[i][0] == PLAYO && board[i][1] == PLAYO && board[i][2] == PLAYO)
		{
			if (wentFirst == 0)
				aiWin = true;
			else if (wentFirst == 1)
				oppoWin = true;
			break;
		}
	}

	//check columns
	for (int i = 0; i < column; i++)
	{
		if (board[0][i] == PLAYX && board[1][i] == PLAYX && board[2][i] == PLAYX)
		{
			if (wentFirst == 0)
				oppoWin = true;
			else if (wentFirst == 1)
				aiWin = true;
			break;
		}

		if (board[0][i] == PLAYO && board[1][i] == PLAYO && board[2][i] == PLAYO)
		{
			if (wentFirst == 0)
				aiWin = true;
			else if (wentFirst == 1)
				oppoWin = true;
			break;
		}
	}

	//check diagonals
	if ((board[0][0] == PLAYX && board[1][1] == PLAYX && board[2][2] == PLAYX)
		|| (board[0][2] == PLAYX && board[1][1] == PLAYX && board[2][0] == PLAYX))
	{
		if (wentFirst == 0)
			oppoWin = true;
		else if (wentFirst == 1)
			aiWin = true;
	}

	if ((board[0][0] == PLAYO && board[1][1] == PLAYO && board[2][2] == PLAYO)
		|| (board[0][2] == PLAYO && board[1][1] == PLAYO && board[2][0] == PLAYO))
	{
		if (wentFirst == 0)
			aiWin = true;
		else if (wentFirst == 1)
			oppoWin = true;
	}

	//return game state
	if (oppoWin)
		return -1;
	else if (aiWin)
		return 1;
	else if (gameOver)
		return 0;
	else
		return 3;
}

bool checkSpace(vector<vector<int>>& board, int row, int col)
{
	return (board[row][col] == EMPTY);
}

void aiMove(vector<vector<int>>& board, int goFirst)
{
	cout << "AI is deciding your fate, please wait . . ." << endl;
	while (true)
	{
		//int aiRow = rand() % 3;
		//int aiCol = rand() % 3;

		pair<int, int> newMove = minimax_decision(board);
		int newX = newMove.first, newY = newMove.second;

		if (checkSpace(board, newX, newY))
		{
			//space open
			cout << newX << " " << newY << endl;

			if (goFirst == 1)
			{
				board[newX][newY] = PLAYX;
			}
			else if (goFirst == 0)
			{
				board[newX][newY] = PLAYO;
			}
			else
			{
				cerr << "Invalid value for goFirst" << endl;
			}
			break;
		}
	}
}

void oppoMove(vector<vector<int>>& board, int goFirst)
{
	showTemplate();
	int oppoRow, oppoCol;

	while (true)
	{
		int choice;
		cout << "Pick your square (0 - 8)" << endl;
		cin >> choice;

		switch (choice)
		{
			case 0: 
				oppoRow = 0;
				oppoCol = 0;
				break;
			case 1:
				oppoRow = 0;
				oppoCol = 1;
				break;
			case 2:
				oppoRow = 0;
				oppoCol = 2;
				break;
			case 3:
				oppoRow = 1;
				oppoCol = 0;
				break;
			case 4:
				oppoRow = 1;
				oppoCol = 1;
				break;
			case 5:
				oppoRow = 1;
				oppoCol = 2;
				break;
			case 6:
				oppoRow = 2;
				oppoCol = 0;
				break;
			case 7:
				oppoRow = 2;
				oppoCol = 1;
				break;
			case 8:
				oppoRow = 2;
				oppoCol = 2;
				break;
			default:
				oppoRow = rand() % 3;
				oppoCol = rand() % 3;
				break;
		}

		if (checkSpace(board, oppoRow, oppoCol))
		{
			if (goFirst == 0)
			{
				board[oppoRow][oppoCol] = PLAYX;
			}
			else if (goFirst == 1)
			{
				board[oppoRow][oppoCol] = PLAYO;
			}
			else
			{
				cerr << "Invalid value for goFirst" << endl;
			}
			break;
		}
		else
			cerr << "Space is already occupied" << endl;
	}
}




void printBoard(vector<vector<int>>& board, int row, int column)
{
	system("cls");
	cout << "\n\n\tTic Tac Toe\n\n";
	cout << endl;

	vector<vector<string>> copy(row, vector<string>(column, " "));
	
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[0].size(); j++)
		{
			switch (board[i][j])
			{
				case 0:
					copy[i][j] = " ";
					break;
				case 1:
					copy[i][j] = "X";
					break;
				case 2: 
					copy[i][j] = "O";
					break;
				default:
					copy[i][j] = " ";
					break;
			}
		}
	}

	cout << "     |     |     " << endl;

	cout << "  " << copy[0][0] << "  |  " << copy[0][1] << "  |  " << copy[0][2] << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << copy[1][0] << "  |  " << copy[1][1] << "  |  " << copy[1][2] << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << copy[2][0] << "  |  " << copy[2][1] << "  |  " << copy[2][2] << endl;

	cout << "     |     |     " << endl << endl;
}

void showTemplate()
{
	cout << "     |     |     " << endl;

	cout << "  " << "0" << "  |  " << "1" << "  |  " << "2" << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << "3" << "  |  " << "4" << "  |  " << "5" << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << "6" << "  |  " << "7" << "  |  " << "8" << endl;

	cout << "     |     |     " << endl << endl;
}

// minimax decision
// Returns action with maximum value with coordinates (newR, newC)
// This function has been partially completed for you
pair<int, int> minimax_decision(vector<vector<int>>& board)
{
	int row = board.size();
	int column = board[0].size();

	int newR = -1, newC = -1;

	int returnVal = -100;

	// for each action a which is row i and column j

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {

			if (board[i][j] == EMPTY)
			{
				// fill in this part
				// simulate the action by AI to get the resulting board state -this is RESULT(state,a) in the pseudo-code

								// call min_value on the resulting board to get the value of the board and
				// keep track of the row newR and column newC of the action with maximum return value				

				// undo the simulated action by setting the board back to original state

				if (wentFirst == 0)
				{
					board[i][j] = PLAYO;
				}
				else if (wentFirst == 1)
				{
					board[i][j] = PLAYX;
				}

				int temp = min_value(board);

				if (temp >= returnVal)
				{
					newR = i;
					newC = j;
					returnVal = temp;
				}
				board[i][j] = EMPTY;
			}

		}
	}
	return pair<int, int>(newR, newC);
}




// max value, returns a utility value of 
// 1 = AI wins / 0 = tie / -1 = opponent wins
int max_value(vector<vector<int>>& board)
{
	int row = board.size();
	int column = board[0].size();

	// fill in this part

	if (terminal_test(board) == 0)
	{
		//tie
		return 0;
	}
	else if (terminal_test(board) == -1)
	{
		//oppo wins
		return -1;
	}
	else if (terminal_test(board) == 1)
	{
		//AI wins
		return 1;
	}
	else
	{
		int maxUtil = -1000;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				if (board[i][j] == EMPTY)
				{
					if (wentFirst == 0)
					{
						board[i][j] = PLAYO;
					}
					else if (wentFirst == 1)
					{
						board[i][j] = PLAYX;
					}

					maxUtil = max(maxUtil, min_value(board));
					board[i][j] = EMPTY;
				}
			}
		}
		return maxUtil;
	}

}



// min value, returns a utility value of 
// 1 = AI wins / 0 = tie / -1 = opponent wins
int min_value(vector<vector<int>>& board)
{
	int row = board.size();
	int column = board[0].size();

	// fill in this part

	if (terminal_test(board) == 0)
	{
		//tie
		return 0;
	}
	else if (terminal_test(board) == -1)
	{
		//oppo wins
		return -1;
	}
	else if (terminal_test(board) == 1)
	{
		//AI wins
		return 1;
	}
	else
	{
		int minUtil = 1000;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				if (board[i][j] == EMPTY)
				{
					if (wentFirst == 0)
					{
						board[i][j] = PLAYX;
					}
					else if (wentFirst == 1)
					{
						board[i][j] = PLAYO;
					}

					minUtil = min(minUtil, max_value(board));
					board[i][j] = EMPTY;
				}
			}
		}
		return minUtil;
	}
}