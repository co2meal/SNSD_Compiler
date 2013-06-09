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
        cal_value(pValue, a, b,pNode->op_token);
      }
      break;

    case NTSTATEMENTLIST:
      {
        int i;
        Value temp;
        for(i = 0; i < pNode->n_of_child_nodes; i++) {
          evaluate(pNode->child_nodes[i], &temp);
        }
      }
      break;

    case NTSTATEMENT:
      {
        Value temp;

        if (pNode->n_of_child_nodes > 0) {
          evaluate(pNode->child_nodes[0], &temp);
          *pValue = temp;
        } else {
          pValue->type = STATEMENTVALUE;
          pValue->statementValue = "empty statement";
        }
      }
      break;

    case NTIFSTATEMENT:
      {
        Value test, temp;
        evaluate(pNode->child_nodes[0], &temp);
        test_value(&test, temp);

        if (test.type == INTVALUE && test.intValue) {
          evaluate(pNode->child_nodes[1], &temp);
        } else if (pNode->n_of_child_nodes == 3) {
          evaluate(pNode->child_nodes[2], &temp);
        }
        pValue->type = STATEMENTVALUE;
        pValue->statementValue = "if";
      }
      break;

    case NTWHILESTATEMENT:
      {
        Value test, temp;

        while (1) {
          evaluate(pNode->child_nodes[0], &temp);
          test_value(&test, temp);

          if (!(test.type == INTVALUE && test.intValue)) break;

          printf("AAAA  - %d\n", test.intValue);
          evaluate(pNode->child_nodes[1], &temp);
        } 

        pValue->type = STATEMENTVALUE;
        pValue->statementValue = "while";
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

  printf("ASSIGNMENT - %s = \n", identifier);
  print_value(&value);

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
