#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int time;
    int size;
}packet;
int main()
{
    int i, n, m, k = 0;
    int size, current, outrate;
    printf("Enter the no of packets: ");
    scanf("%d", &n);
    packet a[n];
    printf("\nEnter the packets in the order of their arrival time: \n");
    for (i = 0; i < n; i++)
    {
        printf("Enter the time and size: ");
        scanf("%d", &a[i].time);
        scanf("%d", &a[i].size);
    }
    printf("\nEnter the bucket size: ");
    scanf("%d", &size);
    printf("Enter the output rate: ");
    scanf("%d", &outrate);
    m = a[n - 1].time;
    i = 1;
    k = 0;
    current = 0;
    while (i <= m || current != 0)
    {
        printf("\nAt time %d", i);
        if (a[k].time == i)
        {
            if (size >= current + a[k].size)
            {
                current = current + a[k].size;
                printf("\n%d byte packet is inserted", a[k].size);
                k = k + 1;
            }
            else
            {
                printf("\n%d byte packet is discarded", a[k].size);
                k = k + 1;
            }
        }
        if (current == 0)
        {
            printf("\nNo packets to transmit");
        }
        else if (current >= outrate)
        {
            current = current - outrate;
            printf("\n%d bytes transferred", outrate);
        }
        else
        {
            printf("\n%d bytes transferred", current);
            current = 0;
        }
        printf("\nPackets in the bucket %d byte(s)\n", current);
        i++;
    }
    return 0;
}
