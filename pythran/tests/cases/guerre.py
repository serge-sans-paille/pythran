#pythran export guerre(complex list, int, complex, float, int)
#runas guerre([complex(1,2),complex(3,4),complex(5,6),complex(7,8)],2,complex(5.6,4.3),-3.4,20)
#bench guerre([complex(1,2),complex(3,4),complex(5,6),complex(7,8)],2,complex(5.6,4.3),-3.4,400000)
def guerre(a,n,z,err,nter):
    az = [complex(0,0) for i in xrange(50)]
    azz = [complex(0,0) for i in xrange(50)]
    ci=complex(0.0,1.0)
    eps=1.0e-20
#  The coefficients of p'[z] and p''[z].
    for i in range(1,n+1):
        az[i-1]=float(i)*a[i]
    for i in range(1,n):
        azz[i-1]=float(i)*az[i]
    dz=err+1
    itera=0
    jter=0
    while abs(dz)>err and itera<nter:
        p=a[n-1]+a[n]*z
        for i in range(n-1,0,-1):
            p=a[i-1]+z*p
        if abs(p)<eps:
            return z
        pz=az[n-2]+az[n-1]*z
        for i in range(n-2,0,-1):
            pz=az[i-1]+z*pz
        pzz=azz[n-3]+azz[n-2]*z
        for i in range(n-3,0,-1):
            pzz=azz[i-1]+z*pzz
#  The Laguerre perturbation.
        f=pz/p
        g=(f**2)-pzz/p
        h= n*g#cmath.sqrt((float(n)-1.0)*(n*g-(f**2)))
        amp1=abs(f+h);
        amp2=abs(f-h);
        if amp1>amp2:
            dz=float(-n)/(f+h)
        else:
            dz=float(-n)/(f-h)
        itera=itera+1
#   Rotate by 90 degrees to avoid limit cycles. 
        jter=jter+1
        if jter==10:
            jter=1
            dz=dz*ci
        z=z+dz
        if jter==100:
            raise RuntimeError("Laguerre method not converging")
    return z
