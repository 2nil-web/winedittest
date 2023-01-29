
#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER
#include "editline/readline.h"
#else
#include <readline/readline.h>
#include <readline/history.h>
#endif

int main(int argc, char *argv[])
{
  char *line;

  printf("\nType exit to quit the test\n\n");
  while ((line = readline("prompt>"))
    && (strncmp(line, "exit", 4))) {
    printf("string='%s'\n", line);
    add_history(line);
    free(line);
  }
  
  return 0;
}
