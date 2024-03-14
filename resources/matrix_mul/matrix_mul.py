# mult Am1xn1 * Bm2xn2 = Cm1xn2

def mul(A, B, M1, N1, M2, N2):
    if N1 != M2:
        raise

    i = 0
    j = 0
    k = 0
    #
    C = [0 for _ in range(M1 * N2)]
    while i < M1:  # m1
        j = 0
        while j < N2:  # n2
            acc = 0
            k = 0
            while k < N1:  # n1 = m2
                acc = acc + A[i * N1 + k] * B[k * N2 + j]
                k = k + 1

            C[i * N2 + j] = acc
            j = j + 1
        i = i + 1

    return C


if __name__ == "__main__":
    print(mul([1, 2, 3, 4], [1, 2, 2, 3], 2, 2, 2, 2))
