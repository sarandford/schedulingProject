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
			//printf("inserted proc %d to heap! \n", i);
			heap_insert(&procs[i]);
			//printf("heap size is now: %d \n", heap_size());
		}
		i++;
	}
}

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
		//printf("service time: %f heap_size: %d \n", heap_top()->service_time, heap_size());
		service_proc = heap_top();
		//printf("\n about to delete min \n");
		heap_deletemin();
		//printf("\n deleted min size is now: %d \n", heap_size());
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

// ******************************
// FIRST-COME-FIRST-SERVED
// ******************************

// FCFS Heap sorting algorithm
double fcfs_value(proc_t *procs) {
		return procs->arrival_time;
}
void alt_fcfs(int numprocs, proc_t* procs){
	double current_time = 0;
	double avg_wait = 0;
	double avg_tat = 0;
	double current_and_service_time = 0;
	proc_t* service_proc = malloc(sizeof(proc_t));

	heap_init(numprocs,fcfs_value);
	current_time = procs->arrival_time;
	find_arriving(numprocs, current_time,procs);//assumes min is first
	while(heap_size() > 0){
		//printf("service time: %f heap_size: %d \n", heap_top()->service_time, heap_size());
		service_proc = heap_top();
		//printf("\n about to delete min \n");
		heap_deletemin();
		//printf("\n deleted min size is now: %d \n", heap_size());
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
	printf("\n ALT FCFS\n");
	printf("\n average wait time: %f \n", avg_wait);
	printf("\n average turnaround time: %f \n", avg_tat);
	heap_free();
}
// First-Come-First-Served algorithm
void first_come_first_served(int numprocs, proc_t *procs) {
	double avg_wait = 0;
	double avg_tat = 0;
	double current_time = 0; // the time at the intersection between two procs
	int i;
	proc_t* proc;

	// Initialize the heap
	heap_init(numprocs, fcfs_value);

	// Add all the procs to the heap
	for(i=0; i<numprocs; i++) {
		heap_insert(&procs[i]);
	}

	// Pop all the procs off the heap
	for(i=0; i<numprocs; i++) {
		proc = heap_deletemin();
		// The if/else block exists in case there is a space between processes
		if(proc->arrival_time <= current_time) {
			avg_wait += current_time - proc->arrival_time;
			avg_tat += (current_time - proc->arrival_time) + proc->service_time;
		} else {
			avg_tat += proc->service_time;
		}
		current_time += proc->service_time;
	}

	// Calculate averages
	avg_wait = avg_wait / numprocs;
	avg_tat = avg_tat / numprocs;

	// Print the results
	printf("FIRST-COME-FIRST-SERVED:\n");
	printf("Mean Wait Time: \t%f\n", avg_wait);
	printf("Mean Turnaround Time: \t%f\n\n", avg_tat);

	// Free up the heap
	heap_free();
}


// ******************************
// HIGHEST RESPONSE RATIO NEXT
// ******************************

// HRRN Heap sorting algorithm
double hrrn_value(proc_t *procs) {
	// VERY IMPORTANT: I treat wait_time as the total time since the beginning of the simulation,
	// therefore the process wait time is equal to wait_time - arrival_time. The value is made
	// negative because the heap sorts by minimums, not maximums.
	return procs->service_time/(procs->wait_time+procs->service_time);
}

// Highest Response Ratio Next algorithm
void highest_response_ratio_next(int numprocs, proc_t *procs) {
	double avg_wait = 0;
	double avg_tat = 0;
	double current_time = 0;
	int i;
	proc_t* proc;

	// Initialize the heap
	heap_init(numprocs, hrrn_value);

	// Add all the procs to the heap
	for(i=0; i<numprocs; i++) {
		heap_insert(&procs[i]);
	}

	// Pop all the procs off the heap
	for(i=0; i<numprocs; i++) {
		proc = heap_top();
		heap_age(proc->service_time);
		heap_deletemin(); // The heap is resorted when there is a delete
		// The if/else block exists in case there is a space between processes
		if(proc->arrival_time <= current_time) {
			avg_wait += current_time - proc->arrival_time;
			avg_tat += (current_time - proc->arrival_time) + proc->service_time;
		} else {
			avg_tat += proc->service_time;
		}
		current_time += proc->service_time;
	}

	// Calculate averages
	avg_wait = avg_wait / numprocs;
	avg_tat = avg_tat / numprocs;

	// Print the results
	printf("HIGHEST RESPONSE RATIO NEXT:\n");
	printf("Mean Wait Time: \t%f\n", avg_wait);
	printf("Mean Turnaround Time: \t%f\n\n", avg_tat);

	heap_free();
}
void alt_hhrn(proc_t* procs, int numprocs){
	double current_time = 0;
	double avg_wait = 0;
	double avg_tat = 0;
	double current_and_service_time = 0;
	proc_t* service_proc = malloc(sizeof(proc_t));
	//WHAT IF WE JUST HAD A NEGATIVE WAIT 
	heap_init(numprocs, hrrn_value);
	current_time = procs->arrival_time;
	find_arriving(numprocs, current_time,procs);//assumes min is first
	while(heap_size() > 0){
		//printf("service time: %f heap_size: %d \n", heap_top()->service_time, heap_size());
		service_proc = heap_top();
		//printf("\n about to delete min \n");
		heap_deletemin();
		//if any procs have a wait time in between this 
		//printf("\n deleted min size is now: %d \n", heap_size());
		
		avg_wait = avg_wait + (current_time-service_proc->arrival_time);
		current_and_service_time = current_time + service_proc->service_time;
 		while(current_time < current_and_service_time){
			current_time++;
			heap_age(1);
			find_arriving(numprocs, current_time, procs);
		}
		avg_tat = avg_tat + (current_time - service_proc->arrival_time);

	}

	avg_wait = avg_wait / numprocs;
	avg_tat = avg_tat / numprocs;
	printf("\n ALTERNATE HHRN: \n");
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

	// create an array of numprocs from the book_example.txt file (Comment if random)
  if ((procs = procs_read("book_example.txt", &numprocs)) == NULL) {
    fprintf(stderr, "Error reading procs array\n");
    return 2;
  }

  printf("procs array:\n");
  printf("(arrival time, service time)\n");
  procs_print(procs, numprocs);

	// CALL SORTING FUNCTIONS
  	shortest_process_next(numprocs, procs);
	first_come_first_served(numprocs, procs);
	alt_fcfs(numprocs, procs);
	highest_response_ratio_next(numprocs, procs);
	alt_hhrn(procs, numprocs);

  free(procs);   // procs array was dynamically allocated, so free up

  return 0;
}
