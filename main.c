#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int **board, dimension = 0, test_cases = 0;

int solve_board(void) {
  return 0;
}

int read_board(FILE *f) {
  char buf[10], *tok;
  int i, j;

  fgets(buf,10,f);
  tok = strtok(buf," \n");
  dimension = atoi(tok);

  board = malloc(sizeof(int *) * dimension);
  for(i=0;i<dimension;i++)
    board[i] = malloc(sizeof(int) * dimension);
  
  for(i=0;i<dimension;i++) {
    for(j=0;j<dimension;j++) {
      if(!j) {
        fgets(buf,10,f);
	tok = strtok(buf," \n");
	board[i][j] = atoi(tok);
      }
      else {
	tok = strtok(NULL," \n");
	board[i][j] = atoi(tok);
      }
    }
  }
  return 0;
} 

int main(int argc, char **argv) {
  int i, j;
  char buf[10], *tok;
  FILE *f;

  if(argc != 2) 
    return 1;
  f = fopen(argv[1],"r");

  fgets(buf,10,f);
  tok = strtok(buf," \n");
  test_cases = atoi(tok);

  for(i=0;i<test_cases;i++) {
    if(read_board(f)) return 1;
    if(solve_board()) return 1;
  }

  return 0;
}
