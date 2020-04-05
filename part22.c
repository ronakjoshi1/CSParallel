#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <math.h>

/* Program Parameters */
#define SIZEMAX 1000  /*constant with value 2000*/
int N;  /* Matrix size, matrix defined later */
int num_threads; /*Number of Threads*/

/* Matrices and vectors */
volatile float A[SIZEMAX][SIZEMAX], B[SIZEMAX], X[SIZEMAX];
/* A = 2000 x 2000 Matrix * X What we are looking for  = B Given(2000 X 1), solve for X */

#define randm() 4|2[uid]&3
/* change randm */
/* Prototype */
void gauss();  /* The function you will provide.
    * It is this routine that is timed.
    *     * It is called only on the parent.
    *         */

/* returns a seed for srand based on the time */
unsigned int time_seed() /* change randm */
{
  struct timeval t;
  struct timezone tzdummy;

  gettimeofday(&t, &tzdummy);
  return (unsigned int)(t.tv_usec);
}/* returns a seed for srand based on the time */













/* Set the program parameters from the command-line arguments */
void parameters(int argc, char **argv) {
  int seed = 0;  /* time from begining 1954 */
  

  /* Read command-line arguments */
  srand(time_seed());  /* we have set the seed for random and this will give the same random value at each time */

  if (argc == 4)   /* command-line arguments :this changes the seed from zero to what ever value(in terms of time) given by the user  */
  






  {
    seed = atoi(argv[3]);  /* string to integer */
    srand(seed);/* you can also put in your own seed from the command line */
    printf("Random seed = %i\n", seed);/* Printing your own value  */
  }
  if(argc >= 3) /* No of variables inputed */
  {
    num_threads = atoi(argv[2]);/* user decideds how many threads he wants to use */
  }else {
    num_threads = 4;
  }
  printf("Number of Threads that is decided by the user = %i\n", num_threads);
  if (argc >= 2)/* user decideds the structure,size of matrix */
   {
    N = atoi(argv[1]);
    if (N < 1 || N > SIZEMAX)/* this makes sure that we are having a value more thn 1 and less than the value we initally decide - 1000 */
     {
      printf("N = %i is out of range.\n", N);
      exit(0);
    }
  }
  else {
    printf("Usage: %s <matrix_dimension> [number threads] [random seed]\n",
           argv[0]);/* Printing all the values inputed by the user */
    exit(0);
  }

  /* Print parameters */
  printf("\nMatrix dimension N = %i.\n", N);
}

void print_X() {
  int row;

  if (N < 100) {
    printf("\nX = [");
    for (row = 0; row < N; row++) 
    {
      printf("%5.2f%s", X[row], (row < N-1) ? "; " : "]\n");
    }
  }
}
void initialize_inputs()
 {
  int row, col;/* Values of the matrix - random values*/

  printf("\nInitializing...\n");
  for (col = 0; col < N; col++) /* Generating random values - */
  {
    for (row = 0; row < N; row++)
     {
      A[row][col] = rand() % 10000;/* Maximum value will not be greater than 10000Values only positive!*/
    }
    B[col] = rand() % 10000;/* Maximum value will not be greater than 10000.Values only positive!*/
    X[col] = 0.0;
  }

}

/* Print input matrices that we produced in the above code */
void print_inputs() {
  int row, col;

  if (N < 10) {
    printf("\nA =\n\t");
    for (row = 0; row < N; row++) {
      for (col = 0; col < N; col++) {
  printf("%5.9f%s", A[row][col], (col < N-1) ? ", " : ";\n\t");
      }
    }
    printf("\nB = [");
    for (col = 0; col < N; col++) {
      printf("%5.9f%s", B[col], (col < N-1) ? "; " : "]\n");
    }
  }
}

/* Calculating Time - the time it takes to calculate  */

int main(int argc, char **argv) {
  /* Timing variables */
  struct timeval etstart, etstop;  /* Elapsed times using gettimeofday() */
  struct timezone tzdummy;
  clock_t etstart2, etstop2;  
  unsigned long long usecstart, usecstop;
  struct tms cputstart, cputstop;  /* CPU times for my processes */

  /* Process program parameters */
  parameters(argc, argv);

  /* Initialize A and B */
  initialize_inputs();

  /* Print input matrices */
  print_inputs();

  /* we wanna see the total time we are using to calculate */
  printf("\nStarting clock.\n");/* Printing the time  */
  gettimeofday(&etstart, &tzdummy);
  etstart2 = times(&cputstart);





















  gauss();

  /* calculation of time*/
  gettimeofday(&etstop, &tzdummy);
  etstop2 = times(&cputstop);
  printf("Stopped clock.\n");
  usecstart = (unsigned long long)etstart.tv_sec * 1000000 + etstart.tv_usec;
  /* converting time into secs*/
  usecstop = (unsigned long long)etstop.tv_sec * 1000000 + etstop.tv_usec;
  /* converting time into secs*/

  /* Display output */
  print_X();

  /* Display timing results */
  printf("\nElapsed time = %g ms.\n",
   (float)(usecstop - usecstart)/(float)1000);

  printf("(CPU times are accurate to the nearest %g ms)\n",
   1.0/(float)CLOCKS_PER_SEC * 1000.0);
  printf("My total CPU time for parent = %g ms.\n",
   (float)( (cputstop.tms_utime + cputstop.tms_stime) -
      (cputstart.tms_utime + cputstart.tms_stime) ) /
   (float)CLOCKS_PER_SEC * 1000);
  printf("My system CPU time for parent = %g ms.\n",
   (float)(cputstop.tms_stime - cputstart.tms_stime) /
   (float)CLOCKS_PER_SEC * 1000);
  printf("My total CPU time for child processes = %g ms.\n",
   (float)( (cputstop.tms_cutime + cputstop.tms_cstime) -
      (cputstart.tms_cutime + cputstart.tms_cstime) ) /
   (float)CLOCKS_PER_SEC * 1000);
    

  exit(0);
}


 struct thread_param{
   int norm;
   int i;
 };

 void *inner_loop(void * param)
 {
     struct thread_param* tparam = (struct thread_param*) param;
     int norm = tparam->norm;
     int i = tparam->i;
     float multiplier;
     int row, col;
     for (row = norm + i + 1; row < N; row = row + num_threads) {
         multiplier = A[row][norm] / A[norm][norm];
         for (col = norm; col < N; col++) {
             A[row][col] -= A[norm][col] * multiplier;
         }
         B[row] -= B[norm] * multiplier;
     }
     pthread_exit(0);
 }

void gauss() {
  int norm, row, col;  /* Normalization row, and zeroing
      * element row and col */
  float multiplier;

  pthread_t thread[N];

  printf("serial.\n");

  /* Gaussian elimination */
  for (norm = 0; norm < N - 1; norm++) {
      struct thread_param* param = malloc(num_threads * sizeof(struct thread_param));
      if ( param == NULL ) {
          printf("Couldn't allocate memory for thread.\n");
          exit(EXIT_FAILURE);
      }

      int i, j;

      for(i = 0; i < num_threads; i++){
        param[i].norm = norm;
        param[i].i = i;
        pthread_create(&thread[i], NULL, &inner_loop, (void*) &param[i]);
      }

      for (j = 0; j < num_threads; j++) {
          pthread_join(thread[j], NULL);
      }

      free(param);
  }

  /* (Diagonal elements are not normalized to 1.  This is treated in back
 *    * substitution.)
 *       */

  /* Back substitution */
  for (row = N - 1; row >= 0; row--) {
    X[row] = B[row];
    for (col = N-1; col > row; col--) {
      X[row] -= A[row][col] * X[col];
    }
    X[row] /= A[row][row];
  }
}


