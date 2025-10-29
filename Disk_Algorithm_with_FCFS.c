#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int calculate_seek_time(int a, int b) {
    return abs(a - b);
}

void fcfs_simulate(int requests[], int num_requests, int initial_head_pos) {
    int total_seek_time = 0;
    int current_head = initial_head_pos;

    printf("\n--- FCFS Disk Scheduling Simulation ---\n");
    printf("Starting Head Position: %d\n", initial_head_pos);
    printf("Request Sequence: ");
    for (int i = 0; i < num_requests; i++) {
        printf("%d%s", requests[i], (i == num_requests - 1) ? "" : " -> ");
    }
    printf("\n\n");

    printf("Traversal Sequence and Seek Calculation:\n");

    for (int i = 0; i < num_requests; i++) {
        int next_request = requests[i];

        int seek_time = calculate_seek_time(current_head, next_request);
        total_seek_time += seek_time;

        printf("  -> Move from %d to %d | Seek Time = %d\n",
               current_head, next_request, seek_time);

        current_head = next_request;
    }

    printf("\nTotal Head Movement (Seek Time): %d\n", total_seek_time);
}

int main() {
    int num_requests;
    int initial_head_pos;

    printf("Enter the initial position of the disk head: ");
    if (scanf("%d", &initial_head_pos) != 1 || initial_head_pos < 0) {
        fprintf(stderr, "Invalid head position entered. Exiting.\n");
        return 1;
    }

    printf("Enter the number of disk requests: ");
    if (scanf("%d", &num_requests) != 1 || num_requests <= 0) {
        fprintf(stderr, "Invalid number of requests entered. Exiting.\n");
        return 1;
    }

    int *requests = (int *)malloc(num_requests * sizeof(int));
    if (requests == NULL) {
        fprintf(stderr, "Memory allocation failed. Exiting.\n");
        return 1;
    }

    printf("Enter the disk request sequence (track numbers):\n");
    for (int i = 0; i < num_requests; i++) {
        printf("Request %d: ", i + 1);
        if (scanf("%d", &requests[i]) != 1 || requests[i] < 0) {
            fprintf(stderr, "Invalid track number entered. Exiting.\n");
            free(requests);
            return 1;
        }
    }

    fcfs_simulate(requests, num_requests, initial_head_pos);

    free(requests);

    return 0;
}
