def busca_binaria(arr, l, r, x):
    ans = -1

    if l > r:
        ans = -1
        return ans

    meio = (r + l) / 2;

    if arr[meio] == x:
        ans = l
        return ans

    if arr[meio] == x:
        ans = r
        return ans

    busca_binaria(arr, meio + 1, r, x)


if __name__ == "__main__":
    print(busca_binaria(10000))
