#include "bst.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define handle(str)                                                            \
  do {                                                                         \
    perror(str);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

bst_t * bst_init(int type) {
  
  bst_t * bst = malloc(sizeof(bst_t));
  if (!bst)
    handle("bst(): malloc");

  bst->type = type;
  bst->root = NULL;

  return bst;
}

node_t * bst_create_node() {
  node_t * new_node = malloc(sizeof(node_t));
  if (!new_node)
    handle("bst_create_node");
  memset(new_node, 0, sizeof(node_t));
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->parent = NULL;
  return new_node;
}

node_t * resolve_data(node_t * node, int type, void * data) {

  switch (type) {
  case BST_INT:
    node->int_value = *(int*)data;
    break;
  case BST_FLOAT:
    node->float_value = *(float*)data;
    break;
  case BST_CHAR:
    node->char_value = *(char*)data;
    break;
  case BST_STRING:
    memset(node->string_value, 0, STRING_MAX);
    strncpy(node->string_value, (char*)data, STRING_MAX);
    break;
  }
  
  return node;
}

int data_bigger_than_node(int type, node_t * node, void * data) {
  switch (type) {
  case BST_INT:
    return (node->int_value < *(int*)data) ? 1 : 0;
  case BST_FLOAT:
    return (node->float_value < *(float*)data) ? 1 : 0;
  case BST_CHAR:
    return (node->char_value < *(char*)data) ? 1 : 0;
  case BST_STRING:
    return (strcmp(node->string_value, (char*)data) < 0) ? 1 : 0;
  }
  return 0;
}

node_t * traverse(int type, node_t * node, void *data) {

  if (data_bigger_than_node(type, node, data) && node->right != NULL)
    return traverse(type, node->right, data);
  else
    if (node->left != NULL)
      return traverse(type, node->left, data);

  return node;
}

node_t * bst_push(bst_t * bst, void * data) {

  if (!bst)
    return NULL;

  node_t * node = NULL;
  
  if (!bst->root) {
    node = malloc(sizeof(node_t));
    resolve_data(node, bst->type, data);
    bst->root = node;
    return node;
  }

  int type = bst->type;
  node_t * target = traverse(type, bst->root, data);
  if (target) {
    node_t * new_node = bst_create_node();
    resolve_data(new_node, type, data);
    if (data_bigger_than_node(type, target, data))
      target->right = new_node;
    else
      target->left = new_node;
    new_node->parent = target;

    return new_node;
  }

  return NULL;
}

void bst_free(bst_t * bst) {
  if (bst)
    free(bst);
}


void print_helper(int type, node_t * node, int offset) {
  if (!node)
    return;

  print_helper(type, node->right, offset + 10);

  for (int i = 0; i < offset; i++)
    printf(" ");
  
  switch (type) {
  case BST_INT:
    printf("%d\n", node->int_value);break;
  case BST_FLOAT:
    printf("%f\n", node->float_value);break;
  case BST_CHAR:
    printf("%c\n", node->char_value);break;
  case BST_STRING:
    printf("%s\n", node->string_value);break;
  }

  print_helper(type, node->left, offset + 10);
}

void bst_print(bst_t * bst) {
  print_helper(bst->type, bst->root, 0);
}
