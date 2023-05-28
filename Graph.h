#ifndef GRAPH_H
#define GRAPH_H

#include "LocatorHeap.h"
#include <vector>
using std::vector;

#include <limits>
using std::numeric_limits;
using std::greater;
class Edge;

class Vertex
{
public:
    int label;
    vector<Edge*> edges;

    bool visited;
    float distanceTo;
    vector<Vertex*> pathTo;
    Heap<Vertex*>::Locator locator;

    //  Vertex ( int l ) : label (l), visited(false), distanceTo(numeric_limits<float>::infinity()) { }
   
    bool operator < ( const Vertex &v ) const 
    { 
        // TODO for locatorheap implementation
        return distanceTo < v.distanceTo;
    }

    Vertex ( int l ) : label (l) { }
};

class Edge
{
public:
    Vertex *v1, *v2;
    float weight;

    Edge ( Vertex *nv1, Vertex *nv2, float newWeight ) : v1 ( nv1 ), v2 ( nv2 ), weight ( newWeight ) { }
};


class Graph
{
protected:
    vector<Vertex*> v;
    vector<Edge*> e;

public:
    Graph () {}
    
    ~Graph ()
    {
        
          
        for (auto vertex : v) {
            delete vertex;
        }
        for (auto edge : e) {
            delete edge;
        }
    }

   
     Graph(const Graph& other) = delete;
    Graph& operator=(const Graph& other) = delete; 
    Graph(Graph&& other) = delete; 
    Graph& operator=(Graph&& other) = delete; 
    
    void insertVertex ( int label )
    {
        Vertex* newVertex = new Vertex(label);
        v.push_back(newVertex);
    }

    void insertEdge ( int l1, int l2, float weight )
    {
        
        Vertex* vertex1 = nullptr;
        Vertex* vertex2 = nullptr;
        for (auto vertex : v) {
            if (vertex->label == l1) {
                vertex1 = vertex;
            }
            else if (vertex->label == l2) {
                vertex2 = vertex;
            }
            if (vertex1 && vertex2) {
                break;
            }
        }

        
        Edge* newEdge = new Edge(vertex1, vertex2, weight);
        vertex1->edges.push_back(newEdge);
        vertex2->edges.push_back(newEdge);
        e.push_back(newEdge);
    }

    vector<Vertex*> shortestPath ( int start, int end )
    {
     //TODO:Implement Dijkstra Algorithm using LocatorHeap.h
   
    // Check if the start and end vertices are valid
    if (start < 0 || start >= v.size() || end < 0 || end >= v.size()) {
        return vector<Vertex*>();
    }

    // Initialize distances and visited flags for all vertices
    for (auto vertex : v) {
        vertex->visited = false;
        vertex->distanceTo = numeric_limits<float>::infinity();
        vertex->pathTo.clear();
    }

    // Set the distance of the start vertex to 0
    v[start]->distanceTo = 0;

    // Create a heap to store vertices based on their distance
    Heap<Vertex*> heap;

    // Insert all vertices into the heap
    for (auto vertex : v) {
        vertex->locator = heap.insertElement(vertex);
    }

    while (!heap.isEmpty()) {
        // Get the vertex with the minimum distance from the heap
        Vertex* currentVertex = heap.removeMin();

        // Mark the current vertex as visited
        currentVertex->visited = true;

        // Stop the algorithm if we reached the end vertex
        if (currentVertex->label == end) {
            break;
        }

        // Explore the neighbors of the current vertex
        for (Edge* edge : currentVertex->edges) {
            Vertex* neighborVertex = (edge->v1 != currentVertex) ? edge->v1 : edge->v2;

            if (!neighborVertex->visited) {
                // Calculate the distance to the neighbor vertex via the current vertex
                float distance = currentVertex->distanceTo + edge->weight;

                // Update the distance and path if the new distance is smaller
                if (distance < neighborVertex->distanceTo) {
                    neighborVertex->distanceTo = distance;
                    neighborVertex->pathTo = currentVertex->pathTo;
                    neighborVertex->pathTo.push_back(currentVertex);

                    // Update the heap to reflect the new distance
                    heap.update(neighborVertex->locator);
                }
            }
        }
    }

    // Retrieve the shortest path from the start vertex to the end vertex
    return v[end]->pathTo;

        
    }
};

#endif


