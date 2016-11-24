# BWT-Search
BWT (burrow wheeler transform) Backward Search.

This is state of the art technique used for substring search over large text.

Currently used as the major search algorithm in DNA Analysis.


## Assumptions & Requirements :-
1. BWT encoded file with below format :-
``` 
  [<offset1>]<text1>[<offset2>]<text2>[<offset3>]<text3>... ...
```
where *offset1*, *offset2*, *offset3*, etc. are integer values that are used as unique identifiers.


## How to compile :-
1. git clone https://github.com/victor-unsw/BWT-Search
2. move to BWT-Search folder
3. cmake .
4. make 


## Syntax :-
```
./bwtsearch -n [input folder] [output file] "search text"
```
*input folder* : folder containing input files
*output file* : file which will contain result
*search text* : substring to be searched


## Features :-
1. BWT backward search algorithm is used for substring search.
2. Search takes constant time i.e. O(1).
3. State of the art technique used for substring search.

