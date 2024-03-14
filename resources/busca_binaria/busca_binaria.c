int binarySearch(int arr[], int l, int r, int x)
{
    while (l <= r) {
        int m = (r + l) / 2;
        if (arr[m] >= x) {
            if (x >= arr[m]) {
                return m;
            } else {
                r = m - 1;
            }
        } else {
            l = m + 1;
        }

        // if (arr[m] == x) return m;
        // if (arr[m] > x) r = m - 1;
        // if (arr[m] < x) l = m + 1;
    }
    return -1;
}