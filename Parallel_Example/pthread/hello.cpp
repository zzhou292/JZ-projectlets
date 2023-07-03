#include <pthread.h>
#include <stdio.h>

void *PrintHello(void *id) { printf("Thread%d: Hello World!\n", id); }

int main() {
  pthread_t thread0, thread1;
  pthread_create(&thread0, NULL, PrintHello, (void *)0);
  pthread_create(&thread1, NULL, PrintHello, (void *)1);
  pthread_join(thread0, NULL);
  pthread_join(thread1, NULL);
  return 0;
}
