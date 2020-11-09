#include<iostream>
///#include<Windows.h> use if sleep function in required
using namespace std;
class queen_info
{
public:
	int xy;
	queen_info* link;
};

float board[9][10];

void show(float board[9][10], queen_info* stand_by_list, queen_info* board_list) //shows visually where queens are placed 
{
	queen_info* temp1 = stand_by_list;
	queen_info* temp2 = board_list;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j++)
			if ((i == 0 || j == 0 || j == 9) && int(board[i][j] * 10) % 10 != 0 && int(board[i][j] * 100) % 10 == 0)
				cout << "[" << board[i][j] << "0]";
			else if ((i == 0 || j == 0 || j == 9) && int(board[i][j] * 10) % 10 == 0 && int(board[i][j] * 100) % 10 == 0)
				cout << "[" << board[i][j] << ".00]";
			else if ((i == 0 || j == 0 || j == 9) && int(board[i][j] * 100) % 10 != 0)
				cout << "[" << board[i][j] << "]";
			else if (board[i][j] != 0)
				cout << "[  " << board[i][j] << " ]";
			else
				cout << "[    ]";
		cout << "     " << endl;
	}
	while (temp1->link != NULL)
	{
		cout << temp1->xy << " ";
		temp1 = temp1->link;
	}cout << "          " << endl;
	cout << "cordinates xy= ";
	while (temp2 != NULL)
	{
		cout << temp2->xy << " ";
		temp2 = temp2->link;
	}cout << "          ";
}

int main()
{
	queen_info* stand_by_list; //list of queens not on board
	queen_info* stand_end; //end pointer of stand_by_list

	queen_info* board_list = NULL;//list of queens on the board
	queen_info* board_end = NULL;//end pointer of board_lsit


	int i, j, space = 1,//tells id there is space to put queen
		not_place[8], not_p = 0,//which positions not to place queen at
		number_of_queens = 8;

	stand_by_list = new queen_info;
	stand_end = stand_by_list;

	for (i = 0; i < number_of_queens + 1; i++)//assigning number_of_queens (+1 for NULL link) to the stand_by_list 
	{
		stand_end->xy = -1;
		if (i != number_of_queens)
		{
			stand_end->link = new queen_info;
			stand_end = stand_end->link;
		}
		else
		{
			stand_end->link = NULL; break;
		}
	}//creating list of queens NOT on board

	while (stand_by_list->link != NULL) //keeps executing till no queen is left 
	{
		for (i = 1; i <= 9; i++)
		{
			if (i == 9) //if no position is available to place a queen
			{
				space = 0;
				break;
			}
			if (int(board[i][0]) == 0)//if row i has no queen in it
			{
				for (j = 1; j <= 9; j++)
				{
					if (j == 9)// if no place horizontally is avaiable in the given row 
					{
						space = 0;
						break;
					}
					if (int(board[0][j]) == 0) //the column has no queen in it
					{
						int mod = i - j;
						if (board[i][j] == 0 && (mod <= 0 && int(board[0][mod * -1] * 10) % 10 == 0) || (mod > 0 && int(board[mod][0] * 10) % 10 == 0))//checks if L-> R diagonal is clear for a given i,j co ordinate
						{
							mod = i + j - 9;
							if ((mod <= 0 && int(board[0][9 + mod] * 100) % 10 == 0) || (mod > 0 && int(board[mod][9] * 100) % 10 == 0)) // checks if L<-R diagonal is clear for a given i, j co ordinate
							{
								board[i][j] = 2; //assigns a queen
								stand_by_list->xy = i * 10 + j;

								///////////////transfers queen from stand_by_list to board_list///////////
								if (board_list == NULL)
								{
									board_list = stand_by_list;
									board_end = board_list;

									stand_by_list = stand_by_list->link;
									board_list->link = NULL;
								}
								else
								{
									board_end->link = stand_by_list;
									stand_by_list = stand_by_list->link;
									board_end = board_end->link;
									board_end->link = NULL;
								}
								///////////////////////////////////////////////////////////////////////

								board[i][0] += 1;//+ assigns 1 to the row in which queen belongs 
								board[0][j] += 1; //+ assigns 1 to the column in which queen belongs (this is done so that no other queen can be placed in this row or column)

								mod = i - j;  //  L->R
								(mod <= 0 ? board[0][j - i] = (board[0][j - i] * 10 + 1) / 10 : board[i - j][0] = (board[i - j][0] * 10 + 1) / 10);//+ assigns 0.1 to signal L->R diagonal is taken 

								mod = i + j - 9;//L <-R
								(mod <= 0 ? board[0][9 + mod] = (board[0][9 + mod] * 100 + 1) / 100 : board[mod][9] = (board[mod][9] * 100 + 1) / 100);//+ assigns 0.01 to signal L<-R diagonal is taken 
								space = 1;
								goto out;
							}
						}
					}
				}
			}
		}
	out:;
		if (space == 0)//if no space is available to place a new queen then one old queen is removed and checked if a new queen can be placed anywhere other than the place where the old queen was just removed from
		{
			not_place[not_p] = board_list->xy;
			not_p++;

			i = board_list->xy / 10; j = board_list->xy % 10;

			queen_info* temp = board_list;
			board_list = board_list->link;
			delete temp;

			stand_end->link = new queen_info;
			stand_end = stand_end->link;
			stand_end->xy = -1;
			stand_end->link = NULL;

			board[i][j] = 1;

			int mod = i - j;
			(mod <= 0 ? board[0][mod * -1] = (board[0][mod * -1] * 10 - 1) / 10 : board[mod][0] = (board[mod][0] * 10 - 1) / 10);

			mod = i + j - 9;
			(mod <= 0 ? board[0][9 + mod] = (board[0][9 + mod] * 100 - 1) / 100 : board[mod][9] = (board[mod][9] * 100 - 1) / 100);

			board[0][j] -= 1; board[i][0] -= 1;
		}
		else
			for (i = 0; i < not_p; i++)
				board[not_place[i] / 10][not_place[i] % 10] = 0;

		system("cls");
		show(board, stand_by_list, board_list); //displays the action going on
		//Sleep(500); use this function incase code is too fastly executed to be seen
	}
	cout << "success!" << endl;
exit:;
	system("pause");
}