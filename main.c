#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct unit {
  int **board, move_count;
  struct unit *queue_next, *prev;
} Unit;

typedef struct queue {
  Unit *first;
  int element_count;
} Queue;

Queue *search_space = NULL;
int **init_board, dimension = 0, test_cases = 0;

Unit *create_unit(int **board, int move_count, Unit *prev) {
  Unit *ret = malloc(sizeof(Unit));
  ret->board = board;
  ret->move_count = move_count;
  ret->queue_next = NULL;
  ret->prev = prev;
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

Unit *queue_pop(void) {
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

int is_win(int **board) {
  int i, j;
  for(i=0;i<dimension;i++) {
    for(j=0;j<dimension;j++)
      if(board[i][j]) return 0;
  }
  return 1;
}

void copy_board(int **board, int **new_board) {
  int i, j;
  for(i=0;i<dimension;i++) {
    for(j=0;j<dimension;j++) 
      new_board[i][j] = board[i][j];
  }
}
  
void swap(int **board, int i, int j, int count) {
  if(i < 0 || i == dimension || j < 0 || j == dimension || !count)
    return;
  if(board[i][j]) {
    board[i][j] = 0;
    swap(board, i - 1, j, count - 1);
    swap(board, i, j - 1, count - 1);
    swap(board, i + 1, j, count - 1);
    swap(board, i, j + 1, count - 1);
  }
  else {
    board[i][j] = 1;
    swap(board, i - 1, j, count - 1);
    swap(board, i, j - 1, count - 1);
    swap(board, i + 1, j, count - 1);
    swap(board, i, j + 1, count - 1);
  }
}
 
int **transform_board(int **board, int i, int j) {
  int k;
  int **new_board = malloc(sizeof(int *) * dimension);
  for(k=0;k<dimension;k++) 
    new_board[k] = malloc(sizeof(int) * dimension);

  copy_board(board,new_board);
  swap(new_board,i,j,2);
  return new_board;
}

void generate_sucessors(Unit *elem) {
  int i, j;
  int **temp_board = NULL;
  Unit *temp_unit = NULL;

  if(elem->move_count == 1000)
    return;

  for(i=0;i<dimension;i++) {
    for(j=0;j<dimension;j++) {
      temp_board = transform_board(elem->board, i, j);
      temp_unit = create_unit(temp_board, elem->move_count + 1, elem);
      queue_push(temp_unit);
    }
  }
}

int bfs(void) {
  Unit *temp = NULL;
  init_queue();
  queue_push(create_unit(init_board,0,NULL));
  while(search_space->element_count) {
    temp = queue_pop();
    if(is_win(temp->board)) {
      printf("moves to win: %d\n",temp->move_count);
      return 1;
    }
    else
      generate_sucessors(temp);
  }
  return 0;
}

int solve_board(void) {
  if(bfs()) {
    printf("Found solution\n");
    return 0;
  }
  return 1;
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
