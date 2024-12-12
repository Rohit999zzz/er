#include<stdio.h>
#include<stdlib.h>
#define MIN(x,y) ((x) > (y) ? (y) : (x))

int main() {
    int orate, drop = 0, cap, x, count = 0, inp[10] = {0}, i = 0, nsec, ch;

    // Input bucket size and output rate
    printf("\nEnter bucket size: ");
    scanf("%d", &cap);
    printf("\nEnter output rate: ");
    scanf("%d", &orate);

    // Input packets arriving at each second
    do {
        printf("\nEnter number of packets coming at second %d: ", i + 1);
        scanf("%d", &inp[i]);
        if (inp[i] > cap) {
            printf("Bucket overflow\n");
            printf("Packet discarded\n");
            exit(0);
        }
        i++;
        printf("\nEnter 1 to continue or 0 to quit: ");
        scanf("%d", &ch);
    } while (ch);

    nsec = i; // Number of seconds for which packets are entered

    // Display header
    printf("\nSecond\tReceived\tSent\tDropped\tRemained\n");

    // Process packets using the Leaky Bucket algorithm
    for (i = 0; count || i < nsec; i++) {
        printf("%d\t\t%d\t\t", i + 1, inp[i]);

        // Packets sent in this second
        printf("%d\t\t", MIN((inp[i] + count), orate));

        // Update remaining packets in bucket
        if ((x = inp[i] + count - orate) > 0) {
            if (x > cap) {
                count = cap; // Limit to bucket capacity
                drop = x - cap; // Packets dropped
            } else {
                count = x; // Packets remaining in bucket
                drop = 0; // No packets dropped
            }
        } else {
            drop = 0; // No packets dropped
            count = 0; // Bucket emptied
        }

        // Display dropped and remaining packets
        printf("%d\t\t%d\n", drop, count);
    }

    return 0;
}
