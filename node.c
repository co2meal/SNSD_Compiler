#include <stdio.h>
#include <stdlib.h>

#include "value.h"
#include "node.h"

void init_node(Node** ppNode, tagNodeType type) {
  *ppNode = (Node*)malloc((size_t) sizeof (Node));
  (*ppNode)->type = type;
}

void push_child_node(Node* pNode, Node* pChildNode) {
  pNode->child_nodes[pNode->n_of_child_nodes++] = pChildNode;
}

void print_node(Node* pNode) {
  printf("node type = %d\n", (int)(pNode->type));

  if (pNode->type == NTIDENTIFIER) {
    printf("  node name = %s\n", pNode->name);
  }
  // printf("node value intvalue = %d\n", $2.value.intValue);
}