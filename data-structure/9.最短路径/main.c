#include <stdio.h>

#include "graph.h"

void init_undirected_graph(struct Graph *g) {
    graph_init(g, 6, UNDIRECTED_GRAPH);

    graph_add_edge(g, 0, 1, 6);
    graph_add_edge(g, 0, 2, 3);
    graph_add_edge(g, 1, 2, 2);
    graph_add_edge(g, 1, 3, 5);
    graph_add_edge(g, 2, 3, 3);
    graph_add_edge(g, 2, 4, 4);
    graph_add_edge(g, 3, 4, 2);
    graph_add_edge(g, 3, 5, 3);
    graph_add_edge(g, 4, 5, 5);

    // graph_save(g, "g.dot");
}

void init_directed_graph(struct Graph *g) {
    graph_init(g, 6, DIRECTED_GRAPH);

    graph_add_edge(g, 0, 1, 16);
    graph_add_edge(g, 0, 3, 13);
    graph_add_edge(g, 3, 1, 4);
    graph_add_edge(g, 1, 2, 12);
    graph_add_edge(g, 2, 3, 9);
    graph_add_edge(g, 3, 4, 14);
    graph_add_edge(g, 2, 4, 7);
    graph_add_edge(g, 2, 5, 20);
    graph_add_edge(g, 4, 5, 4);

    // graph_save(g, "g.dot");
}

int main() {
    struct Graph g1, g2, flow;
    struct Matrix dists;

    init_undirected_graph(&g1);

    printf("Test Dijikstra\n");
    graph_dijikstra(&g1, 0);
    for (int i = 0; i < g1.v; i++) {
        printf("%d => %d : %d \n", 0, i, g1.dists[i]);
    }

    printf("Test Floyd\n");
    graph_floyd(&g1, &dists);
    for (int i = 0; i < dists.rows; i++) {
        for (int j = 0; j < dists.cols; j++) {
            printf("%2d ", matrix_get(&dists, i, j));
        }

        printf("\n");
    }

    init_directed_graph(&g2);

    printf("Test Ford Fulkerson\n");
    printf("%d\n", graph_ford_fulkerson(&g2, &flow));

    graph_destroy(&g1);
    graph_destroy(&g2);
}