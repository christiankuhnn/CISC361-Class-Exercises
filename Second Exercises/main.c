#include<stdio.h>
#include<stdbool.h>

int main()
{
    // Initialize variables
    int i = 0, num_processes = 0, total_time = 0, x, output_flag = 0, time_quantum = 0;
    int wait_time = 0, turnaround_time = 0, arrival_time[10], burst_time[10], temp[10];
    float average_wait_time = 0, average_turnaround_time = 0;
    bool round_robin_algorithm = true; // Set round_robin_algorithm flag to true

    for(i = 0; i < 10; i++)
    {
        arrival_time[i] = 0;
        burst_time[i] = 0;
        temp[i] = 0;
    }

    // Define Number of Processes
    while(num_processes < 1 || num_processes > 10)
 {
        printf("\nEnter Total Number of Processes (1 - 10):\t");
        scanf("%d", &num_processes);

        if (num_processes < 1 || num_processes > 10)
        {
            printf("Incorrect Value Entered");
        }
    }

    // Define Process Details
    x = num_processes;
    for(i = 0; i < num_processes; i++)
    {
        printf("\nEnter Details of Process[%d]\n", i + 1);
        printf("Arrival Time (>-1):\t");
        scanf("%d", &arrival_time[i]);
        printf("Burst Time (>0):\t");
        scanf("%d", &burst_time[i]);
        temp[i] = burst_time[i];

        if (arrival_time[i] < 0 || burst_time[i] < 1)
        {
            printf("Incorrect Values Entered");
            i--;
        }
    }

    // Define Quantum
    if (round_robin_algorithm)
    {
        while(time_quantum < 1)
        {
            printf("\nEnter Time Quantum (>0):\t");
            scanf("%d", &time_quantum);

            if (time_quantum < 1)
            {
                printf("Incorrect Value Entered");
            }
        }
    }

    // Prepare Output
    printf("\nProcess ID\t\tArrival Time\t\tBurst Time\t Turnaround Time\t Waiting Time\n");

    // Perform Scheduling Calculations
    wait_time = 0;
    turnaround_time = 0;

    if (!round_robin_algorithm)
    {
        // FCFS Scheduling
        for (i = 0; i < num_processes; i++)
        {
            turnaround_time += burst_time[i];
            wait_time += turnaround_time - arrival_time[i];

            printf("%d\t\t\t%d\t\t\t%d\t\t%d\t\t%d\n",
                   i + 1, arrival_time[i], burst_time[i], turnaround_time, wait_time);
        }
    }
    else
    {
        // Round Robin Scheduling
        int remaining_time[10];
        for (i = 0; i < num_processes; i++)
            remaining_time[i] = burst_time[i];

        int current_time = 0;
        int completed = 0;

        while (completed != num_processes)
        {
            for (i = 0; i < num_processes; i++)
            {
                if (remaining_time[i] > 0)
                {
                    if (remaining_time[i] <= time_quantum)
                    {
                        current_time += remaining_time[i];
                        turnaround_time += current_time - arrival_time[i];
                        wait_time += current_time - arrival_time[i] - burst_time[i];
                        remaining_time[i] = 0;
                        completed++;
                    printf("%d\t\t\t%d\t\t\t%d\t\t%d\t\t%d\n",
                           i + 1, arrival_time[i], burst_time[i], turnaround_time, wait_time);
                }
                else
                {
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                }
            }
        }
  }
 }



// Calculate average waiting and turnaround times
average_wait_time = (float) wait_time / num_processes;
average_turnaround_time = (float) turnaround_time / num_processes;

printf("\n\nAverage Waiting Time: %f", average_wait_time);
printf("\nAverage Turnaround Time: %f\n", average_turnaround_time);

return 0;

}           
