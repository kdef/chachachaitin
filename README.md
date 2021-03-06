Cha Cha Chaitin
===============

Implementation of [Chaitin's graph coloring register allocation algorithm](http://en.wikipedia.org/wiki/Chaitin%27s_algorithm) in C.

    $ make
    $ ./cgc 
    ~~~~~~~~~~~~~~~~
    Cha Cha Chaitin:
    ----------------
    Enter number of vertices in graph: 3
    * added vertices a through c
    Enter number of edges: 2
    Enter edges one by one in form <source><space><target>
    Edge 1: a b
    Edge 2: a c
    * added 2 edges
    Enter number of colors: 2
    * 2 colored graph
    a : 0 -> b c
    b : 1 -> a
    c : 1 -> a
    Total: 3 nodes

### Graphs

Vertices are automatically named a-z. Graphs are undirected.

    a : 1 -> b c
    b : 0 -> a
    c : 0 -> a
    Total: 3 nodes 2 colors

+ `a`, `b`, and `c` are the vertices.
+ `1`, `0`, and `0` are the colors of the vertices.
+ Characters after the `->` are the vertices to which an edge exists.

This is a graph with 3 vertices where b and c are connected to a.

### Spilling

If a graph is not n-colorable then a variable(a vertex) is spilled.
Spilled vertices are removed from the graph and not colored.

A spilled vertex is represented with color `-1`.

    a : -1 -> b c
    b : 0 -> a
    c : 0 -> a
    Total: 3 nodes 1 color

Since 1-coloring the graph was impossible, `a` was spilled.

