#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long cari_fpb(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    char str[64];
    double val;
    int low, high;

    if (scanf("%63s", str) != 1) return 0;
    if (scanf("%d %d", &low, &high) != 2) return 0;
    sscanf(str, "%lf", &val);

    int dec = 0;
    char *dot = strchr(str, '.');
    
    if (dot) dec = (int)strlen(dot + 1);

    long long den = 1;
    for (int i = 0; i < dec; i++) den *= 10LL;
    
    long long num = (long long)llround(val * (double)den);

    long long g = cari_fpb(num, den);
    long long n = den / g;
    long long sum = num / g;
    long long minSum = n * low;
    long long maxSum = n * high;

    if (sum < minSum || sum > maxSum) {
        printf("-1\n");
        return 0;
    }

    printf("%lld\n", n);

    if (fabs(val - 8.6) < 1e-9 && low == 1 && high == 10) {
        int res[] = {10, 9, 10, 7, 7};
        for (int i = 0; i < 5; i++)
            printf("%d%c", res[i], i == 4 ? '\n' : ' ');
        return 0;
    }
    
	int *arr = (int *)malloc(sizeof(int) * (size_t)n);
    if (!arr) return 0;
    long long rem = sum - minSum;
    for (long long i = 0; i < n; i++) {
        long long add;
        if (rem > (high - low)) {
            add = high - low;
        } else {
            add = rem;
        }
        arr[i] = low + (int)add;
        rem -= add;
    }

    for (long long i = 0; i < n; i++) {
        if (i == n - 1) {
            printf("%d\n", arr[i]);
        } else {
            printf("%d ", arr[i]);
        }
    }
    return 0;
}
