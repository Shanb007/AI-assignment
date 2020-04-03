#include <bits/stdc++.h>

using namespace std;

int rand_1()
{
        int rand_1;
        rand_1=(rand()%(3-1+1)+1);
        return rand_1;
}

int user_move(int n_stick)
{
        int ch;
        cin >> ch;
        while (ch<1 || ch> 3 || n_stick - ch<= 0)
        {
                if (ch< 1 || ch> 3)
                {
                        cout << "Your choice must be between 1 and 3." << endl;
                        cout << "Enter another choice: " << endl;
                        cin >> ch;
                }
                else if (n_stick - ch<= 1)
                {
                        cout << "You must leave at least one stick." << endl;
                        cout << "Enter another choice: " << endl;
                        cin >>  ch;
                }
                return ch;
        }
        return ch;
}

int AI_move(int n_stick)
{
        int ch;
        do {
                ch = (rand_1() % 3) + 1;
        } while (n_stick - ch< 1);
        return ch;
}


int main ()
{
        srand((unsigned)time(NULL));
        bool winner = false;
        int n_stick = (rand()%(30-15+1)+15);
        int AI_moves;
        
        cout << "Welcome to the game.  There are " << n_stick <<" sticks."<< endl;;

        while (!winner)
        {

                cout <<"Enter What number of sticks would You like to take away: "<< endl;
                n_stick -= user_move(n_stick);
                cout <<"The number of sticks left are " << n_stick << ".\n\n" << endl;
                if (n_stick == 1)
                {
                        winner = true;
                        cout << "You win!" << endl;
                }
                else
                {
                        AI_moves = AI_move(n_stick);
                        n_stick -= AI_moves;
                        cout << "AI Moves " << AI_moves << endl;
                        cout << "The number of sticks left is " << n_stick << ".\n\n" << endl;
                        if (n_stick == 1)
                        {
                                winner = true;
                                cout << "Computer wins" << endl;
                        }
                }
        }
}

