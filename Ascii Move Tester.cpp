// Ascii Move Tester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int main()
{

    char move;
    while (1)
    {
        cout << "Make a Move 1-9\n";
        cin >> move;
        int test = (int)move;
        if (test < 49 || test > 57)
        {
            cout << "Dumbass\n";
            // https://www.cplusplus.com/forum/beginner/48568/
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            int val = move - '0';
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    cout << "Move Made = " << move;
}

