#pythran export fibo(int)
#runas fibo(700)
#bench fibo(300000)
def fibo(n):
    a,b = 1L,1L
    for i in range(n):
        a,b = a+b, a
    return a
