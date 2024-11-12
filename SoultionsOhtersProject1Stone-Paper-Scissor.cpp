#include <iostream>
#include <cstdlib>
using namespace std;

enum enGameChoice
{
	Stone = 1,
	Paper = 2,
	Scorsese = 3
};
enum enWinner
{
	Player = 1,
	Computer = 2,
	Draw = 3
};

struct strRoundInfo
{
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string NameWinner;
};
struct strGameResult
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};
short RandomNumber(short From, short To)
{
	return rand() % (To - From + 1) + From;
}
string WinnerName(enWinner Winner)
{
	string ArrWinnerName[3] = {"Player1", "Computer", "No Winner"};
	return ArrWinnerName[Winner - 1];
}
enWinner WhoWonThrRound(strRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
	{
		return Draw;
	}
	switch (RoundInfo.PlayerChoice)
	{
	case Stone:
		if (RoundInfo.ComputerChoice == Paper)
		{
			return Computer;
		}
		break;
	case Paper:
		if (RoundInfo.ComputerChoice == Scorsese)
		{
			return Computer;
		}
		break;
	case Scorsese:
		if (RoundInfo.ComputerChoice == Stone)
		{
			return Computer;

		}
		break;
	}
	return Player;
}
string ChoiceName(enGameChoice Choice)
{
	string ArrGameChoice[3] = {"Stone", "Paper", "Scissors"};
	return ArrGameChoice[Choice - 1];
}
void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case Player:
		system("color 2F");
		break;
	case Computer:
		system("color 4F");
		cout << "\a";
		break;
	default:
		system("color 6F");
		break;
	}
}
void PrintRoundResult(strRoundInfo RoundInfo)
{
	cout << "\n_________________Round [" << RoundInfo.RoundNumber << "]_______________\n\n";
	cout << "Player1 Choice : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer choice :  " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Winner Rounds : " << RoundInfo.NameWinner << endl;
	cout << "_____________________________________\n\n";
	cout << endl;

	SetWinnerScreenColor(RoundInfo.Winner);
}
enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return Player;
	else if (ComputerWinTimes > Player1WinTimes)
		return Computer;
	else
		return Draw;
}
strGameResult FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	strGameResult GameResults;
	GameResults.GameRounds = GameRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);
	return GameResults;
}
enGameChoice ReadPlayer1Choice()
{
	short Choice = 0;
	do
	{
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
		cin >> Choice;
	} while (Choice < 1 || Choice > 3);
	return (enGameChoice)Choice;
}
enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}
strGameResult PlayGame(short HowManyRounds)
{
	strRoundInfo RoundInfo;
	short PlayerWonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;
	for (short i = 1; i <= HowManyRounds; i++)
	{
		cout << "____________[" << i << "]------------ Begin" << endl;
		RoundInfo.RoundNumber = i;
		RoundInfo.PlayerChoice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonThrRound(RoundInfo);
		RoundInfo.NameWinner = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == Player)
		{
			PlayerWonTimes++;
		}
		else if (RoundInfo.Winner == Computer)
		{
			ComputerWonTimes++;
		}
		else
		{
			DrawTimes++;
		}
		PrintRoundResult(RoundInfo);
	}
	return FillGameResults(HowManyRounds, PlayerWonTimes, ComputerWonTimes, DrawTimes);
}
string Tabs(short NumberOfTabs)
{
	string t = "";
	for (int i = 1; i <= NumberOfTabs; i++)
	{
		t = t + "\t";
	}
	return t;
}
void ShowGameOverScreen()
{
	cout << Tabs(2) << "__________________________________________________________\n\n";
	cout << Tabs(2) << " +++ G a m e O v e r ++ +\n ";
	cout << Tabs(2) << "__________________________________________________________\n\n";
}
void ShowFinalGameResults(strGameResult GameResults)
{
	cout << Tabs(2) << "_____________________ [Game Results]_____________________\n\n";
	cout << Tabs(2) << "Game Rounds : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player1 won times : " << GameResults.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer won times : " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw times : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "___________________________________________________________\n";
	SetWinnerScreenColor(GameResults.GameWinner);
}
short ReadHowManyRounds()
{
	short GameRounds = 0;
	do
	{
		cout << "How Many Rounds 1 to 10 ? \n";
		cin >> GameRounds;
	} while (GameRounds < 1 || GameRounds > 10);
	return GameRounds;
}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		strGameResult GameResult = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResult);

		cout << Tabs(2) << "Do you want Play Again Y/N ? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{

	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}
