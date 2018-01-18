#include "Validation/validation.h"
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

//#define PTHREAD_SYNC

int SharedVariable = 0;

struct thread_args {
  int ID;
  pthread_mutex_t * mutex;
  pthread_barrier_t * barrier;
};

void * SimpleThread(void * rawArgs) {
  struct thread_args args = *((struct thread_args *) rawArgs);

  int which = args.ID;
  int num, val;
  for(num = 0; num < 20; num++) {

    //implements the spirit of the guideline while actually compiling
    if(rand() > RAND_MAX/2){
      struct timespec t = (struct timespec) {
        0,      //0 secs
        500000  //500k nanos = 500 millis as per the project
      };
      nanosleep(&t, NULL);
    }

    #ifdef PTHREAD_SYNC
      //locks mutex to allow atomic increment
      pthread_mutex_lock(args.mutex);
    #endif

    val = SharedVariable;
    printf("*** thread %d sees value %d\n", which, val);
    SharedVariable = val + 1;

    #ifdef PTHREAD_SYNC
      //releases the mutex after atomic increment
      pthread_mutex_unlock(args.mutex);
    #endif
  }
  #ifdef PTHREAD_SYNC
    //waits for all threads to reach barrier
    pthread_barrier_wait(args.barrier);
  #endif
  val = SharedVariable;
  printf("Thread %d sees final value %d\n", which, val);
}



int main(int argc, char * argv[]) {
  int numThreads;
  //boiler plate to add to validation code
  if (argc != 2) {
    printf("Correct usage:\n   ./sync.o n\nwhere n is the number of threads\n");
    exit(0);
  }else{
    struct ValidatedInt cand = parseInt(argv[1]);
    if(!cand.error){
      numThreads = cand.value;
    }else{
      printf("Error, could not parse argument. (%d)\n", cand.error);
      exit(0);
    }
  }

  //initializes the pthread constructs we need
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_barrier_t barrier;
  pthread_barrier_init(&barrier, NULL, numThreads);

  //array to store our pthread handles
  pthread_t threads[numThreads];

  //array of arguments to pass to corresponding threads
  struct thread_args args[numThreads];

  for(int i = 0; i < numThreads; i++) {
    //initializes each thread arg
    args[i] = (struct thread_args) {
      i, &mutex, &barrier
    };

    //spawns the threads
    pthread_create(&threads[i], NULL, SimpleThread, &args[i]);
  }

  //waits for all threads to finish before exiting
  for(int i = 0; i < numThreads; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
