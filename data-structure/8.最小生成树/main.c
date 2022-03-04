#include <stdio.h>

#include "graph.h"

void init_undirected_graph(struct Graph *g) {
    graph_init(g, 6, UNDIRECTED_GRAPH);

    graph_add_edge(g, 0, 1, 1);
    graph_add_edge(g, 0, 2, 1);
    graph_add_edge(g, 0, 3, 1);
    graph_add_edge(g, 1, 2, 1);
    graph_add_edge(g, 4, 5, 1);
}

void test_undirected_graph() {
    struct Graph g;
    init_undirected_graph(&g);

    printf("Degree: \n");
    for (int i = 0; i < 6; i++) {
        printf("%d => %d\n", i, graph_degree(&g, i));
    }

    printf("DFS:");
    graph_dfs(&g, 0);
    printf("\n");

    printf("BFS:");
    graph_bfs(&g, 0);
    printf("\n");

    graph_destroy(&g);
}

void init_directed_graph(struct Graph *g) {
    graph_init(g, 4, DIRECTED_GRAPH);

    graph_add_edge(g, 0, 3, 1);
    graph_add_edge(g, 0, 2, 1);
    graph_add_edge(g, 2, 1, 1);
    graph_add_edge(g, 1, 0, 1);
}

void test_directed_graph() {
    struct Graph g;
    init_directed_graph(&g);

    printf("Degree: \n");
    for (int i = 0; i < 6; i++) {
        printf("%d => %d(%d in, %d out)\n", i, graph_degree(&g, i), graph_in_degree(&g, i),
               graph_out_degree(&g, i));
    }

    printf("DFS:");
    graph_dfs(&g, 0);
    printf("\n");

    printf("BFS:");
    graph_bfs(&g, 0);
    printf("\n");

    graph_destroy(&g);
}

void test_spanning_tree() {
    struct Graph g, t_prim, t_kruskal, t_dfs, t_bfs;
    graph_init(&g, 4, UNDIRECTED_GRAPH);

    graph_add_edge(&g, 0, 1, 1);
    graph_add_edge(&g, 0, 2, 2);
    graph_add_edge(&g, 0, 3, 3);
    graph_add_edge(&g, 1, 2, 4);

    graph_spanning_tree_bfs(&g, &t_bfs);
    // graph_save(&t_bfs, "t_bfs.dot");

    graph_spanning_tree_dfs(&g, &t_dfs);
    // graph_save(&t_dfs, "t_dfs.dot");

    graph_spanning_tree_prim(&g, &t_prim);
    // graph_save(&t_prim, "t_prim.dot");

    graph_spanning_tree_kruskal(&g, &t_kruskal);
    // graph_save(&t_kruskal, "t_kruskal.dot");

    graph_destroy(&g);
    graph_destroy(&t_prim);
    graph_destroy(&t_kruskal);
    graph_destroy(&t_dfs);
    graph_destroy(&t_bfs);
}

int main() {
    printf("Test undirected graph\n");
    test_undirected_graph();
    printf("Test directed graph\n");
    test_directed_graph();
    printf("Test_spanning_tree\n");
    test_spanning_tree();
}