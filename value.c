#include <stdio.h>
#include "value.h"

void print_value(Value* pValue) {
  if (pValue->type == INTVALUE) {
    printf("INTVALUE-%d\n", pValue->intValue);
  } else if (pValue->type == DOUBLEVALUE) {
    printf("DOUBLEVALUE-%g\n", pValue->doubleValue);
  } else if (pValue->type == STATEMENTVALUE) {
    printf("STATEMENTVALUE-%s\n", pValue->statementValue);
  } else if (pValue->type == ERRORVALUE) {
    printf("ERRORVALUE-%s\n", pValue->errorValue);
  } else {
    printf("UNKNOWNVALUE-T.T-%d\n", pValue->type);
  }
}

void add_value(Value* pValue, Value a, Value b) {
  Value result;
  if (a.type == ERRORVALUE) {
    *pValue = a;
    return;
  }
  if (b.type == ERRORVALUE) {
    *pValue = b;
    return;
  }

  if (a.type == INTVALUE && b.type == INTVALUE) {
    result.type = INTVALUE;
    result.intValue = a.intValue + b.intValue;
  } else {
    if (a.type == INTVALUE) {
      a.type = DOUBLEVALUE;
      a.doubleValue = (double)a.intValue;
    }
    if (b.type == INTVALUE) {
      b.type = DOUBLEVALUE;
      b.doubleValue = (double)b.intValue;
    }

    result.type = DOUBLEVALUE;
    result.doubleValue = a.doubleValue + b.doubleValue;
  }

  *pValue = result;
}

void sub_value(Value* pValue, Value a, Value b) {
  Value result;
  if (a.type == ERRORVALUE) {
    *pValue = a;
    return;
  }
  if (b.type == ERRORVALUE) {
    *pValue = b;
    return;
  }

  if (a.type == INTVALUE && b.type == INTVALUE) {
    result.type = INTVALUE;
    result.intValue = a.intValue - b.intValue;
  } else {
    if (a.type == INTVALUE) {
      a.type = DOUBLEVALUE;
      a.doubleValue = (double)a.intValue;
    }
    if (b.type == INTVALUE) {
      b.type = DOUBLEVALUE;
      b.doubleValue = (double)b.intValue;
    }

    result.type = DOUBLEVALUE;
    result.doubleValue = a.doubleValue - b.doubleValue;
  }

  *pValue = result;
}

void mul_value(Value* pValue, Value a, Value b) {
  Value result;
  if (a.type == ERRORVALUE) {
    *pValue = a;
    return;
  }
  if (b.type == ERRORVALUE) {
    *pValue = b;
    return;
  }

  if (a.type == INTVALUE && b.type == INTVALUE) {
    result.type = INTVALUE;
    result.intValue = a.intValue * b.intValue;
  } else {
    if (a.type == INTVALUE) {
      a.type = DOUBLEVALUE;
      a.doubleValue = (double)a.intValue;
    }
    if (b.type == INTVALUE) {
      b.type = DOUBLEVALUE;
      b.doubleValue = (double)b.intValue;
    }

    result.type = DOUBLEVALUE;
    result.doubleValue = a.doubleValue * b.doubleValue;
  }

  *pValue = result;
}

void div_value(Value* pValue, Value a, Value b) {
  Value result;
  if (a.type == ERRORVALUE) {
    *pValue = a;
    return;
  }
  if (b.type == ERRORVALUE) {
    *pValue = b;
    return;
  }

  if (a.type == INTVALUE && b.type == INTVALUE) {
    result.type = INTVALUE;
    result.intValue = a.intValue / b.intValue;
  } else {
    if (a.type == INTVALUE) {
      a.type = DOUBLEVALUE;
      a.doubleValue = (double)a.intValue;
    }
    if (b.type == INTVALUE) {
      b.type = DOUBLEVALUE;
      b.doubleValue = (double)b.intValue;
    }

    result.type = DOUBLEVALUE;
    result.doubleValue = a.doubleValue / b.doubleValue;
  }

  *pValue = result;
}

void test_value(Value* pValue, Value a) {
  Value result;

  result.type = INTVALUE;
  if (a.type == INTVALUE) {
    result.intValue = a.intValue != 0;
  } else if (a.type == DOUBLEVALUE) {
    result.intValue = a.doubleValue != 0.0;
  } else if (a.type == ERRORVALUE) {
    result = a;
  } else {
    result.type = ERRORVALUE;
    result.errorValue = "invalid test.";
  }

  *pValue = result;
}
/*
void calculate_value(Value* pValue, Value a, Value b, int op) {

  Value result;
  if (a.type == ERRORVALUE) {
    *pValue = a;
    return;
  }
  if (b.type == ERRORVALUE) {
    *pValue = b;
    return;
  }

  if (a.type == INTVALUE && b.type == INTVALUE) {
    result.type = INTVALUE;
    
    switch(op) {
      case PLUS:
        result.intValue = a.intValue + b.intValue;
        break;
      case MINUS:
        result.intValue = a.intValue - b.intValue;
        break;
      case MULTIPLY:
        result.intValue = a.intValue * b.intValue;
        break;
      case DIVIDE:
        if (b.intValue == 0) {
          printf("error: can not divide by zero\n");
          break;
        }
        result.type = DOUBLEVALUE;
        result.doubleValue = (double)a.intValue / (double)b.intValue;
        break;

      default:
        printf("unknown operator\n");
        break;
    }
    
  } else {
    if (a.type == INTVALUE) {
      a.type = DOUBLEVALUE;
      a.doubleValue = (double)a.intValue;
    }
    if (b.type == INTVALUE) {
      b.type = DOUBLEVALUE;
      b.doubleValue = (double)b.intValue;
    }

    result.type = DOUBLEVALUE;
    switch(op) {
      case PLUS:
        result.doubleValue = a.doubleValue + b.doubleValue;
        break;
      case MINUS:
        result.doubleValue = a.doubleValue - b.doubleValue;
        break;
      case MULTIPLY:
        result.doubleValue = a.doubleValue * b.doubleValue;
        break;
      case DIVIDE:
        if (b.doubleValue == 0) {
          printf("error: can not divide by zero\n");
          break;
        }        
        result.doubleValue = a.doubleValue / b.doubleValue;
        break;

      default:
        printf("unknown operator\n");
        break;
    }
  }

  *pValue = result;
}
*/
