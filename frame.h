#define MAX_VARIABLE_NAME    100
#define MAX_GLOBAL_VARIABLES 1000
#define MAX_LOCAL_VARIABLES  100
#define MAX_FRAME_STACK_SIZE 1000

typedef struct Frame {
  int n_of_local_variables;
  char local_variables_name[MAX_LOCAL_VARIABLES][MAX_VARIABLE_NAME];
  Value local_variables_value[MAX_LOCAL_VARIABLES];
  Value* pReturnValue;
} Frame;
