/* wordsearch.c
 *
 * Ben Mitchell
 * 2015-09-11
 *
 * Florian Pontani & Sidney Jackson
 * fpontan1 & sjacks85
 * (917) 454-8493 & (386) 956-5577
 * Monday, September 23, 2015
 * CS 600.120
 * Homework #4
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
  fprintf(stderr, "printDirection: Oh no! Bad output file handle!\n");
  return -1;
 }

 /* check if dr is acceptable */
 if( !((dr == 1) || (dr == 0) || (dr == -1)) ){
  fprintf(stderr, "printDirection: Bad row direction: \"%d\".\n", dr);
  return 1;
 }

 /* check if dc is acceptable */ 
 if( !((dc == 1) || (dc == 0) || (dc == -1)) ){
  fprintf(stderr, "printDirection: Bad column direction: \"%d\".\n", dc);
  return 1;
 }

 /* check if the direction has magnitude */
 if( (dc == 0) && (dr == 0) ){
  fprintf(stderr, "printDirection: Row and column directions are both zero.\n");
 }

 /* determine direction */

 /* print D for down, U for up */
 if( dr == -1 ){
  fprintf(outfile, "U");
 }
 if( dr == 1 ){
  fprintf(outfile, "D");
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
	char c;
	int word_length = 0; 
	word[maxsize] = '\0';
	if (!infile){
		fprintf(stderr, "readWord: Bad file handle!\n");
		word[0] = '\0';
		return 0;
	}
	
	
	while ((c  = fgetc(infile)) != EOF ){
		
		// if there's weird stuff in the input, complain
		if (ispunct(c)){
			fprintf(stderr, "readWord: Bad Input!\n");
			return 0;
		}
		// detect the end of a line
		if (isspace(c) && (word_length !=0)) {
			word[word_length] = '\0';
			return word_length;
		}
		// if the word is really long, stop filling the array
		// but continue emptying the input file
		if (word_length >= MAX_GRID_SIZE){
			while ( isalpha(c) || isdigit(c) ){
				//To reach end of word max is surpssed.
				c = fgetc(infile);
				word_length++;
			}
			// neatly terminate the string and dip
			word[MAX_GRID_SIZE-1] = '\0';
			return MAX_GRID_SIZE - 1;

		}
		// if everything is ok, add the word to the array
		// and increment the counter
		if ( isalpha(c) || isdigit(c) ){
			word[word_length] = c;
			word_length++;
		}
	}
	// if the end of the file is reached, terminate the string and return
	word[word_length] = '\0';
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

 /* make sure the file handle works */
 if(!gridfile){
  fprintf(stderr,"loadGrid: Bad grid file handle!\n");
  return -1;
 }
 char c;
 int width = 0, height = 0;

 /* find the length of the first line of the grid, then go back to the start */
 c = fgetc(gridfile);
 if( c == EOF ){
  fprintf(stderr,"loadGrid: Grid file is empty!\n");
  return 0;
 }
 while( ((c != '\n') && (c != EOF)) ){
  width++;
  c = fgetc(gridfile);
 }
 /* this is important */
 rewind(gridfile);

 /* make sure the grid is within the expected size */
 if( width > MAX_GRID_SIZE ){
  fprintf(stderr,"loadGrid: Grid is too big!\n");
  return 0;
 }

 /* make sure the grid is actually a square, not missing rows or columns,
  * and that there isn't any other unexpected tomfoolery going on */
 for(int i = 0; i < MAX_GRID_SIZE + 1; i++){
  for(int j = 0; j < MAX_GRID_SIZE + 1; j++){
   c = fgetc(gridfile);
 /* check for things that could throw the program off */
   if( isspace(c) || ispunct(c) || c == EOF ){
 
 /* if it's the end of the file, check if the number of
  * columns and rows match, and return.  */
    if( c == EOF ){
     if(width == height){
      return width;
     }else{
      fprintf(stderr,"loadGrid: Grid width & height do not match!\n");
      return 0;
     }
    }    
  /* if there's a new line, increment the height */
    if( c == '\n' ){
     height++;
  /* if a line's width doesn't match the others, print an error */
     if( width != j ){
      fprintf(stderr,"loadGrid: Grid width not uniform!\n");
      return 0;
     }else{
  /* at the end of the line, if eveythin's still ok, go to the next line */
      break;
     }
    }else{
     fprintf(stderr,"loadGrid: Grid file contains non-letter charcters at (%d, %d)\n",i,j);
     return 0;
    }
   }else{
  /* if nothing sus is going on, load the character into the gfrid. */
    if( j > MAX_GRID_SIZE ){
     fprintf(stderr,"loadGrid: Grid is too girthsome!\n");
     return 0;
    }
  /* ensure the grid isn't too long */
    if( i > MAX_GRID_SIZE - 1 ){
     fprintf(stderr,"loadGrid: Grid is too long!");
     return 0;
    }
    grid[i][j] = c;
   }
  }// end j loop
 }//  end i loop

  /* at the end, if no errors have been returned, return the grid size */
   return width;
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
	
	/*Match variable returned*/
 	bool check = false; 
 
	/*Length of the word parameter passed to the function.*/
	int word_length = strlen(word);
 
	/*Checks to see if the word is too big for the grid.*/
	if (word_length > gridsize){
 		return false;
 	}
 
	/*Increments designated change in direction 
  	* for each letter examined from the starting point*/
 	for (int steps = 0; steps < word_length; steps++){
 		int row_check = (row + steps*dr);
 		int column_check = (col + steps*dc);
 
 		int i = row_check;
 		int j = column_check;
 	
 		/*Checks to see if word check extends beyond grid*/
 		if (i >= gridsize || j >= gridsize){
 			return false;
 		}
		/* see if the input word matches one in the grid */ 	
		if (word[steps] == grid[i][j]){
 			check = true;
		} else {
			return false;
		}
	}	
	return check;
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

        int words_found = 0;
	bool found = false;
        int dr;
        int dc;
        int row;
        int col;

	/*Ensures that there's a file to write output to.*/
	
	if (!outfile){
	       fprintf(stderr, "findWord: Missing/Closed Output file\n");	
	       return -1;
	}
 
	for (dr = -1; dr < 2; dr++) {
            for (dc = -1; dc < 2; dc++) {
                for (row = 0; row < gridsize; row++) {
                    for (col = 0; col < gridsize; col++) {
			/* don't check the direction <0,0> because
			 * it makes printDirection() angry */
			if( dr == 0 && dc == 0 ){
				dc++;
			}
			/* look for a word */                        
			if(checkMatch(grid, gridsize, word, row, col, dr, dc)){
			/* if the word was found, say which word, and where it was found */
                                fprintf(outfile,"Found \"%s\" at %d %d, ",word,row,col);
                                printDirection (outfile, dr, dc);
				fprintf(outfile,"\n");
                                words_found++;
				found = true;
			}
                    }
                }
            }
        }
	if( !found ){
		 fprintf(outfile,"\"%s\" - Not Found\n",word);
	}
        return words_found;

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
        /*Parameter for the read_word function.*/
        char word[gridsize];

        /*Number of words found.*/
        int num_words = 0;

        /*Length of word as determined by the readWord function*/
        int length;

        /*While there are still words to be read from the wordfile passed to it...*/

	if(!wordfile){
		fprintf(stderr, "solvePuzzle: Missing Wordfile!\n");
		return -1;
	}

	if(!outfile){
		fprintf(stderr, "solvePuzzle: Missing Wordfile!\n");
		return -1;
	}

        do{

        /*Retrieves the word and word length from stdin to pass to findWord*/

                length = readWord(wordfile, word, gridsize);
                char curr_word[length];

        /*Current word being sought after.*/
                for (int j = 0; j < length + 1; j++){
                        curr_word[j] = word[j];
        /*Prints the number of occurences if a found word.*/
                        if( j == length ){
                                 num_words += findWord(grid, gridsize, curr_word, outfile);
                        }
      		}
        }while( length != 0 && !feof(wordfile));
        
	return num_words;

}
