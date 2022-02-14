#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <ctime>

using namespace std;

const int CENTRAL_NUMBER = 5;
const int PARTIES = 8;
const int MAX_CHOICE = 2;
const int ARRAY_SIZE = 3;
const int ZERO_NUMBER = 4;
const int CROSSES = 1;
const int GOOD[4] = { 1, 3, 7, 9 };
const int BAD[4] = { 2, 4, 6, 8 };

int field[3][3] = { {0,0,0},{0,0,0},{0,0,0} };
char symbols[5] = { '-','X','-','-', 'O' };

int counter = 0;
int computerChoice = 0;
int gameCounter = 0;
int machineScore = 0;
int userScore = 0;

void clear();
void showFieldNumeration();
void showTie();
void showScore();
void machineTurn();
void machineFirstTurn(int);
void showIntro();
void userTurn();
bool emptyCellCheck(int);
bool checkTrap();
int checkPreWinLose(int);
bool checkWin();
void showField();
void printError(int);
void printMachineTurn(int);
void changeCell(int, int);
int computerSign();
int userSign();
int getGoodCell();

int main()
{
	int choice = 0;
	int machineCrossCounter = 0;
	
	for (int i = 0; i < PARTIES; i++)
	{
		gameCounter++;
		counter = 0;
		computerChoice = 0;

		for (int i = 0; i < ARRAY_SIZE; i++)
		{
			for (int j = 0; j < ARRAY_SIZE; j++)
			{
				field[i][j] = 0;
			}
		}

		showIntro();

		do
		{
			cout << "Your choice: ";
			cin >> choice;

			if (choice < 1 or choice > MAX_CHOICE)
			{
				printError(MAX_CHOICE);
			}

		} while (choice != 1 and choice != MAX_CHOICE);

		showFieldNumeration();

		if (choice == 1)
		{
			counter++;
			userTurn();
			showFieldNumeration();

			counter++;
			machineTurn();
		}
		else
		{
			machineCrossCounter++;
			counter++;
			machineFirstTurn(machineCrossCounter);
		}

		while (counter < ARRAY_SIZE * ARRAY_SIZE)
		{
			showFieldNumeration();
			printMachineTurn(computerChoice);

			counter++;
			userTurn();

			if (checkWin())
			{
				userScore++;
				showFieldNumeration();
				cout << "User won!" << endl;
				break;
			}

			showFieldNumeration();

			counter++;
			if (counter > ARRAY_SIZE * ARRAY_SIZE)
				break;

			machineTurn();

			if (checkWin())
			{
				machineScore++;
				showFieldNumeration();
				cout << "Machine won!" << endl;
				break;
			}

		}
		if (!checkWin())
		{
			showFieldNumeration();
			showTie();
		}
	}

	return 0;
}

void showScore()
{
	cout << "Current score machine " << machineScore << " : " << userScore << " user" << endl << endl;
}

void clear()
{
	system("cls");
}

void showFieldNumeration()
{
	clear();
	showScore();
	cout << "Numeration of field positions: " << endl;

	for (int j = 1; j < ARRAY_SIZE * ARRAY_SIZE; j += ARRAY_SIZE)
	{
		cout << " " << j << " " << "|" << " " << j + 1 << " " << "|" << " " << j + 2;
		if (j + 2 != ARRAY_SIZE * ARRAY_SIZE)
			cout << endl << " ---------" << endl;
	}
	cout << endl;

	showField();
}

void showField()
{
	cout << "\nActual game field: " << endl;

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		for (int j = 0; j < ARRAY_SIZE; j++)
		{
			cout << " " << symbols[field[i][j]];
			if (j != ARRAY_SIZE - 1)
				cout << " |";
		}
		if (i != ARRAY_SIZE - 1)
			cout << endl << " ---------" << endl;
	}
	cout << endl << endl;
}

void printMachineTurn(int cell)
{
	cout << "Machine put \"" << symbols[computerSign()] << "\" into " << cell << " cell." << endl;
}

int computerSign()
{
	if (counter % 2 != 0)
		return CROSSES;
	else
		return ZERO_NUMBER;
}

int userSign()
{
	if (counter % 2 == 0)
		return CROSSES;
	else
		return ZERO_NUMBER;
}

int checkPreWinLose(int sign)
{
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		for (int j = 0; j < ARRAY_SIZE; j++)
		{
			if (field[i][j] == 0)
			{
				field[i][j] = sign;
				if (checkWin())
				{
					field[i][j] = 0;
					return j + i * 3 + 1;
				}
				field[i][j] = 0;
			}
		}
	}
	return 0;
}

bool checkWin()
{
	int sumRow = 0;
	int sumColumn = 0;
	int sumDiagonal1 = 0;
	int sumDiagonal2 = 0;

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		sumRow = 0;
		sumColumn = 0;

		sumDiagonal1 += field[i][i];
		sumDiagonal2 += field[i][ARRAY_SIZE - i - 1];
		for (int j = 0; j < ARRAY_SIZE; j++)
		{
			sumRow += field[i][j];
			sumColumn += field[j][i];
		}
		if (sumRow == 3 or sumRow == 12 or sumColumn == 3 or sumColumn == 12)
		{
			return true;
		}
	}
	if (sumDiagonal1 == 3 or sumDiagonal1 == 12 or sumDiagonal2 == 3 or sumDiagonal2 == 12)
	{
		return true;
	}

	return false;
}

void machineFirstTurn(int machineCrossCounter)
{
	int random = 0;
	srand(time(NULL));

	if (machineCrossCounter == 1)
	{
		changeCell(5, computerSign());
		computerChoice = 5;
	}
	else
	{
		random = rand() % 4 + 1;
		computerChoice = GOOD[random - 1];
		changeCell(computerChoice, computerSign());
		Sleep(2000);
	}
}

void machineTurn()
{
	int random = 0;
	srand(time(NULL));
	
	do
	{
		if (checkPreWinLose(computerSign()))
		{
			random = checkPreWinLose(computerSign());
		}
		else if (checkPreWinLose(userSign()))
		{
			random = checkPreWinLose(userSign());
		}
		else if (emptyCellCheck(CENTRAL_NUMBER))
		{
			random = CENTRAL_NUMBER;
		}
		else if (checkTrap())
		{
			random = BAD[rand() % 4];
		}
		else if (getGoodCell() != 0)
		{
			random = getGoodCell();
		}
		else
		{
			random = rand() % 9 + 1;
		}
	} while (!emptyCellCheck(random));

	computerChoice = random;
	changeCell(random, computerSign());
	Sleep(2000);
}

void showIntro()
{
	cout << "Welcome to the tic-tac toe" << endl << endl;
	cout << "Game " << gameCounter << "!" << endl;
	cout << "__________________________" << endl;
	cout << "Select your side: \n1. Crosses \n2. Zeros" << endl;
}

void userTurn()
{
	int userTurnChoice = 0;

	cout << "It's your turn" << endl;

	do
	{
		cout << "Input number of the cell: ";
		cin >> userTurnChoice;

		if (userTurnChoice < 1 or userTurnChoice > ARRAY_SIZE * ARRAY_SIZE)
		{
			printError(ARRAY_SIZE * ARRAY_SIZE);
			continue;
		}

		if (!emptyCellCheck(userTurnChoice))
		{
			cout << "Cell already occupied" << endl;
			cout << "Try another cell" << endl;
		}

	} while (!emptyCellCheck(userTurnChoice) or userTurnChoice < 1 or userTurnChoice > ARRAY_SIZE * ARRAY_SIZE);

	if (counter % 2 != 0)
	{
		changeCell(userTurnChoice, 1);
	}
	else
	{
		changeCell(userTurnChoice, ZERO_NUMBER);
	}
}

void printError(int maxChoice)
{
	cout << "Error! Input [1.." << maxChoice << "]" << endl;
}

void showTie()
{
	cout << "The game is over, tie" << endl;
}

void changeCell(int userTurnChoice, int valueNumber)
{
	int row = (userTurnChoice - 1) / ARRAY_SIZE;
	int column = (userTurnChoice - 1) % ARRAY_SIZE;

	field[row][column] = valueNumber;
}

int getGoodCell()
{
	int goodSize = sizeof(GOOD) / sizeof(GOOD[0]);

	for (int i = 0; i < goodSize; i++)
	{
		if (emptyCellCheck(GOOD[i]))
			return GOOD[i];
	}

	return 0;
}

bool checkTrap()
{

	bool trap = false;
	int columnSum = 0;
	int columnSum3 = 0;

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		columnSum += field[i][0];
		columnSum3 += field[i][ARRAY_SIZE - 1];
	}

	if (columnSum == 1 and columnSum3 == 1)
	{
		trap = true;
	}

	return trap;
}

bool emptyCellCheck(int userTurnChoice)
{
	bool emptyCell = true;
	int row = (userTurnChoice - 1) / ARRAY_SIZE;
	int column = (userTurnChoice - 1) % ARRAY_SIZE;

	if (field[row][column] != 0)
	{
		emptyCell = false;
	}

	return emptyCell;
}
