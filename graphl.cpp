//Jared Hazel
//CSS 502A
//Assignment 3
//Due Date: 2/16/2021
//This class finds the depth-first path

#include "graphl.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

//-------------------------------- Default Constructor --------------------------
//This method adds default values to the point array 
//Loops through array to add values 
GraphL::GraphL(){
  for(int i=0; i<100; i++){
    point[i].visited = false;
    point[i].edgeHead = NULL;
    point[i].data = NULL;
  }
}

//-------------------------------- Deconstructor --------------------------
//This method frees all memory
//It loops through point and deletes any used Edge Nodes until they are all NULL
//and then the program deletes NodeData 
GraphL::~GraphL(){
 for(int i=0; i<100; i++){
    while(point[i].edgeHead != NULL){
      EdgeNode *temp = NULL;
      temp = point[i].edgeHead;
      point[i].edgeHead = point[i].edgeHead->nextEdge;
      delete temp;
      temp=NULL;
    }
    if(point[i].data != NULL){
      delete point[i].data;
      point[i].data = NULL;
    }
  }
}

//-------------------------------- Build Graph--------------------------
//This method reads the text file and adds the values to the point array 
void GraphL::buildGraph( ifstream & infile1){
  //Loops through text file 
  while(!infile1.eof()){

   string p="";
   getline(infile1, p);
   if(p == ""){
    infile1.close();
    break;
   }

   size = stoi(p);
   string location;
  //Gets name of locations for nodes
   for(int i=0; i<size; i++){
    getline(infile1, location);
    //If location string is bigger than 50 chars, it is edited down to 50 chars 
    if((location.length()) > 50){
      string temp;
      for(int l=0; l<50; l++){
        temp = temp + location[l];
      }
      location = temp;
    }
    //Creates new NodeData to add location to point 
    NodeData *locationData = new NodeData;
    *locationData = location;
    delete point[i].data;
    point[i].data = NULL;
    point[i].data = locationData;
    location = "";
   }

   int graphNode=1;
   int edgeNode=1;
   string hold;
   //This adds all edges to point 
   //Leaves loop once 0 0 is read 
   while(graphNode != 0){
     
     getline(infile1, hold);
     stringstream stream(hold);
     while(1){
      stream>>graphNode;
      stream>>edgeNode;
      if(!stream)
        break;
    }

    if(graphNode == 0 || edgeNode == 0){
      break;
    }
    //Adds new edgeHead 
    if(point[(graphNode-1)].edgeHead == NULL){

     EdgeNode *edgeNew = new EdgeNode;
     edgeNew->adjGraphNode = edgeNode;
     edgeNew->nextEdge = NULL;
     point[graphNode-1].edgeHead = edgeNew;
    }
    //Adds new nextEdge from edgeHead 
    else if(point[graphNode-1].edgeHead->nextEdge == NULL){

      EdgeNode *edgeNew = new EdgeNode;
      edgeNew->adjGraphNode = edgeNode;
      edgeNew->nextEdge = NULL;
      point[graphNode-1].edgeHead->nextEdge = edgeNew;
    }
    else{
      //Loop through edges until you find the NULL spot
      EdgeNode *current = point[graphNode-1].edgeHead->nextEdge;
      while(current->nextEdge != NULL){
        current = current->nextEdge;
      }
      EdgeNode *edgeNew = new EdgeNode;
      edgeNew->adjGraphNode = edgeNode;
      edgeNew->nextEdge = NULL;
      current->nextEdge = edgeNew;
    }
  }
    break;
  }
}

//-------------------------------- Display Graph --------------------------
//This method displays all values from point array 
void GraphL::displayGraph(){
  cout<<"Graph:"<<endl;
  for(int i=0; i<size; i++){
    cout<<"Node"<<(i+1)<<"               "<<*point[i].data<<endl<<endl;
    //If no edges are linked to position, then nothing is printed 
    if(point[i].edgeHead == NULL){
      cout<<endl;
    }
    //Finds the number of edges in a point[i]
    else{
      EdgeNode *current = point[i].edgeHead;
      int countEdge=0;
      while(current != NULL){
        countEdge++;
        current = current->nextEdge;
      }
      //Loop displays edge of a point[i]
      EdgeNode displayEdge = *point[0].edgeHead;
      for(int t = countEdge; t>0; t-- ){
        displayEdge = *point[i].edgeHead;
        int getEdge=1;
        while(getEdge != t ){
          getEdge++;
          displayEdge = *displayEdge.nextEdge;
        }
        cout<<"    edge  "<<(i+1)<<"  "<<displayEdge.adjGraphNode<<endl;
      }
      delete current;
      current = NULL;
    }
  }
  cout<<endl;
}

//-------------------------------- Depth First Search --------------------------
//This method finds a path based on the depth first search 
void GraphL::depthFirstSearch(){
  cout<<"Depth-first ordering: 1 ";
  //Variables to help keep track of the path 
  int smallest=150;
  int currentPoint=0;
  int visitCount=0;
  int notConnected = 0;
  //string offShoot;
  //int offShootCount=0;

  point[currentPoint].visited = true;
  visitCount++;
  //Loops through to ensure all nodes are counted 
  while(visitCount < size){
    //Sees if edge head is NULL or notConnected
    //Then finds the smallest adjGraphNode to continue path 
    if(point[currentPoint].edgeHead != NULL){
      EdgeNode depthNode = *point[currentPoint].edgeHead;

      while(depthNode.nextEdge != NULL){
        if(depthNode.adjGraphNode < smallest){
          if(point[depthNode.adjGraphNode-1].visited == false){
            smallest = depthNode.adjGraphNode;
          }
        }
        depthNode = *depthNode.nextEdge;
       }

       if(depthNode.adjGraphNode < smallest) {
           if(point[depthNode.adjGraphNode-1].visited == false){
            smallest = depthNode.adjGraphNode;
          }
        }
     }
     //If smallest is found then that value is printed, marked as visited,
     //smallest variable is resetted and goes back to top of loop 
    if(smallest != 150){
      if(visitCount < size-1){
        cout<<smallest<<" ";
      }
      else{
        cout<<smallest;
      }
      currentPoint = smallest-1;
      point[currentPoint].visited = true;
      visitCount++;
      smallest = 150;
      notConnected--;
    }
    else{
      //Goes back to the start of the point to find unused values 
      currentPoint = 0;
      smallest = 150;
      notConnected++;
      //If notConnected equals size (meaning unable to find new nodes)
      //Then you find remaining values that haven't been visited 
      //and resets values to find other nodes 
      if(notConnected == size){
        for(int a=0; a<size; a++){
          if(point[a].visited == false){
            point[a].visited = true;
            if(visitCount < size-1){
              cout<<a+1<<" ";
            }
            else{
              cout<<a+1;
            }
            visitCount++;
            smallest = 150;
            notConnected=0;
            a=size;
          }
        }
      }
    }
  }
  cout<<endl<<endl;
}