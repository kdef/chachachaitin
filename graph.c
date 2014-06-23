#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

// graph.c 

vertex* graph_add_vertex(graph* the_graph, graph_type element) {
    if (the_graph == NULL) {
        // this is bad
        return NULL;
    }

    // make a new node
    vertex* new_vert = malloc(sizeof(vertex));
    new_vert->element = element;
    new_vert->color = -1;
    new_vert->removed = 0;
    new_vert->num_edges = 0;
    new_vert->edges = NULL;
    new_vert->next = NULL;

    vertex* cur_vertex = the_graph->vertices;
    if (cur_vertex == NULL) {
        the_graph->vertices = new_vert;
    } else {
        // put at the end
        while (cur_vertex->next != NULL) {
            cur_vertex = cur_vertex->next;
        }
        cur_vertex->next = new_vert;
    }
    the_graph->size++;

    return new_vert;
}

vertex* graph_get_vertex(graph* g, graph_type element) {
    vertex* node;
    for (node = g->vertices; node != NULL; node = node->next) {
        if (node->element == element) return node;
    }
    return NULL;
}

// helper to create an edge
void graph_create_edge(vertex* from, vertex* to) {
    edge* new_edge = malloc(sizeof(edge));
    new_edge->to = to;
    new_edge->next = NULL;

    edge* last_edge = from->edges;
    if (last_edge == NULL) {
        from->edges = new_edge;
    } else {
        // insert at the end
        while (last_edge->next != NULL) {
            last_edge = last_edge->next;
        }
        last_edge->next = new_edge;
    }
    from->num_edges++;
}

void graph_add_edge(vertex* src, vertex* dest) {
    if (src == NULL || dest == NULL) {
        // this is bad
        return;
    }

    graph_create_edge(src, dest);

    // add another edge if the graph is undirected
    // TODO: assume always undirected for now
    graph_create_edge(dest, src);
}

graph* create_graph() {
    graph* a_graph = malloc(sizeof(graph));
    a_graph->size = 0;
    a_graph->vertices = NULL;
    return a_graph;
}

void free_edge_list(edge* head) {
    edge* node = head;
    edge* temp;
    while (node != NULL) {
        temp = node;
        node = node->next;
        free(temp);
    }
}

void destroy_graph(graph* a_graph) {
    if (a_graph == NULL) {
        return;
    }

    if (a_graph->vertices != NULL) {
        vertex* node = a_graph->vertices;
        vertex* temp;
        while (node != NULL) {
            temp = node;
            node = node->next;

            // free all this nodes edges
            free_edge_list(temp->edges);
            temp->edges = NULL;
            
            free(temp);
        }
        a_graph->vertices = NULL;
    }
    free(a_graph);
}

// assumes element is a char
void print_graph(graph* g) {
    if (g == NULL || g->size <= 0) {
        printf("Empty graph.\n");
        return;
    }

    // not empty
    vertex* node;
    for (node = g->vertices; node != NULL; node = node->next) {
        printf("%c : %d ->", node->element, node->color);
        // print each edge
        edge* e;
        for (e = node->edges; e != NULL; e = e->next) {
            printf(" %c", e->to->element);
        }
        printf("\n");
    }
    printf("Total: %d nodes\n", g->size);
}

