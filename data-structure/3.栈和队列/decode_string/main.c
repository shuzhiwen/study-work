#include <stdio.h>

#include "stack.h"

// TODO:
void decode_string(char *s) {
    Stack stack;
    stack_init(&stack, 10);

    for (int i = 0; s[i] != 0; i++) {
        if ((s[i] >= '0' && s[i] <= '9') || s[i] == '[') {  //遇到数字或左括弧压栈
            stack_push(&stack, s[i] - '0');
        }

        if (s[i] == ']') {  //遇到右括弧
            int j = 0, Brackets_sum = 0;

            for (j = i - 1;; j--) {  //找到对应的左括弧
                if (s[j] == ']') {
                    Brackets_sum++;
                } else if (s[j] == '[') {
                    if (Brackets_sum) {
                        Brackets_sum--;
                    } else {
                        break;
                    }
                }
            }

            stack_pop(&stack);  //弹出左括弧

            if (j != 0 && s[j - 1] && s[j - 1] > '0' &&
                s[j - 1] <= '9') {  //若前面是数字则将数字减一
                stack_push(&stack, stack_pop(&stack) - 1);

                if (stack_peek(&stack)) {  //数字不为０时继续遍历直到数字为０
                    i = j - 1;
                } else {  //数字为０时弹出
                    stack_pop(&stack);
                }
            }
        }

        if (s[i] >= 'a' && s[i] <= 'z') {  //遇到字母输出
            printf("%c", s[i]);
        }
    }

    printf("\n");
}

int main() {
    decode_string("3[a]2[bc]");      // 输出 aaabcbc
    decode_string("3[a2[c]]");       // 输出 accaccacc
    decode_string("2[abc]3[cd]ef");  // 输出 abcabccdcdcdef
}
