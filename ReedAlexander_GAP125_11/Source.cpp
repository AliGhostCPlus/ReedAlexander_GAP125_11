#include <iostream>
#include <conio.h>

///////////////////////////////////////////////////////////
// Global variables                                     //
/////////////////////////////////////////////////////////
static constexpr char s_kUpkey = 'w';
static constexpr char s_kDownkey = 's';
static constexpr char s_kLeftKey = 'a';
static constexpr char s_kRightKey = 'd';
static constexpr char s_QuitKey = 'q';
static constexpr int s_kWidth = 8;  //Note  s_ to denote that these are static variables. static in this instance means that 
static constexpr int s_kHeight = 8; //"Only one of these can ever exist". (edited)[6:16 PM]  I spoke with a programmer from support and he suggested to take this route insted 
bool g_continueGame = true;
static constexpr char s_kExitIcon = 'X';
static constexpr char s_kWall = '#';
// players variables 
static constexpr char s_kPlayerIcon = '@';
static constexpr int s_kPlayerStartX = 0;
static constexpr int s_kPlayerStartY = 0;
static int s_playerX = s_kPlayerStartX;
static int s_playerY = s_kPlayerStartY;
char grid[s_kWidth * s_kHeight] { 
              '.', '.', '.', '.', '.','.','.','.',
              '#', '.', '#', '.', '#','.','#','#',
              '#', '#', '#', '.', '.','.','.','.',
              '#', '.', '#', '#', '#','#','#','.',
              '.', '.', '.', '.', '.','#','.','.',                  // Originally I had my character already place in the MAP
              '.', '#', '#', '#', '.','.','.','#',                 // I changed it to have the player to be built in the MAP
              '.', '#', '.', '#', '#','#','#','X',
              '.', '.', '.', '.', '.','.','.','.', };
/*             
@ . . . . . . .
# . # . # . # #
# # # . . . . .
# . # # # # # .
. . . . . # . .
. # # # . . . #                                                  // This is a rookie move but I type my map in by looking at the prototype 
. # . # # # # X
. . . . . . . .
*/
///////////////////////////////////////////////////////////
// Functions                                            //
/////////////////////////////////////////////////////////
int GetInputEndUser();
void MoveThroughMaze();                                         // I keep a sections will all my functions group together.
bool IsPlayerPositionValid();
bool IsWall();
bool IsExit();



int GetIndexFromCoordinates(int x, int y, int width)           // This function is the algorithm of the game 
{
    if (x < 0 || x >= s_kWidth)                               // This is for the x-axis horizontal left and right movements
    {
        return -1;
    }

    else if (y < 0 || y >= s_kHeight)                        // This is the y-axis veritical up ,down movements
    {
        return -1;
    }    
    return x + y * width;                                 // This will do the mathatics for the move of the character.
}

void PrintGrid()
{
    system("cls");                                      // clear system  keeps the game on screen while clearing it.
    for (int y = 0; y < s_kHeight; ++y)                //  this is the vertical column
    {
        for (int x = 0; x < s_kWidth; ++x)           //  this is the horizontal column
        {
            int retrieveIndex = GetIndexFromCoordinates(x, y, s_kWidth);                   // This void function prints the that grind and addeds my player at the same time 
            if (retrieveIndex == -1)                                                       // Line 75 checks to she if it the grid has made a error and if so it will execute the if statement
            {
                std::cout << "An error has occured\n";
                return ;
            }
            int playerIndex = GetIndexFromCoordinates(s_playerX, s_playerY, s_kWidth);    //  This will get my Coordinates I am using static int these will be stored in memory
                                                                                         // This should make the code run more efficiently

            if (retrieveIndex == playerIndex)
            {
                std::cout << s_kPlayerIcon << " ";
            }
            else
            {
                std::cout << grid[retrieveIndex]<< " ";
            }
        }
        std::cout << "\n";
    }
}
void Introduction()
{
    std::cout << "Welcome to the maze game!\n";
    std::cout << "The rules are simple!\n";
    std::cout << "You must get your character get the X!\n";                              // I like to prepare a welcome message.
    std::cout << "You are not allowed out of bounds\n";                                  // I like to keep one function just for welcome messenges.
}                                                                                       // I thought this was some professional and routine 

///////////////////////////////////////////////////////////
// This will collect the user data for the game         //
/////////////////////////////////////////////////////////
int GetInputEndUser()  
{
    std::cout <<"Hello what direction would you like to move to ? \n";
    std::cout << "You can move vertical or horizontal! \n";
    int input = -1;
    std::cout << "press w for up,s for down,a for left,d for right! or press q to quit \n"; // This will explain main controls of the game
    while (input = _getch())
        return input;
    
    return input;
}
///////////////////////////////////////////////////////////
// This This will move the character to thought maze    //
/////////////////////////////////////////////////////////
bool IsPlayerPositionValid()
{
    if (s_playerX < 0 || s_playerX >=s_kWidth)                                              // This is for the x-axis horizontal left and right movements
    {
        std::cout<<"illegal move will not allow\n";
        return false;
    }

    if (s_playerY < 0 || s_playerY >= s_kHeight)                                           // This is for the x-axis horizontal left and right movements
    {
        std::cout << "illegal move will not allow\n";    
        return false;
    }
     
    return true;
}
bool IsWall()
{
    int playerIndex = GetIndexFromCoordinates(s_playerX, s_playerY, s_kWidth);             // This functions will check if wall is present 
    if (grid[playerIndex] == s_kWall)
    {
        std::cout<<"Wall is present move not allowed\n";
        return true;
    }
    return false;
}
bool IsExit()
{
    int playerIndex = GetIndexFromCoordinates(s_playerX, s_playerY, s_kWidth);           // This functions will check if you have reached the goal 
    if(grid[playerIndex] == s_kExitIcon)
    {
        std::cout << "You have won good job!\n";
        return true;
    }

    return false;
}
void MoveThroughMaze()
{                                                                                    //This function will move the character 
    int oldPlayerX= s_playerX;
    int oldPlayerY = s_playerY;
    if (IsExit())
    {
        g_continueGame = false;
        
    }
    else
    {
        switch (GetInputEndUser())
        {
            case s_kUpkey:                                                         // This will move your character up but the w key
            {               
                s_playerY -= 1;
                break;
            }
            case s_kDownkey:                                                       // This will move your character down by using the s key
            {
                s_playerY += 1;
                break;

            }
            case s_kLeftKey:                                                       //This will move your character down by using the a key
            {
                s_playerX -= 1;
                break;
            }
            case s_kRightKey:                                                      //This will move your character down by using the d key
            {
                s_playerX += 1;
                break;
            }
            case 'q':
            {
                g_continueGame = false;                                           // By pressing the q this will end the game 
                break;
            }
            default:
            {
                std::cout << "Key was invalid \n";
            }
        }
        if (!IsPlayerPositionValid() || IsWall())
        {
            s_playerX = oldPlayerX;
            s_playerY = oldPlayerY;
        }

    }
  
   

   /*if (IsExit())
   {
       g_continueGame = false;                                              // I left this here as a note. I had this here originally for 
   }  */                                                                   //  To end the game but it was ending the game with the character on the X
    
          
}
///////////////////////////////////////////////////////////
// The game is formed here                              //
/////////////////////////////////////////////////////////
void MazeGame()
{
    Introduction();
    do
    {
        PrintGrid();                                                  // I keep a game loop for all my programs 
        MoveThroughMaze();
    } while (g_continueGame==true);  
}
///////////////////////////////////////////////////////////
// Start of main functions                              //
/////////////////////////////////////////////////////////

int main()
{
    MazeGame();                                                  // I put the main game loop in the main functions I like it this way
    system("pause");                                             // however if this is unprofessional please adivse 
    return 0;
}
