#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define INF 99999

static void graph_init_marked(struct Graph *g) {
    if (g->marked == NULL) {
        g->marked = malloc(g->v * sizeof(bool));
    }
    for (int i = 0; i < g->v; i++) {
        g->marked[i] = false;
    }

    if (g->path == NULL) {
        g->path = malloc(g->v * sizeof(int));
    }
    for (int i = 0; i < g->v; i++) {
        g->path[i] = -1;
    }
}

static void graph_destroy_marked(struct Graph *g) {
    if (g->marked != NULL) {
        free(g->marked);
    }
    if (g->path != NULL) {
        free(g->path);
    }
}

// TODO: DONE
void graph_init(struct Graph *g, int num_vertices, enum GraphType type) {
    g->v = num_vertices;
    g->e = 0;
    g->type = type;
    matrix_init(&g->m, num_vertices, num_vertices, ROW_MAJOR);
    g->marked = NULL;
    g->path = NULL;
}

// TODO: DONE
void graph_destroy(struct Graph *g) {
    g->v = 0;
    g->e = 0;
    matrix_destroy(&g->m);
    graph_destroy_marked(g);
}

// TODO: DONE
void graph_add_edge(struct Graph *g, int u, int v, DataType weight) {
    matrix_set(&g->m, u, v, weight);
    if (g->type == UNDIRECTED_GRAPH) {
        matrix_set(&g->m, v, u, weight);
    }
    g->e++;
}

// TODO: DONE
int graph_degree(struct Graph *g, int v) {
    if (g->type == UNDIRECTED_GRAPH) {
        return graph_in_degree(g, v);
    }

    return graph_in_degree(g, v) + graph_out_degree(g, v);
}

// TODO: DONE
int graph_in_degree(struct Graph *g, int v) {
    int n = 0;

    for (int i = 0; i < g->v; ++i) {
        if (matrix_get(&g->m, i, v) != 0) {
            n++;
        }
    }

    return n;
}

// TODO: DONE
int graph_out_degree(struct Graph *g, int v) {
    int n = 0;

    for (int i = 0; i < g->v; ++i) {
        if (matrix_get(&g->m, v, i) != 0) {
            n++;
        }
    }

    return n;
}

// TODO: DONE
// 判断是否连通图
bool graph_is_connected(struct Graph *g) {
    graph_dfs(g, 0);

    for (int i = 0; i < g->v; i++) {
        if (!g->marked[i]) {
            return false;
        }
    }

    if (g->type == UNDIRECTED_GRAPH) {
        return true;
    }

    // Flip edge direction
    g->m.mode = 1 - g->m.mode;
    graph_dfs(g, 0);
    bool connected = true;
    for (int i = 0; i < g->v; i++) {
        if (!g->marked[i]) {
            connected = false;
            break;
        }
    }
    g->m.mode = 1 - g->m.mode;

    return connected;
}

// TODO: DONE
// 判断两个顶点是否连通
bool graph_is_vertex_connected(struct Graph *g, int u, int v) {
    graph_dfs(g, u);
    return g->marked[v];
}

// TODO: DONE
// 两个顶点之间的距离
DataType graph_vertex_distance(struct Graph *g, int u, int v) {
    graph_dfs(g, u);

    if (!g->marked[v]) {
        return -1;
    }

    DataType dist = 0;
    while (g->path[v] >= 0) {
        dist += matrix_get(&g->m, g->path[v], v);
        v = g->path[v];
    }

    return dist;
}

// TODO: DONE
// 判断sg是否为g的子图
bool graph_is_subgraph(struct Graph *g, struct Graph *sg) {
    if (g->m.rows < sg->m.rows) {
        return false;
    }

    for (int i = 0; i < sg->m.rows; i++) {
        for (int j = 0; j < sg->m.cols; j++) {
            if (matrix_get(&sg->m, i, j) != 0 && matrix_get(&g->m, i, j) == 0) {
                return false;
            }
        }
    }
    return true;
}

// TODO: DONE
// 判断sg是否是g的（强）连通分量
bool graph_is_connected_component(struct Graph *g, struct Graph *sg) {
    return graph_is_subgraph(g, sg) && graph_is_connected(sg);
}

void graph_dfs_recursion(struct Graph *g, int v, int from) {
    g->marked[v] = true;
    g->path[v] = from;

    for (int i = 0; i < g->v; i++) {
        if (matrix_get(&g->m, v, i) != 0 && !g->marked[i]) {
            graph_dfs_recursion(g, i, v);
        }
    }
}

void graph_dfs(struct Graph *g, int v) {
    graph_init_marked(g);
    graph_dfs_recursion(g, v, -1);
}

void graph_bfs(struct Graph *g, int v) {
    graph_init_marked(g);

    Queue q;

    queue_init(&q);

    queue_enqueue(&q, v);
    g->marked[v] = true;
    g->path[v] = -1;

    while (!queue_empty(&q)) {
        int u = queue_dequeue(&q);

        for (int i = 0; i < g->v; i++) {
            if (matrix_get(&g->m, u, i) != 0 && !g->marked[i]) {
                queue_enqueue(&q, i);
                g->marked[i] = true;
                g->path[i] = u;
            }
        }
    }

    queue_destroy(&q);
}

void graph_save(struct Graph *g, const char *filename) {
    FILE *fp = fopen(filename, "w");

    fprintf(fp, "strict %sgraph {\n", g->type == DIRECTED_GRAPH ? "di" : "");

    for (int i = 0; i < g->v; i++) {
        for (int j = 0; j < g->v; j++) {
            int weight = matrix_get(&g->m, i, j);
            if (weight != 0) {
                fprintf(fp, "\t%d %s %d [label = %d]\n", i, g->type == DIRECTED_GRAPH ? "->" : "--",
                        j, weight);
            }
        }
    }

    fprintf(fp, "}\n");

    fclose(fp);
}

void graph_matrix_init(struct Graph *g) {
    for (int i = 0; i < g->v; i++) {
        for (int j = 0; j < g->v; j++) {
            if (i != j && matrix_get(&g->m, i, j) == 0) {
                matrix_set(&g->m, i, j, INF);
            }
        }
    }
}

// 用Dijikstra算法计算顶点v到其它顶点的距离,
// 并将距离记录在dists中，路径记录在path中
void graph_dijikstra(struct Graph *g, int v) {
    int dis, now = v, from = -1;
    bool visited[g->v];

    g->dists = malloc(sizeof(DataType) * g->v);
    for (int i = 0; i < g->v; i++) {
        g->dists[i] = INF;
    }
    for (int i = 0; i < g->v; i++) {
        visited[i] = false;
    }
    graph_matrix_init(g);
    graph_init_marked(g);
    g->dists[now] = 0;

    while (visited[now] != true && graph_out_degree(g, now) != 0) {
        visited[now] = true;
        g->path[now] = from;
        for (int i = 0; i < g->v; i++) {  // 更新
            dis = matrix_get(&g->m, now, i) + g->dists[now];
            if (dis < g->dists[i]) {
                g->dists[i] = dis;
            }
        }

        from = now;
        dis = INF;
        for (int i = 0; i < g->v; i++) {  // 找下一条边
            if (visited[i] == false && g->dists[i] < dis) {
                dis = g->dists[i];
                now = i;
            }
        }
    }
}

// 辅助函数，实现矩阵的复制
void copy_matrix(struct Matrix *m1, struct Matrix *m2) {
    for (int i = 0; i < m2->rows; i++) {
        for (int j = 0; j < m2->cols; j++) {
            matrix_set(m1, i, j, matrix_get(m2, i, j));
        }
    }
}

// 用Floyd算法计算顶点两两之间的距离, 将其记录在dists矩阵中
void graph_floyd(struct Graph *g, struct Matrix *dists) {
    struct Matrix m;

    matrix_init(dists, g->v, g->v, ROW_MAJOR);
    matrix_init(&m, g->v, g->v, ROW_MAJOR);
    copy_matrix(dists, &g->m);
    copy_matrix(&m, dists);
    graph_matrix_init(g);

    for (int i = 0; i < g->v; i++) {  // 逐个加点
        for (int j = 0; j < g->v; j++) {
            if (i != j && matrix_get(&m, j, i) != INF) {
                for (int k = 0; k < g->v; k++) {
                    if (i != k && matrix_get(&m, i, k) != INF) {
                        int dis = matrix_get(&m, j, i) + matrix_get(&m, i, k);

                        if (dis < matrix_get(&m, j, k)) {
                            matrix_set(dists, j, k, dis);
                        }
                    }
                }
            }
        }

        copy_matrix(&m, dists);
    }
}

void graph_update_flow(struct Graph *g, struct Graph *flow, int s, int t) {
    int begin = t, max_flow = INF;

    while (begin != s) {
        int data = matrix_get(&flow->m, flow->path[begin], begin);

        if (max_flow > data) {
            max_flow = data;
        }

        begin = flow->path[begin];
    }

    begin = t;
    while (begin != s) {
        int sur_cap = matrix_get(&flow->m, flow->path[begin], begin);
        int cur_flow = matrix_get(&flow->m, begin, flow->path[begin]);

        matrix_set(&flow->m, flow->path[begin], begin, sur_cap - max_flow);
        matrix_set(&flow->m, begin, flow->path[begin], max_flow + cur_flow);

        begin = flow->path[begin];
    }
}

// 用Ford Fulkerson算法计算从s到t的最大流，返回最大流的值，并将流量记录在flow中
DataType graph_ford_fulkerson(struct Graph *g, struct Graph *flow) {
    int s, t, max_flow = 0;

    graph_init(flow, g->v, DIRECTED_GRAPH);
    copy_matrix(&flow->m, &g->m);

    for (int i = 0; i < g->v; i++) {
        if (graph_in_degree(g, i) == 0) {
            s = i;
        }
        if (graph_out_degree(g, i) == 0) {
            t = i;
        }
    }

    while (true) {
        graph_dfs(flow, s);

        if (flow->marked[t] == false) {
            break;
        }

        graph_update_flow(g, flow, s, t);
    }

    for (int i = 0; i < g->v; i++) {
        if (matrix_get(&flow->m, t, i) != 0) {
            max_flow += matrix_get(&flow->m, t, i);
        }
    }

    return max_flow;
}
