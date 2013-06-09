struct Function;

typedef enum { INTVALUE = 1000, DOUBLEVALUE, STATEMENTVALUE, FUNCTIONVALUE, ERRORVALUE } tagValueType;

typedef struct Value {
  tagValueType type;
  union {
    int intValue;
    double doubleValue;
    char* statementValue;
    char* errorValue;
    struct Function* functionValue;
  };
} Value;
