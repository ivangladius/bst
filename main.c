
#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int main() {

  bst_t * bst = bst_init(BST_INT);

  for (int i = 0; i < 10; i++)
    bst_push(bst, &i);

  bst_print(bst);

  bst_free(bst);

  return 0;
}
