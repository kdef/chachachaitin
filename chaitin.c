#include <stdlib.h>
#include "stack.h"
#include "chaitin.h"

// chaitin.c

// return 1 if node has no neighbors of color
// return 0 otherwise
int valid_node_color(vertex* node, int color) {
    // no edges means any color will work
    if (node->num_edges == 0) return 1;

    edge* e;
    for (e = node->edges; e != NULL; e = e->next) {
        if (e->to->color == color) return 0;
    }
    return 1;
}

void remove_node(vertex* node) {
    node->removed = 1;
    // decrease the degree of each connected node
    edge* e;
    for (e = node->edges; e != NULL; e = e->next) {
        e->to->num_edges--;
    }
}

// reset the removed and num_edges fields of a node
void reset_node(vertex* v) {
    int count = 0;
    edge* e;
    for (e = v->edges; e != NULL; e = e->next) {
        count++;
    }
    v->num_edges = count;
    v->removed = 0;
}

// chaitin's algorithm
void color_graph(graph* g, int n) {
    if (g == NULL) return;
    if (g->vertices == NULL) return;

    int size = g->size;
    int spilled = 0; // number of nodes not considered
    
    // simplify graph
    int simplified; // did we simplify the graph on this iteration?
    vertex* node;
    while (spilled < g->size) {
        // remove all nodes with degree < n
        do {
            simplified = 0;
            for (node = g->vertices; node != NULL; node = node->next) {
                if ((node->removed == 0) && (node->num_edges < n)) {
                    remove_node(node);
                    // push it onto the stack for coloring
                    size--;
                    push(node);
                    simplified = 1;
                }
            }//for
        } while ((size != 0) && (simplified == 1));

        // spill if we can't color this
        if (size == 0) {
            break;
        } else {
            empty_stack();
            spill(g); 
            spilled++;
            size = g->size - spilled;
        }
    }

    // color in reverse order of removal
    int i;
    while (!is_stack_empty()) {
        node = pop();
        reset_node(node);
        // use first available color
        for (i = 0; i < n; i++) {
            if (valid_node_color(node, i)) {
                node->color = i;
                break;
            }
        }//for
    }
}

vertex* spill(graph* g) {
    vertex* to_spill = g->vertices;
    vertex* node;
    for (node = g->vertices; node != NULL; node = node->next) {
        if (node->num_edges > to_spill->num_edges) to_spill = node;
    }

    remove_node(to_spill);
    return to_spill;
}

