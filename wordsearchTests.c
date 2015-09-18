/* wordsearchTests.c
 *
 * Ben Mitchell
 * 2015-09-11
 *
 * <Your name here>
 * <Date you last modified this file here>
 *
 * Unit tests for word-search puzzle functions.
 *
 * Scaffolding for CS120-F15, HW4 - contains unit-tests
 * for word-search puzzle functions; hopefully it's pretty
 * comprehensive, but feel free to add more test cases of your
 * own.  If you make any extra "helper" functions, you should
 * create a function in here to test them, and put in enough
 * test cases to make sure they work.
 */
#include "wordsearch.h"
#include <assert.h>
#include <string.h>

/* macro to help make writing tests quicker.
 * NOTE: we could use assert() instead, but
 * that will stop us when the first test fails;
 * this macro lets us keep going and try the rest
 * of them, but it tracks how many failed, and 
 * prints a line-number so we know which tests
 * ran into problems. 
 */
#define TEST(X) testCounter++; if ( !(X) ) { rval = false; printf("---test failed at %s:%d---\n", __FILE__, __LINE__); testsFailed++;}


/* Helper function to compare two files, character by character,
 * to see whether they are the same.  Returns 0 if the two
 * files are identical, otherwise returns non-0 
 * NOTE: this means it works like strcmp and other comparison
 * functions; if you want to test for file equality, you want
 * to check for fileCmp()==0, or !fileCmp()
 *
 * We will use this to help test some of our functions that produce
 * output.
 */
int fileCmp(FILE *f1, FILE *f2) {
  // make sure file handles are valid
  if (!f1 || !f2) {
    fprintf(stderr, "WARNING: fileCmp given un-open filehandles!\n");
    return -1; // if one (or both) isn't open, they're not equal by definition
  }

  char c1, c2;
  // loop through both files one character at a time, checking whether
  // they match or not
  while ( (c1 = fgetc(f1)) == (c2 = fgetc(f2)) && c1 != EOF ) {
    // keep on reading
  }
  
  // this will be 0 if the files were the same all the way through, and
  // non-0 otherwise.
  return c1 - c2;
}

/* helper to call fileCmp using file names instead of
 * file handles.
 */
int fileCompare(char fname1[], char fname2[]) {
  FILE *f1 = fopen(fname1, "r");
  FILE *f2 = fopen(fname2, "r");
  int rval = fileCmp(f1, f2);

  // close files, but only if they are actually open
  if (f1)
    fclose(f1);
  if (f2)
    fclose(f2);

  return rval;
}

/* before we use the fileCompare and fileCmp functions to
 * test other things, let's make sure they work...
 */
bool test_fileCompare() {
  bool rval = true;
  int testCounter = 0;
  int testsFailed = 0;

  FILE* fp1;
  FILE* fp2;
  fp1 = fopen("test1.txt", "w");
  assert(fp1);
  fprintf(fp1, "this\nis\na test\n");
  fclose(fp1);

  fp1 = fopen("test2.txt", "w");
  assert(fp1);
  fprintf(fp1, "this\nis\na different test\n");
  fclose(fp1);

  fp1 = fopen("test3.txt", "w");
  assert(fp1);
  fprintf(fp1, "this\nis\na test\n");
  fclose(fp1);

  fp1 = fopen("test1.txt", "r");
  fp2 = fopen("test1.txt", "r");
  assert(fp1);
  assert(fp2);
  TEST(!fileCmp(fp1, fp2));
  fclose(fp1);
  fclose(fp2);

  fp1 = fopen("test1.txt", "r");
  fp2 = fopen("test2.txt", "r");
  assert(fp1);
  assert(fp2);
  TEST(fileCmp(fp1, fp2));
  fclose(fp1);
  fclose(fp2);

  fp1 = fopen("test1.txt", "r");
  fp2 = fopen("test3.txt", "r");
  assert(fp1);
  assert(fp2);
  TEST(!fileCmp(fp1, fp2));
  fclose(fp1);
  fclose(fp2);

  TEST(!fileCompare("test1.txt", "test1.txt"));
  TEST(!fileCompare("test2.txt", "test2.txt"));
  TEST(!fileCompare("test3.txt", "test3.txt"));

  TEST(fileCompare("test1.txt", "test2.txt"));
  TEST(fileCompare("test2.txt", "test1.txt"));
  TEST(fileCompare("test2.txt", "test3.txt"));
  TEST(fileCompare("test3.txt", "test2.txt"));
  TEST(!fileCompare("test1.txt", "test3.txt"));
  TEST(!fileCompare("test3.txt", "test1.txt"));

  // NOTE: missing.txt shouldn't exist... 
  TEST(fileCompare("test1.txt", "missing.txt"));
  TEST(fileCompare("missing.txt", "test1.txt"));
  TEST(fileCompare("missing.txt", "notthere.txt"));


  printf("\t\t%d tests run, %d passed, %d failed\n", testCounter, (testCounter - testsFailed), testsFailed);
  return rval;
}


/* Test the printDirections() function */
bool test_printDirection() {
  bool rval = true;
  int testCounter = 0;
  int testsFailed = 0;
  FILE *fp = fopen("test1.txt", "w");
  assert(fp);
  
  // try all valid directions
  for (int i=-1; i<2; i++) {
    for (int j=-1; j<2; j++) {
      TEST(printDirection(fp, i, j) == 0);
      fprintf(fp, "\n");
    }
  }

  // try some bad directions (shouldn't print anything, but should
  // return an error code)
  TEST(printDirection(fp, -2, 0) == 1);
  TEST(printDirection(fp, 0, 2) == 1);
  TEST(printDirection(fp, 7, -12) == 1);

  fclose(fp);

  // manually print the string we ought to get
  fp = fopen("test2.txt", "w");
  assert(fp);
  fprintf(fp, "UL\nU\nUR\nL\n\nR\nDL\nD\nDR\n");
  fclose(fp);

  // see if we got what we expected
  TEST (!fileCompare("test1.txt", "test2.txt"));

  // check what happens if we give it a closed filehandle
  fp = fopen("missing.txt", "r");
  TEST(printDirection(fp, 1, 1) == -1);

  printf("\t\t%d tests run, %d passed, %d failed\n", testCounter, (testCounter - testsFailed), testsFailed);
  return rval;
}


/* Test the readWord() function */
bool test_readWord() {
  bool rval = true;
  int testCounter = 0;
  int testsFailed = 0;

  FILE *fp = fopen("test1.txt", "w");
  assert(fp);
  // write some words to a file
  fprintf(fp, "a\nbbbbb ccc\n  defg  \n \t   hijklmnop\n1234567890123 45\n");
  fclose(fp);

  // re-open for reading
  FILE *fin = fopen("test1.txt", "r");
  assert(fin);

  char word[11];
  word[10] = '\0'; // just to be safe...
  int size;

  size = readWord(fin, word, 10);
  TEST(size == 1 && !strncmp(word, "a", 11));

  size = readWord(fin, word, 10);
  TEST(size == 5 && !strncmp(word, "bbbbb", 11));

  size = readWord(fin, word, 10);
  TEST(size == 3 && !strncmp(word, "ccc", 11));

  size = readWord(fin, word, 10);
  TEST(size == 4 && !strncmp(word, "defg", 11));

  size = readWord(fin, word, 10);
  TEST(size == 9 && !strncmp(word, "hijklmnop", 11));

  size = readWord(fin, word, 10);
  TEST(size == 9 && !strncmp(word, "123456789", 11));

  size = readWord(fin, word, 10);
  TEST(size == 2 && !strncmp(word, "45", 11));

  fclose(fin);

  // make sure it handles a bad filehandle gracefully (size=0, word="")
  fin = fopen("missing.txt", "r");
  size = readWord(fin, word, 10);
  TEST(size == 0 && !strncmp(word, "", 11));

  printf("\t\t%d tests run, %d passed, %d failed\n", testCounter, (testCounter - testsFailed), testsFailed);
  return rval;
}


/* test the loadGrid() function */
bool test_loadGrid() {
  bool rval = true;
  int testCounter = 0;
  int testsFailed = 0;
  char grid[MAX_GRID_SIZE][MAX_GRID_SIZE];

  FILE *fp;

  /* 
   * create test grid files:
   */

  // 1x1 grid (valid)
  fp = fopen("test1.txt", "w");
  assert(fp);
  fprintf(fp, "a\n");
  fclose(fp);

  // 2x2 grid (valid)
  fp = fopen("test2.txt", "w");
  assert(fp);
  fprintf(fp, "aa\nbb\n");
  fclose(fp);

  // 3x3 grid (valid)
  fp = fopen("test3.txt", "w");
  assert(fp);
  fprintf(fp, "abc\ndef\n123\n");
  fclose(fp);

  // 10x10 grid (valid)
  fp = fopen("test4.txt", "w");
  assert(fp);
  for (int i=0; i<10; i++) {
    for (int j=0; j<10; j++) {
      fprintf(fp, "%c", 'a'+( ((10*i)+j) % 26));
    }
    fprintf(fp, "\n");
  }
  fclose(fp);

  // 2x3 grid (invalid)
  fp = fopen("test5.txt", "w");
  assert(fp);
  fprintf(fp, "aa\nbb\ncc\n");
  fclose(fp);

  // 7x4 grid (invalid)
  fp = fopen("test6.txt", "w");
  assert(fp);
  fprintf(fp, "aaaaaaa\nbbbbbbb\nccccccc\nddddddd\n");
  fclose(fp);

  // 11x11 grid (invalid)
  fp = fopen("test7.txt", "w");
  assert(fp);
  for (int i=0; i<11; i++) {
    for (int j=0; j<11; j++) {
      fprintf(fp, "%c", 'a'+( ((11*i)+j) % 26));
    }
    fprintf(fp, "\n");
  }
  fclose(fp);

  // 20x20 grid (invalid)
  fp = fopen("test8.txt", "w");
  assert(fp);
  for (int i=0; i<20; i++) {
    for (int j=0; j<20; j++) {
      fprintf(fp, "%c", 'a'+( ((20*i)+j) % 26));
    }
    fprintf(fp, "\n");
  }
  fclose(fp);

  // 3x3 grid with punctiation (invalid)
  fp = fopen("test9.txt", "w");
  assert(fp);
  fprintf(fp, "aa.\nbb?\n,.'\n");
  fclose(fp);

  // 10x11 grid (invalid)
  fp = fopen("test10.txt", "w");
  assert(fp);
  for (int i=0; i<10; i++) {
    for (int j=0; j<11; j++) {
      fprintf(fp, "%c", 'a'+( ((11*i)+j) % 26));
    }
    fprintf(fp, "\n");
  }
  fclose(fp);


  // 11x10 grid (invalid)
  fp = fopen("test11.txt", "w");
  assert(fp);
  for (int i=0; i<11; i++) {
    for (int j=0; j<10; j++) {
      fprintf(fp, "%c", 'a'+( ((10*i)+j) % 26));
    }
    fprintf(fp, "\n");
  }
  fclose(fp);


  // uneven grid with (invalid)
  fp = fopen("test12.txt", "w");
  assert(fp);
  fprintf(fp, "aaa\nbb\nccc\n");
  fclose(fp);


  /* 
   * Try to load test the grid files
   */

  // try to load valid grids, make sure they contain what they should
  fp = fopen("test1.txt", "r");
  assert(fp);
  TEST(loadGrid(grid, fp) == 1);
  TEST(grid[0][0] == 'a');
  fclose(fp);

  fp = fopen("test2.txt", "r");
  assert(fp);
  TEST(loadGrid(grid, fp) == 2);
  TEST(grid[0][0] == 'a');
  TEST(grid[0][1] == 'a');
  TEST(grid[1][0] == 'b');
  TEST(grid[1][1] == 'b');
  fclose(fp);

  fp = fopen("test3.txt", "r");
  assert(fp);
  TEST(loadGrid(grid, fp) == 3);
  TEST(grid[0][0] == 'a');
  TEST(grid[0][1] == 'b');
  TEST(grid[0][2] == 'c');
  TEST(grid[1][0] == 'd');
  TEST(grid[1][1] == 'e');
  TEST(grid[1][2] == 'f');
  TEST(grid[2][0] == '1');
  TEST(grid[2][1] == '2');
  TEST(grid[2][2] == '3');
  fclose(fp);

  fp = fopen("test4.txt", "r");
  assert(fp);
  TEST(loadGrid(grid, fp) == 10);
  for (int i=0; i<10; i++) {
    for (int j=0; j<10; j++) {
      TEST(grid[i][j] == 'a'+( ((10*i)+j) % 26) );
    }
  }
  fclose(fp);


  // make sure invalid grids don't get loaded
  fp = fopen("test5.txt", "r");
  assert(fp);
  TEST(loadGrid(grid, fp) == 0);
  fclose(fp);

  fp = fopen("test6.txt", "r");
  assert(fp);
  TEST(loadGrid(grid, fp) == 0);
  fclose(fp);

  fp = fopen("test7.txt", "r");
  assert(fp);
  TEST(loadGrid(grid, fp) == 0);
  fclose(fp);

  fp = fopen("test8.txt", "r");
  assert(fp);
  TEST(loadGrid(grid, fp) == 0);
  fclose(fp);

  fp = fopen("test9.txt", "r");
  assert(fp);
  TEST(loadGrid(grid, fp) == 0);
  fclose(fp);

  fp = fopen("test10.txt", "r");
  assert(fp);
  TEST(loadGrid(grid, fp) == 0);
  fclose(fp);

  fp = fopen("test11.txt", "r");
  assert(fp);
  TEST(loadGrid(grid, fp) == 0);
  fclose(fp);

  fp = fopen("test12.txt", "r");
  assert(fp);
  TEST(loadGrid(grid, fp) == 0);
  fclose(fp);

  // test with bad filehandle
  fp = fopen("missing.txt", "r");
  TEST(loadGrid(grid, fp) == -1);


  printf("\t\t%d tests run, %d passed, %d failed\n", testCounter, (testCounter - testsFailed), testsFailed);
  return rval;
}


/* test the checkMatch() function */
bool test_checkMatch() {
  bool rval = true;
  int testCounter = 0;
  int testsFailed = 0;

  // write test grid
  FILE *fp = fopen("testgrid.txt", "w");
  assert(fp);
  /* grid is:
    abcd
    efgh
    ijkl
    mnop
   */
  fprintf(fp, "abcd\nefgh\nijkl\nmnop\n");
  fclose(fp);

  /* NOTE: these tests assume that some earlier things worked (particularly
   * loadGrid()), so if those tests didn't pass, these test results may not
   * actually tell us anything about whether findWord() works or not.  */


  // read test grid
  char grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
  fp = fopen("testgrid.txt", "r");
  assert(fp);

  int size = loadGrid(grid, fp);
  fclose(fp);

  TEST(checkMatch(grid, size, "abc", 0, 0, 0, 1));
  for (int i=-1; i<2; i++){
    for (int j=-1; j<2; j++) {
      if ((i == 0 && j == 0) || ( i==0 && j == 1) ) {
        continue;
      }
      TEST(!checkMatch(grid, size, "abc", 0, 0, i, j));
    }
  }

  TEST(checkMatch(grid, size, "cgko", 0, 2, 1, 0));
  TEST(!checkMatch(grid, size, "cgko", 0, 0, 1, 0));
  TEST(!checkMatch(grid, size, "cgko", 0, 2, -1, 0));
  TEST(!checkMatch(grid, size, "cgko", 0, 2, 1, 1));

  TEST(checkMatch(grid, size, "kji", 2, 2, 0, -1));
  TEST(!checkMatch(grid, size, "kji", 2, 2, 0, 1));
  TEST(!checkMatch(grid, size, "kji", 2, 0, 0, -1));

  TEST(checkMatch(grid, size, "pl", 3, 3, -1, 0));
  TEST(!checkMatch(grid, size, "pl", 3, 3, 1, 0));
  TEST(!checkMatch(grid, size, "pl", 0, 3, 1, 0));
  TEST(!checkMatch(grid, size, "pl", 0, 0, 1, 1));

  TEST(checkMatch(grid, size, "afk", 0, 0, 1, 1));
  TEST(checkMatch(grid, size, "ifc", 2, 0, -1, 1));
  TEST(checkMatch(grid, size, "pkfa", 3, 3, -1, -1));
  TEST(checkMatch(grid, size, "hkn", 1, 3, 1, -1));

  for (int i=-1; i<2; i++){
    for (int j=-1; j<2; j++) {
      if (i == 0 && j == 0) {
        continue;
      }
      TEST(checkMatch(grid, size, "a", 0, 0, i, j));
    }
  }

  printf("\t\t%d tests run, %d passed, %d failed\n", testCounter, (testCounter - testsFailed), testsFailed);
  return rval;
}


/* test the findWord() function */
bool test_findWord() {
  bool rval = true;
  int testCounter = 0;
  int testsFailed = 0;

  /* NOTE: these tests assume that some earlier things worked (particularly
   * loadGrid()), so if those tests didn't pass, these test results may not
   * actually tell us anything about whether findWord() works or not.  */

  // write test grid
  FILE *fp = fopen("testgrid.txt", "w");
  assert(fp);
  /* grid is:
    abcd
    efgk
    ijkj
    ijki
   */
  fprintf(fp, "abcd\nefgk\nijkj\nijki\n");
  fclose(fp);

  // read test grid
  char grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
  fp = fopen("testgrid.txt", "r");
  assert(fp);
  int size = loadGrid(grid, fp);
  fclose(fp);

  fp = fopen("test1.txt", "w");
  assert(fp);
  // things we should find
  TEST(findWord(grid, size, "abc", fp) == 1);
  TEST(findWord(grid, size, "cba", fp) == 1);
  TEST(findWord(grid, size, "cgkk", fp) == 1);
  TEST(findWord(grid, size, "jf", fp) == 1);
  TEST(findWord(grid, size, "afk", fp) == 1);
  TEST(findWord(grid, size, "kkj", fp) == 1);
  TEST(findWord(grid, size, "jgd", fp) == 1);
  TEST(findWord(grid, size, "ikfa", fp) == 1);
  TEST(findWord(grid, size, "ijk", fp) == 3);
  TEST(findWord(grid, size, "a", fp) == 8);
  TEST(findWord(grid, size, "i", fp) == 24);

  // things we shouldn't find
  TEST(findWord(grid, size, "q", fp) == 0);
  TEST(findWord(grid, size, "afi", fp) == 0);
  TEST(findWord(grid, size, "abcdefg", fp) == 0);
  TEST(findWord(grid, size, "", fp) == 0);
  fclose(fp);

  // the output we want to get
  fp = fopen("test2.txt", "w");
  assert(fp);
  fprintf(fp, "Found \"abc\" at 0 0, R\n");
  fprintf(fp, "Found \"cba\" at 0 2, L\n");
  fprintf(fp, "Found \"cgkk\" at 0 2, D\n");
  fprintf(fp, "Found \"jf\" at 2 1, U\n");
  fprintf(fp, "Found \"afk\" at 0 0, DR\n");
  fprintf(fp, "Found \"kkj\" at 1 3, DL\n");
  fprintf(fp, "Found \"jgd\" at 2 1, UR\n");
  fprintf(fp, "Found \"ikfa\" at 3 3, UL\n");
  fprintf(fp, "Found \"ijk\" at 2 0, R\n");
  fprintf(fp, "Found \"ijk\" at 3 0, R\n");
  fprintf(fp, "Found \"ijk\" at 3 3, U\n");
  fprintf(fp, "Found \"a\" at 0 0, UL\n");
  fprintf(fp, "Found \"a\" at 0 0, U\n");
  fprintf(fp, "Found \"a\" at 0 0, UR\n");
  fprintf(fp, "Found \"a\" at 0 0, L\n");
  fprintf(fp, "Found \"a\" at 0 0, R\n");
  fprintf(fp, "Found \"a\" at 0 0, DL\n");
  fprintf(fp, "Found \"a\" at 0 0, D\n");
  fprintf(fp, "Found \"a\" at 0 0, DR\n");
  fprintf(fp, "Found \"i\" at 2 0, UL\n");
  fprintf(fp, "Found \"i\" at 2 0, U\n");
  fprintf(fp, "Found \"i\" at 2 0, UR\n");
  fprintf(fp, "Found \"i\" at 2 0, L\n");
  fprintf(fp, "Found \"i\" at 2 0, R\n");
  fprintf(fp, "Found \"i\" at 2 0, DL\n");
  fprintf(fp, "Found \"i\" at 2 0, D\n");
  fprintf(fp, "Found \"i\" at 2 0, DR\n");
  fprintf(fp, "Found \"i\" at 3 0, UL\n");
  fprintf(fp, "Found \"i\" at 3 0, U\n");
  fprintf(fp, "Found \"i\" at 3 0, UR\n");
  fprintf(fp, "Found \"i\" at 3 0, L\n");
  fprintf(fp, "Found \"i\" at 3 0, R\n");
  fprintf(fp, "Found \"i\" at 3 0, DL\n");
  fprintf(fp, "Found \"i\" at 3 0, D\n");
  fprintf(fp, "Found \"i\" at 3 0, DR\n");
  fprintf(fp, "Found \"i\" at 3 3, UL\n");
  fprintf(fp, "Found \"i\" at 3 3, U\n");
  fprintf(fp, "Found \"i\" at 3 3, UR\n");
  fprintf(fp, "Found \"i\" at 3 3, L\n");
  fprintf(fp, "Found \"i\" at 3 3, R\n");
  fprintf(fp, "Found \"i\" at 3 3, DL\n");
  fprintf(fp, "Found \"i\" at 3 3, D\n");
  fprintf(fp, "Found \"i\" at 3 3, DR\n");
  fprintf(fp, "\"q\" - Not Found\n");
  fprintf(fp, "\"afi\" - Not Found\n");
  fprintf(fp, "\"abcdefg\" - Not Found\n");
  fprintf(fp, "\"\" - Not Found\n");
  fclose(fp);

  TEST(!fileCompare("test1.txt", "test2.txt"));

  // test with a bad filehandle
  fp = fopen("", "w");
  TEST(findWord(grid, size, "foo", fp) == -1);

  printf("\t\t%d tests run, %d passed, %d failed\n", testCounter, (testCounter - testsFailed), testsFailed);
  return rval;
}


/* test the solvePuzzle() function */
bool test_solvePuzzle() {
  bool rval = true;
  int testCounter = 0;
  int testsFailed = 0;
  FILE *fp;
  FILE *fp2;

  /* NOTE: we hopefully don't need that many tests here, because all of the
   * functions that solvePuzzle() relies on are tested elsewhere.  We just
   * need to test whether the code in solvePuzzle() works, which means we
   * don't need to test every possible good/bad data combination for all
   * the functions it calls.  */


  // full test, example 1
  fp = fopen("testgrid.txt", "w");
  assert(fp);
  fprintf(fp, "abcd\nefgh\nijkl\nmnop\n");
  fclose(fp);

  fp = fopen("testwords.txt", "w");
  assert(fp);
  fprintf(fp, "abc\nafk\nlkj\ncgko\nplh\nhgf\nkji\nhkn\nifc\nxyz\nabcdefg\n");
  fclose(fp);

  fp = fopen("test1.txt", "w");
  assert(fp);
  fprintf(fp, "Found \"abc\" at 0 0, R\n");
  fprintf(fp, "Found \"afk\" at 0 0, DR\n");
  fprintf(fp, "Found \"lkj\" at 2 3, L\n");
  fprintf(fp, "Found \"cgko\" at 0 2, D\n");
  fprintf(fp, "Found \"plh\" at 3 3, U\n");
  fprintf(fp, "Found \"hgf\" at 1 3, L\n");
  fprintf(fp, "Found \"kji\" at 2 2, L\n");
  fprintf(fp, "Found \"hkn\" at 1 3, DL\n");
  fprintf(fp, "Found \"ifc\" at 2 0, UR\n");
  fprintf(fp, "\"xyz\" - Not Found\n");
  fprintf(fp, "\"abcdefg\" - Not Found\n");
  fclose(fp);

  char grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
  fp = fopen("testgrid.txt", "r");
  assert(fp);
  int size = loadGrid(grid, fp);
  fclose(fp);

  fp = fopen("test2.txt", "w");
  fp2 = fopen("testwords.txt", "r");
  assert(fp);
  assert(fp2);
  
  TEST(solvePuzzle(grid, size, fp2, fp) == 9);
  fclose(fp);
  fclose(fp2);

  TEST(!fileCompare("test1.txt", "test2.txt"));


  // full test, example 2
  // grid:
  /*
     budihcro
     ffvdgjre
     fdsdlmmc
     iiahccoh
     yeseodis
     bdehresi
     potaebgf
     gcldnbcl
  */

  fp = fopen("testgrid.txt", "w");
  assert(fp);
  fprintf(fp, "budihcro\n");
  fprintf(fp, "ffvdgjre\n");
  fprintf(fp, "fdsdlmmc\n");
  fprintf(fp, "iiahccoh\n");
  fprintf(fp, "yeseodis\n");
  fprintf(fp, "bdehresi\n");
  fprintf(fp, "potaebgf\n");
  fprintf(fp, "gcldnbcl\n");
  fclose(fp);

  fp = fopen("testwords.txt", "w");
  assert(fp);
  fprintf(fp, "code\nprogram\nshoe\nfish\nbread\norchid\n");
  fclose(fp);

  fp = fopen("test1.txt", "w");
  assert(fp);
  fprintf(fp, "Found \"code\" at 7 1, U\n");
  fprintf(fp, "\"program\" - Not Found\n");
  fprintf(fp, "Found \"shoe\" at 2 2, DR\n");
  fprintf(fp, "Found \"fish\" at 2 0, DR\n");
  fprintf(fp, "Found \"fish\" at 6 7, U\n");
  fprintf(fp, "Found \"bread\" at 6 5, UL\n");
  fprintf(fp, "Found \"orchid\" at 0 7, L\n");
  fclose(fp);

  fp = fopen("testgrid.txt", "r");
  assert(fp);
  size = loadGrid(grid, fp);
  fclose(fp);

  fp = fopen("test2.txt", "w");
  fp2 = fopen("testwords.txt", "r");
  assert(fp);
  assert(fp2);
  
  TEST(solvePuzzle(grid, size, fp2, fp) == 6);
  fclose(fp);
  fclose(fp2);

  TEST(!fileCompare("test1.txt", "test2.txt"));

  // Test with bad filehandles
  fp = fopen("", "w");
  fp2 = fopen("missing.txt", "r");
  TEST(solvePuzzle(grid, size, fp2, fp) == -1);
  
  printf("\t\t%d tests run, %d passed, %d failed\n", testCounter, (testCounter - testsFailed), testsFailed);
  return rval;
}

/* main() for unit test program; runs all tests */
int main() {
  bool passed = true;
  printf("Running function tests for wordsearch...\n");

  /* test functions one at a time, starting with
   * ones that don't have internal dependencies...
   */
 
  printf("\ttesting fileCompare()...\n");
  if (test_fileCompare()) {
    printf("\t\tfileCompare() passed!\n");
  } else {
    printf("*!*\t\tfileCompare() FAILED!\n");
    passed = false;
  }

  printf("\ttesting printDirection()...\n");
  if (test_printDirection()) {
    printf("\t\tprintDirection() passed!\n");
  } else {
    printf("*!*\t\tprintDirection() FAILED!\n");
    passed = false;
  }

  printf("\ttesting readWord()...\n");
  if (test_readWord()) {
    printf("\t\treadWord() passed!\n");
  } else {
    printf("*!*\t\treadWord() FAILED!\n");
    passed = false;
  }
 
  printf("\ttesting loadGrid()...\n");
  if (test_loadGrid()) {
    printf("\t\tloadGrid() passed!\n");
  } else {
    printf("*!*\t\tloadGrid() FAILED!\n");
    passed = false;
  }

  printf("\ttesting checkMatch()...\n");
  if (test_checkMatch()) {
    printf("\t\tcheckMatch() passed!\n");
  } else {
    printf("*!*\t\tcheckMatch() FAILED!\n");
    passed = false;
  }

  printf("\ttesting findWord()...\n");
  if (test_findWord()) {
    printf("\t\tfindWord() passed!\n");
  } else {
    printf("*!*\t\tfindWord() FAILED!\n");
    passed = false;
  }

  printf("\ttesting solvePuzzle()...\n");
  if (test_solvePuzzle()) {
    printf("\t\tsolvePuzzle() passed!\n");
  } else {
    printf("*!*\t\tsolvePuzzle() FAILED!\n");
    passed = false;
  }

  // check to see if we ran into problems
  if (passed) {
    printf("===========================\nALL TESTS PASSED!\n");
  } else {
    printf("===========================\nWARNING: SOME TESTS FAILED!\n");
  }

   return 0;
}
