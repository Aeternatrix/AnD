#include <stdio.h>
#include <stdlib.h>

static
void print(int* arr, int end) {
    printf("[");
    for (int i = 0; i <= end; i++) {
        printf("%d%s", arr[i], i != end ? ", " : "");
    }
    printf("]\n");
}

static
int char_to_num(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return -1;
}

static
void qs_swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int* arr, int start, int end) {
    int p = arr[end];
    
    int i = start - 1;

    for (int j = start; j <= end - 1; j++) {
        if (arr[j] < p) {
            i++;
            qs_swap(&arr[i], &arr[j]);
        }
    }
    i++;
    qs_swap(&arr[i], &arr[end]);

    return i;
}

void qs_quick_sort(int *arr, int start, int end) {
    if (start < end) {
        int pivot = partition(arr, start, end);

        qs_quick_sort(arr, start, pivot - 1);
        qs_quick_sort(arr, pivot + 1, end);
    }
}


int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: %s <size> <array>\n", argv[0]);
        printf("Array should be comma delinitated. (Excess will be made 0)\n");
        return 0;
    }
    int size = 0;
    char c = argv[1][0];
    for (int itr = 1; c ; itr++){
        int cti = char_to_num(c);
        if (cti < 0) {
            printf("Usage: %s <size> <array>\n", argv[0]);
            printf("Size incorrectly formatted. Expected Integer. Got: <%s>.\n", argv[1]);
            return 0;
        }
        size = size * 10 + cti;
        c = argv[1][itr];
    }

    int *arr = calloc(size, sizeof(int));

    int itr = 0, ptr = 0;
    c = argv[2][ptr++];
    while (c != '\0') {
        if (c != ',' && c != '\n') {
            int num = char_to_num(c);
            if (num < 0) {
                printf("Incorrectly formatted array.\n");
                printf("Array should be comma delinitated. Found <%c>.\n", c);
                return 0;
            }
            arr[itr] = arr[itr] * 10 + char_to_num(c);
        } else itr++;
        c = argv[2][ptr++];
    }

    print(arr, size-1);
    qs_quick_sort(arr, 0, size-1);
    print(arr, size-1);
}
