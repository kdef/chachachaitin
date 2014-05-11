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
    if (cur_vertex != NULL) {
        while (cur_vertex->next != NULL) {
            cur_vertex = cur_vertex->next;
        }
        cur_vertex->next = new_vert;
    } else {
        // put at the front
        the_graph->vertices = new_vert;
    }
    the_graph->size++;

    return new_vert;
}

// uses the first vertex node containing a given element to add an edge
void graph_add_edge_ele(graph* g, graph_type src, graph_type dest) {
    if (g == NULL || g->vertices == NULL) return;

    vertex* a = NULL;
    vertex* b = NULL;
    // find the nodes in the graph
    vertex* node;
    for (node = g->vertices; node != NULL; node = node->next) {
        if (node->element == src) {
            a = node;
            if (b != NULL) break;
        } else if (node->element == dest) {
            b = node;
            if (a != NULL) break;
        }
    }
    graph_add_edge(a, b);
}

void graph_add_edge(vertex* src, vertex* dest) {
    if (src == NULL || dest == NULL) {
        // this is bad
        return;
    }

    edge* new_edge = malloc(sizeof(edge));
    new_edge->to = dest;
    new_edge->next = NULL;

    edge* last_edge = src->edges;
    if (last_edge != NULL) {
        while (last_edge->next != NULL) {
            last_edge = last_edge->next;
        }
        last_edge->next = new_edge;
    } else {
        src->edges = new_edge;
    }
    src->num_edges++;

    // add another edge if the graph is undirected
    if (1 == 1) {
        edge* new_edge = malloc(sizeof(edge));
        new_edge->to = src;
        new_edge->next = NULL;

        last_edge = dest->edges;
        if (last_edge != NULL) {
            while (last_edge->next != NULL) {
                last_edge = last_edge->next;
            }
            last_edge->next = new_edge;
        } else {
            dest->edges = new_edge;
        }
        dest->num_edges++;
    }
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

