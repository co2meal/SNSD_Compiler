#include <stdio.h>
#include "value.h"

// void print_value(Value value) {
//   if (value.type == INTVALUE) {
//     printf("INTVALUE-%d\n", value.intValue);
//   } else if (value.type == DOUBLEVALUE) {
//     printf("DOUBLEVALUE-%g\n", value.doubleValue);
//   } else {
//     printf("QQQQ-!!\n");
//   }
// }
void print_value(Value* pValue) {
  if (pValue->type == INTVALUE) {
    printf("INTVALUE-%d\n", pValue->intValue);
  } else if (pValue->type == DOUBLEVALUE) {
    printf("DOUBLEVALUE-%g\n", pValue->doubleValue);
  } else if (pValue->type == ERRORVALUE) {
    printf("ERRORVALUE-%s\n", pValue->errorValue);
  } else {
    printf("QQQQ-!!\n");
  }
}
