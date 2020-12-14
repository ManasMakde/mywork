#include<iostream>
#include <stdlib.h>
#include<conio.h>
#include<string>
using namespace std;
int moves = 0;
int toint(char c)
{
    return (int)(c - '0');
}
void instructions()
{
    cout<<"here are the codes for placing your move (you are O)"<<endl;
    cout<<"   0   1   2" <<endl;
    cout<<"0 [00][01][02]" <<endl;
    cout<<"1 [10][11][12]" <<endl;
    cout<<"2 [20][21][22]" <<endl;
    cout<<" for example type '11' to place in center " <<endl;
    cout << "press any key to continue...";
    _getch();
    system("cls");

}
void show(int a[][3])
{
    system("cls");
    cout<<"<your move>" <<endl;
    cout<<"   0  1  2" <<endl;
    for (int i = 0; i < 3; i++)
    {
        cout<<i << " ";
        for (int j = 0; j < 3; j++)
        {
            if (a[i][j] == -1)
                cout<<"[X]";
            else
                if (a[i][ j] == 1)
                    cout<<"[O]";
                else
                    cout<<"[ ]";
        }
        cout<<endl;
    }
}
int gameover(int a[][3]) //checks if any row column or cross connects to 3
{

    int i, j;
    for (i = 0; i < 3; i++)
    {
        if (a[i][ 0] + a[i][1] + a[i][2] == 3)
            return 3;
        if (a[i][ 0] + a[i][ 1] + a[i][ 2] == -3)//checking horizontal
            return -3;
    }
    for (j = 0; j < 3; j++)
    {
        if (a[0][ j] + a[1][ j] + a[2][ j] == 3)
            return 3;
        if (a[0][ j] + a[1][ j] + a[2][ j] == -3)//checking vertical
            return -3;
    }
    if (a[0][ 0] + a[1][ 1] + a[2][ 2] == 3)
        return 3;
    if (a[0][ 0] + a[1][ 1] + a[2][ 2] == -3)//diagonal L->R
        return -3;
    if (a[0][ 2] + a[1][ 1] + a[2][ 0] == 3)
        return 3;
    if (a[0][ 2] + a[1][ 1] + a[2][ 0] == -3)//diagonal R->L
        return -3;

    return 1;// no one has won yet all clear for next move
}
int bot_move(int a[][3],  int &moves)
{
    moves++;
    if (moves == 5)
        return -1;
    int i, j, k;
    for (i = 0; i < 3; i++)
    {
        if (a[i][ 0] + a[i][ 1] + a[i][ 2] == -2)//to win first (horizontal)
        {
            for (k = 0; k < 3; k++)
                if (a[i][ k] == 0)
                {
                    a[i][ k] = -1;
                    return 1;
                }
            break;
        }
    }

    for (j = 0; j < 3; j++)
    {
        if (a[0][ j] + a[1][ j] + a[2][ j] == -2)// //puts X to complete of block (vertical)
        {
            for (k = 0; k < 3; k++)
                if (a[k][ j] == 0)
                {
                    a[k][ j] = -1;
                    return 1;
                }
            break;
        }
    }
    if (a[0][ 0] + a[1][ 1] + a[2][ 2] == -2)//diagonal L->R
    {
        for (k = 0; k < 3; k++)
            if (a[k][ k] == 0)
            {
                a[k][ k] = -1;
                return 1;
            }
    }
    for (j = 0; j < 3; j++)
    {
        if (a[0][ j] + a[1][ j] + a[2][ j] == 2)// //puts X to complete of block (vertical)
        {
            for (k = 0; k < 3; k++)
                if (a[k][ j] == 0)
                {
                    a[k][ j] = -1;
                    return 1;
                }
            break;
        }
    }
    for (i = 0; i < 3; i++)
    {
        if (a[i][ 0] + a[i][ 1] + a[i][ 2] == 2) //puts X to complete of block (horizontal)
        {
            for (k = 0; k < 3; k++)
                if (a[i][ k] == 0)
                {
                    a[i][ k] = -1;
                    return 1;
                }
            break;
        }
    }
    if (a[0][ 0] + a[1][ 1] + a[2][ 2] == 2)//diagonal L->R
    {
        for (k = 0; k < 3; k++)
            if (a[k][ k] == 0)
            {
                a[k][ k] = -1;
                return 1;
            }
    }
    if (a[0][ 2] + a[1][ 1] + a[2][ 0] == -2)//diagonal R->L
    {
        for (k = 0; k < 3; k++)
            if (a[k][ 2 - k] == 0)
            {
                a[k][ 2 - k] = -1;
                return 1;
            }
    }
    if (a[0][ 2] + a[1][ 1] + a[2][ 0] == 2)//diagonal R->L
    {
        for (k = 0; k < 3; k++)
            if (a[k][ 2 - k] == 0)
            {
                a[k][ 2 - k] = -1;
                return 1;
            }
    }

again:;
    i = rand()%3; j = rand()%3;
    if (a[i][ j] != 0)
        goto again;
    a[i][ j] = -1;
    return 1;

}
int player_move(int a[][3])
{
    string n;
    int number=33;
 invalid:;
    cout << "enter move number=>";;
    getline(cin,n);
    if(n!="")
    number = toint(n[0]) * 10 + toint(n[1]);
    if (n.length()<3 && number%10< 3&& number%10>=0 && number % 100/10 < 3 && number % 100/10 >= 0 && a[number % 100 / 10][number % 10] ==0)
        a[number % 100 / 10][number%10] = 1;
    else
    {
        cout<<"invalid move!" <<endl;
        goto invalid;
    }

    return 1;
}
void run_game()
{

    int a[3][3] = { 0 };
    int moves = 0, i, j;
    instructions();
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            a[i][ j] = 0;
    while (gameover(a) == 1)//check if someone won or tied
    {
        show(a);
        player_move(a);
        if (bot_move(a,moves) == -1)
            break;
    }
    show(a);
    if (gameover(a) == -3)
       cout<<"bot wins!";
    else
        if (gameover(a) == 3)
           cout<<"you win...this time";

        else
            cout<<"it's a tie! better luck next time champ";

ended:;
    // return latest_msg_index;
}
int main()
{
    run_game();
    _getch();
}
