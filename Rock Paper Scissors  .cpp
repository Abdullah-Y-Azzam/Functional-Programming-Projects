#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner RoundWinner;
	string WinnerName = "";
};
struct stGameResults
{
	short GameRounds = 0;
	short Player1WonTimes = 0;
	short ComputerWonTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

int ReadHowManyRounds()
{
	int NumberOfRounds = 0;
	
	cout << "How many Rounds 1 to 10\n";
	cin >> NumberOfRounds;
	 
	return NumberOfRounds;
}

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

void SetScreenColor(stRoundInfo RoundInfo)
{
	switch (RoundInfo.RoundWinner)
	{
	case Player1:
		system("color 2F");
		break;
	case Computer:
		system("color 4F");
		cout << "\a";
		break;
	case Draw:
		system("color 6F");
		break;
	}
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.Player1Choice)
	{
	case Stone:
		
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
	case Paper:
		
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
	case Scissors:
		
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
	}
	return enWinner::Player1;
}

enWinner WhoWonTheGame(short Player1WinTimes , short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
	{
		return enWinner::Player1;
	}
	else if (ComputerWinTimes > Player1WinTimes)
	{
		return enWinner::Computer;
	}
	else
	{
		return enWinner::Draw;
	}
}

string ChoiceName(enGameChoice Choice)
{
	string arrGameChoices[3] = { "Stone" , "Paper" , "Scissors" };
	return arrGameChoices[Choice - 1];
}

string WinnerStringName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player1" , "Computer", "No Winner (Draw)" };
	return arrWinnerName[Winner - 1];
}

enGameChoice ReadPlayer1Choice()
{
	short Choice = 1;

	cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
	cin >> Choice;

	return enGameChoice(Choice);
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
	cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
	cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
	cout << "_________________________________________\n" << endl;
}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short Player1WonTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1;  GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins:\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerStringName(RoundInfo.RoundWinner);
	
		if (RoundInfo.RoundWinner == enWinner::Player1)
			Player1WonTimes++;
		else if (RoundInfo.RoundWinner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResult(RoundInfo);
		SetScreenColor(RoundInfo);
	}
	return { HowManyRounds , Player1WonTimes , ComputerWinTimes , DrawTimes , WhoWonTheGame(Player1WonTimes , ComputerWinTimes)};
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void ShowGameOverScreen()
{
	cout << "___________________________________________\n";
	cout << "		+++ G a m e  O v e r +++            \n";
	cout << "___________________________________________\n";
}

void ShowFinalGameResult(stGameResults GameResult)
{
	cout << "________________________________[Game Results]________________________________\n\n";
	cout << "Game Rounds       : " << GameResult.GameRounds << endl;
	cout << "Player1 Won Times : " << GameResult.Player1WonTimes << endl;
	cout << "Computer Won Times: " << GameResult.ComputerWonTimes << endl;
	cout << "Draw Times        : " << GameResult.DrawTimes << endl;
	GameResult.WinnerName = WinnerStringName(GameResult.GameWinner);
	cout << "Final Winner      : " << GameResult.WinnerName << endl;
	cout << "______________________________________________________________________________\n\n";
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResult(GameResults);

		cout << "\nDo you want to play again? (Y/N): ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();

	return 0;
}