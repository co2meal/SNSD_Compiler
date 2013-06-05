typedef enum { INTVALUE = 1000, DOUBLEVALUE, ERRORVALUE } tagValueType;

typedef struct Value {
  tagValueType type;
  union {
    int intValue;
    double doubleValue;
    char* errorValue;
  };
} Value;
