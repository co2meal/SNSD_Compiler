#include <stdio.h>
#include <string.h>

#include "value.h"
#include "node.h"
#include "function.h"
#include "frame.h"
#include "y.tab.h"

char* getValueType(tagValueType type); 

Frame frame_stack[MAX_FRAME_STACK_SIZE];
int top_of_frame_stack = -1;
int return_count = -1;

int n_of_global_variables = 0;
char global_variables_name[MAX_GLOBAL_VARIABLES][MAX_VARIABLE_NAME];
Value global_variables_value[MAX_GLOBAL_VARIABLES];

Value get_variable (char* identifier);
void set_variable (char* identifier, Value value);
void evaluate(Node* pNode, Value* pValue) {
  if (return_count != top_of_frame_stack) return;
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

    case NTUNARYOPERATOR :
    {
        Value a;
        evaluate(pNode->child_nodes[0], &a);
        cal_uminus (pValue, a);
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

        if ( (test.type == INTVALUE) && (test.intValue == 1) ) {
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

    case  NTFUNCDECLARE:
      {
        Function* pFn;
        Value value;
        create_function(&pFn, pNode->child_nodes[1], pNode->child_nodes[2]);
        value.type = FUNCTIONVALUE;
        value.functionValue = pFn;

        set_variable(pNode->child_nodes[0]->name, value);
        pValue->type = STATEMENTVALUE;
        pValue->statementValue = "a function is defined.";
      }
      break;

    case NTRETURNSTATEMENT:

      {
        evaluate(pNode->child_nodes[0], frame_stack[top_of_frame_stack].pReturnValue);
        return_count --;
      }
      break;

    case NTLOCALSTATEMENT:
      {
        int i;
        Node* parameter_list = pNode->child_nodes[0];

        for(i=0;i<parameter_list->n_of_child_nodes;i++) {
          char* identifier = parameter_list->child_nodes[i]->name;
          register_local_frame(&frame_stack[top_of_frame_stack], identifier);
        }
        pValue->type = STATEMENTVALUE;
        pValue->statementValue = "local variables are defined.";

      }
      break;

    case NTFUNCCALL:
      {
        int i;
        Value value;
        Function* pFn;
        Node* expression_list;
        Node* statement_list;
        value = get_variable(pNode->child_nodes[0]->name);
        expression_list = pNode->child_nodes[1];

        if (value.type != FUNCTIONVALUE) {
          pValue->type = ERRORVALUE;
          pValue->errorValue = "no function name error";
        } else {
          Value temp;
          pFn = value.functionValue;
          statement_list = pFn->statement_list;

          pValue->type = ERRORVALUE;
          pValue->errorValue = "nothing is returned";

          top_of_frame_stack ++;
          return_count ++;
          init_frame(&frame_stack[top_of_frame_stack], pValue, pFn, expression_list);
          if (pValue->type != ERRORVALUE) {
            evaluate(statement_list, &temp);
          }
          top_of_frame_stack --;
          return_count = top_of_frame_stack;
        }
      }
      break;

    default:
      printf("not evaluated...\n");
  }
}

Value get_variable (char* identifier) {
  int i;
  Value value;
  int found = 0;

  if (top_of_frame_stack != -1) {
    Frame* pFrame = &frame_stack[top_of_frame_stack];

    for (i=0;i<pFrame->n_of_local_variables;i++) {
      if (strcmp(pFrame->local_variables_name[i], identifier) == 0)
        break;
    }
    if (i < pFrame->n_of_local_variables) {
      value = pFrame->local_variables_value[i];
      found = 1;
    }
  }

  if(!found) {
    for (i=0;i<n_of_global_variables;i++) {
      if (strcmp(global_variables_name[i], identifier) == 0)
        break;
    }
    if (i < n_of_global_variables) {
      value = global_variables_value[i];
    } else {
      value.type = ERRORVALUE;
      value.errorValue = "undefined variable error";
    }
  }
  return value;
}


void set_variable (char* identifier, Value value) {
  int i;
  Value* pValue = NULL;

  if (top_of_frame_stack != -1) {
    Frame* pFrame = &frame_stack[top_of_frame_stack];
    for (i=0;i<pFrame->n_of_local_variables;i++) {
      if (strcmp(pFrame->local_variables_name[i], identifier) == 0)
        break;
    }
    if (i < pFrame->n_of_local_variables) {
      pValue = &pFrame->local_variables_value[i];
    }
  }

  if (pValue == NULL) {
    for (i=0;i<n_of_global_variables;i++) {
      if (strcmp(global_variables_name[i], identifier) == 0)
        break;
    }
    if (i < n_of_global_variables) {
      pValue = &global_variables_value[i];
    } else {
      printf("global registerd...\n");
      strcpy(global_variables_name[n_of_global_variables], identifier);
      pValue = &global_variables_value[n_of_global_variables];
      n_of_global_variables++;
    }
  }

  *pValue = value;
}

char* getValueType(tagValueType type) {
  switch(type) {
    case INTVALUE: return "Integer value";
    case DOUBLEVALUE: return "Double value";
    case STATEMENTVALUE: return "statement value";
    case FUNCTIONVALUE: return "Function value";
    case ERRORVALUE: return "Error value";
    default: return "unknown value";
  }
}
