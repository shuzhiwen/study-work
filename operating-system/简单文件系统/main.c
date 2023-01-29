#include "file.h"

int main() {
    char command[20];
    char parameter[20];

    struct Vector vec;
    struct FileTree root;
    struct FileTree *p = &root;

    vector_init(&vec, 10);
    filetree_init(p, true, "root", NULL);

    while (true) {  // 输入要求：一个命令不带参数或带一个参数
        printf("> ");
        scanf("%s", &command);
        if (strcmp(command, "ls") == 0) {
            ls(p);
        } else if (strcmp(command, "cd") == 0) {
            scanf("%s", &parameter);
            cd(&p, &root, parameter);
        } else if (strcmp(command, "show") == 0) {
            show(&root);
            printf("当前文件数量: %d\n", vec.size);
        } else if (strcmp(command, "makedir") == 0) {
            scanf("%s", &parameter);
            makedir(p, parameter);
        } else if (strcmp(command, "makefile") == 0) {
            scanf("%s", &parameter);
            makefile(&vec, p, parameter);
        } else if (strcmp(command, "delfile") == 0) {
            scanf("%s", &parameter);
            delnode(&vec, false, p, parameter);
        } else if (strcmp(command, "deldir") == 0) {
            scanf("%s", &parameter);
            delnode(&vec, true, p, parameter);
        } else if (strcmp(command, "exit") == 0) {
            vector_destroy(&vec);
            filetree_free(&root);
            break;
        } else {
            printf("找不到命令: %s\n", command);
            while (true) {
                char c = getchar();

                if (c == '\n') break;
            }
        }
    }
}