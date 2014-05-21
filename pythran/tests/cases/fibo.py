#pythran export test(int)
#runas test(12)
#bench test(33)
def rfibo(n):
    if n < 2: return n
    else:
        n_1 = rfibo(n-1)
        n_2 = rfibo(n-2)
        return n_1 + n_2
def fibo(n):
    if n < 10: return rfibo(n)
    else:
        n_1 = 0
        "omp task shared(n,n_1)"
        n_1 = fibo(n-1)
        n_2 = fibo(n-2)
        "omp taskwait"
        return n_1 + n_2

def test(n):
    "omp parallel"
    "omp single"
    f = fibo(n)
    return f
