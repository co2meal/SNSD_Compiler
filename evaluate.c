#include <stdio.h>
#include <string.h>

#include "value.h"
#include "node.h"
#include "y.tab.h"

Value vbltable[1000];
char idx2stringtable[1000][100];
int n_of_idx2stringtable = 0;

Value get_variable (char* identifier);
void set_variable (char* identifier, Value value);

void evaluate(Node* pNode, Value* pValue) {
  print_node(pNode);
  switch(pNode->type) {
    case NTINTEGER:
      printf("pNode->value.type: %d\n", (int)pNode->value.type);
      printf("pNode->value.intValue: %d\n", pNode->value.intValue);
      *pValue = pNode->value;
      break;

    case NTDOUBLE:
      *pValue = pNode->value;
      break;

    case NTIDENTIFIER:
      *pValue = get_variable(pNode->name);
      break;

    case NTASSIGNMENT:
      {
        Value rhs;
        evaluate(pNode->child_nodes[1], &rhs);
        set_variable(pNode->child_nodes[0]->name, rhs);
        *pValue = rhs;
      }
      break;

    case NTBINARYOPERATOR:
      {
        Value a, b;
        evaluate(pNode->child_nodes[0], &a);
        evaluate(pNode->child_nodes[1], &b);
        switch (pNode->op_token) {
          case PLUS:
        printf("hello\n");
            add_value(pValue, a,b);
            break;
          case MINUS:
            sub_value(pValue, a,b);
            break;
          case MULTIPLY:
            mul_value(pValue, a, b);
            break;
          case DIVIDE:
            div_value(pValue, a, b);
            break;
        }
      }
      break;

    default:
      printf("not evaluated...\n");
  }
}

Value get_variable (char* identifier) {
  Value value;
  int i;
  for(i=0;i<n_of_idx2stringtable;i++) {
    if (strcmp(idx2stringtable[i], identifier) == 0)
      break;
  }
  if (i == n_of_idx2stringtable) {
    value.type = ERRORVALUE;
    value.errorValue = "undefined variable error";
  } else {
    value = vbltable[i];
  }

  return value;
}


void set_variable (char* identifier, Value value) {
  int i;
  for(i=0;i<n_of_idx2stringtable;i++) {
    if (strcmp(idx2stringtable[i], identifier) == 0)
      break;
  }

  if (i == n_of_idx2stringtable) {
    printf("registerd...\n");
    strcpy(idx2stringtable[n_of_idx2stringtable], identifier);
    n_of_idx2stringtable++;
  }

  vbltable[i] = value;
}
