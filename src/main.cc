#include "graph.h"

int main()
{
    Graph graph;
    graph.LoadGraphFromFile("/home/lunarskii/project/A2_SimpleNavigator_v1.0-1/src/graph2.txt");
    graph.ExportGraphToDot("/home/lunarskii/project/A2_SimpleNavigator_v1.0-1/src/output.txt");
}