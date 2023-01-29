#include "sparse_matrix.h"

#include <math.h>

int sparse_matrix_item_position_compare(struct Item *lhs, struct Item *rhs) {
    return lhs->row == rhs->row ? lhs->col - rhs->col : lhs->row - rhs->row;
}

void sparse_matrix_init(SparseMatrix *m, int rows, int cols) {
    list_init(m);
    m->rows = rows;
    m->cols = cols;
}

// TODO:
// 将m的第row行第col列设置为value
// 如果下标越界返回 `STATUS_ERR_INVALID_RANGE`
enum Status sparse_matrix_set(SparseMatrix *m, int row, int col, double value) {
    if (m->cols < col || m->rows < row || row < 0 || col < 0) {  // 检查下标越界
        return STATUS_ERR_INVALID_RANGE;
    }

    struct ListNode *Newnode = (struct ListNode *)malloc(sizeof(struct ListNode));

    Newnode->data.col = col;
    Newnode->data.row = row;
    Newnode->data.value = value;

    if (m->head == NULL) {  // 当矩阵没有元素
        m->head = m->tail = Newnode;
        m->tail = NULL;
    } else {
        struct ListNode *p = m->head, *q = NULL;  // q记录p的上一个节点

        while (p != NULL) {
            if (p->data.row == row && p->data.col == col) {  // 如果坐标相等则改变原有节点中的数值
                p->data.value = value;
                free(Newnode);
                break;
            } else if (p->data.row > row || (p->data.row == row && p->data.col > col)) {
                if (q == NULL) {  // 头部插入
                    Newnode->next = p;
                    m->head = Newnode;
                } else {  // 中部插入
                    Newnode->next = p;
                    q->next = Newnode;
                }
                break;
            } else if (p->next == NULL) {  // 尾部插入
                p->next = Newnode;
                Newnode->next = NULL;
                m->tail = Newnode;
                break;
            }

            q = p;
            p = p->next;
        }
    }

    m->size++;
    return STATUS_OK;
}

// TODO:
// 返回m的第row行第col列
// 如果下标越界返回NAN
double sparse_matrix_get(SparseMatrix *m, int row, int col) {
    struct ListNode *p = m->head;

    if (m->head == NULL) {
        return 0;
    } else if (m->cols < col || m->rows < row) {  // 下标越界检查
        return NAN;
    }

    while (p != NULL) {  // 搜索对应的位置
        if (p->data.row == row && p->data.col == col) {
            return p->data.value;
        }

        p = p->next;
    }

    return 0;
}

// TODO:
// c = a + b
// 假设a，b有相同的行列
void sparse_matrix_add(SparseMatrix *c, SparseMatrix *a, SparseMatrix *b) {
    struct ListNode *p = c->head, *p1 = a->head, *p2 = b->head;

    while (p1 != NULL && p2 != NULL) {
        if (sparse_matrix_item_position_compare(&p1->data, &p2->data) < 0) {
            sparse_matrix_set(c, p1->data.row, p1->data.col, p1->data.value);
            p1 = p1->next;
        } else if (sparse_matrix_item_position_compare(&p1->data, &p2->data) > 0) {
            sparse_matrix_set(c, p2->data.row, p2->data.col, p2->data.value);
            p2 = p2->next;
        } else {
            sparse_matrix_set(c, p1->data.row, p1->data.col, p1->data.value + p2->data.value);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    if (p1 != NULL && p2 == NULL) {
        while (p1) {
            sparse_matrix_set(c, p1->data.row, p1->data.col, p1->data.value);
            p1 = p1->next;
        }
    } else if (p2 != NULL && p1 == NULL) {
        while (p2) {
            sparse_matrix_set(c, p2->data.row, p2->data.col, p2->data.value);
            p2 = p2->next;
        }
    }
}
