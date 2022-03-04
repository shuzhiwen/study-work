#include <stdio.h>

#include "stack.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int calculate(int a, int b, char sign) {
    switch (sign) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
    }
}

// TODO:
int rpn(char **tokens, int len) {
    Stack s;
    stack_init(&s, len);

    for (int i = 0; i < len; i++) {
        if (tokens[i][0] >= '0' && tokens[i][0] <= '9') {  //遇到数字压栈
            int j = 0, sum = 0;

            while (tokens[i][j] != 0) {
                sum = sum * 10 + tokens[i][j] - '0';
                j++;
            }

            stack_push(&s, sum);
        }

        if (tokens[i][0] == '+') {  //遇到符号弹出数字并求值，将结果压栈
            if (stack_top(&s) > 40) {
                char sign = stack_pop(&s);
                stack_push(&s, calculate(stack_pop(&s), stack_pop(&s), sign));
                stack_push(&s, '+');
            } else {
                stack_push(&s, calculate(stack_pop(&s), stack_pop(&s), '+'));
            }
        }

        if (tokens[i][0] == '-') {
            if (stack_top(&s) > 40) {
                char sign = stack_pop(&s);
                stack_push(&s, calculate(stack_pop(&s), stack_pop(&s), sign));
                stack_push(&s, '-');
            } else {
                stack_push(&s, calculate(stack_pop(&s), stack_pop(&s), '-'));
            }
        }

        if (tokens[i][0] == '*') {
            if (stack_top(&s) == '/') {
                char sign = stack_pop(&s);
                stack_push(&s, calculate(stack_pop(&s), stack_pop(&s), '/'));
                stack_push(&s, '*');
            } else {
                stack_push(&s, calculate(stack_pop(&s), stack_pop(&s), '*'));
            }
        }

        if (tokens[i][0] == '/') {
            if (stack_top(&s) == '*') {
                char sign = stack_pop(&s);
                stack_push(&s, calculate(stack_pop(&s), stack_pop(&s), '*'));
                stack_push(&s, '/');
            } else {
                stack_push(&s, calculate(stack_pop(&s), stack_pop(&s), '/'));
            }
        }
    }

    if (stack_top(&s) < '0' || stack_top(&s) > '9') {  //字符串遍历结束
        char sign = stack_pop(&s);
        stack_push(&s, calculate(stack_pop(&s), stack_pop(&s), sign));
    }

    return stack_pop(&s);
}

int main() {
    char *s1[] = {"2", "1", "+", "3", "*"};
    char *s2[] = {"4", "13", "5", "/", "+"};

    printf("%d\n", rpn(s1, ARRAY_SIZE(s1)));  // 9
    printf("%d\n", rpn(s2, ARRAY_SIZE(s2)));  // 6
}