#ifndef GRAPH_H
#define GRAPH_H

// type of the elements in the graph
typedef char graph_type;

// a graph
typedef struct graph_tag {
    int size; // number of vertices in graph
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

vertex* graph_add_vertex(graph*, graph_type);
void graph_add_edge_ele(graph*, graph_type, graph_type);
void graph_add_edge(vertex*, vertex*);

void print_graph(graph*);

graph* create_graph();
void destroy_graph(graph*);

#endif

