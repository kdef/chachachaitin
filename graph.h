#ifndef GRAPH_H
#define GRAPH_H

typedef char graph_type;

// a graph - implemented as an adjacency list
typedef struct graph_tag {
    int size;
    struct vertex_node* vertices;
} graph;

// a vertex in the graph
typedef struct vertex_node {
    graph_type element;
    int color;
    int removed;
    int num_edges;
    struct edge_node* edges;
    struct vertex_node* next;
} vertex;

// an edge between vertices
typedef struct edge_node {
    struct vertex_node* to;
    struct edge_node* next;
} edge;

graph* create_graph();
void destroy_graph(graph*);

vertex* graph_add_vertex(graph*, graph_type);
void graph_add_edge(vertex*, vertex*);

// return the first vertex with the given element
vertex* graph_get_vertex(graph*, graph_type);

// print graph as a list of vertices
void print_graph(graph*);

#endif

