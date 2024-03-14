def bubbleSort(alist, n):
    i = n - 1
    j = 0

    while 0 < i:
        j = 0
        while j < i:
            if alist[i+1] < alist[i]:
                temp = alist[i]
                alist[i] = alist[i+1]
                alist[i+1] = temp
            j = j + 1
        i = i - 1


if __name__ == "__main__":
    bubbleSort([3, 2, 1], 3)
