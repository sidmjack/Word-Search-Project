/* wordsearch.c
 *
 * Ben Mitchell
 * 2015-09-11
 *
 * <Your name here>
 * <Date you last modified this file here>
 *
 * Functions needed for a word-search puzzle solver.
 *
 * Scaffolding for CS120-F15, HW4 - contains function
 * stubs for all required functions.  You should implement
 * all these functions.  If you want to implement additional
 * "helper" functions, you are free to do so.
 */

#include "wordsearch.h"
#include <ctype.h>
#include <string.h>

/* printDirection
 *
 * Prints a human-readable string representing the specified direction
 *
 * Parameters:
 * outfile - filehandle to print output to
 * dr - "delta-row", or change in row each step
 * dc - "delta-column", or change in column each step
 *
 * Returns 0 on success, non-0 on errors
 */
int printDirection (FILE* outfile, int dr, int dc) {

 /* check if file is actually there */
 if(!outfile){
  fprintf(stderr, "Oh no! Bad file handle!\n");
  return 1;
 }

 /* check if dr is acceptable */
 if( !((dr == 1) || (dr == 0) || (dr == -1)) ){
  fprintf(stderr, "Bad row direction: \"%d\".\n", dr);
  return 1;
 }

 /* check if dc is acceptable */ 
 if( !((dc == 1) || (dc == 0) || (dc == -1)) ){
  fprintf(stderr, "Bad column direction: \"%d\".\n", dc);
  return 1;
 }

 /* check if the direction has magnitude */
 if( (dc == 0) && (dr == 0) ){
  fprintf(stderr, "Error: row and column direction are both zero.\n");
 }

 /* determine direction */

 /* print D for down, U for up */
 if( dr == -1 ){
  fprintf(outfile, "D");
 }
 if( dr == 1 ){
  fprintf(outfile, "U");
 }

 /* print R for right, L for left */
 if( dc == 1 ){
  fprintf(outfile, "R");
 }
 if( dc == -1 ){
  fprintf(outfile, "L");
 }

 /* return */
 return 0;

}




/* readWord
 *
 * Safe function to read a word and store it in a fixed-size array.
 *
 * Reads a single word from the input stream character by character and stores
 * it in the provided array.  Normally it reads and stores characters until the
 * first whitespace, which indicates the end of the word.  It also strips
 * leading whitespace before it starts.
 *
 * Since we expect a fixed size buffer, if the word is too long we will stop
 * storing characters when we get to maxsize, and discard any remaining
 * characters in the word (i.e. until we get to whitespace), so that we're not
 * leaving a partial word on the input stream.
 *
 * Parameters:
 * infile - filehandle to read from
 * word - character array to store result
 * maxsize - the maximum number of characters to store; will write to at most
 *           maxsize elements of the word array (i.e. 0 -> maxsize-1).  This
 *           should generally be the actual size of the array.
 *
 * Returns: the size of the word that was read, 0 if we couldn't read a word
 */
int readWord (FILE *infile, char word[], int maxsize) {
  return -1;
}

/* loadGrid
 *
 * Function to load a grid of characters from a textfile.
 * The grid must be square (i.e. rows == cols), and the size
 * must be less than MAX_GRID_SIZE.
 *
 * Parameters:
 * grid - a MAX_GRID_SIZE by MAX_GRID_SIZE 2D array; gets filled
 *        with characters by this function.
 * gridfile - an open filehandle to read from.
 *
 * Returns: the size of the new grid, or 0 if there was an error.
 */
int loadGrid (char grid[][MAX_GRID_SIZE], FILE* gridfile) {
   return -1;
}


/* checkMatch
 *
 * tests whether the specified word is present in the grid at the
 * specified location, going in the specified direction.
 *
 * Parameters:
 * grid - the puzzle grid
 * gridsize - the width(/height) of the grid
 * word - the word to search for
 * row - row of the starting point
 * col - column of the starting point
 * dr - "delta-row", or change in row each step
 * dc - "delta-column", or change in column each step
 *
 * Returns: true if the word is matched, false otherwise
 */
bool checkMatch (char grid[][MAX_GRID_SIZE], int gridsize, char word[], int row, int col, int dr, int dc) {
  return false;
}


/* findWord
 *
 * searches the puzzle grid for the given word
 *
 * Parameters:
 * grid - the puzzle grid
 * gridsize - the width(/height) of the grid
 * word - the word to search for (should be a null-terminated C-string)
 * outfile - filehandle for printing output
 *
 * Return: the number of times the word was found (0 if it was not found)
 *
 * Depends on:
 * checkMatch()
 * printDirection()
 */
int findWord (char grid[][MAX_GRID_SIZE], int gridsize, char word[], FILE* outfile) {
  return -1;
}


/* solvePuzzle
 *
 * main driver loop for solving word-search puzzles.
 *
 * Parameters:
 * grid - the puzzle grid 
 * gridsize - the width(/height) of the grid
 * wordfile - filehandle to read input (words to look for)
 * outfile - filehandle for writing output (locations words were found)
 *
 * Returns: the number of words that were found, or -1 for an error
 *
 * Depends on:
 * readWord()
 * findWord()
 */
int solvePuzzle (char grid[][MAX_GRID_SIZE], int gridsize, FILE* wordfile, FILE* outfile) {
   return -1;
}
