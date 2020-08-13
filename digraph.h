#ifndef _DIGRAPH_H
#define _DIGRAPH_H
//structure of link list 
struct node {
    struct node* next;
    int         data;
};
typedef struct node* List;

//graph
struct GraphNode {
    List list;   // adjacency list
    int vertice;      // index of vertice
    struct GraphNode* next;  //point to next graph node
};
typedef struct GraphNode* Graph;

//void insert_node(List lhead, int w);
Graph create_graph_node(int v);

//num is the total number of vertices
Graph initialise_graph(int num);
Graph findGraphNodeByV(Graph graph, int v);
void insert_edge(Graph head, int v, int w);


void freegraph(Graph ghead);
#endif