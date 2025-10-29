#include <stdio.h>
#include <stdlib.h>


int main() {
    int n, m, i, j, k;

    printf("Enter number of processes (N): ");
    scanf("%d", &n);

    printf("Enter number of resource types (M): ");
    scanf("%d", &m);

    int max[n][m];
    int allocation[n][m];
    int available[m];
    int need[n][m];
    int work[m];
    int finish[n];
    int safeSequence[n];
    int count = 0;

    printf("\nEnter Maximum resources matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter Allocation matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("\nEnter Available resources vector:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &available[i]);
        work[i] = available[i];
    }

    for (i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int possible = 1;
    while (count < n && possible) {
        possible = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int canExecute = 1;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = 0;
                        break;
                    }
                }

                if (canExecute) {
                    for (k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    possible = 1;
                }
            }
        }
    }

    if (count == n) {
        printf("\nSystem is in a safe state.\n");
        printf("Safe Sequence: <");
        for (i = 0; i < n; i++) {
            printf("P%d", safeSequence[i]);
            if (i < n - 1) {
                printf(", ");
            }
        }
        printf(">\n");
    } else {
        printf("\nSystem is in an unsafe state. Deadlock might occur.\n");
    }

    return 0;
}
