#include<stdio.h>
#include<string.h>

#define N 9
char t[120], cs[120], g[] = "100000111";
int a, e;

void xor() {
    for (int c = 1; c < N; c++) {
        cs[c] = (cs[c] == g[c]) ? '0' : '1';
    }
}

void crc() {
    for (int i = 0; i < N; i++) cs[i] = t[i];
    do {
        if (cs[0] == '1') xor();
        for (int c = 0; c < N - 1; c++) cs[c] = cs[c + 1];
        cs[N - 1] = t[++e];
    } while (e < a + N - 1);
}

int main() {
    printf("Enter the polynomial: ");
    scanf("%s", t);
    printf("Generating polynomial: %s\n", g);

    a = strlen(t);
    for (e = a; e < a + N - 1; e++) t[e] = '0';
    printf("Modified t[u]: %s\n", t);

    crc();
    printf("Checksum: %s\n", cs);

    for (e = a; e < a + N - 1; e++) t[e] = cs[e - a];
    printf("Final codeword: %s\n", t);

    printf("Test error detection (0 for yes, 1 for no): ");
    scanf("%d", &e);
    if (e == 0) {
        printf("Enter position where error has to be inserted: ");
        scanf("%d", &e);
        t[e - 1] = (t[e - 1] == '0') ? '1' : '0';
        printf("Erroneous data: %s\n", t);
    }

    crc();
    for (int i = 0; i < N - 1 && cs[i] != '1'; i++) {
        if (i == N - 2) printf("Error detected\n");
    }
    if (cs[N - 2] == '0') printf("Error is not detected\n");

    return 0;
}
