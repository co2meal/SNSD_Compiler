#include <stdio.h>
#include <stdlib.h>

#include "value.h"
#include "node.h"
#include "function.h"

Function* create_function(Node* pl, Node* sl) {
  Function* res =(Function*) malloc((size_t) sizeof(Function));

  res->parameter_list = pl;
  res->statement_list = sl;

  return res;
}