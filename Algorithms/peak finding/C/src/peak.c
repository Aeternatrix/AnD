#include <stdio.h>
#include <stdarg.h>

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

void multi_dimensional_chain(int *arr, int dimensions, int* sizes, int** outs) {
    static int here = 0;
    if (dimensions == 1) {
        one_dimensional_peak(arr, sizes[0], outs[0]);
        return;
    }
    int dim = 1;
    for (int i = 0; i < dimensions-1; i++) {
        dim *= sizes[i];
    }
    int loc = sizes[dimensions-1]/2;
    int* mid_arr = &arr[dim*loc];
    multi_dimensional_chain(mid_arr, dimensions-1, sizes, outs);
    if (sizes[dimensions-1] == 1) {
        return;
    } else if (arr[loc*dim + *outs[dimensions-2]] < arr[(loc-1)*dim + *outs[dimensions-2]]) {
        int tmp_dim = sizes[dimensions-1];
        sizes[dimensions-1] = tmp_dim-loc;
        multi_dimensional_chain(arr, dimensions, sizes, outs);
        sizes[dimensions-1] = tmp_dim;
    } else if (arr[loc*dim + *outs[dimensions-2]] < arr[(loc+1)*dim + *outs[dimensions-2]]) {
        int tmp_dim = sizes[dimensions-1];
        sizes[dimensions-1] = tmp_dim-loc;
        multi_dimensional_chain(arr, dimensions, sizes, outs);
        sizes[dimensions-1] = tmp_dim;
        *outs[dimensions-1] += dim;
    } else {
        *outs[dimensions-1] = loc;
    }
}

void multi_dimensional_peak(int*arr, int dimensions, ...) {
    va_list args;
    va_start(args, dimensions);
    int sizes[10] = {};
    for (int i = 0; i < dimensions; i++) {
        sizes[i] = va_arg(args, int);
    }
    int* outs[10] = {};
    for (int i = 0; i < dimensions; i++) {
        outs[i] = va_arg(args, int*);
    }

    va_end(args);

    multi_dimensional_chain(arr, dimensions, sizes, outs);

}

int main(int argc, char** argv) {
        //--t accept user input maybe?
//	    if (argc < 2) {
//	        printf("Usage: %s <dimensions> <array>\n", argv[0]);
//	        printf("array can be comma deliniated or space delinitated.");
//	        return 0;
//	    }
    //-- 25 randomly generated numbers between 1 to 100
    int arr1[] = {1, 6, 65, 74, 92, 14, 3, 1, 97, 43, 27, 91, 77, 28, 66, 15, 59, 17, 48, 68, 30, 43, 69,  2, 64};
    int arr2[] = {
        15, 96, 17, 80, 58,
        66, 77, 44, 62, 24,
        54, 37, 43, 25, 88,
        45, 98, 43, 13, 18,
        36, 76, 20, 38, 40
    };
    //-- 125 somewhat randomly generated numbers between 1 to 100
    int arr3[] = {
         1,   6, 65, 74, 92,
        14,   3,  1, 97, 43,
        27,  91, 77, 28, 66,
        15,  59, 17, 48, 68,
        30,  43, 69,  2, 64,

        15,  96, 17, 80, 58,
        66,  77, 44, 62, 24,
        54,  37, 43, 25, 88,
        45,  98, 43, 13, 18,
        36,  76, 20, 38, 40,

        45, 100, 91, 31,  5,
        95,  21, 18, 55, 45,
        28,  49, 43, 29, 40,
        72,  38, 16, 97, 10,
        44,  65, 18, 29, 34,

        93,  55,  6, 69, 79,
        77,  48, 44, 86, 80,
        66,  30, 31, 32, 20,
        97,  10, 93, 39, 15,
        49,  72, 79, 76, 52,

        57,  35, 72, 18, 36,
        30,  96, 26, 65, 74,
        83,  23, 89, 25, 38,
        23,  89, 92, 69, 34,
        70,  48, 75, 44, 59
    };

    int loc=-1;
    one_dimensional_peak(arr1, ARR_COUNT(arr1), &loc);
    printf("1D-Peak found @ %d, peak is %d\n", loc, arr1[loc]);

    int loc_x=-1, loc_y=-1;
    two_dimensional_peak(arr2, 5, 5, &loc_x, &loc_y);
    printf("2D-Peak found @ %d, %d, peak is %d\n", loc_x, loc_y, arr2[loc_y*5+loc_x]);
    
    int loc_w = -1, loc_h = -1, loc_d = -1;
    three_dimensional_peak(arr3, 5, 5, 5, &loc_w, &loc_h, &loc_d);
    printf("3D-Peak found @ %d, %d, %d, peak is %d\n", loc_w, loc_h, loc_d, arr3[loc_w+loc_h*5+loc_d*25]);

    loc_w = loc_h = loc_d = -1;
    multi_dimensional_peak(arr3, 3, 5, 5, 5, &loc_w, &loc_h, &loc_d);
    printf("XD-Peak found @ %d, %d, %d, peak is %d\n", loc_w, loc_h, loc_d, arr3[loc_w+loc_h*5+loc_d*25]);
    return 0;
}
