/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // calculate total number of tiles and set tile counter
    int number_of_tiles = d * d - 1;
    int tile_counter = number_of_tiles;

    // iterate board, dimensions d * d, left to right, top to bottom
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            
            // position of board gets current number, starting with
            // tile counter at total number of tiles
            board[i][j] = tile_counter;

            // if there is an odd number of tiles, swap 1 and 2
            if(number_of_tiles % 2)
            {
                if(tile_counter == 2)
                {
                    board[i][j] = 1;
                }
                if(tile_counter == 1)
                {
                    board[i][j] = 2;
                }
            }

            // decrement tile counter on each iteration
            tile_counter--;
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // iterate board, dimensions d * d, left to right, top to bottom
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            // substitute underscore for 0
            if(board[i][j] == 0)
            {
                printf(" _  ");
            }
            // print with %2d to format as two-digit integer
            else
            {
                printf("%2d  ", board[i][j]);
            }
            
        }
        // print two line breaks after each row
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // initialize vars to store location of blank tile
    int blank_i, blank_j;

    // find blank tile
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(board[i][j] == 0)
            {
                blank_i = i;
                blank_j = j;
            }
        }
    }

    // find tile user wishes to move
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(board[i][j] == tile)
            {
                // if tile is horizontally or vertically adjacent to
                // blank tile, swap values of each tile
                if((i == blank_i - 1 && j == blank_j)
                || (i == blank_i + 1 && j == blank_j)
                || (j == blank_j - 1 && i == blank_i)
                || (j == blank_j + 1 && i == blank_i))
                {
                    board[i][j] = 0;
                    board[blank_i][blank_j] = tile;
                    blank_i = i;
                    blank_j = j;
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int counter = 0;

    // iterate over table, left to right, top to bottom
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            // if last position is reached, numbers are in order
            if(i == d - 1 && j == d - 1)
            {
                return true;
            }
            // otherwise if number is greater than preceding number
            // return false, or reset counter and continue
            else
            {
                if(board[i][j] < counter)
                {
                    return false;
                }
                else
                {
                    counter = board[i][j];
                }
            }
        }
    }
    return true;
}