#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "btree.h"
#include "btree_vis.h"
#include "huffman.h"

int main() {
    char *s = "go go gophers";
    char *t = "her sphere goes here";
    char *es1 = "0001101000110100011110110111001111100";
    char *es2 = "101110101110110111110010111010111010101100001101011111101011101011101010";

    struct BTree *h1 = huffman_build_using_array(s);
    struct BTree *h2 = huffman_build_using_heap(s);

    // btree_print(h1);
    // btree_print(h2);

    int n1 = huffman_encode(h1, s);
    int n2 = huffman_encode(h2, s);
    printf("\n");

    n1 = huffman_encode(h1, t);
    n2 = huffman_encode(h2, t);
    printf("\n");

    n1 = huffman_decode(h1, es1);
    n2 = huffman_decode(h2, es2);

    btree_destroy(h1);
    btree_destroy(h2);
}
