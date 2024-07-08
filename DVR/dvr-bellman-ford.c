#include <stdio.h>
#include <stdlib.h>

#define INFINITY 9999
#define MAX 10

void bellmanFordSingleSource(int costMatrix[MAX][MAX], int numNodes, int source) {
    int distance[MAX], nextHop[MAX];
    int i, j, k;

    // Initialize the distance and nextHop arrays
    for (i = 0; i < numNodes; i++) {
        distance[i] = INFINITY;
        nextHop[i] = -1;
    }
    distance[source] = 0;

    // Bellman-Ford algorithm
    for (k = 0; k < numNodes - 1; k++) { // Repeat numNodes-1 times
        for (i = 0; i < numNodes; i++) {
            for (j = 0; j < numNodes; j++) {
                if (costMatrix[i][j] != INFINITY && distance[i] != INFINITY &&
                    distance[j] > distance[i] + costMatrix[i][j]) {
                    distance[j] = distance[i] + costMatrix[i][j];
                    nextHop[j] = (i == source) ? j : nextHop[i];
                }
            }
        }
    }

    // Print the final distance and next hop arrays
    printf("Distance from source node %d:\n", source);
    for (i = 0; i < numNodes; i++) {
        if (distance[i] == INFINITY) {
            printf("Node %d: %7s\n", i, "INF");
        } else {
            printf("Node %d: %7d\n", i, distance[i]);
        }
    }

    printf("\nNext Hop from source node %d:\n", source);
    for (i = 0; i < numNodes; i++) {
        printf("Node %d: %7d\n", i, nextHop[i]);
    }
}

int main() {
    int numNodes, sourceNode, i, j;
    int costMatrix[MAX][MAX];

    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    printf("Enter the cost matrix (enter 9999 for infinity):\n");
    for (i = 0; i < numNodes; i++) {
        for (j = 0; j < numNodes; j++) {
            scanf("%d", &costMatrix[i][j]);
        }
    }

    printf("Enter the source node: ");
    scanf("%d", &sourceNode);

    bellmanFordSingleSource(costMatrix, numNodes, sourceNode);

    return 0;
}
