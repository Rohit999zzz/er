#include<stdio.h>

struct node {
    unsigned dist[20]; // Distance vector for the node
    unsigned from[20]; // Tracks the source of the minimum distance
} rt[10]; // Routing table for each node

int main() {
    int dmat[20][20]; // Cost matrix
    int n, i, j, k, count;

    // Input the number of nodes
    printf("\nEnter the number of nodes: ");
    scanf("%d", &n);

    // Input the cost matrix
    printf("\nEnter the cost matrix\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &dmat[i][j]);
            if (i == j) {
                dmat[i][j] = 0; // Distance to itself is zero
            }
            rt[i].dist[j] = dmat[i][j]; // Initialize distance vector
            rt[i].from[j] = j; // Initialize source as itself
        }
    }

    // Distance Vector Routing Algorithm
    do {
        count = 0;
        for (i = 0; i < n; i++) { // For each router
            for (j = 0; j < n; j++) { // For each destination
                for (k = 0; k < n; k++) { // For each intermediate node
                    if (rt[i].dist[j] > dmat[i][k] + rt[k].dist[j]) {
                        rt[i].dist[j] = dmat[i][k] + rt[k].dist[j]; // Update distance
                        rt[i].from[j] = k; // Update source
                        count++; // Increment change count
                    }
                }
            }
        }
    } while (count != 0); // Repeat until no changes

    // Display routing tables
    for (i = 0; i < n; i++) {
        printf("\n\nState value for router %d is \n", i + 1);
        printf("\nNode \t Via \t Dist.");
        for (j = 0; j < n; j++) {
            printf("\n%d \t %d \t %d ", j + 1, rt[i].from[j] + 1, rt[i].dist[j]);
        }
    }
    printf("\n\n");
    return 0;
}
