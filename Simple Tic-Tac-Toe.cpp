// Simple Tic-Tac-Toe.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <random>
#include <ctime>

using namespace std;

mt19937 mt(time(nullptr));
struct winner { bool check; int player; };

int Turn(int errCnt);
winner CompTurn(int gamestate[]);
winner HumanTurn(int gamestate[]);
winner CheckWin(int gamestate[]);
void Victor(int win);
void BoardState(int gamestate[]);
void FinalBoardState(int gamestate[]);

int main()
{
    // null for nullptr?
    int gameState[10] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, NULL };
    winner victor;
    victor.check = false;
    victor.player = 2;
    int errCnt = 0;
    int starter = Turn(errCnt);
    cout << "Player = X, AI = O\n";
    if (starter == '3')
    {
        int ran = mt() % 2 + 1;
        switch (ran)
        {
        case 1:          //setting cases to equal the expected outputs seems to keep things stable
            victor = CompTurn(gameState);
            break;

        case 2:
            victor = HumanTurn(gameState);
            break;
        }
        //Victor(victor.player);
    }
    switch (starter)
    {
    case '1':          //setting cases to equal the expected outputs seems to keep things stable
        victor = CompTurn(gameState);
        break;

    case '2':
        victor = HumanTurn(gameState);
        break;
    }
    // For some reason, Victor() isn't working
    Victor(victor.player);
}

int Turn(int errCnt)
{
    char start;       //setting this to a char prevented the string error
    errCnt++;
    cout << "Who will go first? 1 = Ai; 2 = Player; 3 = Random\n";
    cin >> start;

    if (errCnt >= 10)
    {
        // exit(84840);
        exit(1491149029);
    }
    if (start == '1' || start == '2' || start == '3')
    {
        return start;
    }
    else
    {
        cout << "Invalid Input. Type Again.\n";
        Turn(errCnt);
    }
}

winner CompTurn(int gamestate[])
{
    int i = 0;
    int n = 3;
    int move;
    winner cvictor;
    cvictor.check = false;
    cvictor.player = 2;
    winner test;
    test.check = false;
    test.player = 2;
    //cout << "Current Board\n";
    //while (n < 9)
    //{
    //    for (i; i < n; i++)
    //    {
    //        switch (gamestate[i])
    //        {
    //        case 0:
    //            cout << "O";
    //            break;
    //        case 1:
    //            cout << "X";
    //            break;
    //        case 2:
    //            cout << " ";
    //            break;
    //        }
    //        cout << "\n";
    //    }
    //    n += 3;
    //}
    //cout << "Make a Move [1-9]\n";
    //cin >> move;
    move = mt() % 9;
    //move--;
    if (gamestate[move] == 0 || gamestate[move] == 1)
    {
        //  cout << "Move Already Made\n";
        cvictor = CompTurn(gamestate);
    }
    else
    {
        gamestate[move] = 0;
        test = CheckWin(gamestate);
        if (test.check)
        {
            cvictor = test;
            cout << "Final Board State\n";
            FinalBoardState(gamestate);
            return cvictor;
        }
        cvictor = HumanTurn(gamestate);
    }
    return cvictor;
}

winner HumanTurn(int gamestate[])
{
    //int i = 0;
    //int n = 3;
    char moveholder;
    int movetest;
    int move;
    winner hvictor;
    hvictor.check = false;
    hvictor.player = 2;
    winner test;
    test.check = false;
    test.player = 2;
    //cout << "Current Board\n";
    //while (n < 10)
    //{
    //    for (i; i < n; i++)
    //    {
    //        switch (gamestate[i])
    //        {
    //        case 0:
    //            cout << "O";
    //            break;
    //        case 1:
    //            cout << "X";
    //            break;
    //        case 2:
    //            cout << "|";
    //            break;
    //        }
    //    }
    //    n += 3;
    //    cout << "\n";
    //}
    BoardState(gamestate);
    /*cout << "Make a Move [1-9]\n";
    cin >> move;
    move--;*/

    while (1)
    {
        cout << "Make a Move 1-9\n";
        cin >> moveholder;
        int movetest = (int)moveholder;
        if (movetest < 49 || movetest > 57)
        {
            cout << "Invalid input, try again.\n";
            BoardState(gamestate);
            // https://www.cplusplus.com/forum/beginner/48568/
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            move = movetest - '0';
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    move--;

    if (gamestate[move] == 0 || gamestate[move] == 1)
    {
        cout << "Move Already Made\n";
        hvictor = HumanTurn(gamestate);
    }
    else
    {
        gamestate[move] = 1;
        test = CheckWin(gamestate);
        if (test.check)
        {
            hvictor = test;
            cout << "Final Board State\n";
            FinalBoardState(gamestate);
            return hvictor;
        }
        hvictor = CompTurn(gamestate);
    }
    return hvictor;
}

void BoardState(int gamestate[])
{
    int i = 0;
    int n = 3;
    cout << "Current Board\n";
    while (n < 10)
    {
        for (i; i < n; i++)
        {
            switch (gamestate[i])
            {
            case 0:
                cout << "O";
                break;
            case 1:
                cout << "X";
                break;
            case 2:
                cout << "|";
                break;
            }
        }
        n += 3;
        cout << "\n";
    }
}

void FinalBoardState(int gamestate[])
{
    int i = 0;
    int n = 3;
    //    cout << "Current Board\n";
    while (n < 10)
    {
        for (i; i < n; i++)
        {
            switch (gamestate[i])
            {
            case 0:
                cout << "O";
                break;
            case 1:
                cout << "X";
                break;
            case 2:
                cout << "|";
                break;
            }
        }
        n += 3;
        cout << "\n";
    }
}

winner CheckWin(int gamestate[])
{
    winner victor;
    victor.check = false;
    victor.player = 2;
    // Comp Horizontal Test
    if ((gamestate[0] == 0 && gamestate[1] == 0 && gamestate[2] == 0) || (gamestate[3] == 0 && gamestate[4] == 0 && gamestate[5] == 0) || (gamestate[6] == 0 && gamestate[7] == 0 && gamestate[8] == 0))
    {
        victor.check = true;
        victor.player = 0;
    }
    // Comp Vertical Test
    else if ((gamestate[0] == 0 && gamestate[3] == 0 && gamestate[6] == 0) || (gamestate[1] == 0 && gamestate[4] == 0 && gamestate[7] == 0) || (gamestate[2] == 0 && gamestate[5] == 0 && gamestate[8] == 0))
    {
        victor.check = true;
        victor.player = 0;
    }
    // Comp Diagonal Test
    else if ((gamestate[0] == 0 && gamestate[4] == 0 && gamestate[8] == 0) || (gamestate[2] == 0 && gamestate[4] == 0 && gamestate[6] == 0))
    {
        victor.check = true;
        victor.player = 0;
    }
    // Human Horizontal Test
    else if ((gamestate[0] == 1 && gamestate[1] == 1 && gamestate[2] == 1) || (gamestate[3] == 1 && gamestate[4] == 1 && gamestate[5] == 1) || (gamestate[6] == 1 && gamestate[7] == 1 && gamestate[8] == 1))
    {
        victor.check = true;
        victor.player = 1;
    }
    // Human Vertical Test
    else if ((gamestate[0] == 1 && gamestate[3] == 1 && gamestate[6] == 1) || (gamestate[1] == 1 && gamestate[4] == 1 && gamestate[7] == 1) || (gamestate[2] == 1 && gamestate[5] == 1 && gamestate[8] == 1))
    {
        victor.check = true;
        victor.player = 1;
    }
    // Human Diagonal Test
    else if ((gamestate[0] == 1 && gamestate[4] == 1 && gamestate[8] == 1) || (gamestate[2] == 1 && gamestate[4] == 1 && gamestate[6] == 1))
    {
        victor.check = true;
        victor.player = 1;
    }
    // Draw Test
    else
    {
        bool DrawTest = true;
        for (int i = 0; i < 9; i++)
        {
            if (gamestate[i] == 2)
            {
                DrawTest = false;
            }
        }
        if (DrawTest)
        {
            cout << "Final Board State\n";
            FinalBoardState(gamestate);
            cout << "The Game is a Draw.\n";
            exit(NULL);
        }
    }
    return victor;
}

void Victor(int win)
{
    switch (win)
    {
    case 0:
        cout << "You Lose!\n";
        break;
    case 1:
        cout << "You Win!\n";
        break;
    }
}