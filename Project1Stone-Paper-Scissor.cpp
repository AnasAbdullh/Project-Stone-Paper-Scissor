#include <iostream>
#include <cstdlib>
using namespace std;

enum enGameStPaSc
{
    stone = 1,
    Paper = 2,
    Scissors = 3
};

enum enStatus
{
    Draw = 1,
    Player = 2,
    Computer = 3,
    NotWinner = 4
};

struct strProject1Stone
{
    int Player1Won = 0;
    int ComputerWon = 0;
    int DrawTimes = 0;
    int Rounds = 0;
   
};

short AskToUserHowManyRoundsTheGame()
{
    short Rounds;
    cout << "How Many Rounds In The Game ? " << endl;
    cin >> Rounds;
    return Rounds;
}

int RandomNumber(int from, int to)
{
  int RandNumber = rand() % (to - from + 1) + from;
  return RandNumber;
}

void NumberRoundBegins(short Number)
{
    cout << "Round [" << Number << "]" << " begins :\n";
}

int  PlayerChoice()
{
    int PlayerChoice = 0;
    do
    {
    cout << "\nYour choice : [1]:Stone, [2]:Paper, [3]:Scissors ?";
    cin >> PlayerChoice;

    } while (PlayerChoice <= 0 || PlayerChoice > 3);
    return PlayerChoice;
}

int ComputerChoice()
{
   int ComputerChoice;
   ComputerChoice = RandomNumber(1, 3);
   return ComputerChoice;
}

enGameStPaSc checkChoice(int Number)
{
    if (Number == 1)
    {
        return enGameStPaSc::stone;
    }
    else if (Number == 2)
    {
        return enGameStPaSc::Paper;
    }
    else if (Number == 3)
    {
        return enGameStPaSc::Scissors;
    }
}

string PrintChoice(int Number)
{
    enGameStPaSc choice = checkChoice(Number);

    if (choice == 1)
      return  "Stone" ;
    else if (choice == 2)
        return "Paper" ;
    else if (choice == 3)
       return "Scissors" ;
}

enStatus SelectWin(int ChoicePlayer , int ChoiceComputer)
{
    if (ChoicePlayer == ChoiceComputer)
    {
        return enStatus::Draw;
    }
    else if (ChoicePlayer == 2 && ChoiceComputer == 1 )
    {
        return enStatus::Player;
    }
    else if (ChoicePlayer == 3 && ChoiceComputer == 2)
    {
        return enStatus::Player;
    }
    else if (ChoicePlayer == 1 && ChoiceComputer == 2)
    {
        return enStatus::Computer;
    }
    else if (ChoicePlayer == 1 && ChoiceComputer == 3)
    {
        return enStatus::Player;
    }
    else if (ChoicePlayer == 1 && ChoiceComputer == 2)
    {
        return enStatus::Computer;
    }
    else if (ChoicePlayer == 3 && ChoiceComputer == 1)
    {
        return enStatus::Computer;
    }
}

string PrintWin(enStatus win)
{

    if (win == enStatus::Computer)
    {
        return "Computer ";
    }
    else if (win == enStatus::Player)
    {
         return "Player" ;
    }
    else if (win == enStatus::Draw)
    {
       return  "Not winner";
    }
}

void ColorChoice(enStatus choice)
{
    if (choice == enStatus::Draw)
    {
        system("color 6F");
    }
    else if (choice == enStatus::Player)
    {
        system("color 2F");
    }
    else if (choice == enStatus::Computer)
    {
        system("echo \a");
        system("color 4F");
    }
}

void PrintLineRound(int Number)
{
    cout << "\n_______________Round [" << Number << "] ________________" << endl;
    cout << "\n";
} 
int CalculateResultFinally(enStatus win, strProject1Stone &result)
{
    if (win == enStatus::Draw)
    {
        return result.DrawTimes++;
    } else if  (win == enStatus::Player)
    {
        return result.Player1Won++;
    }
    else if (win == enStatus::Computer)
    {
        return result.ComputerWon++;
    }
}

void PrintResult(int ChoicePlayer , int ChoiceComputer , strProject1Stone &win)
{
   
    cout << "Player Choice   : " << PrintChoice (ChoicePlayer) << endl;
    cout << "Computer Choice : " << PrintChoice (ChoiceComputer) << endl;
    cout << "Round Winner    : " << PrintWin(SelectWin(ChoicePlayer , ChoiceComputer)) << endl;
    ColorChoice(SelectWin(ChoicePlayer , ChoiceComputer));
    CalculateResultFinally(SelectWin(ChoicePlayer, ChoiceComputer), win);
}

void PrintAndDownLine()
{
    cout << "_________________________________________" << endl;
    cout << "\n";
}

void CheckRound(strProject1Stone& win)
{
  win.Rounds = AskToUserHowManyRoundsTheGame();

    for (size_t i = 1; i <= win.Rounds; i++)
    {
        NumberRoundBegins(i);
        int player = PlayerChoice();
        PrintLineRound(i);
        PrintResult(player, ComputerChoice(), win);
        PrintAndDownLine();

    }
}
string  FinalWinner(strProject1Stone Final)
{
    if (Final.Player1Won  > Final.ComputerWon)
    {
        return "Player";
    }
    else if (Final.Player1Won < Final.ComputerWon) 
    {
        return "Computer";
    }
    else if (Final.Player1Won == Final.ComputerWon)
    {
        return "Not Winner";
    }
}

void PrintGameResults(strProject1Stone result)
{
    cout << "\t\t\t______________________________________________________" << endl;
    cout << "\n";
    cout << "\t\t\t\t\t +++ G a m e O v e r +++" << endl;
    cout << "\n";
    cout << "\t\t\t_______________________________________________________" << endl;
    cout << "\n";
    cout << "\t\t\t____________________[ Game Result ] ___________________" << endl;
    cout << "\t\t\t Game Rounds         : " << result.Rounds << endl;
    cout << "\t\t\t player won times    : " << result.Player1Won << endl;
    cout << "\t\t\t Computer  won times : " << result.ComputerWon << endl;
    cout << "\t\t\t Draw times          : " << result.DrawTimes << endl;
    cout << "\t\t\t Final Winner        : " << FinalWinner(result) << endl; 
    cout << "\t\t\t_______________________________________________________" << endl;
    cout << "\n";

} void RestScreen()
{
    system("cls");
    system("color 0F");
}

void AskPlayAgain(strProject1Stone &Again)
{
    string again;
    cout << "\t\t\tDo you want to play again ? Y/N ? ";
    cin >> again;
    cout << "\n";

    if (again == "Y" || again == "y")
    {
        Again.ComputerWon = 0;
        Again.DrawTimes = 0;
        Again.Player1Won = 0;
        Again.Rounds = 0;
        RestScreen();
       
        CheckRound(Again);
        PrintGameResults(Again);
        AskPlayAgain(Again);

    }
    else if (again == "N" || again == "n")
    {
        
    }
   
} 
void StartGame()
{
 
    strProject1Stone result;
    CheckRound(result);
    PrintGameResults(result);
    AskPlayAgain(result);
}



int main(int argc, char const *argv[])
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}