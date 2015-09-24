HW4 README for CS 120, Fall 2015
Names: Sidney Jackson & Florian Pontani
Contact Information:
sjacks85@jhu.edu
flo@jhu.edu

Summary of the Word Search Program:
	The purpose of this program is to solve word search problems.
The user will pass a square word search grid of a max length of 10 and
also pass either a single word or set of words (contained in a file)
to main for our program to search the given grid for the given 
words. Our program, after "searching" though the grid will then
write to an outfile stating which words were found or not, and if they
were found, the starting coordinate(s) of the word along with the 
direction in which to read to find the sought for word(s).

SOURCE CODE:
***hw4.c***
	The mainfile that takes 2 arguments, passes the gridfile to 
main, the input from stdin or a file, and uses the solvePuzzle
to solve wordsearch grids.

***wordsearch.h***
	Contains the delcarations offunctions needed to 
execute the hw.4

***wordSearch.c*** 
	Defines the wordsearch functions.

***Makefile***
	The makefile link the files into a single, cohesive
executable program.

FUNCTIONS:
printDirection: 
	Given a row and column direction, 
this function prints "human-readable" directions for
finding a word found on the passed wordsearch grid.  

readWord: 
	Given either a single word as input or a set of words
separated by whitespace in a text file, this function stores 
the stream of input characters of the word distinguished in an
array of character. The function then returns the length of
the word.
 
loadGrid:
	Given a textfile contiaining the grid, this 
function first determines whether the grid  fits the maxlength
and square-grid conditions required to be evaluated. After
loading the grid of characters, this function returns
the size of the new grid.

checkMatch:
	Given the starting coordinates and the 
direction, this function confirms the specified location
and direction of a specified word.

findWord:
	Given the word to search for, this function runs through four
different loops that test each possible starting coordinate and
direction testing the sought after word against the evaluated 
grid characters until a match is found or until the loops are
exhausted. It then writes the result to an outfile.

solvePuzzle: 
	Given the wordfile full of words to be sought after, this puzzle
combines the functions listed above to use a particular/ a given
gridfile to search for a single or set of words given to this
function.

Trials and Tribulations:
The logic for executing the code wasn't so much an issue when it came to 
writing the code. It was more so the difficulty of anticipating how to
deal with bad input. It wasn't hard to get the program running; however, 
we didn't realize there was a series of function tests that we were 
encouraged to use thoughout the creation of our program. While it ran
perfectly using "correct" input, it didn't handle error too well initially.

One of the more frustrating aspects of this assignment was utilizing 
bitbucket and version control. It was pretty difficult figuring out. 
We had to create more than one repository, spend quite a bit of time
learning how to use the commands, and working with both a local and remote
version. For most of the project, we only had one of us use version control
while the other sent tarballs of edited code to avoid version conflicts 
(but also becuase it was never quite 100% figured out).

Another new tool that took sometime learning, but proved to be helpful
in the long run, was the gdb debugging tool. This saved a bit of time
debugging towards the end of the week when we started to get the hang 
of it.

Not realizing that there were function tests for us to test our functions, 
we mostly tested out code on tests we created. While this was good 
practice, it also caused us to rush debugging toward the end since we had
such a small amount of time with the provided tests. We ran into more
than our fair share of seg faults and spent a good amount of time working
on error handling after we started using the test files.

One last frustration that was experiences during testing our functions
was that some of the tests we failed, we didn't actually fail. Times when
our functions would handle undesired input and response appropriately as 
well as tests we failed only becuase the correct output was written to
out file in a different order, made it difficult at times to discern 
whether our code actually had serious flaws. The findWord function, for 
example, produced the same exact output as the test file had. The only
difference was in the order that the output was written. This, in turn, 
impacted the solveWord puzzle making it appear that our functions were
failing more tests than they deserved to. The functions we struggled with
most, as a result, were loadgrid and readWord.

Feedback:
The assignment was challenging, but effective. Though neither have been 
quite mastered yet, out familiarity with version control is great enough
so that we can at least work from two different computers and have access
to an updated version of code multiple people are working on. 
Additionally, learning how to use gdb as a debugging tool will prove
to allow us more time to work on error handling and working code logic 
instead of toiling over debugging our program. The assignment was fair.
However, we did feel that it was difficult to understand what exactly
was being tested by given function tests- even given the code.
(This is where gdb proved to be especially helpful).
