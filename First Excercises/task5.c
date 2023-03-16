#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_NO_OF_THREADS 2
#define MAX_NO_OF_ELEMENTS 100000000

typedef struct arg_data {
    int thread_number;
    int startpart;
    int endpart;
} arg_data;

//shared data on which threads will work concurrently
//array which will be summed
static int arr[MAX_NO_OF_ELEMENTS];

//sum variable that will store the total sum
static long long int sum;

void* worker_sum(void* arg)
{
    arg_data* current_thread_data = (arg_data*)arg;
    int current_thread_sum = 0;
    printf("Current thread no is : %d\n", current_thread_data->thread_number);
    //Determine the bounds
    int startpart = current_thread_data->startpart;
    int endpart = current_thread_data->endpart;
    printf("Here we will sum %d to %d\n", arr[startpart], arr[endpart - 1]);
    //Generate the sum
    for (int i = startpart; i < endpart; i++) {
        current_thread_sum += arr[i];
    }
    sum += current_thread_sum;
    return NULL;
}

int main() {
    //let the array consists of first MAX_NO_OF_ELEMENTS integers,
    //1 to MAX_NO_OF_ELEMENTS
    for (int i = 0; i < MAX_NO_OF_ELEMENTS; i++)
        arr[i] = i + 1;

    //pthread objects
    pthread_t id[MAX_NO_OF_THREADS];

    //argument data to send in worker functions
    arg_data arg_arr[MAX_NO_OF_THREADS];

    //total number of threads we will create
    int no_of_threads = MAX_NO_OF_THREADS;

    //Setup timing
    clock_t start, end;
    double cpu_time_taken;
    start = clock();

    //creating the child threads
    int startpart = 0;
    int endpart = MAX_NO_OF_ELEMENTS / no_of_threads;

    for (int i = 0; i < no_of_threads; i++) {
        arg_arr[i].thread_number = i;
        arg_arr[i].startpart = startpart;
        arg_arr[i].endpart = endpart;
        pthread_create(&id[i], NULL, worker_sum, (void*)&arg_arr[i]);
        startpart = endpart;
        endpart += MAX_NO_OF_ELEMENTS / no_of_threads;
    }

    //joining the threads one by one
    for (int i = 0; i < no_of_threads; i++) {
        pthread_join(id[i], NULL);
    }

    end = clock();
    cpu_time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("All child threads have finished their works...\n");
    printf("Total sum: %lld\n", sum);
    printf("Time taken to sum all the numbers is %lf seconds.\n", cpu_time_taken);

    return 0;
}
