#include <stdio.h>

typedef struct pcb {
  int pid;
  struct pcb *next;
} PCB ;

typedef struct ready_queue {
  PCB *head;
  PCB *tail;
} RQ;

int main () {
  RQ ready_queue;
  ready_queue.head = NULL;
  ready_queue.tail = NULL;
  return 0;
}
