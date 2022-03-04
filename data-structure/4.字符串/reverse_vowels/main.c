#include <malloc.h>
#include <stdio.h>
#include <string.h>

int Isvowel(char s) {
    return (s == 'a' || s == 'e' || s == 'i' || s == 'o' || s == 'u' || s == 'A' || s == 'E' ||
            s == 'I' || s == 'O' || s == 'U');
}

// TODO:
void reverse_vowels(char *s) {
    char *str = (char *)malloc(sizeof(s)), *p1, *p2;

    strcpy(str, s);
    p1 = str;
    p2 = str + strlen(str);

    while (p2 - p1 > 0) {
        if (*p2 == '\0') {
            p2--;
        } else {
            char s = *p1;
            *p1 = *p2;
            *p2 = s;
            p1++;
            p2--;
        }

        while (!Isvowel(*p1)) {
            p1++;
            if (p1 == s + strlen(s)) {
                break;
            }
        }
        while (!Isvowel(*p2)) {
            p2--;
            if (p2 == s) {
                break;
            }
        }
    }

    puts(str);
}

int main() {
    reverse_vowels("hello");     // 打印  holle
    reverse_vowels("leetcode");  // 打印 leotcede
}
