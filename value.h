typedef enum { INTVALUE = 1000, DOUBLEVALUE, STATEMENTVALUE, ERRORVALUE } tagValueType;

typedef struct Value {
  tagValueType type;
  union {
    int intValue;
    double doubleValue;
    char* statementValue;
    char* errorValue;
  };
} Value;
