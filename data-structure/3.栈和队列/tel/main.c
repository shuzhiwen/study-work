#include "queue.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int enter_queue(Queue *q, int i, char s) {
  if (s == '2') {
    switch (i) {
      case 3:
        queue_enqueue(q, 'a');
        break;
      case 2:
        queue_enqueue(q, 'b');
        break;
      case 1:
        queue_enqueue(q, 'c');
        break;
      case 0:
        return false;
    }
  } else if (s == '3') {
    switch (i) {
      case 3:
        queue_enqueue(q, 'd');
        break;
      case 2:
        queue_enqueue(q, 'e');
        break;
      case 1:
        queue_enqueue(q, 'f');
        break;
      case 0:
        return false;
    }
  } else if (s == '4') {
    switch (i) {
      case 3:
        queue_enqueue(q, 'g');
        break;
      case 2:
        queue_enqueue(q, 'h');
        break;
      case 1:
        queue_enqueue(q, 'i');
        break;
      case 0:
        return false;
    }
  } else if (s == '5') {
    switch (i) {
      case 3:
        queue_enqueue(q, 'j');
        break;
      case 2:
        queue_enqueue(q, 'k');
        break;
      case 1:
        queue_enqueue(q, 'l');
        break;
      case 0:
        return false;
    }
  } else if (s == '6') {
    switch (i) {
      case 3:
        queue_enqueue(q, 'm');
        break;
      case 2:
        queue_enqueue(q, 'n');
        break;
      case 1:
        queue_enqueue(q, 'o');
        break;
      case 0:
        return false;
    }
  } else if (s == '7') {
    switch (i) {
      case 4:
        queue_enqueue(q, 'p');
        break;
      case 3:
        queue_enqueue(q, 'q');
        break;
      case 2:
        queue_enqueue(q, 'r');
        break;
      case 1:
        queue_enqueue(q, 's');
        break;
      case 0:
        return false;
    }
  } else if (s == '8') {
    switch (i) {
      case 3:
        queue_enqueue(q, 't');
        break;
      case 2:
        queue_enqueue(q, 'u');
        break;
      case 1:
        queue_enqueue(q, 'v');
        break;
      case 0:
        return false;
    }
  } else if (s == '9') {
    switch (i) {
      case 4:
        queue_enqueue(q, 'w');
        break;
      case 3:
        queue_enqueue(q, 'x');
        break;
      case 2:
        queue_enqueue(q, 'y');
        break;
      case 1:
        queue_enqueue(q, 'z');
        break;
      case 0:
        return false;
    }
  }

  return true;
}

void q_num_operation(int q_num[], int index, char digits[]) {
  if (digits[index] == '7' || digits[index] == '9') {
    q_num[index] = 4;
  } else {
    q_num[index] = 3;
  }

  q_num[index - 1]--;
}

// TODO:
void print_letters(char * digits)
{
  int q_num[10] = { 0 }, n = strlen(digits), all_case = 1;
  Queue q, q_print;

  queue_init(&q);
  queue_init(&q_print);

  for (int i = 0; i < n; i++) { //记录每个数字代表字母的个数
    if (digits[i] == '7' || digits[i] == '9') {
      q_num[i] = 4;
    } else {
      q_num[i] = 3;
    }

    all_case *= q_num[i];
  }

  printf("[");

  for (int i = 0; i < strlen(digits); i++) { //字符串中的数字入队列ｑ
    queue_enqueue(&q, digits[i]);
  }

  int count = 0; //ｃｏｕｎｔ为每次ｗｈｉｌｅ循环记一次数

  while (q_num[0]) { //遍历未结束的判断条件
    char s = queue_dequeue(&q);
    
    if (count && !(count % n)) { //打印一组数据
      while (!queue_empty(&q_print)) {
        printf("%c", queue_dequeue(&q_print));
      }

      if (count / n != all_case) {
        printf(", ");
      }

      q_num[n - 1]--;

      for (int i = n - 1; i > 0; i--) {
        if (q_num[i] == 0) {
          q_num_operation(q_num, i, digits);
        }
      }
    }

    enter_queue(&q_print, q_num[count % n], s);
    queue_enqueue(&q, s);
    count++;
  }
  
  printf("]\n"); 
}

int main()
{
  print_letters("23"); // 打印: ad, ae, af, bd, be, bf, cd, ce, cf.
}
