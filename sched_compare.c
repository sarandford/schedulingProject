#include <stdio.h>   // for printf()
#include <stdlib.h>  // for atoi()

#include "procs.h"
#include "procheap.h"

// DO NOT CHANGE THESE TWO CONSTANTS !
#define INTER_ARRIVAL_TIME 3   // mean poisson dist
#define SERVICE_TIME       5   // mean poisson dist

void find_arriving(int numprocs, int current_time,proc_t *procs){
	int i = 0;//counter 
	while(i<numprocs){
		if (procs[i].arrival_time == current_time){
			printf("\n inserted proc %d to heap! \n", i);
			heap_insert(&procs[i]);
			printf("\n heap size is now: %d \n", heap_size());
		}
		i++;
	}
}
/**
int min_arriving(int numprocs, proc_t *procs){
	int i = 0;//counter
	int min_arrival_time = procs[0].arrival_time;//stores the min arrival time
	proc_t *min_proc = &procs[0];
	while(i<numprocs){
		if(procs[i].arrival_time < min_arrival_time){
			min_proc = &procs[i];
			min_arrival_time = procs[i].arrival_time;
		}
		
		i++;	
	}
	heap_insert(min_proc);
	//printf("\n min arrving time = %d \n", min_arrival_time);
	return min_arrival_time;
}
**/
double spn_value(proc_t *procs){
	return procs->service_time;
}
void shortest_process_next(int numprocs, proc_t *procs){
	double current_time = 0;
	double avg_wait = 0;
	double avg_tat = 0;
	double current_and_service_time = 0;
	proc_t* service_proc = malloc(sizeof(proc_t));

	heap_init(numprocs, spn_value);
	current_time = procs->arrival_time;
	find_arriving(numprocs, current_time,procs);//assumes min is first 
	while(heap_size() > 0){
		printf("service time: %f heap_size: %d \n", heap_top()->service_time, heap_size());
		service_proc = heap_top();
		printf("\n about to delete min \n");
		heap_deletemin();
		printf("\n deleted min size is now: %d \n", heap_size());
		avg_wait = avg_wait + (current_time-service_proc->arrival_time);
		current_and_service_time = current_time + service_proc->service_time;
 		while(current_time < current_and_service_time){

			current_time++;
			find_arriving(numprocs, current_time, procs);
		}
		avg_tat = avg_tat + (current_time - service_proc->arrival_time);
	
	}

	avg_wait = avg_wait / numprocs;
	avg_tat = avg_tat / numprocs;
	printf("\n average wait time: %f \n", avg_wait);
	printf("\n average turnaround time: %f \n", avg_tat);
	heap_free();
	
}




int main(int argc, char** argv)
{
  int numprocs, seed;
  proc_t *procs;   // array of procs with service time and arrival time

  if (argc < 3) {
    fprintf(stderr, "USAGE: %s numprocs seed\n", argv[0]);
    return 1;
  }

  numprocs = atoi(argv[1]);
  seed = atoi(argv[2]);

  // create an array of numprocs randomly generate (arrival time, service time)
  //procs = procs_random_create(numprocs, seed, INTER_ARRIVAL_TIME, SERVICE_TIME);
  
  // Uncomment the next block of code and comment the line above if
  // you want to read the input from a file instead of generating
  // random values. This can be useful for debugging your code with
  // known inputs.  The file, "book_example.txt", contains an example
  // from the book.

  
  if ((procs = procs_read("book_example.txt", &numprocs)) == NULL) {
    fprintf(stderr, "Error reading procs array\n");
    return 2;
  }
  

  printf("procs array:\n");
  printf("(arrival time, service time)\n");
  procs_print(procs, numprocs);
  heap_init(numprocs,spn_value);

  shortest_process_next(numprocs, procs);

  /* Either call your implemented functions for performing FCFS, SPN,
     and HRRN, or insert your code here to perform these algorithms.
     My recommendation is to write one or more functions for these
     algorithms in order for your main to be more readable and
     manageable.
  */
   
  

  free(procs);   // procs array was dynamically allocated, so free up

  return 0;
}
