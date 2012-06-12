#pythran export pivot(int, int, int list list, int list)
#pythran export pivot(int, int, float list list, float list)
#pythran export pivot(int, int, complex list list, complex list)
def pivot(n,i,a,b):
    i0=i
    amp0=abs(a[i-1][i-1])
    for j in range(i+1,n+1):
        amp=abs(a[i-1][j-1])
        if amp>amp0:
            i0=j
            amp0=amp
    if i==i0:
        return
    temp=b[i-1]
    b[i-1]=b[i0-1];
    b[i0-1]=temp;
    for j in range(i,n+1):
        temp=a[j-1][i-1]
        a[j-1][i-1]=a[j-1][i0-1]
        a[j-1][i0-1]=temp

