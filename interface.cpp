#include <iostream>
#include "tests.h"
#include "GraphPrinter.h"

using namespace std;

Graph<int>* Graph1()
{
    Graph<int>* gr = new Graph<int>(7, true);
    gr->changeEdge(0, 1, 15);
    gr->changeEdge(0, 2, 2);
    gr->changeEdge(0, 6, 1);
    gr->changeEdge(2, 3, 3);
    gr->changeEdge(2, 4, 4);
    gr->changeEdge(3, 1, 1);
    gr->changeEdge(4, 1, 2);
    gr->changeEdge(5, 4, 10);
    gr->changeEdge(6, 0, 1);
    return gr;   
}
Graph<int>* Graph2()
{
    Graph<int>* gr = new Graph<int>(10, false);
    gr->changeEdge(0, 7, 1);
    gr->changeEdge(7, 1, 100);
    gr->changeEdge(7, 3, 15);
    gr->changeEdge(7, 3, 12);
    gr->changeEdge(7, 6, 2);
    gr->changeEdge(3, 6, 3);
    gr->changeEdge(1, 2, 10);
    gr->changeEdge(2, 3, 20);
    gr->changeEdge(4, 5, 9);

    return gr;
}



template <typename T>
void GraphConstructuor(Graph<T>* graph) {
    int choose = 0;
    int ver1 = 0;
    int ver2 = 0;
    T weight = T(1);
    while (true)
    {
        cout << "1 - change an edge" << endl;
        cout << "2 - Print Matrix" << endl;
        cout << "3 - Find Shortest path from ver1 to ver2" << endl;
        cout << "4 - exit" << endl;
        cin >> choose;
        switch (choose)
        {
        case 1:
            cout << endl;
            cout << "Enter the first vertex: ";
            cin >> ver1;
            cout << "Enter the second vertex: ";
            cin >> ver2;
            cout << "Enter a weight of the edge: ";
            cin >> weight;
            cout << endl;
            graph->changeEdge(ver1, ver2, weight);
            break;
        case 2:
            cout << endl;
            AdjacencyMatrix(graph);
            cout << endl;
            break;
        case 3:
            cout << endl;
            cout << "Enter the first vertex: ";
            cin >> ver1;
            cout << "Enter the second vertex: ";
            cin >> ver2;
            cout << endl;
            PrintDijkstra(graph, ver1, ver2);
            cout << endl;
            break;
        default:
            return;
        }
    }
};


void interfaceGraph()
{
    int choose = 0;
    int number = 0;
    int i = 0;
    int j = 0;
    int vert1 = 0;
    int vert2 = 0;
    int weight = 0;
    Graph<int>* gr;

    cout << "1 - Graph1" << endl;
    cout << "2 - Graph2" << endl;
    cout << "3 - to create a graph yourself" << endl;
    cout << "4 - exit" << endl;
    cin >> choose;
    cout << endl;
    switch (choose)
    {
    case 1:
        gr = Graph1();
        GraphConstructuor(gr);
        break;
    case 2:
        gr = Graph2();
        GraphConstructuor(gr);
        break;
    case 3:
        cout << "Enter a number of vertexes" << endl;
        cin >> number;
        cout << "Enter 1 if the graph is directed" << endl;
        cin >> choose;
        switch (choose)
        {
        case 1:
            gr = new Graph<int>(number, true);
            GraphConstructuor(gr);
            break;
        default:
            gr = new Graph<int>(number, false);
            GraphConstructuor(gr);
            break;
        }

    }
};


int main() {
    alltests();
    interfaceGraph();
    return 0;
};