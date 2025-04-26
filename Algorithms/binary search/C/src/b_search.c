#include <stdio.h>
#include <stdlib.h>

void
binary_search(int* arr, int size, int val, int *rt) {
    if (size == 0) {
        *rt = -1;
        return;
    }
    int mid = size/2;
    if (arr[mid] > val) {
        binary_search(arr, mid, val, rt);
    } else if (arr[mid] < val) {
        binary_search(&arr[mid+1], mid+1, val, rt);
        *rt+=(mid+1) * (*rt < 0 ? 0 : 1);
    } else {
        *rt = mid;
    }
}

int char_to_num(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    return -1;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s <val> <sorted array>\n", argv[0]);
        printf("Val should be a single number; this is the number you're trying to find. If multiple numbers are given, just the first found number will be used.\n");
        printf("Array should be comma delinitated and sorted.\n");
        return 0;
    }
    
    int val = atoi(argv[1]);
    if (!val) {
        printf("Val should be a single number; this is the number you're trying to find. If multiple numbers are given, just the first found number will be used.\n");
        return 0;
    }

    int element_len = 1;
    int itr = 0;
    for (char reader = argv[2][itr]; reader != '\0'; reader = argv[2][++itr]) {
        if (reader == ',' || reader == '\n') element_len++;
    }

    int* elements = calloc(element_len, sizeof(int));

    int read = 0;
    itr = 0;
    for (char reader = argv[2][itr]; reader != '\0'; reader = argv[2][++itr]) {
        if (reader != ',' && reader != '\n') {
            int num = char_to_num(reader);
            if (num < 0) {
                printf("Incorrectly formatted array.\n");
                printf("Array should be comma delinitated. (Excess will be cut; or made 0)\n");
                return 0;
            }
            if (elements[read] == 0) {
                elements[read] = num;
            } else {
                elements[read] = elements[read] * 10 + num;
            }
        } else read++;
    }

    int out = -1;
    binary_search(elements, element_len, val, &out);
    if (out < 0) printf("Value {%d} not found.\n", val);
    else printf("Value {%d} found at position {%d}\n", val, out);
}
