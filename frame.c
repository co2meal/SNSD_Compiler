#include <stdio.h>
#include <string.h>

#include "value.h"
#include "node.h"
#include "function.h"
#include "frame.h"

void register_local_frame(Frame* pFrame, char* identifier) {
  int idx = pFrame->n_of_local_variables;
  Value value;
  value.type = ERRORVALUE;
  value.errorValue = "undefined variable error";

  strcpy(pFrame->local_variables_name[idx], identifier);
  pFrame->local_variables_value[idx] = value;
  pFrame->n_of_local_variables++;
}

void init_frame(Frame* pFrame, Value* pReturnValue, Function* pFn, Node* expression_list) {
  int i;
  printf("init_frame start\n");

  pFrame->n_of_local_variables = 0;
  pFrame->pReturnValue = pReturnValue;
  pReturnValue->type = INTVALUE; // only for default type...


  // TODO(co2meal): handle error when different expression_list length and parameter_list length
  if (pFn->parameter_list->n_of_child_nodes != expression_list->n_of_child_nodes) {
    pReturnValue->type = ERRORVALUE;
    pReturnValue->errorValue = "parameter length is different error";
    return;
  }

  for(i=0; i < pFn->parameter_list->n_of_child_nodes; i++) {
    Value value;
    char* identifier = pFn->parameter_list->child_nodes[i]->name;
    register_local_frame(pFrame, identifier);

    evaluate(expression_list->child_nodes[i], &value);
    set_variable(identifier, value);
  }

}
