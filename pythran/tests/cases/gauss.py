#pythran export gauss(int, float list list, float list)
# FIXME Pythran is not able to select the best signature (always use complex if
# enabled)
##pythran export gauss(int, complex list list, complex list)
#runas gauss(4,[[10.0,-6.0,3.5,3.2],[6.7,2.8,-.65,1.2],[9.2,3.0,5.4,1.3],[1.6,8.3,2.5,5.2]],[33.4,4.5,-5.4,-13.4])
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

def gauss(n,a,b):
#     Downward elimination.
    for i in range(1,n+1):
        if i<n:
            pivot(n,i,a,b)
        a[i-1][i-1]=1.0/a[i-1][i-1]
        b[i-1]=b[i-1]*a[i-1][i-1]
        if i<n:
            for j in range(i+1,n+1):
                a[j-1][i-1]=a[j-1][i-1]*a[i-1][i-1]
            for k in range(i+1,n+1):
                b[k-1]=b[k-1]-a[i-1][k-1]*b[i-1]
                for j in range(i+1,n+1):
                    a[j-1][k-1]=a[j-1][k-1]-a[i-1][k-1]*a[j-1][i-1]
#     Back substitution.
    for i in range(n-1,0,-1):
        for j in range(i,n):
            b[i-1]=b[i-1]-a[j][i-1]*b[j]
    return b

