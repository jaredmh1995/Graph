//Jared Hazel
//CSS 502A
//Assignment 3
//Due Date: 2/16/2021
//This class finds the shortest path of a graph

#include "graphm.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

//-------------------------------- Default Constructor --------------------------
//This method constructs the inital values for TableType T
GraphM::GraphM(){
  for(int i=0; i<=100; i++){
    for(int t=0; t<=100; t++){
      T[i][t].visited = false;
      T[i][t].dist = 2147483647;
      T[i][t].path = 0;
    }
  }
}

//-------------------------------- Deconstructor --------------------------------
//Because we are not using pointers in this class, it does nothing 
//But it was added since my program required a deconstructor to run a class
GraphM::~GraphM(){

}

//-------------------------------- Build Graph --------------------------------
//This method takes the data from the text file and adds them to the C array
//Note: to match T array, C is also not using index 0
void GraphM::buildGraph( ifstream & infile1){

  while(!infile1.eof()){

  //This part gets the size of the graph and add defaults values to the C array
  int num=0;
  string p="";
  getline(infile1, p);
  if(p == ""){
    infile1.close();
    break;
  }

  num = stoi(p);

  for(int i=1; i<=num; i++){
    for(int t=1; t<=num; t++){
      C[i][t] = 2147483647;
    }
  }

  size = num;
  //Then the method gets the location and loops through based
  //on the size 
  string location;
  for(int i=1; i<=num; i++){
    getline(infile1, location);
    //If the location is bigger then 50 chars, then the string is edited down
    if((location.length()) > 50){
      string temp;
      for(int l=0; l<50; l++){
        temp = temp + location[l];
      }
      location = temp;
    }
    
    data[i] = location;
    location = "";
  }
  //The part of this method gets the connection information between the nodes
  //After all information is added to C, then the method ends 
  int left;
  int top;
  int value;
  string hold;
  getline(infile1, hold);
  stringstream stream(hold);
  while(1){
      stream>>left;
      stream>>top;
      stream>>value;
      if(!stream)
        break;
    }

  while(value != 0){
    C[left][top] = value;
    getline(infile1, hold);
    stringstream stream(hold);

    while(1){
      stream>>left;
      stream>>top;
      stream>>value;
      if(!stream)
        break;
    }
  }
  break;
 }
}

//-------------------------------- Insert Edge --------------------------------
//This method adds a new edge between nodes 
//Assumtpion: This is additional edges after the inital graph build
//             Cannot add additional node(s) and cannot change already established path
//             Based on the instructions, you are inserting an edge, not changing edges
bool GraphM::insertEdge(int left, int top, int dist){
  //If the values are largers than size, then return false 
  if((left>size) || (top>size)){
    return false;
  }
  //If it already has a value, return false 
  else if(C[left][top] != 2147483647){
    return false;
  }
  //If it does equal 2147483647, then you update C, find shortest path
  // and return true 
  else{
    C[left][top] = dist;
    findShortestPath();
    return true;
  }
}

//-------------------------------- Remove Edge --------------------------------
//This method removes the edges between two nodes 
bool GraphM::removeEdge(int left, int top){
  //Determines if values are within the bounds of the graph
  //if not, false is returned 
  if(left<1 || left>size){
    return false;
  }
  else if(top<1 || top>size){
    return false;
  }
  //Value at graph point is returned to default value 
  //and shortest path is found again
  else{
    C[left][top] = 2147483647;
    findShortestPath();
    return true;
  }
}

//------------------------------ Find Shortest Path --------------------------------
//This method finds the shortest path based on the values in C.  Then addes those 
//values and apth into T
void GraphM::findShortestPath(){
  //Makes visited false to ensure method works
  //Could be doing re-edits from insert or remove method 
  for(int r=1; r<=size; r++){
    for(int y=1; y<=size; y++){
      T[r][y].visited = false;
    }
  }

  //This loop goes through each position to find the shorest path from that node
  for(int source=1; source<=size; source++){

    //Make all values infinity to start off
    //Could be doing re-edits from insert or remove method 
    for(int p=1; p<=size; p++){
      T[source][p].dist = 2147483647;
      T[source][p].path = 0;
    }

    //Tracks current potion, counts path distance, 
    //and ensures all nodes are counted
    int currentPos = source;
    int runningTotal=0;
    int counter=1;

    //This loop goes through the graph to make sure every node is visited 
    while(counter != size){
      //This loop finds the next smallest path to an unvisited node from the source 
      for(int i=1; i<=size; i++){

        if(C[currentPos][i] != 2147483647){

          if(T[source][i].dist > (C[currentPos][i]+runningTotal)){

            if(T[source][i].visited == false){

              T[source][i].dist = C[currentPos][i]+runningTotal;
              T[source][i].path = currentPos;
            }
          }
        }
      }

      //Finds the next smallest route to continue
      int temp = 2147483647;
      for(int i=1; i<=size; i++){

        if(T[source][i].dist < temp){

          if(T[source][i].visited == false){
            temp = T[source][i].dist;
            currentPos = i;
          }
        }
      }
      //Once node is selected, it is marked as visited and counter is increased
      runningTotal = T[source][currentPos].dist;
      T[source][currentPos].visited = true;
      counter++;
    }
  }
}

//-------------------------------- Display All --------------------------------
//This method displays the shortest route from a single node to all others
//using in information in T
void GraphM::displayAll(){
  cout<<"Description         From node   To node   Dijkstra's     Path    "<<endl;
  //Loops through T based on the size
  for(int i=1; i<=size; i++){
    //Displays location
    cout<<data[i]<<endl<<endl;
    //This loop displays shortest path and distance, if available, from 
    //a single node to all others 
    for(int t=1; t<=size; t++){
      
      if(t != i){
        //i variable is under From node
        //t variable is under To Node 
        cout<<setw(22)<<i;
        cout<<setw(13)<<t;
        //If no path is avialable then ---- is displayed
        //Otherwise distance from T is displayed 
        if( T[i][t].dist == 0 || T[i][t].dist == 2147483647){
          cout<<setw(11)<<"----"<<endl;
        }
        else{
          cout<<setw(11)<<T[i][t].dist;
          string pathList="";
          int track = t;
          //This loop displays the path from variable i to t 
          while(track != i){

            pathList =   to_string(T[i][track].path) + " "+pathList;
            track = T[i][track].path;
          }
          cout<<"           "<<pathList<<""<<t<<endl;
        }
      }
    }
  }
}

//-------------------------------- Display --------------------------------
//This method displays distance and path from one node to another 
void GraphM::display(int nodeOne, int nodeTwo){
  cout<<endl;
  //If not connection present then ---- is displayed 
  if(T[nodeOne][nodeTwo].dist == 0 || T[nodeOne][nodeTwo].dist == 2147483647){
    cout<<setw(5)<<nodeOne<<setw(5)<<nodeTwo<<"        "<<"----"<<endl;
  }
  //
  else{
    int track = nodeTwo;
    string placeList="";
    //This loop gets the numerical path you would take 
    while(track != (nodeOne)){
      placeList = to_string(T[nodeOne][track].path) + " "+placeList;
      track = T[nodeOne][track].path;
    }

    placeList = placeList + to_string(nodeTwo);
    //Prints nodes, distance, and numerical path 
    cout<<setw(5)<<nodeOne<<setw(5)<<nodeTwo<<setw(8)<<T[nodeOne][nodeTwo].dist;
    cout<<"      "+placeList<<endl;
    track = nodeTwo;
    stringstream stream(placeList);
    //This loops prints out the locations you visit in the path 
    while(1){
      int dataNum;
      stream>>dataNum;
      if(!stream)
        break;
      cout<<data[dataNum]<<endl;
      cout<<endl;
    }
  }
}