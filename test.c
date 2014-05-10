#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"
#include "stack.h"
#include "chaitin.h"

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif


// create and use a simple graph
void test_graph() {
    DEBUG_PRINT("\ntest_graph:\n");
    DEBUG_PRINT("  creating graph...\n");

    // allocate a new graph
    graph* my_graph = create_graph();
    assert(my_graph != NULL);
    assert(my_graph->size == 0);
    assert(my_graph->vertices == NULL);

    DEBUG_PRINT("  adding a new vertex...\n");

    // add a vertex
    vertex* first_node = graph_add_vertex(my_graph, 'a');
    assert(my_graph->size == 1);
    assert(my_graph->vertices == first_node);
    assert(first_node->color == -1);
    assert(first_node->removed == 0);
    assert(first_node->element == 'a');
    assert(first_node->num_edges == 0);
    assert(first_node->edges == NULL);
    assert(first_node->next == NULL);

    DEBUG_PRINT("  adding edge to a new vertex...\n");

    vertex* second_node = graph_add_vertex(my_graph, 'b');
    assert(my_graph->size == 2);
    // add edge from 'a' to 'b'
    graph_add_edge(first_node, second_node);
    assert(first_node->edges->to == second_node);
    assert(first_node->edges->next == NULL);
    assert(second_node->edges->to == first_node);
    
    // print it
    #ifdef DEBUG
    print_graph(my_graph);
    #endif
    
    DEBUG_PRINT("  freeing graph...\n");

    // free the graph
    destroy_graph(my_graph);

    printf("+ graph test passed!\n");
}

// create and use a stack
void test_stack() {
    DEBUG_PRINT("\ntest_stack:\n");

    vertex a;
    a.element = 'a';
    vertex b;
    b.element = 'b';

    DEBUG_PRINT("  push 2 nodes...\n");

    push(&a);
    push(&b);

    DEBUG_PRINT("  pop them off...\n");

    vertex* c = pop();
    assert(c->element == 'b');
    vertex* d = pop();
    assert(d->element == 'a');

    DEBUG_PRINT("  ensure stack is empty...\n");

    assert(is_stack_empty());

    DEBUG_PRINT("  fill the stack...\n");

    int i;
    for (i = 0; i < MAX_STACK_SIZE; i++) {
        push(NULL);
    }
    assert(is_stack_full());

    empty_stack();
    assert(is_stack_empty());

    printf("+ stack test passed!\n");
}


// 2 color a 3 node, 2 edge graph
void test_chaitin() {
    DEBUG_PRINT("\ntest_chaitin:\n");
    DEBUG_PRINT("  creating graph...\n");

    graph* g = create_graph();

    vertex* a = graph_add_vertex(g, 'a');
    vertex* b = graph_add_vertex(g, 'b');
    vertex* c = graph_add_vertex(g, 'c');
    
    graph_add_edge(a, b);
    graph_add_edge(a, c);

    assert(a->color == -1);
    assert(b->color == -1);
    assert(c->color == -1);

    DEBUG_PRINT("  coloring graph...\n");

    color_graph(g, 2);

    #ifdef DEBUG
    print_graph(g);
    #endif

    assert(a->color == 0);
    assert(b->color == 1);
    assert(c->color == 1);

    destroy_graph(g);

    printf("+ algorithm test (no spill) passed!\n");
}

// 1 color a 3 node, 2 edge graph
// the node with the most edges should be spilled
void test_chaitin_spill() {
    DEBUG_PRINT("\ntest_chaitin_spill:\n");
    DEBUG_PRINT("  creating graph...\n");

    graph* g = create_graph();

    vertex* a = graph_add_vertex(g, 'a');
    vertex* b = graph_add_vertex(g, 'b');
    vertex* c = graph_add_vertex(g, 'c');

    graph_add_edge(a, b);
    graph_add_edge(a, c);
    
    assert(a->color == -1);
    assert(b->color == -1);
    assert(c->color == -1);

    DEBUG_PRINT("  coloring graph...\n");

    color_graph(g, 1);

    #ifdef DEBUG
    print_graph(g);
    #endif

    assert(a->color == -1); // spilled node
    assert(b->color == 0);
    assert(c->color == 0);

    destroy_graph(g);

    printf("+ algorithm test (spill) passed!\n");
}

int main(int argc, char * argv[]) {
    test_graph();
    test_stack();
    test_chaitin();
    test_chaitin_spill();
    return EXIT_SUCCESS;
}
