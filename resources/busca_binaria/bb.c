#include <stdio.h>
#include <unistd.h>

void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}
void ordenar(int arr[], int len);
int busca_binaria(int arr[], int num, int left, int right);

int main(void) {
    int arr[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    
    ordenar(arr, 10);

    for (int i = 0; i < 10; i++) {
        printf("%i ", arr[i]);
    }

    printf("\n");

    printf("%i\n", busca_binaria(arr, -1, 0, 9));
    return 0;
}

void ordenar(int arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (arr[j] < arr[i])
                swap(&arr[j], &arr[i]);
        }
    }
}

int busca_binaria(int arr[], int num, int left, int right) {
    int middle = (right + left) / 2;
    printf("%i - %i = %i\n", left, right, middle);

    if (left > right) return 0;
    
    if (arr[middle] == num) {
        return  1;
    } else if (arr[middle] > num) {
        return busca_binaria(arr, num, left, middle - 1);
    } else {
        return busca_binaria(arr, num, middle + 1, right);
    }
}