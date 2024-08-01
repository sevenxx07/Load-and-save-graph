# Formulation of the problem
Implementation of a library for loading and saving a data structure (graph) from/to a file, both in textual representation and in binary form. 
The input entry of the graph is prescribed and the graph is entered as a list of edges, where each edge is defined by the number of the starting vertex, 
the number of the ending vertex and then an integer indicating the cost of the edge. All numeric values ​​correspond to the range of a 32-bit integer, type int.
A graph is represented as a list of all edges in the graph. Graph edges are defined using a triplet of integers (start vertex, end vertex, edge cost).
Text chart format
Each line contains three integers (one edge) from the range of a 32-bit signed integer. The numbers are always separated by one space and there is one new #
line character after each triplet of numbers. Example of text notation of the graph in the image<br />
![obrazek](https://github.com/user-attachments/assets/547f5349-1b97-4687-91df-44e634654900)<br />

0 1 7<br />
0 2 9<br />
0 5 14<br />
1 2 10<br />
1 3 15<br />
2 3 11<br />
2 5 255<br />
3 4 20001<br />
4 5 9<br />
# Implementation of the problem
I used separate structure for edge and graph. Edge structure contains information about two vertices that make this edge and about cost. The graph structure 
contains array of pointers to edges, size and capacity of graph that is dynamically allocated
