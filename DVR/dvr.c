#include <stdio.h>
#include <stdbool.h>
typedef struct
{
    int distance[20];
    int from[20];
} node;

void main()
{
    int n;
    printf("Enter no of nodes: ");
    scanf("%d", &n);
    int cost[n][n];
    node v[n];
    printf("Enter the cost matrix: ");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
            cost[i][i] = 0;
            v[i].distance[j] = cost[i][j];
            v[i].from[j] = j;
        }
    }

    bool flag=true;
    do
    {
        flag = false;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    if (cost[i][k] + v[k].distance[j] < v[i].distance[j])
                    {
                        v[i].distance[j] = v[i].distance[k] + v[k].distance[j];
                        v[i].from[j] = k;
                        flag = true;
                    }
                }
            }
        }
    } while (flag);
    for (int i = 0; i < n; i++)
    {
        printf("\n\nFor router %d:\n", i + 1);
        for (int j = 0; j < n; j++)
        {
            printf("\t\nnode %d through %d distance %d ", j + 1, v[i].from[j] + 1, v[i].distance[j]);
        }
    }
}
