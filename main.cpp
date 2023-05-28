
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

#include "Graph.h"

int main(int argc, const char * argv[]) {

    // Snippet 1: read filename and open file
    string filename;
    // cin >> filename;

    filename= "graph_large1.txt";
    // filename= "graph_large2.txt";
    // filename= "graph_medium.txt";
    // filename= "graph_small1.txt";
    // filename= "graph_small2.txt";
    cout << "Filename of graph to load: "<<filename<<endl;

    ifstream inputfile(filename);
    if (!inputfile) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }
    else{
        cout<<"File Successfuly OPENED"<<endl;
    }
    // ifstream file(filename);

    // // Check if file is open
    // if (!file.is_open()) {
    //     cerr << "Error opening file!" << endl;
    //     return 1;
    // }

    // Snippet 2: get number graph size
    // int numVertices, numEdges;
    // file >> numVertices >> numEdges;
     int numVertices, numEdges;
    inputfile >> numVertices >> numEdges;

    // Snippet 3: create graph
    Graph g;

    // Snippet 4: read edges
    // create vertices
    for (int i = 0; i < numVertices; i++) {
        g.insertVertex(i);
    }

    // create edges
    for (int i = 0; i < numEdges; i++) {
        int v1, v2;
        float weight;
        inputfile >> v1 >> v2 >> weight;
        g.insertEdge(v1, v2, weight);
    }
    // for (int i = 0; i < numEdges; i++) {
    //     int v1, v2, weight;
    //     file >> v1 >> v2 >> weight;
    //     g.insertEdge(v1, v2, weight);
    // }

    // Snippet 5: read start and end of path
    int startVertex, endVertex;
    inputfile >> startVertex >> endVertex;
    inputfile.close();
    // file >> startVertex >> endVertex;
    // file.close();

    cout << "Shortest path from " << startVertex << " to " << endVertex << ":" << endl;

    // vector<Vertex*> path;

    // // Call shortest path on your graph for the start and end vertices and save result to path
    // g.shortestPath(startVertex, endVertex, path);

    // for (auto i : path) { // this is a for-each loop
    //     cout << i->label << " ";
    // }
    // // cout endline at very end
    // cout << endl;
    // return 0;

    vector<Vertex*> path = g.shortestPath(startVertex, endVertex);
    

    for (auto i : path) { // this is a for-each loop
        cout << i->label << " ";
    }
    cout<<endVertex;
    // cout endline at very end
    cout << endl;
    return 0;
}
