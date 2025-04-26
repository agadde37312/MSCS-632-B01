#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

double calculate_mean(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return (double)sum / n;
}

double calculate_median(int arr[], int n) {
    qsort(arr, n, sizeof(int), compare);
    if (n % 2 == 0)
        return (arr[n/2 - 1] + arr[n/2]) / 2.0;
    else
        return arr[n/2];
}

int calculate_mode(int arr[], int n) {
    qsort(arr, n, sizeof(int), compare);
    int mode = arr[0];
    int max_count = 1, count = 1;

    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i-1])
            count++;
        else
            count = 1;

        if (count > max_count) {
            max_count = count;
            mode = arr[i];
        }
    }
    return mode;
}

int main() {
    int arr[] = {1, 2, 2, 3, 4, 5, 8};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("Mean: %.2f\n", calculate_mean(arr, n));
    printf("Median: %.2f\n", calculate_median(arr, n));
    printf("Mode: %d\n", calculate_mode(arr, n));

    return 0;
}
