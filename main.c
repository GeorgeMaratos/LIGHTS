#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct unit {
  int **board, move_count;
  struct unit *queue_next, *next;
} Unit;

typedef struct queue {
  Unit *first;
  int element_count;
} Queue;

Queue *search_space = NULL;
int **init_board, dimension = 0, test_cases = 0;

Unit *create_unit(int **board, int move_count) {
  Unit *ret = malloc(sizeof(Unit));
  ret->board = board;
  ret->move_count = move_count;
  ret->queue_next = NULL;
  return ret;
}

void *init_queue() {
  search_space = malloc(sizeof(Queue));
  search_space->first = NULL;
  search_space->element_count = 0;
}

void queue_push(Unit *elem) {
  Unit* temp = NULL;
  temp = search_space->first;
  search_space->first = elem;
  elem->queue_next = temp;
  search_space->element_count++;
}

Unit *queue_pop() {
  Unit *ret = NULL, *temp = NULL;
  if(search_space->element_count == 1) {
    ret = search_space->first;
    search_space->first = NULL;
    search_space->element_count--;
  }
  else if(search_space->element_count > 1) {
    temp = search_space->first;
    while(temp->queue_next->queue_next)
      temp = temp->queue_next;
    ret = temp->queue_next;
    temp->queue_next = NULL;
    search_space->element_count--;
  }
  return ret;
}

int solve_board(void) {
  return 0;
}

int read_board(FILE *f) {
  char buf[10], *tok;
  int i, j;

  fgets(buf,10,f);
  tok = strtok(buf," \n");
  dimension = atoi(tok);

  init_board = malloc(sizeof(int *) * dimension);
  for(i=0;i<dimension;i++)
    init_board[i] = malloc(sizeof(int) * dimension);
  
  for(i=0;i<dimension;i++) {
    for(j=0;j<dimension;j++) {
      if(!j) {
        fgets(buf,10,f);
	tok = strtok(buf," \n");
	init_board[i][j] = atoi(tok);
      }
      else {
	tok = strtok(NULL," \n");
	init_board[i][j] = atoi(tok);
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
