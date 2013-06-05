typedef enum {
  NTSTATEMENTLIST,
  NTSTATEMENT,
  NTASSIGNMENT,
  NTEXPRESSION,
  NTIDENTIFIER,
  NTBINARYOPERATOR,
  NTUNARYOPERATOR,
  NTINTEGER, NTDOUBLE
} tagNodeType;

typedef struct Node {
  tagNodeType type;

  // if type is NTINTEGER or NTDOUBLE
  Value value;

  // if type is NTIDENTIFIER
  char name[100];

  // otherwise
  struct Node* child_nodes[100];
  int n_of_child_nodes;
} Node;
