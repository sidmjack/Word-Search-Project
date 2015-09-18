/* wordsearch.h
 *
 * Ben Mitchell
 * 2015-09-09
 *
 * <Your name here>
 * <Date you last modified this file here>
 *
 * Headers for functions needed for a word-search puzzle solver
 *
 * Scaffolding for CS120-F15, HW4 - contains headers for all
 * required functions, as well as constants.  You shouldn't
 * remove or modify anything that's here, but if you want to
 * add extra functions of your own, that's fine.
 */

#ifndef _CS120_SCAFFOLD_WORDSEARCH_H
#define _CS120_SCAFFOLD_WORDSEARCH_H

#include <stdio.h>
#include <stdbool.h>

#define MAX_GRID_SIZE 10
#define MAX_WORD_LENGTH 20

/* print a human-readable direction based on a (delta-Y, delta-X) pair */
int printDirection(FILE* outfile, int dr, int dc);

/* read a word from an input stream; safe for fixed-size buffer */
int readWord(FILE *infile, char word[], int maxsize);

/* load a puzzle grid from a textfile; returns size, or 0 if error */
int loadGrid(char grid[][MAX_GRID_SIZE], FILE* gridfile); 

/* check for a word match at the given location and direction */
bool checkMatch(char grid[][MAX_GRID_SIZE], int gridsize, char word[], int row, int col, int dr, int dc);

/* search a puzzle grid for the given word */
int findWord(char grid[][MAX_GRID_SIZE], int gridsize, char word[], FILE* outfile);

/* given a puzzle, read words and try to find them */
int solvePuzzle(char grid[][MAX_GRID_SIZE], int gridsize, FILE* wordfile, FILE* outfile);

#endif
