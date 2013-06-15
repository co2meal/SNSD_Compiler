typedef enum {
  NTSTATEMENTLIST,
  NTSTATEMENT,
  NTIFSTATEMENT,
  NTWHILESTATEMENT,
  NTRETURNSTATEMENT,
  NTASSIGNMENT,
  NTEXPRESSIONLIST,
  NTEXPRESSION,
  NTIDENTIFIER,
  NTBINARYOPERATOR,
  NTUNARYOPERATOR,
  NTINTEGER, NTDOUBLE,
  NTFUNCDECLARE,
  NTFUNCCALL,
  NTPARAMETERLIST
} tagNodeType;

typedef struct Node {
  tagNodeType type;

  // if type is NTINTEGER or NTDOUBLE
  Value value;

  // if type is NTIDENTIFIER
  char name[100];

  // if type is NTBINARYOPERATOR
  int op_token;

  // otherwise
  struct Node* child_nodes[100];
  int n_of_child_nodes;
} Node;
