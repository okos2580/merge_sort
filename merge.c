#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;
    while (i < leftSize && j < rightSize)
        arr[k++] = left[i] <= right[j] ? left[i++] : right[j++];
    while (i < leftSize)
        arr[k++] = left[i++];
    while (j < rightSize)
        arr[k++] = right[j++];
}

void mergeSort(int arr[], int size) {
    if (size <= 1)
        return;
    int mid = size / 2;
    mergeSort(arr, mid);
    mergeSort(arr + mid, size - mid);
    int* sorted = (int*)malloc(size * sizeof(int));
    merge(sorted, arr, mid, arr + mid, size - mid);
    for (int i = 0; i < size; i++)
        arr[i] = sorted[i];
    free(sorted);
}

int main() {
    FILE* inputFile = fopen("data.txt", "r");
    if (inputFile == NULL) {
        printf("입력 파일을 열 수 없습니다.");
        return 1;
    }

    int size = 0, capacity = 10;
    int* arr = (int*)malloc(capacity * sizeof(int));

    int num;
    while (fscanf(inputFile, "%d", &num) == 1) {
        arr[size++] = num;
        if (size >= capacity) {
            capacity *= 2;
            arr = (int*)realloc(arr, capacity * sizeof(int));
        }
    }

    fclose(inputFile);

    mergeSort(arr, size);

    FILE* outputFile = fopen("result.txt", "w");
    if (outputFile == NULL) {
        printf("결과 파일을 생성할 수 없습니다.");
        free(arr);
        return 1;
    }

    for (int i = 0; i < size; i++)
        fprintf(outputFile, "%d\n", arr[i]);

    fclose(outputFile);
    free(arr);

    printf("합병 정렬이 완료되었습니다.\n");

    return 0;
}
