#ifndef GRAPHM_H
#define GRAPHM_H
#include "nodedata.h"
#include <iostream>
#include <fstream>

class GraphM{

public:

  GraphM();

  ~GraphM();

  void buildGraph( ifstream & );

  bool insertEdge(int one, int two, int dist);

  bool removeEdge(int one, int two);

  void findShortestPath();

  void displayAll();

  void display(int one, int two);

private:

struct TableType {
    bool visited;          // whether node has been visited
    int dist;              // shortest distance from source known so far
    int path;              // previous node in path of min dist
  };

  //Note: used 101 because position 0 is not being used

  NodeData data[101];              // data for graph nodes 
  int C[101][101];            // Cost array, the adjacency matrix
  int size;                             // number of nodes in the graph
  TableType T[101][101];      // stores visited, distance, path

};

#endif   