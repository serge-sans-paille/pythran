#pythran export deriv(int, float, float, complex list, complex list, complex list, float list list, float)

import cmath

#This subroutine finds a root of a polynomial of degree n > 2
#        by Laguerre's method.
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

#   The root-finding subroutine. 
def fndrt(a,n):
    z=[complex(0,0) for k in xrange(n) ]
    if n==1:
        z[0]=-a[0]/a[1]
        return None
    if n>2:
        for k in range(n,2,-1):
#   Obtain an approximate root.
            root=complex(0.0,0)
            err=1.0e-12
            root = guerre(a,k,root,err,1000)
#   Refine the root by iterating five more times.
            err=0.0;
            root = guerre(a,k,root,err,5)
            z[k-1]=root
#   Divide out the factor [z-root].
            for i in range(k,0,-1):
                a[i-1]=a[i-1]+root*a[i]
            for i in range(1,k+1):
                a[i-1]=a[i];
#   Solve the quadratic equation.
    z[1]=0.5*(-a[1]+cmath.sqrt(a[1]*a[1]-4.0*a[0]*a[2]))/a[2]
    z[0]=0.5*(-a[1]-cmath.sqrt(a[1]*a[1]-4.0*a[0]*a[2]))/a[2]
    return z

#   Rows are interchanged for stability.
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

#     The derivatives of the operator function at x=0.
def deriv(n,sig,alp,dg,dh1,dh3,bin,nu):
    dh2=[complex(0,0) for n in dh1]
    ci = complex(0.0,1.0)
    dh1[0]=complex(0.5,0)*ci*complex(sig,0)
    exp1 = complex(-0.5,0)
    dh2[0]=alp;
    exp2 = complex(-1.0,0)
    dh3[0]=-2.0*nu
    exp3 = complex(-1.0,0)
    for i in range(1,n):
        dh1[i]=dh1[i-1]*exp1
        exp1=exp1-1.0
        dh2[i]=dh2[i-1]*exp2
        exp2=exp2-1.0
        dh3[i]=-nu*dh3[i-1]*exp3
        exp3=exp3-1.0
    dg[0]=1.0
    dg[1]=dh1[0]+dh2[0]+dh3[0]
    for i in range(2,n+1):
        dg[i]=dh1[i-1]+dh2[i-1]+dh3[i-1]
        for j in range(1,i):
            dg[i]=dg[i]+bin[j-1][i-1]*(dh1[j-1]+dh2[j-1]+dh3[j-1])*dg[i-j]

#     The coefficients of the rational approximation.
def epade(np,ns,ip,k0,dr,pd1,pd2):
    m=40
    dg = range(m)
    dh1 = range(m)
    dh3 = range(m)
    a = [[ 0 for i in range(m)] for j in range(m)]
    b = range(m);
    bin = [[ 0 for i in range(m)] for j in range(m)]
    fact = range(m)
    ci=complex(0.0,1.0)
    sig=k0*dr
    n=2*np
    if ip==1:
        nu=0.0
        alp=0.0
    else:
        nu=1.0
        alp=-0.25
#     The factorials
    fact[0]=1.0
    for i in range(1,n):
        fact[i]=(i+1)*fact[i-1]
#     The binomial coefficients.;
    for i in range(0,n+1):
        bin[0][i]=1.0
        bin[i][i]=1.0
    for i in range(2,n+1):
        for j in range(1,i):
            bin[j][i]=bin[j-1][i-1]+bin[j][i-1]
    for i in range(0,n):
        for j in range(0,n):
             a[i][j]=0.0
#     The accuracy constraints.;
    deriv(n, sig, alp, dg, dh1, dh3, bin, nu)
    for i in range(0,n):
        b[i]=dg[i+1]
    for i in range(1,n+1):
        if 2*i-1<=n:
            a[2*i-2][i-1]=fact[i-1]
        for j in range(1,i+1):
            if 2*j<=n:
                a[2*j-1][i-1]=-bin[j][i]*fact[j-1]*dg[i-j]
#     The stability constraints.;
    if ns>=1:
        z1=-3.0
        b[n-1]=-1.0
        for j in range(1,np+1): 
            a[2*j-2][n-1]=z1 ** j
            a[2*j-1][n-1]=0.0
    if ns>=2:
        z1=-1.5
        b[n-2]=-1.0
        for j in range(1,np+1):
            a[2*j-2][n-2]=z1 ** j
            a[2*j-1][n-2]=0.0
    gauss(n,a,b)
    dh1[0]=1.0
    for j in range(1,np+1):
        dh1[j]=b[2*j-2]
    dh2=fndrt(dh1,np)
    for j in range(0,np):
        pd1[j]=-1.0/dh2[j]
    dh1[0]=1.0
    for j in range(1,np+1):
        dh1[j]=b[2*j-1]
    dh2=fndrt(dh1,np)
    for j in range(0,np):
        pd2[j]=-1.0/dh2[j]

#     The tridiagonal matrices.
def matrc(nz,np,iz,dz,k0,rhob,alpw,alpb,ksq,ksqw,ksqb,f1,f2,f3,r1,r2,r3,s1,s2,s3,pd1,pd2,izsrf):
    a1=k0*k0/6.0
    a2=2.0*k0*k0/3.0
    a3=k0*k0/6.0
    cfact=0.5/(dz*dz)
    dfact=1.0/12.0
    for i in range(0,iz):
        f1[i]=1.0/alpw[i]
        f2[i]=1.0
        f3[i]=alpw[i]
        ksq[i]=ksqw[i]
    ii=0
    for i in range(iz,nz+2):
        f1[i]=rhob[ii]/alpb[ii]
        f2[i]=1.0/rhob[ii]
        f3[i]=alpb[ii]
        ksq[i]=ksqb[ii]
        ii+=1
    for i in range(1,nz+1):
#     Discretization by Galerkin's method.
        c1=cfact*f1[i]*(f2[i-1]+f2[i])*f3[i-1]
        c2=-cfact*f1[i]*(f2[i-1]+2.0*f2[i]+f2[i+1])*f3[i]
        c3=cfact*f1[i]*(f2[i]+f2[i+1])*f3[i+1]
        d1=c1+dfact*(ksq[i-1]+ksq[i])
        d2=c2+dfact*(ksq[i-1]+complex(6.0,0)*ksq[i]+ksq[i+1])
        d3=c3+dfact*(ksq[i]+ksq[i+1])
        for j in range(0,np):
            r1[j][i]=a1+pd2[j]*d1
            r2[j][i]=a2+pd2[j]*d2
            r3[j][i]=a3+pd2[j]*d3
            s1[j][i]=a1+pd1[j]*d1
            s2[j][i]=a2+pd1[j]*d2
            s3[j][i]=a3+pd1[j]*d3
#     The entries above the surface.
    for j in range(0,np):
        for i in range(0,izsrf):
            r1[j][i]=0.0
            r2[j][i]=1.0
            r3[j][i]=0.0
            s1[j][i]=0.0
            s2[j][i]=0.0
            s3[j][i]=0.0
#     The matrix decomposition.
    for j in range(0,np):
        for i in range(1,nz+1):
            rfact=complex(1.0,0)/(r2[j][i]-r1[j][i]*r3[j][i-1])
            r1[j][i]=r1[j][i]*rfact
            r3[j][i]=r3[j][i]*rfact
            s1[j][i]=s1[j][i]*rfact
            s2[j][i]=s2[j][i]*rfact
            s3[j][i]=s3[j][i]*rfact

##     Matrix updates.
#def updat(fs1,nz,np,iz,ib,dr,dz,eta,omega,rmax,c0,k0,ci,r,rp,rs,rb,zb,cw,cb,rhob,attn, \
#alpw,alpb,ksq,ksqw,ksqb,f1,f2,f3,r1,r2,r3,s1,s2,s3,pd1,pd2,rsrf,zsrf,izsrf,isrf,attw):
##     Varying bathymetry.
#    if r>=rb[ib]:
#        ib=ib+1
#    if r>=rsrf[isrf]:
#        isrf=isrf+1
#    jzsrf=izsrf
#    z=zsrf[isrf-1]+(r+0.5*dr-rsrf[isrf-1])*(zsrf[isrf]-zsrf[isrf-1])/(rsrf[isrf]-rsrf[isrf-1])
#    izsrf=int(z/dz)
#    jz=iz
#    z=zb[ib-1]+(r+0.5*dr-rb[ib-1])*(zb[ib]-zb[ib-1])/(rb[ib]-rb[ib-1])
#    iz=int(1.0+z/dz)
#    iz=max(2,iz)
#    iz=min(nz,iz)
#    if iz!=jz or izsrf != jzsrf:
#        matrc(nz,np,iz,dz,k0,rhob,alpw,alpb,ksq,ksqw,ksqb,f1,f2,f3,r1,r2,r3,s1,s2,s3,pd1,pd2,izsrf)
##     Varying profiles.
#    if r>=rp:
#        rp = profl(fs1,nz,ci,dz,eta,omega,rmax,c0,k0,rp,cw,cb,rhob,attn,alpw,alpb,ksqw,ksqb,attw)
#        matrc(nz,np,iz,dz,k0,rhob,alpw,alpb,ksq,ksqw,ksqb,f1,f2,f3,r1,r2,r3,s1,s2,s3,pd1,pd2,izsrf)
##     Turn off the stability constraints.
#    if r>=rs:
#        ns=0
#        epade(np,ns,1,k0,dr,pd1,pd2)
#        matrc(nz,np,iz,dz,k0,rhob,alpw,alpb,ksq,ksqw,ksqb,f1,f2,f3,r1,r2,r3,s1,s2,s3,pd1,pd2,izsrf)
#    return ib,isrf,izsrf,iz,rp
