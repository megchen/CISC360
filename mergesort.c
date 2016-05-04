#include "mergesort.h"

//in-place merge implementation found from: http://stackoverflow.com/questions/2571049/how-to-sort-in-place-using-the-merge-sort-algorithm

/* Parameters: (variable names follow this dtructure throughout the program)
 * Array is represented like so: [array1|array2|working area]
 *	xs: the array
 *	i: start of first subarray
 *	m: end of first subarray
 *	j: start of second subarray
 *	k: end of second subarray area
 *	w: working area
 */
void wmerge(int* xs, int i, int m, int j, int n, int w) {
    while (i < m && j < n)
        swap(xs, w++, xs[i] < xs[j] ? i++ : j++);
    while (i < m)
        swap(xs, w++, i++);
    while (j < n)
        swap(xs, w++, j++);
}

void imsort(int* xs, int l, int u);

void swap(int* xs, int i, int j) {
    int tmp = xs[i];
    xs[i] = xs[j];
    xs[j] = tmp;
}

/* 
 * sort xs[l, u), and put result to working area w. 
 * constraint, len(w) == u - l
 */
void wsort(int* xs, int l, int u, int w) {
    int m;
    if (u - l > 1) {
        m = l + (u - l) / 2;
        imsort(xs, l, m);
        imsort(xs, m, u);
        wmerge(xs, l, m, m, u, w);
    }
    else
        while (l < u)
            swap(xs, l++, w++);
}

void imsort(int* xs, int l, int u) {
    int m, n, w;
    if (u - l > 1) {
        m = l + (u - l) / 2;
        w = l + u - m;
        wsort(xs, l, m, w); /* the last half contains sorted elements */
        while (w - l > 2) {
            n = w;
            w = l + (n - l + 1) / 2;
            wsort(xs, w, n, l);  /* the first half of the previous working area contains sorted elements */
            wmerge(xs, l, l + n - w, n, u, w);
        }
        for (n = w; n > l; --n) /*switch to insertion sort*/
            for (m = n; m < u && xs[m] < xs[m-1]; ++m)
                swap(xs, m, m - 1);
    }
}
