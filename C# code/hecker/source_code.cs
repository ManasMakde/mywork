using System;
using System.IO;
using System.Linq;

namespace c_hash_testing
{
    static class hecker
    {
        static int[,] puzzle;
        static void print_file(string location) //print the file of given location-name
        {
                using (StreamReader sr = new StreamReader(location))
                {
                    string line;
                    while ((line = sr.ReadLine()) != null)
                    {
                        Console.WriteLine(line);
                    }
                }

        }
        static void show_puzzle()//shows the puzzle created
        {
            Random r = new Random();
            for (int i = 0; i < puzzle.GetLength(0); i++)
            {
                for (int j = 0; j < puzzle.GetLength(0); j++)
                    if (puzzle[i, j] == 0)
                        Console.Write((char)r.Next((int)'a', (int)'z'));
                    else
                        Console.Write((char)puzzle[i, j]);

                Console.Write("\n");
            }


        }
        static int put_word_at(string word)//puts word at any location within the puzzzle
        {
            Random r = new Random();
        again:;
            for (int i = r.Next(0, 1000) % (int)(puzzle.GetLength(0) / 2); i < puzzle.GetLength(0); i += 2)
                for (int j = r.Next(0, (int)(puzzle.GetLength(0) / 2)); j < (int)(puzzle.GetLength(0) / 2); j += r.Next(0, 4))
                    if (puzzle[i, j] == 0)
                    {
                        int spaces;
                        for (spaces = 1; spaces < word.Length && puzzle[i, j + spaces] == 0; spaces++) ;
                        if (spaces >= word.Length)
                        {
                            for (int l = 0; l < word.Length; l++)
                                puzzle[i, j + l] = (int)word[l];
                            return 1;
                        }
                    }

            return -1;
        }
        static void create_puzzle(string sentence)//creates the actual puzzle of the given sentence
        {

            string[] words = sentence.Split(' '); //assigns each word of the sentence into string array
            int largest = (words.OrderByDescending(n => n.Length).First().Length > words.Length ? words.OrderByDescending(n => n.Length).First().Length - 1 : words.Length);
            puzzle = new int[largest * 2, largest * 2];
            int i = 0;
            while (i < words.Length)//individually puts words into the puzzle (if they have / infront of them) using function put_word_at()
            {
                if (words[i] != "" && words[i][0] == '/')
                {
                    words[i] = words[i].Substring(1, words[i].Length - 1);
                    if (put_word_at(words[i]) == -1)
                        Console.WriteLine("ERROR");

                }
                i++;
            }
            show_puzzle();//shows the final puzzle
        }
        static int instructions()//prints the instructions of the game
        {
            try
            {
                print_file("game_files\\hecker_intro.txt");//prints cool intro
                print_file("game_files\\instructions.txt");//prints instructions
            }
            catch
            { return -2; }

        again:;
            Console.WriteLine("Enter command=>");
            string choice = Console.ReadLine();
            choice = choice.ToLower();
            if (choice == "/abort")
            {
                Console.WriteLine("You have aborted the mission,the worlds secrets are safe...for now");
                return -1;
            }
            else if (choice == "/start")
            {
                return 1;
            }
            else if (choice == "/about")
            { print_file("game_files\\about.txt"); goto again; }

            else
            { Console.WriteLine("ERROR: INVALID COMMAND"); goto again; }

        }
        static string select_mission()//allows user to select mission
        {
            string[] missions;
            try
            {

                missions = Directory.GetFiles("game_files\\missions", "*.txt").Select(Path.GetFileName).ToArray();
            }
            catch
            {
                return "missing";
            }

            Console.WriteLine("-------------------");
            Console.WriteLine("SELECT YOUR MISSION");
            Console.WriteLine("-------------------");
            for (int i = 0; i < missions.Length; i++)
                Console.WriteLine("/" + missions[i].Substring(0, missions[i].Length - 4));
            again:;
            string mission = Console.ReadLine();
            mission = mission.ToLower();
            if (mission.Substring(1, mission.Length - 1) == "abort")
            {
                Console.WriteLine("You have aborted the mission,the worlds secrets are safe...for now");
                return "abort";
            }
            try
            {
                mission = mission.Substring(1, mission.Length - 1) + ".txt";
            }
            catch { Console.WriteLine("ERROR: INVALID COMMAND" + mission); goto again; }

            for (int i = 0; i < missions.Length; i++)
                if (mission == missions[i])
                    return mission.Substring(0, mission.Length);


            Console.WriteLine("ERROR: INVALID COMMAND");
            goto again;
            return "ERROR";
        }
        static int create_mission(string mission)//creates and executes the actual game play
        {
            try
            {
                using (StreamReader r = new StreamReader("game_files\\missions\\" + mission))
                {
                    Console.WriteLine("HOLD ON, HACKING INTO THE DATABASE USING HTML...");

                    Console.WriteLine("FETCHING ENCRYPTED DATA....");

                    Console.WriteLine("DATA FOUND! CONVERTING INTO GRAPHICAL STRING FORMAT... ");

                    Console.Write("---------------------------\nFIND THE WORDS (HORIZONTAL) AND DECRYPT THE MESSAGE\n---------------------------\n");

                    string temp = r.ReadLine();
                    temp = temp.Trim();
                    create_puzzle(temp);
                    string[] words = temp.Split(' ');
                again:;
                    for (int i = 0; i < words.Length; i++)
                    {
                        if (words[i][0] == '/')
                            for (int j = 0; j < words[i].Length - 1; j++)
                                Console.Write("-");
                        else
                            Console.Write(words[i]);
                        Console.Write(" ");
                    }
                    Console.Write("\n");

                    for (int i = 0; i <= words.Length && (i < words.Length ? words[i][0] != '/' : true); i++)
                        if (i == words.Length)
                            return 1;

                    Console.WriteLine("Enter a word found=>");
                    string answer = Console.ReadLine();

                    if (answer == "/abort")
                        return -1;
                    for (int i = 0; i < words.Length; i++)
                        if (words[i][0] == '/' && answer == words[i].Substring(1, words[i].Length - 1))
                        {
                            Console.Write("GIVEN INPUT MATCHES ENCRYPTION...\n");                           
                            words[i] = words[i].Substring(1, words[i].Length - 1);
                            goto again;
                        }


                    Console.WriteLine("ERROR GIVEN INPUT DOES NOT MATCH ENCRYPTION, TRY AGAIN...");
                    goto again;

                }
            }
            catch
            {
                Console.WriteLine("FILES MISSING");
                return -2;
            }

        }
        static public void run_game()//runs the complete game
        {
            int stat = instructions();
            if (stat == -1)
                goto end_of_game;
            else if (stat == -2)
            { Console.WriteLine("FILES MISSING"); goto end_of_game; }

            string mission = select_mission();

            if(mission=="missing")
            { Console.WriteLine("FILES MISSING"); goto end_of_game; }
            else if (mission == "abort")
                goto end_of_game;

            stat = create_mission(mission);
            if (stat == 1)
                Console.WriteLine("CONGRATS! YOU HAVE SINGLE HANDEDLY MANAGED TO LEAK ONE OF THE MOST CLASSIFIED FILES & SCREW UP THE WORLD!");
            else if (stat == -2)
            { Console.WriteLine("FILES MISSING"); }
            else
                Console.WriteLine("YOU HAVE ABORTED THE MISSION,THE WORLDS SECRETS ARE SAFE...FOR NOW");
            end_of_game:;
        }
    }
    class Primary
    {
        static void Main(string[] args)
        {

            hecker.run_game();
            Console.ReadKey();
        }

    }
}