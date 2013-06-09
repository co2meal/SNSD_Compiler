#include <stdio.h>
#include <stdlib.h>

#include "value.h"
#include "node.h"
#include "function.h"

void create_function(Function** ppFunction, Node* pl, Node* sl) {
  *ppFunction = (Function*) malloc((size_t) sizeof(Function));

  (*ppFunction)->parameter_list = pl;
  (*ppFunction)->statement_list = sl;
}