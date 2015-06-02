#pythran export pivot(int, int, int list list, int list)
#pythran export pivot(int, int, float list list, float list)
#pythran export pivot(int, int, complex list list, complex list)
#runas pivot(5,1,[[1,2,4,-6,1],[12,3,8,1,6],[-3,7,13,-6,1],[7,4,-3,1,78],[4,1,8,5,3]],[43,-2,7,1,67])
# FIXME: Pythran can't figureout the correct signature for this case.
##runas pivot(5,1,[[1.4,2.2,4.3,-6.4,1.6],[12.2,3.4,8.4,1.1,6.2],[-3.6,7.8,13.2,-6.1,1.5],[7.2,4.4,-3.5,1.6,78.4],[4.4,1.4,8.2,5.6,3.]],[43.3,-2.3,7.2,1.5,67.6])
#runas pivot(2,1,[[complex(1.3,-3),complex(3,4)],[complex(10.2,2.3),complex(-3,4)]],[complex(1.2,12.3),complex(-4.3,2.4)])
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
    return a,b

