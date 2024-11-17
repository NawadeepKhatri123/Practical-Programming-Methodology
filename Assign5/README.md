
This C++ program demonstrates basic functional programming techniques such as map, filter, reduce, zip, and generate using std::function and templates to work with vectors of vectors. It provides a clean, functional-style interface for operating on sequences of data.

Features

generate: Generates a sequence of values based on a user-defined function.

zip: Combines two vectors into a single vector of paired elements.

filter: Filters elements of a vector based on a predicate.

map: Transforms elements of a vector using a user-defined function.

reduce: Aggregates the elements of a vector using a binary operation and an identity value.

printElem: Prints a single vector of elements.

printVec: Prints a vector of vectors, calling printElem on each subvector.

Compilation & Execution


Steps to compile and run:
Save the program in a file named temp.cpp.

Compile using a C++11 or later standard.

Copy code
  
    g++ -o temp temp.cpp

Run the executable:

    ./program
