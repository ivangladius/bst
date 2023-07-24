
#ifndef BST_TREE
#define BST_TREE

#define BST_INT 0
#define BST_FLOAT 1
#define BST_CHAR 2
#define BST_STRING 3

#define STRING_MAX 4096

typedef struct node {
  union {
    int int_value;
    float float_value;
    char char_value;
    char string_value[STRING_MAX];
  };
  struct node * left;
  struct node * right;
  struct node * parent;
} node_t;

typedef struct bst {
  int type;
  node_t * root;
} bst_t;

bst_t *bst_init(int);
node_t *bst_push(bst_t *bst, void *data);
void bst_free(bst_t * bst);
void bst_print(bst_t * bst);
#endif
