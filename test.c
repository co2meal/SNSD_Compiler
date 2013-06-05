#include <stdio.h>
#include "value.h"

Value fn () {
  Value res;
  res.type = INTVALUE;
  res.intValue = 999;
  return res;
}

int main() {
  Value v;

  v = fn();

  // printf("v.a => %d\n", v.a);
  printf("v.intValue => %d\n", v.intValue);

}