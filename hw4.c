/**************************************
 * hw4.c 
 *
 * Ben Mitchell
 * 2015-09-08
 *
 * <Your name here>
 * <Date you last modified this file here>
 *
 * Program for solving word search puzzles.
 *
 *
 * Scaffolding for CS120-F15, HW4 - fill in
 * main, but keep it short; my reference implementation
 * has about 20 lines of actual code in main (not counting
 * comments and whitespace).
 *************************************/

#include <stdio.h>
#include "wordsearch.h"

int main (int argc, char* argv[]) {
 /* make sure the agruments are ok */
 if( argc != 2 ){
  fprintf(stderr,"Usage: hw4 <puzzle file>\n");
  return 1;
 }
 
 /* set up input and output, panic if something goes wrong */
 FILE* gridfile;
 gridfile = fopen(argv[1],"r");
 if( !gridfile ){
  fprintf(stderr,"Oops, couldn't open puzzle file!\n");
  return 1;
 }
 
 /* load the grid into an array */
 int maxsize = MAX_GRID_SIZE;
 char grid[maxsize][maxsize];
 int size;
 size = loadGrid(grid, gridfile);
 fclose(gridfile);
 if( size == 0 ){
  fprintf(stderr,"Error loading grid!\n");
  return 1;
 }

// FILE* out;
// FILE* in;
// in = fopen("in.txt","r");
// out = fopen("out.txt","a+");

 /* toil mindlessly */
 int result;
 result = solvePuzzle(grid, size, stdin, stdout);
// fclose(out);
 if( result == -1 ){
  fprintf(stderr,"Uh-oh! Could not solve puzzle!");
  return 1;
 }
 
  return 0;
}
