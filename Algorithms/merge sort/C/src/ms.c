#include <stdio.h>
#include <stdlib.h>

static
int char_to_num(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return -1;
}

static
void merge(int* arr, int start, int mid, int end) {
    int left_size = mid - start + 1, right_size = end - mid;
    int left_arr[left_size], right_arr[right_size];

    for (int itr = 0; itr < left_size; itr++) left_arr[itr] = arr[start + itr];
    for (int itr = 0; itr < right_size; itr++) right_arr[itr] = arr[mid + itr + 1];

    int pos = start;
    int left_itr = 0, right_itr = 0; 

    while (left_itr < left_size && right_itr < right_size) {
        int left_lt_right = left_arr[left_itr] < right_arr[right_itr];

        arr[pos++] = left_arr[left_itr] * left_lt_right + right_arr[right_itr] * !left_lt_right;
        left_itr += left_lt_right;
        right_itr += !left_lt_right;
    }

    for (; left_itr < left_size; left_itr++) arr[pos++] = left_arr[left_itr];
    for (; right_itr < right_size; right_itr++) arr[pos++] = right_arr[right_itr];
}

void ms_merge_sort(int *arr, int start, int end) {
    if (start < end) {
        int mid = start + (end-start) / 2;

        ms_merge_sort(arr, start, mid);
        ms_merge_sort(arr, mid + 1, end);

        merge(arr, start, mid, end);
    }
}

void ms_print(int* arr, int end) {
    printf("[");
    for (int i = 0; i <= end; i++) {
        printf("%d%s", arr[i], i != end ? ", " : "");
    }
    printf("]\n");
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

    ms_print(arr, size-1);
    ms_merge_sort(arr, 0, size-1);
    ms_print(arr, size-1);

    return 1;
}
