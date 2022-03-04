#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define value(g, x, y) g->m.buffer[matrix_coord_to_index(&g->m, x, y)]

// TODO:
void graph_init(struct Graph *g, int num_vertices, enum GraphType type) {
    g->e = 0;
    g->type = type;
    g->v = num_vertices;
    matrix_init(&g->m, num_vertices, num_vertices, 0);
    memset(g->m.buffer, 0, sizeof(DataType) * num_vertices * num_vertices);
}

// TODO:
void graph_destroy(struct Graph *g) {
    g->e = 0;
    g->v = 0;
    matrix_destory(&g->m);
}

// TODO:
void graph_add_edge(struct Graph *g, int u, int v, DataType weight) {
    if (v >= g->v || u >= g->v) {
        return;
    }

    if (g->type == 0) {
        value(g, v, u) = weight;
        value(g, u, v) = weight;
    } else if (g->type == 1) {
        value(g, u, v) = weight;
    }
}

void graph_delete_edge(struct Graph *g, int u, int v) {
    if (v >= g->v || u >= g->v) {
        return;
    }

    if (g->type == 0) {
        value(g, v, u) = 0;
        value(g, u, v) = 0;
    } else if (g->type == 1) {
        value(g, u, v) = 0;
    }
}

// TODO:
int graph_degree(struct Graph *g, int v) {
    if (g->type == 1) {
        return graph_in_degree(g, v) + graph_out_degree(g, v);
    } else {
        return graph_in_degree(g, v);
    }
}

// TODO:
int graph_in_degree(struct Graph *g, int v) {
    int degree = 0;

    if (v >= g->v) {
        return 0;
    }

    for (int i = 0; i < g->v; i++) {
        if (value(g, i, v) != 0) {
            degree++;
        }
    }

    return degree;
}

// TODO:
int graph_out_degree(struct Graph *g, int v) {
    int degree = 0;

    if (v >= g->v) {
        return 0;
    }

    for (int i = 0; i < g->v; i++) {
        if (value(g, v, i) != 0) {
            degree++;
        }
    }

    return degree;
}

// TODO:
// 判断是否连通图
bool graph_is_connected(struct Graph *g) {
    for (int i = 0; i < g->v; i++) {
        for (int j = i + 1; j < g->v; j++) {
            if (!graph_is_vertex_connected(g, i, j) || !graph_is_vertex_connected(g, j, i))
                return false;
        }
    }

    return true;
}

//判断u到v是否有路径(辅助)
bool have_road_between_uv(struct Graph *g, int u, int v) {
    int *visit = malloc(sizeof(int) * g->v);
    int *queue = malloc(sizeof(int) * g->v);
    int begin = 0, end = 0;

    memset(visit, 0, sizeof(visit));
    memset(queue, 0, sizeof(queue));
    queue[0] = u;
    visit[u] = 1;

    while (begin <= end) {
        for (int i = 0; i < g->v; i++) {
            if (value(g, queue[begin], i) != 0) {
                if (i == v) {
                    return true;
                } else if (visit[i] == 0) {
                    queue[++end] = i;
                    visit[i] = 1;
                }
            }
        }

        begin++;
    }

    return false;
}

// TODO:
// 判断两个顶点是否连通
bool graph_is_vertex_connected(struct Graph *g, int u, int v) {
    return have_road_between_uv(g, u, v) && have_road_between_uv(g, v, u);
}

//辅助
int find_next_vertex(struct Graph *g, int u, int index) {
    for (int i = index + 1; i < g->v; i++) {
        if (value(g, u, i) != 0) {
            return i;
        }
    }

    return -1;
}

int dfs(struct Graph *g, int begin, int end, int *visit) {
    int index = -1, dis = 0;

    while (!dis && (index = find_next_vertex(g, begin, index)) != -1) {
        if (index == end) {
            return dis + value(g, begin, index);
        } else if (visit[index] == 0) {
            visit[index] = 1;
            dis += dfs(g, index, end, visit);
        }
    }

    if (dis) {
        return dis + value(g, begin, index);
    } else {
        return 0;
    }
}

// TODO:
// 两个顶点之间的距离
DataType graph_vertex_distance(struct Graph *g, int u, int v) {
    int *visit = malloc(sizeof(int) * g->v);

    memset(visit, 0, sizeof(visit));
    visit[u] = 1;

    if (have_road_between_uv(g, u, v)) {
        return dfs(g, u, v, visit);
    } else if (have_road_between_uv(g, v, u)) {
        return dfs(g, u, v, visit);
    } else
        return -1;  // NO SUCH ROAD
}

// TODO:
// 判断sg是否为g的子图
bool graph_is_subgraph(struct Graph *g, struct Graph *sg) {
    if (sg->v > g->v || sg->e > g->e || sg->type != g->type) {
        return false;
    }

    for (int i = 0; i < sg->v; i++) {
        for (int j = 0; j < sg->v; j++) {
            if (value(sg, i, j) != 0 && value(sg, i, j) != value(g, i, j)) {
                return false;
            }
        }
    }

    return true;
}

bool is_other_vertex(struct Graph *g, struct Graph *sg, int index) {
    bool flag = false;

    for (int i = 0; i < g->v; i++) {
        if (value(sg, index, i) || value(sg, i, index)) {
            return false;
        }

        if (value(g, index, i) || value(g, i, index)) {
            flag = true;
        }
    }

    return flag;
}

// TODO:
// 判断sg是否是g的（强）连通分量
bool graph_is_connected_component(struct Graph *g, struct Graph *sg) {
    if (graph_is_subgraph(g, sg) == 0 || graph_is_connected(sg) == 0) {
        return false;
    }

    for (int i = 0; i < g->v; i++) {
        if (is_other_vertex(g, sg, i)) {
            for (int j = 0; j < g->v; j++) {  //增边
                if (value(g, i, j)) {
                    graph_add_edge(sg, i, j, value(g, i, j));
                }
                if (value(g, j, i)) {
                    graph_add_edge(sg, j, i, value(g, j, i));
                }
            }

            if (graph_is_connected(sg)) {
                return false;
            }  //判断

            for (int j = 0; j < g->v; j++) {  //删边
                if (value(sg, i, j)) {
                    graph_delete_edge(sg, i, j);
                }
                if (value(sg, j, i)) {
                    graph_delete_edge(sg, j, i);
                }
            }
        }
    }

    return true;
}
