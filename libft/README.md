*This project has been created as part of the 42 curriculum by maguzman.*


## Description 

Create a C library containing 43 functions programmed for manipulating strings, memory and lists.

libc fubctions: reimplement 23 functions from libc (with their prototypes and matching behaviour as defined in man page).

Additional functions: develop 11 functions that are either not in libc or behave differently from the standard function.

Linked list: Set of 9 functions for list manipulation.

## Instructions

### Running tests

### Running internal tests

There is a tests folder outside of libft

use this command to run it:

`cd tests && gcc babel_tests.c ../libft/ft_*.c -I../libft -lbsd -o babel_tests && ./babel_tests`


### Running external tests

#### [War Machine](https://github.com/0x050f/libft-war-machine)

First build the library from the libft folder:

`cd libft && make`

Then go to the war machine directory, set the path to your libft folder in `config.sh`, and run the script:

Go to the directory where you cloned, add the correct Path in the config.sh file and run the script

`bash grademe.sh`

You can also test individual functions

`bash grademe.sh ft_atoi`

#### [Libft Unit Test](https://github.com/alelievr/libft-unit-test)

### Notes

#### Section 1 - Building blocks

The functions in this sections inspects and moves raw data. 

##### Character Inspectors

- isalpha, isdigit, isalnum - checks for letters, numbers, or both
- isascii, isprint - checks if a character is valid ASCII or printable
- toupper, tolower - transform case

###### Memory Movers (copy data from A to B)

- memset - fill a memory block with a single byte value
- bzero - clear memory (set everything to 0)
- memcpy - copy bytes, but assume no overlap
- memmove - copy bytes, handles overlapping memory safely

###### Search and Compare (find things, measure difference)

- strchr, strrchr - find a character in a string (forward/reverse)
- strncmp, memcmp - compare bytes/strings.
    - memcmp tells which one comes first. (-) is smaller, (+) if larger
- memchr - find a byte in memory, returns the address
- strnstr - find a substring

##### Type Converter

- atoi - string to integer
- itoa - integer to string

#### Section 2 - builders and transformers

The functions in this sections create new strings throught transformation and writing data. Combine, reshape and display.

##### Memory Allocators (create something new)

- substr - extract a piece of a string, return it as a new string
- strjoin - connect two strings together into a new string
- strtrim - remove characters off the edges of a string
- split - split a tring into multiple strings by a delimiter.

##### Function Appliers (transform each character)

- strmapi - apply a function to every character, build a new string from results
- striteri - apply a function to every character, modify them in place

##### Output Writers (send data somewhere)

- putchar_fd, putstr_fd, putendl_fd, putnbr_fd - write to a file descriptor (character, string, string+newline, number)

#### Section 3 -Link List 

Data structures and elements linking each other.
We need a strcuture to hold data and then dinamically allocate memory for each block and then link them. 

They are useful for allocating thousands of data structures, for example whats needed for a neural network.

They are also very quick as it is easier to just direct to different addresses where this data structures are allocated instead of cpying or replacing. 

##### Difference with arrays
Arrays are great at random access througth their indexes, but not practical to insert or delete elements.  

Link lists are made of a long chain of nodes, each node containing 2 parts, data and an address to the next node in line. 

They do not have an index, but each of them contain an address to where the next node is located. They can be anywhere in the memory.

Inserting a node is easy as it takes the previous address and then points to the next one. But searching is mucho longer. 



#### Makefile

`ar`
The GNU ar program creates, modifies, and extracts from archives.  An archive is a single file holding a collection of other files in a structure that makes it possible to retrieve the original individual files (called members of the archive).
`r` - inserts/replaces object files into the archive.
`c` - create the archive.
`s` - write an index (symbol table) into the archive, making linking faster. 


## Resources

#### Memmove
if both are empty we need to NULL
- https://marmota.medium.com/c-language-making-memmove-def8792bb8d5
- https://book-of-gehn.github.io/articles/2024/09/21/Behind-memcpy-memmove.html

#### Split

##### 2D array
- [Dinamically allocate a 2D array](https://www.youtube.com/watch?v=ZLc_OpzND2c)

#### Link Lists:
- [Introduction to Link Lists](https://www.youtube.com/watch?v=MCIwn7mY4jY)

#### AI
- AI was used in this project as a Socratic teacher dealing with examples to better understand some concepts and to ask questions to clarify my own thinking. 

## Friendly repos: 

- https://github.com/aiamlucas/c-the-universe-and-everything
- https://github.com/vineetme/libft_docs


