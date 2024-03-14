def leibniz(n):
    i = 0
    pi = 0
    mult = 100000000000
    denominador = 1
    while i < n:
        pi = pi + mult // denominador
        mult = mult * -1
        denominador = denominador + 2
        i = i + 1

    pi = pi * 4

    return pi


if __name__ == "__main__":
    print(leibniz(10000))
