# Multiway-Sort
Implementation of the multi-pass multi-way sorting algorithm in C++.

## Q4: External Memory Sorting
Consider the following relations:
> Emp (eid (integer), ename (string), age (integer), salary (double))

Fields of types integer, double, and string occupy 4, 8, and 40 bytes, respectively. <br>
Each block can fit at most one tuple of an input relation. <br>
There are at most 22 blocks available to the sort algorithm in the main memory. <br>
Implement the multi-pass multi-way sorting for the relation Emp in C++. The relation should be sorted by eid. <br>
+ The input relation is stored in a CSV file, i.e., each tuple is in a separate line and fields of each record are separated by commas.
+ The result of the sort must be stored in a new CSV file. The file that stores the relation Emp is Emp.csv.
+ Your program must assume that the input file is in the current working directory, i.e., the one from which your program is running.
+ The program must store the result in a new CSV file with the name EmpSorted.csv in the current working directory.
__________________________________________________________________________________________________________________________________________________

## To run the Algorithm
1. Add your Emp.csv to the source directory.
2. Run:
```
> g++ -o out multiwaySort.cpp
> out.exe
```
3. Required Sort is implemented and the file is stored in source directory.

__________________________________________________________________________________________________________________________________________________
Oregon State University, Winter 2021 (CS540)
