#include <iostream>
#include <list> 
#include <iterator>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

char board[3][3] = {
		{'1', '2', '3'},
		{'4', '5', '6'},
		{'7', '8', '9'}
};

vector<char> computerMoves = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
 
void drawBoard()
{
	cout << "-------------" << endl;
	for (int k = 0; k < 3; k++)
	{
		cout << "| " << board[k][0] << " | " << board[k][1] << " | " << board[k][2] << " |" << endl;
		cout << "-------------" << endl;
	}

	cout << endl;
}

void insertIntoBoard(int decision, char player)
{
	int row = decision / 3;
	int col = decision % 3;

	if (board[row][col] == 'X' || board[row][col] == 'O')
	{
		throw exception("That cell is already filled");
	}

	try
	{
		board[row][col] = player;
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
	}
	
}

char GetAndValidateInput(string playerName, char player)
{
	bool isOK = false;
	int move;
	char playerInput;

	while (!isOK)
	{
		string input;
		cout << playerName << ": ";
		cin >> input;

		try
		{
			move = stoi(input);
			playerInput = move;
			if (!(move > 0 && move < 10))
			{
				throw invalid_argument("Invalid argument");
			}

			// decrese input by 1 because user choice start from 1, but array...
			move--;
			insertIntoBoard(move, player);
		}
		catch (const std::invalid_argument& ex)
		{
			cout << "Invalid argument, please insert a number between 0-9" << endl;
			continue;
		}
		catch (const std::exception & ex)
		{
			cout << ex.what() << endl;
			continue;
		}

		isOK = true;
	}

	// Convert to char and return
	return playerInput + '0';
}

// Not used but it can show you available moves
void outputComputerMoves(int index)
{
	int a = 0;
	for (auto it = computerMoves.begin(); it != computerMoves.end(); ++it)
	{
		if (a++ == index)
		{
			cout << "| ";
		}
		cout << *it << " ";
	}

	cout << endl;
}

void updateComputerMoves_old(int moveIndex, int index)
{
	char move = computerMoves[moveIndex];
	char temp = computerMoves[index];

	computerMoves[index] = move;
	computerMoves[moveIndex] = temp;
}

void updateComputerMoves(char remove)
{
	vector<char>::iterator it;
	it = find(computerMoves.begin(), computerMoves.end(), remove);
	computerMoves.erase(it);
}

int GetComputerInput()
{
	int ComputerLength = computerMoves.size();
	int moveIndex = rand() % ComputerLength;
	char move = computerMoves[moveIndex];
	updateComputerMoves(move);
	int computerMove = move - '0' - 1; // converting from char number to int number and decreasing by 1 because of arrays starting at 0
	return computerMove;
}

bool checkWinner(int &round)
{
	int side = 3;
	
	// rows
	for (int i = 0; i < side; i++)
	{
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
		{
			cout << "Winner! " << board[i][0] << endl;
			return true;
		}
	}

	// columns
	for (int i = 0; i < side; i++)
	{
		if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
		{
			cout << "Winner! " << board[0][i] << endl;
			return true;
		}
	}

	//diagonals
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
	{
		cout << "Winner! " << board[0][0] << endl;
		return true;
	}
	if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
	{
		cout << "Winner! " << board[0][2] << endl;
		return true;
	}

	round++;

	if (round == 9)
	{
		cout << "Draw!" << endl;
		return true;
	}
	
	return false;
	
}

int main()
{
	srand((unsigned)time(0));

	bool isComputerAlive = true;
	int playerMove = -1;
	int index = 0;

	int round = 0;
	drawBoard();

	bool endGame = false;

	// game loop
	while (!endGame)
	{
		//outputComputerMoves(index);

		playerMove = GetAndValidateInput("player1", 'X');
		
		system("cls");
		drawBoard();

		if (checkWinner(round))
		{
			endGame = true;
			break;
		}

		if (isComputerAlive)
		{
			updateComputerMoves(playerMove);
			int computerMove = GetComputerInput();
			insertIntoBoard(computerMove, 'O');
		}
		else
		{
			GetAndValidateInput("player2", 'O');
		}

		system("cls");
		drawBoard();

		if (checkWinner(round))
		{
			endGame = true;
			break;
		}
	}
	

	return 0;
}