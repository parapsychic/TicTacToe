// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <iterator>

char computerInput = 'X';
char userInput = 'O';

struct Move
{
	int row, col;
};

void printTable(char cells[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << cells[i][j];
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

/* ALGO STARTS HERE */

bool isMovesLeft(char cells[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (cells[i][j] == '_')
			{
				return true;
			}
		}
	}
	return false;
}

int evaluate(char cells[3][3])
{

	for (int row = 0; row < 3; row++)
	{
		if (cells[row][0] == cells[row][1] &&
			cells[row][1] == cells[row][2])
		{
			if (cells[row][0] == computerInput)
			{
				return 10;
			}

			else if (cells[row][0] == userInput)
			{
				return -10;
			}
		}
	}

	for (int col = 0; col < 3; col++)
	{
		if (cells[0][col] == cells[1][col] &&
			cells[1][col] == cells[2][col])
		{
			if (cells[0][col] == computerInput)
				return +10;

			else if (cells[0][col] == userInput)
				return -10;
		}
	}

	if ((cells[0][0] == cells[1][1] && cells[1][1] == cells[2][2] ) ||
		(cells[0][2] == cells[1][1] && cells[1][1] == cells[2][0]))
	{

		if (cells[1][1] == computerInput)
		{
			return 10;
		}

		else if (cells[1][1] == userInput)
		{
			return -10;
		}
	}

	return 0;
}

int minimax(char cells[3][3], int depth, bool isMaximizer)
{
	int score = evaluate(cells);

	if (std::abs(score) == 10)
		return score;

	if (!isMovesLeft(cells))
	{
		return 0;
	}

	if (isMaximizer)
	{
		int best = -1000;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (cells[i][j] == '_')
				{
					cells[i][j] = computerInput;
					best = std::max(best, minimax(cells, depth + 1, !isMaximizer));

					cells[i][j] = '_';
				}
			}
		}
		return best + depth;
	}
	else
	{

		int best = 1000;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (cells[i][j] == '_')
				{
					cells[i][j] = userInput;
					best = std::min(best, minimax(cells, depth + 1, !isMaximizer));

					cells[i][j] = '_';
				}
			}
		}
		return best + depth;
	}
}

Move findBestMove(char cells[3][3])
{
	int bestVal = -1000;
	Move bestMove;
	bestMove.col = -1;
	bestMove.row = -1;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (cells[i][j] == '_')
			{
				cells[i][j] = computerInput;

				int moveVal = minimax(cells, 0, false);

				cells[i][j] = '_';

				if (moveVal > bestVal)
				{
					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}
	return bestMove;
}

// algo stops here

void placeCell(char cells[3][3])
{

	Move nextMove = findBestMove(cells);
	cells[nextMove.row][nextMove.col] = 'X';
}

void getInput(char cells[3][3])
{

	
	while (true)
	{
		int select;
		std::cout << "Enter a number: ";
		std::cin >> select;
		if (select > 9 || select < 0)
		{
			std::cout << "Enter a valid number";
			continue;
		}

		int i = select / 3;
		int j = select % 3 - 1;
		if (cells[i][j] != '_')
		{
			std::cout << "Cell already selected\n";
			continue;
		}
		cells[i][j] = 'O';
		break;
	}
}

bool check(char cells[3][3])
{
	if (!isMovesLeft(cells))
	{
		std::cout << "TIED" << std::endl;
		return true;
	}

	for (int i = 0; i < 3; i++)
	{
		if (cells[i][0] == cells[i][1] && cells[i][1] == cells[i][2])
		{
			if (cells[i][0] == computerInput)
			{
				std::cout << "Computer Wins" << std::endl;
				return true;
			}

			if (cells[i][0] == userInput)
			{
				std::cout << "User Wins" << std::endl;
				return true;
			}
		}

		if (cells[0][i] == cells[1][i] && cells[1][i] == cells[2][i])
		{
			if (cells[1][i] == computerInput)
			{
				std::cout << "Computer Wins" << std::endl;
				return true;
			}

			if (cells[1][i] == userInput)
			{
				std::cout << "User Wins" << std::endl;
				return true;
			}
		}
	}

	if (cells[0][0] == cells[1][1] && cells[1][1] == cells[2][2] ||
		cells[0][2] == cells[1][1] && cells[1][1] == cells[2][0])
	{

		if (cells[1][1] == computerInput)
		{
			std::cout << "Computer Wins" << std::endl;
			return true;
		}

		if (cells[1][1] == userInput)
		{
			std::cout << "User Wins" << std::endl;
			return true;
		}
	}
	return false;
}

int main()
{
	bool first;
	char cells[3][3];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cells[i][j] = '_';
		}
	}

	int input;
	std::cout << "Select who goes first: \n1. You \n2. Computer\n";

	std::cin >> input;
	first = input == 1 ? true : false;

	if (first)
	{
		getInput(cells);
	}

	while (true)
	{
		placeCell(cells);
		std::cout << std::endl;
		printTable(cells);
		if (check(cells))
		{
			break;
		}

		getInput(cells);
		std::cout << std::endl;
		printTable(cells);
		if (check(cells))
		{
			break;
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
