//Name: Benjamin Wilfong
//Date: 9/20/2014 (Revised)
//File Name: boardrecursion.cpp
//Program Description: The program reads a checkerboard file into a 2D array,
//                     then displays the board on the console. It then counts
//                     the number of areas using recursion. The areas are
//                     counted using the tile counts after the recursion is done.


#include <iostream>
#include <fstream>

using namespace std;

void readArray(int, int, char[][8]);
void displayContents(char[][8]);
int  countTiles(int, int, int, int, char[][8], bool[][8]);


int main()
{
   const int MAX_WIDTH   = 8,            //Boundaries for the board
	         MAX_HEIGHT  = 8;

   int tileCount = 0;

   char boardContents[8][8] = {0};       //Array to hold board data
   bool checkTiles[8][8]    = {false};   //Parallel array check if
                                         //tile has previously
                                         //been processed.

   int areaCount = 0;                    //Variable to count number of areas

   readArray(MAX_WIDTH, MAX_HEIGHT, boardContents); //will read contents of file to array
   displayContents(boardContents);                  //will output contents of array to console


   /*
   The following loop will obtain the tile count for each valid
   tile within an area. If the value returned by countTiles()
   is greater than 0, we can assume that the tile processed
   was a part of an unprocessed area on the board. In the
   revised version, the second loop and extra array for storing
   the return values is omitted. Instead, a decision structure
   was placed inside the loop, along with an integer variable
   that will hold the return value of each function call.

   In the previous version, a third parallel array was used
   to store each return value. The values were then processed
   for their area and tile count. The update eliminates the
   need for the 3rd array by continually overwriting a single
   integer variable and doing the area processing during
   each iteration of the for() loop.
   */


   cout << "Number of tiles in areas: ";

   for (int i = 0; i < MAX_HEIGHT; i++)
   {
      for (int j = 0; j < MAX_WIDTH; j++)
      {
         tileCount = countTiles(MAX_HEIGHT, MAX_WIDTH, i, j,
                                    boardContents, checkTiles);

         if (tileCount != 0)
         {
            cout << tileCount << " ";
            areaCount++;
         }
      }
   }
   cout << endl
        << "Number of areas: "
        << areaCount;
}

// The following readArray() function will
// accept the height and width parameters
// of the board, along with the 2d array
// to contain the contents of the board.
// the required file is opened and read
// into the array.

void readArray(int HEIGHT, int WIDTH, char boardContents[8][8])
{

   ifstream boardData;
   boardData.open("board.txt");

   if (!boardData)
      cout << "File open failure." << endl;

   for (int i = 0; i < WIDTH; i++)
      for (int j = 0; j < HEIGHT; j++)
         boardData >> boardContents[i][j];

   boardData.close();

}//end readArray()

//This function simply accepts the 2D array
//as an argument and displays the elements.

void displayContents(char boardContents[8][8])
{
   for (int i = 0; i < 8; i++)
   {
      for(int j = 0; j < 8; j++)
         cout << boardContents[i][j];

      cout << endl;
   }
}//end displayContents()

//The last function countTiles() will accept the boundaries,
//two indexes, the board contents and its parallel array
//as parameters. First, the function makes sure that
//both indexes have not exceeded the maximum boundaries.
//If so, a flag is set to true and the function will return 0.
//Also, if the tile processed is black or already been handled,
//the function will also return 0. These are the bases cases.
//In the general case, (an unprocessed white tile), four recursive
//calls are made which process the area above, below, and
//to the left and right of the original index. All valid tiles processed
//by the calls will be marked as 'true' or processed until they
//hit the base case, in which 0 will be returned and 1 will be added
//for each valid call, eventually returning the number of tiles
//in the area.

int countTiles(int WIDTH, int HEIGHT, int i, int j,
               char boardContents[8][8], bool checkTiles[8][8])
{
   bool outOfBounds = false;

   if (i < 0 || j < 0 || i >= HEIGHT || j >= WIDTH)
      outOfBounds = true;

   if (outOfBounds == true)
         return 0;

   else if (boardContents[i][j] == 'b' ||
            checkTiles[i][j]    == true)
         return 0;

   else
   {
         checkTiles[i][j] = true;

         return countTiles(WIDTH, HEIGHT, i + 1, j, boardContents, checkTiles)
              + countTiles(WIDTH, HEIGHT, i - 1, j, boardContents, checkTiles)
              + countTiles(WIDTH, HEIGHT, i, j + 1, boardContents, checkTiles)
              + countTiles(WIDTH, HEIGHT, i, j - 1, boardContents, checkTiles)
              + 1;
   }
}//end countTiles()
