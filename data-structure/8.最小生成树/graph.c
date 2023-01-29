#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 9999
#define Vertex_list(g, index) (&(g->adjlist.buffer[index].adj_verts))

// TODO:
void graph_init(struct Graph *g, int num_vertices, enum GraphType type) {
    g->e = 0;
    g->v = num_vertices;
    g->type = type;

    vector_init(&g->adjlist, num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        struct Vertex new;

        new.data = i;
        list_init(&new.adj_verts);
        vector_push_back(&g->adjlist, new);
    }

    g->marked = (bool *)malloc(sizeof(bool) * num_vertices);
    g->path = (int *)malloc(sizeof(int) * num_vertices);
}

// TODO:
void graph_destroy(struct Graph *g) {
    g->e = 0;
    g->v = 0;
    vector_destroy(&g->adjlist);
    free(g->marked);
    free(g->path);
}

// TODO:
void graph_add_edge(struct Graph *g, int u, int v, int w) {
    list_push_back(Vertex_list(g, u), v);
    Vertex_list(g, u)->tail->weight = w;
    if (g->type == 0) {
        list_push_back(Vertex_list(g, v), u);
        Vertex_list(g, v)->tail->weight = w;
    }

    g->e++;
}

// TODO:
int graph_degree(struct Graph *g, int v) {
    if (g->type == 0) {
        return graph_out_degree(g, v);
    } else {
        return graph_in_degree(g, v) + graph_out_degree(g, v);
    }
}

bool find_v_in_other_list(struct List *l, int v) {
    struct ListNode *p = l->head;

    while (p != NULL) {
        if (p->data == v) {
            return true;
        }

        p = p->next;
    }

    return false;
}

// TODO:
int graph_in_degree(struct Graph *g, int v) {
    if (v >= g->v) {
        return 0;
    } else if (g->type == 0) {
        return Vertex_list(g, v)->size;
    } else {
        int count = 0;

        for (int i = 0; i < g->adjlist.size; i++) {
            if (find_v_in_other_list(Vertex_list(g, i), v)) {
                count++;
            }
        }

        return count;
    }
}

// TODO:
int graph_out_degree(struct Graph *g, int v) {
    if (v >= g->v) {
        return 0;
    } else {
        return Vertex_list(g, v)->size;
    }
}

// TODO:
// 判断是否连通图
bool graph_is_connected(struct Graph *g) {
    for (int i = 0; i < g->v; i++) {
        for (int j = i + 1; j < g->v; j++) {
            if (!graph_is_vertex_connected(g, i, j) || !graph_is_vertex_connected(g, j, i)) {
                return false;
            }
        }
    }

    return true;
}

// TODO:
// 判断两个顶点是否连通
bool graph_is_vertex_connected(struct Graph *g, int u, int v) {
    graph_bfs(g, u);

    if (g->marked[v] == 1) {
        return true;
    } else {
        return false;
    }
}

// 判断u是否为v的入度，如果是，返回u到v的路径的权值
int get_weight(struct Graph *g, int u, int v) {
    struct ListNode *p = Vertex_list(g, u)->head;

    while (p != NULL) {
        if (p->data == v) {
            return p->weight;
        }

        p = p->next;
    }

    return -1;
}

// TODO:
// 两个顶点之间的距离
DataType graph_vertex_distance(struct Graph *g, int u, int v) {
    graph_dfs(g, u);

    int tmp = v, dis = 0;
    while (tmp != -1) {
        dis += get_weight(g, g->path[tmp], tmp);
        tmp = g->path[tmp];
    }

    return dis;
}

void dfs(struct Graph *g, int v, int pre_index) {
    g->path[v] = pre_index;
    g->marked[v] = 1;
    printf("%d", v);

    for (struct ListNode *p = Vertex_list(g, v)->head; p != NULL; p = p->next) {
        if (g->marked[p->data] == 0) {
            dfs(g, p->data, v);
        }
    }
}

void graph_dfs(struct Graph *g, int v) {
    memset(g->marked, false, sizeof(bool) * g->v);
    memset(g->path, -1, sizeof(int) * g->v);

    dfs(g, v, -1);
}

void bfs(struct Graph *g, int v, int pre_index) {
    Queue q;

    queue_init(&q);
    queue_enqueue(&q, v);
    g->marked[v] = true;
    pre_index = v;

    while (true) {
        struct ListNode *p = Vertex_list(g, v)->head;

        for (; p != NULL; p = p->next) {
            if (g->marked[p->data] == false) {
                g->path[p->data] = pre_index;
                g->marked[p->data] = true;
                queue_enqueue(&q, p->data);
            }
        }

        printf("%d", queue_dequeue(&q));
        if (!queue_empty(&q)) {
            v = queue_front(&q)->data;
            pre_index = v;
        } else {
            break;
        }
    }
}

void graph_bfs(struct Graph *g, int v) {
    memset(g->marked, false, sizeof(bool) * g->v);
    memset(g->path, -1, sizeof(int) * g->v);

    bfs(g, v, -1);
}

void graph_save(struct Graph *g, const char *filename) {
    FILE *fp = fopen(filename, "w");

    fprintf(fp, "strict %sgraph {\n", g->type == DIRECTED_GRAPH ? "di" : "");

    for (int i = 0; i < g->v; i++) {
        struct ListNode *p = Vertex_list(g, i)->head;

        while (p != NULL) {
            fprintf(fp, "\t%d %s %d [label = %d]\n", i, g->type == DIRECTED_GRAPH ? "->" : "--",
                    p->data, p->weight);

            p = p->next;
        }
    }

    fprintf(fp, "}\n");

    fclose(fp);
}

// TODO:
// 判断图g是不是树
bool graph_is_tree(struct Graph *g) {
    if (g->e != g->v - 1) {
        return false;
    }

    for (int i = 0; i < g->v; i++) {
        if (graph_degree(g, i) == 0) {
            return false;
        }
    }

    return true;
}

// TODO:
// 判断t是不是g的生成树
bool graph_is_spanning_tree(struct Graph *g, struct Graph *t) {
    if (graph_is_tree(t) == false) {
        return false;
    }

    for (int i = 0; i < t->v; i++) {
        struct ListNode *p = Vertex_list(t, i)->head;

        while (p != NULL) {
            if (get_weight(g, i, p->data) == -1) {
                return false;
            }

            p = p->next;
        }
    }

    return true;
}

// TODO:
// 用dfs生成g的一棵树
void graph_spanning_tree_dfs(struct Graph *g, struct Graph *t) {
    graph_init(t, g->v, g->type);
    graph_dfs(g, 0);

    for (int i = 0; i < g->v; i++) {
        if (g->path[i] != -1) {
            graph_add_edge(t, g->path[i], i, get_weight(g, g->path[i], i));
        }
    }
}

// TODO:
// 用bfs生成g的一棵树
void graph_spanning_tree_bfs(struct Graph *g, struct Graph *t) {
    graph_init(t, g->v, g->type);
    graph_bfs(g, 0);

    for (int i = 0; i < g->v; i++) {
        if (g->path[i] != -1) {
            graph_add_edge(t, g->path[i], i, get_weight(g, g->path[i], i));
        }
    }
}

void find_min_road(struct Graph *g, int *visited, int *u, int *v) {
    int min_weight = INF;

    *u = *v = -1;
    for (int i = 0; i < g->v; i++) {
        if (visited[i] == 1) {
            struct ListNode *p = Vertex_list(g, i)->head;

            while (p != NULL) {
                if (visited[p->data] == 0 && p->weight < min_weight) {
                    min_weight = p->weight;
                    *u = i;
                    *v = p->data;
                }

                p = p->next;
            }
        }
    }
}

// TODO:
// 用prim算法生成g的一棵最小生成树
void graph_spanning_tree_prim(struct Graph *g, struct Graph *t) {
    int *u = malloc(sizeof(int));
    int *v = malloc(sizeof(int));
    int *visited = malloc(sizeof(int) * g->v);

    graph_init(t, g->v, g->type);
    memset(visited, 0, sizeof(int) * g->v);
    visited[0] = 1;

    while (true) {
        find_min_road(g, visited, u, v);
        if (*u == -1 || *v == -1) {
            break;
        }

        visited[*v] = 1;
        graph_add_edge(t, *u, *v, get_weight(g, *u, *v));
    }

    free(u);
    free(v);
    free(visited);
}

// TODO:
// 用kruskal算法生成g的一棵最小生成树
void graph_spanning_tree_kruskal(struct Graph *g, struct Graph *t) {
    struct edge {
        int weight;
        int pre;
        int next;
    } *edges;
    int index = 0;
    bool *visited = malloc(sizeof(int) * g->v);

    graph_init(t, g->v, g->type);
    edges = malloc(sizeof(struct edge) * g->e);

    for (int i = 0; i < g->v; i++) {  // 初始化边集
        struct ListNode *p = Vertex_list(g, i)->head;

        while (p != NULL) {
            int flag = 1;

            for (int j = 0; j < index; j++) {
                if (edges[j].pre == p->data && edges[j].next == i) {
                    p = p->next;
                    flag = 0;
                    break;
                }
            }

            if (flag == 0) {
                continue;
            }

            edges[index].pre = i;
            edges[index].next = p->data;
            edges[index].weight = p->weight;
            p = p->next;
            index++;
        }
    }

    for (int i = 0; i < g->e; i++) {  // 排序
        for (int j = 0; j < g->e; j++) {
            if (edges[i].weight < edges[j].weight) {
                struct edge tmp = edges[i];
                edges[i] = edges[j];
                edges[j] = tmp;
            }
        }
    }

    memset(visited, false, sizeof(int) * g->v);
    for (int i = 0; i < g->e; i++) {  // 生成树
        if (!visited[edges[i].pre] || !visited[edges[i].next]) {
            graph_add_edge(t, edges[i].pre, edges[i].next, edges[i].weight);
            visited[edges[i].pre] = true;
            visited[edges[i].next] = true;
        }
    }

    free(visited);
    free(edges);
}