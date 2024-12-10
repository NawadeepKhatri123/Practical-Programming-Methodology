LAB ASSIGNMENT #7

Description

    This program reads a text file and generates the following statistics:
     
     - Number of characters, words and line
     - The frequency of occurrence of each Word
     - The frequency of occurrence of each letter
	
COMPILATION
	
	g++ -o word word.cpp

USAGE
	
	./word

	make sure you have the file which includes the required resources.

EXAMPLE RUN

	- The text file contains the following text :

    My name is my name and #$%^&* yours is franco is123is
---------------------------------------------------------------------------------------------------------
    Words in the dictionary : My  and  franco  is  my  name  yours

    Number of Letters : 54
    Number of Words : 11
    Number of lines : 1

                /---------------------------\
                |         LETTER FREQ       |
	            \---------------------------/

                     M : *
                     a : ****
                     c : *
                     d : *
                     e : **
                     f : *
                     i : ****
                     m : ***
                     n : ****
                     o : **
                     r : **
                     s : *****
                     u : *
                     y : ***

                /---------------------------\
                |         DICTIONARY        |
	        \---------------------------/

                My                         1
                and                        1
                franco                     1
                is                         4
                my                         1
                name                       2
                yours                      1



                /---------------------------\
                |         HISTOGRAM         |
	        \---------------------------/
       |---------------------------------------------|
       |                       *                     |
       |                       *                     |
       |                       *           *         |
       |     *     *     *     *     *     *     *   |
       |---------------------------------------------|
             ^     ^     ^     ^     ^     ^     ^
My-----------/     |     |     |     |     |     |
and----------------/     |     |     |     |     |
franco-------------------/     |     |     |     |
is-----------------------------/     |     |     |
my-----------------------------------/     |     |
name---------------------------------------/     |
yours--------------------------------------------/

Longest Word is :franco
