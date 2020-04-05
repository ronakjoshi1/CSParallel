#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h> 
#include<time.h>

pthread_mutex_t minimum_value_lock;

void *find_min(void *list_ptr);
int partial_list_size;
#define MIN_INT 100000000;
int coun_t[] = {1,2,4,8,16,32};
int minimum_value = 100000000;
int val[100000000];
int s;

void *find_min(void *list_ptr) {

  int *partial_list_pointer = 0, my_min = 0, i = 0;
  my_min = MIN_INT;
  partial_list_pointer = (int *) list_ptr;

  for (i = 0; i < partial_list_size; i++){ 
    if (partial_list_pointer[i] < my_min)
      my_min = partial_list_pointer[i];
   
    pthread_mutex_lock(&minimum_value_lock);
    if (my_min < minimum_value)
      minimum_value = my_min;
   
    pthread_mutex_unlock(&minimum_value_lock);
  }
  pthread_exit(0);
}


int main() {
  srand( (unsigned)time(NULL) );
  int kl, ql, i;
  for (kl = 0; kl<100000000; kl++){
    val[kl] = rand(); 
    }
  for (ql = 0; ql< 6; ql++){
    clock_t t;
    t = clock(); 
    minimum_value = MIN_INT;
  
  pthread_mutex_init(&minimum_value_lock, NULL); 
  partial_list_size = 100000000/(coun_t[ql]);
  int* starting_addr = val;

  pthread_t threads[coun_t[ql]];
  printf("Creating %d threads\n", coun_t[ql]);
  for(i=0; i < coun_t[ql]; i++) {
    printf("creating thread : %d\n", i);
    s = pthread_create(&threads[i], NULL, find_min, (void*)starting_addr);
    starting_addr += partial_list_size;
   
    }

    for (i = 0; i < coun_t[ql]; i++)
        pthread_join(threads[i], NULL);
    printf("Minimum is : %d\nTime Taken = %ld\n", minimum_value, ((clock() - t)/CLOCKS_PER_SEC));
    printf("Task Completed");
  }
    return 0;
}



