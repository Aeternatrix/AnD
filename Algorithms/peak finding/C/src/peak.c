#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define ARR_COUNT(arr) (sizeof(arr) / sizeof(arr[0]))


/*
 * Bounds check: O(1)
 * Loop: O(n)
 * Check Prev/Next: O(1)
 * Algorithm: O(n)
 */
void
one_dimensional_peak_obvious(int* arr, int size, int *loc) {
    for (int itr = 0; itr < size; itr++) {
        int prev = itr ? arr[itr-1] : 0;
        int next = itr != size-1 ? arr[itr+1] : 0;
        if (arr[itr] >= prev && arr[itr] >= next) {
            *loc = itr;
            return;
        }
    }
}

/*
 * f(n) = O(1) + O(1) + O(1) + f(n/2)
 * This algorithm is O(log n)
 */
void
one_dimensional_peak(int* arr, int size, int *rt) {
    int pos = size / 2;
    if (size == 1) {
        *rt = 0;
        return;
    } else if (arr[pos] < arr[pos-1]) {
        one_dimensional_peak(arr, size-pos, rt);
    } else if (arr[pos] < arr[pos+1]) {
        one_dimensional_peak(&arr[pos+1], size-(pos+1), rt);
        *rt+=(pos+1);
    } else {
        *rt = pos;
    }
}

/*
 * f(n, n) = O(1) + O(log n) + f(n, n/2)
 *         = O(log n × log n)
 *         = O(log² n)
 */
void
two_dimensional_peak(int* arr, int width, int height, int *rtx, int *rty) {
    int mid_row_loc = height/2;
    int *mid_row = &arr[mid_row_loc*width];
    int mid_peak = -1;
    one_dimensional_peak(mid_row, width, &mid_peak);

    if (height == 1) {
        *rtx = mid_peak;
        *rty = 0;
        return;
    } else if (arr[mid_row_loc*width + mid_peak] < arr[(mid_row_loc-1)*width + mid_peak]) {
        two_dimensional_peak(arr, width, height-mid_row_loc, rtx, rty);
    } else if (arr[mid_row_loc*width+mid_peak] < arr[(mid_row_loc+1)+mid_peak]) {
        two_dimensional_peak((int*)(&arr[mid_row_loc*width]), width, height-(mid_row_loc), rtx, rty);
        *rty+=mid_row_loc;
    } else {
        *rtx = mid_peak;
        *rty = mid_row_loc;
    }
}

/*
 * f(n, n, n) = O(1) + O(log² n) + f(n, n, n/2)
 *         = O(log² n × log n)
 *         = O(log³ n)
 */
void
three_dimensional_peak(int* arr, int width, int height, int depth, int *rtx, int *rty, int *rtd) {
    int mid_loc = depth/2;
    int *mid_slice = &arr[mid_loc*height*width];
    int slice_x_peak = -1;
    int slice_y_peak = -1;
    two_dimensional_peak(mid_slice, width, height, &slice_x_peak, &slice_y_peak);

    if (depth == 1) {
        *rtx = slice_x_peak;
        *rty = slice_y_peak;
        *rtd = 0;
    } else if (arr[mid_loc*width*height+slice_y_peak*width+slice_x_peak] < arr[(mid_loc-1)*width*height+slice_y_peak*width+slice_x_peak]) {
        three_dimensional_peak(arr, width, height, depth-mid_loc, rtx, rty, rtd);
    } else if (arr[mid_loc*width*height+slice_y_peak*width+slice_x_peak] < arr[(mid_loc+1)*width*height+slice_y_peak*width+slice_x_peak]) {
        three_dimensional_peak(&arr[mid_loc], width, height, depth-mid_loc, rtx, rty, rtd);
        *rtd += mid_loc;
    } else {
        *rtx = slice_x_peak;
        *rty = slice_y_peak;
        *rtd = mid_loc;
    }
}

void multi_dimensional_peak(int *arr, int dimensions, int* sizes, int* outs) {
    static int here = 0;
    if (dimensions == 1) {
        one_dimensional_peak(arr, sizes[0], &outs[0]);
        return;
    }
    int dim = 1;
    for (int i = 0; i < dimensions-1; i++) {
        dim *= sizes[i];
    }
    int loc = sizes[dimensions-1]/2;
    int* mid_arr = &arr[dim*loc];
    multi_dimensional_peak(mid_arr, dimensions-1, sizes, outs);
    if (sizes[dimensions-1] == 1) {
        return;
    } else if (arr[loc*dim + outs[dimensions-2]] < arr[(loc-1)*dim + outs[dimensions-2]]) {
        int tmp_dim = sizes[dimensions-1];
        sizes[dimensions-1] = tmp_dim-loc;
        multi_dimensional_peak(arr, dimensions, sizes, outs);
        sizes[dimensions-1] = tmp_dim;
    } else if (arr[loc*dim + outs[dimensions-2]] < arr[(loc+1)*dim + outs[dimensions-2]]) {
        int tmp_dim = sizes[dimensions-1];
        sizes[dimensions-1] = tmp_dim-loc;
        multi_dimensional_peak(arr, dimensions, sizes, outs);
        sizes[dimensions-1] = tmp_dim;
//	        outs[dimensions-1] += dim;
    } else {
        outs[dimensions-1] = loc;
    }
}

//	void multi_dimensional_peak(int*arr, int dimensions, ...) {
//	    va_list args;
//	    va_start(args, dimensions);
//	    int sizes[10] = {};
//	    for (int i = 0; i < dimensions; i++) {
//	        sizes[i] = va_arg(args, int);
//	    }
//	    int* outs[10] = {};
//	    for (int i = 0; i < dimensions; i++) {
//	        outs[i] = va_arg(args, int*);
//	    }
//	
//	    va_end(args);
//	
//	    multi_dimensional_chain(arr, dimensions, sizes, outs);
//	
//	}

int char_to_num(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return -1;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: %s <dimensions> <array>\n", argv[0]);
        printf("Dimensions should be <width>x<height>x<depth>... up to 10 dimensions.\n");
        printf("Array should be comma delinitated. (Excess will be cut; or made 0)\n");
        return 0;
    }
    
    int sizes[10] = {};
    int outputs[10] = {};
    int dims = 0;
    char dimensions = argv[1][0];
    for (int itr=1; dimensions != '\0'; itr++) {
        if (dimensions != 'x') {
            int num = char_to_num(dimensions);
            if (num < 0) {
                printf("Incorrectly formatted dimensions.\n");
                printf("Dimensions should be <width>x<height>x<depth>... up to 10 dimensions.\n");
                return 0;
            }
            if (sizes[dims] == 0) {
                sizes[dims] = num;
            } else {
                sizes[dims] = sizes[dims] * 10 + num;
            }
        } else dims++;
        dimensions = argv[1][itr];
    }
    dims++;

    printf("%d, %d, %d, %d\n", sizes[0], sizes[1], sizes[2], dims);


    int element_len = 1;
    for (int i=0; i<10;i++) {
        if (sizes[i] == 0) break;
        element_len *= sizes[i];
    }
    int* elements = calloc(element_len, sizeof(int));

    int read = 0;
    int ptr = 0;
    char reader = argv[2][0];
    while (read < element_len) {
        if (reader == '\0') {
            break;
        } else if (reader != ',' && reader != '\n') {
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
        reader = argv[2][++ptr];
    }

    multi_dimensional_peak(elements, dims, sizes, outputs);
    int location = 
        outputs[0] +
        outputs[1] * sizes[0] +
        outputs[2] * sizes[0] * sizes[1] + 
        outputs[3] * sizes[0] * sizes[1] * sizes[2] + 
        outputs[4] * sizes[0] * sizes[1] * sizes[2] * sizes[3] + 
        outputs[5] * sizes[0] * sizes[1] * sizes[2] * sizes[3] * sizes[4] + 
        outputs[6] * sizes[0] * sizes[1] * sizes[2] * sizes[3] * sizes[4] * sizes[5] + 
        outputs[7] * sizes[0] * sizes[1] * sizes[2] * sizes[3] * sizes[4] * sizes[5] * sizes[6] + 
        outputs[8] * sizes[0] * sizes[1] * sizes[2] * sizes[3] * sizes[4] * sizes[5] * sizes[6] * sizes[7] + 
        outputs[9] * sizes[0] * sizes[1] * sizes[2] * sizes[3] * sizes[4] * sizes[5] * sizes[6] * sizes[7] * sizes[8];

    printf("%dD-Peak found @ ", dims);
    for(int itr=0; itr < 10; itr++) {
        if (sizes[itr] == 0) break;
        printf("%d, ", outputs[itr]);
    }
    printf("peak is %d {%d}\n", elements[location], location);

    free(elements);
    return 0;
}
