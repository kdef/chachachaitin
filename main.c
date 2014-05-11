#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "stack.h"
#include "chaitin.h"

// main.c

void add_vertices_abc(graph* g, int n) {
    int i;
    for (i = 0; i < n; i++) {
        graph_add_vertex(g, 'a' + i);
    }
}

int main(int argc, char * argv[]) {
    int num_vertices = 0;
    int num_edges = 0;
    int num_colors = 0;
    char input[5]; // should only need 4 chars (max size = 1000)

    puts("~~~~~~~~~~~~~~~~");
    puts("Cha Cha Chaitin:");
    puts("----------------");

    graph* g = create_graph();

    // prompt for size
    fputs("Enter number of vertices in graph (<1000): ", stdout);
    fflush(stdout);
    fgets(input, sizeof input, stdin);
    sscanf(input, "%d", &num_vertices);

    fputs("Enter number of edges: ", stdout);
    fflush(stdout);
    fgets(input, sizeof input, stdin);
    sscanf(input, "%d", &num_edges);

    add_vertices_abc(g, num_vertices);
    printf("* added vertices a through %c\n", 'a'+num_vertices-1);

    // read in all edges in form "src dest"
    int i;
    char src;
    char dest;
    puts("Enter edges one by one in form <source><space><target>");
    for (i = 0; i < num_edges; i++) {
        printf("Edge %d: ", i+1);
        fgets(input, sizeof input, stdin);
        sscanf(input, "%c %c", &src, &dest);
        graph_add_edge_ele(g, src, dest);
    }
    printf("* added %d edges\n", num_edges);

    // color the graph
    fputs("Enter number of colors: ", stdout);
    fgets(input, sizeof input, stdin);
    sscanf(input, "%d", &num_colors);

    color_graph(g, num_colors);
    
    printf("* %d colored graph\n", num_colors);
    print_graph(g);

    return EXIT_SUCCESS;
}

