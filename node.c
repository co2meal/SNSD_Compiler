#include <stdio.h>
#include <stdlib.h>

#include "value.h"
#include "node.h"

char* getNodeType(tagNodeType type);

void init_node(Node** ppNode, tagNodeType type) {
  *ppNode = (Node*)malloc((size_t) sizeof (Node));
  (*ppNode)->type = type;
  (*ppNode)->n_of_child_nodes = 0;
}

void push_child_node(Node* pNode, Node* pChildNode) {
  pNode->child_nodes[pNode->n_of_child_nodes++] = pChildNode;
}

void print_node(Node* pNode) {
  printf("node type = %s\n", getNodeType(pNode->type));

  if (pNode->type == NTIDENTIFIER) {
    printf("  node name = %s\n", pNode->name);
  }
  // printf("node value intvalue = %d\n", $2.value.intValue);
}

char* getNodeType(tagNodeType type) {

	switch(type) {
		case NTIDENTIFIER: return "Identifier";
		case NTASSIGNMENT: return "Assignment";
		case NTIFSTATEMENT: return "If Statement";
		case NTWHILESTATEMENT: return "While Statement";
		case NTEXPRESSION: return "Expression";
		case NTBINARYOPERATOR: return "Binary Operator";
		case NTUNARYOPERATOR: return "Unary Operator";
		case NTINTEGER: return "Integer";
		case NTDOUBLE: return "Double";
		case NTFUNCDECLARE: return "Function Declaration";
		case NTPARAMETERLIST: return "Parameter List";
		default:
			return "unkonwn\n";		
			break;
	}
}

