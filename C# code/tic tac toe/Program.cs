using System;
namespace tic_tac_toe
{
    static class ttt // TIC TAC TOE
    {
        static int moves;
        static int[,] a;
        static void instructions()//prints instructions for game
        {
            Console.WriteLine("Here are the numbers for placing your move (you are O)");
            Console.WriteLine("[1][2][3]");
            Console.WriteLine("[4][5][6]");
            Console.WriteLine("[7][8][9]");
            Console.WriteLine("< type 'x' to end game >");
        }
        static void show()
        {
            Console.WriteLine("\n<your move>");
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                    if (a[i, j] == -1)
                        Console.Write("[X]");
                    else
                    if (a[i, j] == 1)
                        Console.Write("[O]");
                    else
                        Console.Write("[ ]");
                
                Console.WriteLine("");
            }
        }
        static int gameover() //checks if any row column or cross connects to 3
        {

            int i, j;
            for (i = 0; i < 3; i++)           
                if (a[i, 0] + a[i, 1] + a[i, 2] == 3||a[i, 0] + a[i, 1] + a[i, 2] == -3)//checking horizontal
                    return a[i, 0] + a[i, 1] + a[i, 2];
                else if (a[0, i] + a[1, i] + a[2, i] == 3||a[0, i] + a[1, i] + a[2, i] == -3)//checking vertical
                    return a[0, i] + a[1, i] + a[2, i];
            
            if (a[0, 0] + a[1, 1] + a[2, 2] == 3|| a[0, 0] + a[1, 1] + a[2, 2] == -3)//checking diagonal L->R
                return a[0, 0] + a[1, 1] + a[2, 2];

            if (a[0, 2] + a[1, 1] + a[2, 0] == 3|| a[0, 2] + a[1, 1] + a[2, 0] == -3)//checking diagonal R->L
                return a[0, 2] + a[1, 1] + a[2, 0];

            return 1;// no one has won yet all clear for next move
        }
        static int bot_move()
        {
            int i, j, k;
            for (i = 0; i < 3; i++)
            {
                if (a[i, 0] + a[i, 1] + a[i, 2] == -2)//to win first (horizontal)
                {
                    for (k = 0; k < 3; k++)
                        if (a[i, k] == 0)
                        {
                            a[i, k] = -1;
                            return 1;
                        }
                    break;
                }
            }

            for (j = 0; j < 3; j++)
            {
                if (a[0, j] + a[1, j] + a[2, j] == -2)// //puts X to complete of block (vertical)
                {
                    for (k = 0; k < 3; k++)
                        if (a[k, j] == 0)
                        {
                            a[k, j] = -1;
                            return 1;
                        }
                    break;
                }
            }
            if (a[0, 0] + a[1, 1] + a[2, 2] == -2)//diagonal L->R
            {
                for (k = 0; k < 3; k++)
                    if (a[k, k] == 0)
                    {
                        a[k, k] = -1;
                        return 1;
                    }
            }
            for (j = 0; j < 3; j++)
            {
                if (a[0, j] + a[1, j] + a[2, j] == 2)// //puts X to complete of block (vertical)
                {
                    for (k = 0; k < 3; k++)
                        if (a[k, j] == 0)
                        {
                            a[k, j] = -1;
                            return 1;
                        }
                    break;
                }
            }
            for (i = 0; i < 3; i++)
            {
                if (a[i, 0] + a[i, 1] + a[i, 2] == 2) //puts X to complete of block (horizontal)
                {
                    for (k = 0; k < 3; k++)
                        if (a[i, k] == 0)
                        {
                            a[i, k] = -1;
                            return 1;
                        }
                    break;
                }
            }
            if (a[0, 0] + a[1, 1] + a[2, 2] == 2)//diagonal L->R
            {
                for (k = 0; k < 3; k++)
                    if (a[k, k] == 0)
                    {
                        a[k, k] = -1;
                        return 1;
                    }
            }
            if (a[0, 2] + a[1, 1] + a[2, 0] == -2)//diagonal R->L
            {
                for (k = 0; k < 3; k++)
                    if (a[k, 2 - k] == 0)
                    {
                        a[k, 2 - k] = -1;
                        return 1;
                    }
            }
            if (a[0, 2] + a[1, 1] + a[2, 0] == 2)//diagonal R->L
            {
                for (k = 0; k < 3; k++)
                    if (a[k, 2 - k] == 0)
                    {
                        a[k, 2 - k] = -1;
                        return 1;
                    }
            }

        again:;
            Random rnd = new Random();
            i = rnd.Next(3); j = rnd.Next(3);
            if (a[i, j] != 0)
                goto again;
            a[i, j] = -1;
            return 1;

        }
        static int player_move()
        {

          while(true)
          {    
            Console.WriteLine("enter move number=>");
            int move = (int)(Console.ReadKey().KeyChar - '0'); //converts char to int using ascii
                if (move == 72)
                    return -1;
            if (move < 10 && move > 0 && a[(move - 1) / 3, (move - 1) % 3]==0)
            {
                a[(move-1) / 3, (move - 1) % 3] = 1;
                break;
            }
                Console.WriteLine("\ninvalid move!");

          }

            return 1;
        }
        static public void run_game()
        {
         restart:;
            moves = 0;
            Console.Clear();
            a = new int[9, 9];
            int  i, j;
            instructions();
            for (i = 0; i < 3; i++)
                for (j = 0; j < 3; j++)
                    a[i, j] = 0;
            while (gameover() == 1)//check if someone won or tied
            {
                show();
                if (player_move() == -1)
                {
                    Console.WriteLine("\ngame has been ended !");
                    goto ended;
                }
                Console.Clear();
                if (gameover() != 1)
                    break;
                bot_move();
            }
            show();
            if (gameover() == -3)
                Console.WriteLine("bot wins! gg");
            else
            if (gameover() == 3)
                Console.WriteLine("you win...this time gg");

            else
                Console.WriteLine("it's a tie! better luck next time champ gg");

            ended:;
            Console.WriteLine("Press 'f' to play again or press any other key to exit...");
            if(Console.ReadKey().KeyChar== 'f')
                goto restart;
            

        }
    }
    class Program
    {
        static void Main(string[] args)
        {
              ttt.run_game();
        }
    }
}
