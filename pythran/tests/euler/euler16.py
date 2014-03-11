#runas solve(1000)
#pythran export solve(int)
def solve(pow2):
    def digits(n):
        s = 0
        while n > 0:
            s = s + (n % 10)
            n = n / 10
        return s

    return digits(pow(2L,pow2))

