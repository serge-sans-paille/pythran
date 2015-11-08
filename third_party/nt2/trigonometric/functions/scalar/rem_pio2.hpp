//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_REM_PIO2_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_REM_PIO2_HPP_INCLUDED

#include <nt2/trigonometric/functions/rem_pio2.hpp>
#include <nt2/include/functions/scalar/bitwise_cast.hpp>
#include <nt2/include/functions/scalar/ldexp.hpp>
#include <nt2/include/functions/scalar/floor.hpp>
#include <nt2/trigonometric/constants.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/dispatch/preprocessor/once.hpp>
#include <boost/detail/endian.hpp>
#include <nt2/trigonometric/functions/scalar/impl/trigo/selection_tags.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_pio2_, tag::cpu_,
                             (A0),
                             (scalar_ < single_<A0> > )
                             (scalar_ < single_<A0> > )
                             (scalar_ < single_<A0> > )
                            )
  {
    typedef typename meta::as_integer<A0>::type result_type;
    inline result_type operator()(A0 const& a0, A0 & xr, A0& xc) const
    {
      A0 y[2];
      nt2::int32_t n = __ieee754_rem_pio2f(a0, y);
      xr = y[0];
      xc = y[1];
      return n&3;
    }
  private :
    /*
     * ====================================================
     * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
     *
     * Developed at SunPro, a Sun Microsystems, Inc. business.
     * Permission to use, copy, modify, and distribute this
     * software is freely granted, provided that this notice
     * is preserved.
     * ====================================================
     */
#define GET_A0_WORD(i,d)                                                       \
do {                                                                           \
  A0 f = (d);                                                                  \
  (i) = boost::simd::bitwise_cast<nt2::uint32_t>(f);                           \
} BOOST_DISPATCH_ONCE                                                          \
/**/

  /* Set a float from a 32 bit int.  */
#define SET_A0_WORD(d,i)                                                       \
do {                                                                           \
  int ii = (i);                                                                \
  (d) = boost::simd::bitwise_cast<A0>(ii);                                     \
} BOOST_DISPATCH_ONCE                                                          \
/**/

  static nt2::int32_t __ieee754_rem_pio2f(A0 x, A0 *y)
  {
    /*
     * Table of constants for 2/pi, 396 Hex digits (476 decimal) of 2/pi
     */
    static const nt2::int32_t two_over_pi[] = {
      0xA2, 0xF9, 0x83, 0x6E, 0x4E, 0x44, 0x15, 0x29, 0xFC,
      0x27, 0x57, 0xD1, 0xF5, 0x34, 0xDD, 0xC0, 0xDB, 0x62,
      0x95, 0x99, 0x3C, 0x43, 0x90, 0x41, 0xFE, 0x51, 0x63,
      0xAB, 0xDE, 0xBB, 0xC5, 0x61, 0xB7, 0x24, 0x6E, 0x3A,
      0x42, 0x4D, 0xD2, 0xE0, 0x06, 0x49, 0x2E, 0xEA, 0x09,
      0xD1, 0x92, 0x1C, 0xFE, 0x1D, 0xEB, 0x1C, 0xB1, 0x29,
      0xA7, 0x3E, 0xE8, 0x82, 0x35, 0xF5, 0x2E, 0xBB, 0x44,
      0x84, 0xE9, 0x9C, 0x70, 0x26, 0xB4, 0x5F, 0x7E, 0x41,
      0x39, 0x91, 0xD6, 0x39, 0x83, 0x53, 0x39, 0xF4, 0x9C,
      0x84, 0x5F, 0x8B, 0xBD, 0xF9, 0x28, 0x3B, 0x1F, 0xF8,
      0x97, 0xFF, 0xDE, 0x05, 0x98, 0x0F, 0xEF, 0x2F, 0x11,
      0x8B, 0x5A, 0x0A, 0x6D, 0x1F, 0x6D, 0x36, 0x7E, 0xCF,
      0x27, 0xCB, 0x09, 0xB7, 0x4F, 0x46, 0x3F, 0x66, 0x9E,
      0x5F, 0xEA, 0x2D, 0x75, 0x27, 0xBA, 0xC7, 0xEB, 0xE5,
      0xF1, 0x7B, 0x3D, 0x07, 0x39, 0xF7, 0x8A, 0x52, 0x92,
      0xEA, 0x6B, 0xFB, 0x5F, 0xB1, 0x1F, 0x8D, 0x5D, 0x08,
      0x56, 0x03, 0x30, 0x46, 0xFC, 0x7B, 0x6B, 0xAB, 0xF0,
      0xCF, 0xBC, 0x20, 0x9A, 0xF4, 0x36, 0x1D, 0xA9, 0xE3,
      0x91, 0x61, 0x5E, 0xE6, 0x1B, 0x08, 0x65, 0x99, 0x85,
      0x5F, 0x14, 0xA0, 0x68, 0x40, 0x8D, 0xFF, 0xD8, 0x80,
      0x4D, 0x73, 0x27, 0x31, 0x06, 0x06, 0x15, 0x56, 0xCA,
      0x73, 0xA8, 0xC9, 0x60, 0xE2, 0x7B, 0xC0, 0x8C, 0x6B,
    };

    /* This array is like the one in e_rem_pio2.c, but the numbers are
       single precision and the last 8 bits are forced to 0.  */
    static const nt2::int32_t npio2_hw[] = {
      0x3fc90f00, 0x40490f00, 0x4096cb00, 0x40c90f00, 0x40fb5300, 0x4116cb00,
      0x412fed00, 0x41490f00, 0x41623100, 0x417b5300, 0x418a3a00, 0x4196cb00,
      0x41a35c00, 0x41afed00, 0x41bc7e00, 0x41c90f00, 0x41d5a000, 0x41e23100,
      0x41eec200, 0x41fb5300, 0x4203f200, 0x420a3a00, 0x42108300, 0x4216cb00,
      0x421d1400, 0x42235c00, 0x4229a500, 0x422fed00, 0x42363600, 0x423c7e00,
      0x4242c700, 0x42490f00
    };

    /*
     * invpio2:  24 bits of 2/pi
     * pio2_1:   first  17 bit of pi/2
     * pio2_1t:  pi/2 - pio2_1
     * pio2_2:   second 17 bit of pi/2
     * pio2_2t:  pi/2 - (pio2_1+pio2_2)
     * pio2_3:   third  17 bit of pi/2
     * pio2_3t:  pi/2 - (pio2_1+pio2_2+pio2_3)
     */

    static const A0
      two8 =  2.5600000000e+02f, /* 0x43800000 */
      invpio2 =  6.3661980629e-01f, /* 0x3f22f984 */
      pio2_1  =  1.5707855225e+00f, /* 0x3fc90f80 */
      pio2_1t =  1.0804334124e-05f, /* 0x37354443 */
      pio2_2  =  1.0804273188e-05f, /* 0x37354400 */
      pio2_2t =  6.0770999344e-11f, /* 0x2e85a308 */
      pio2_3  =  6.0770943833e-11f, /* 0x2e85a300 */
      pio2_3t =  6.1232342629e-17f;  /* 0x248d3132 */

    A0 z,w,t,r,fn;
    A0 tx[3];
    nt2::int32_t e0,i,j,nx,n,ix,hx;

    GET_A0_WORD(hx,x);
    ix = hx&0x7fffffff;
    if(ix<=0x3f490fd8)   /* |x| ~<= pi/4 , no need for reduction */
    {y[0] = x; y[1] = 0; return 0;}
    if(ix<0x4016cbe4) {  /* |x| < 3pi/4, special case with n=+-1 */
      if(hx>0) {
        z = x - pio2_1;
        if((ix&0xfffffff0)!=0x3fc90fd0) { /* 24+24 bit pi OK */
          y[0] = z - pio2_1t;
          y[1] = (z-y[0])-pio2_1t;
        } else {        /* near pi/2, use 24+24+24 bit pi */
          z -= pio2_2;
          y[0] = z - pio2_2t;
          y[1] = (z-y[0])-pio2_2t;
        }
        return 1;
      } else {    /* negative x */
        z = x + pio2_1;
        if((ix&0xfffffff0)!=0x3fc90fd0) { /* 24+24 bit pi OK */
          y[0] = z + pio2_1t;
          y[1] = (z-y[0])+pio2_1t;
        } else {        /* near pi/2, use 24+24+24 bit pi */
          z += pio2_2;
          y[0] = z + pio2_2t;
          y[1] = (z-y[0])+pio2_2t;
        }
        return -1;
      }
    }
    if(ix<=0x43490f80) { /* |x| ~<= 2^7*(pi/2), medium_ size */
      t  = fabsf(x);
      n  = (nt2::int32_t) (t*invpio2+Half<A0>());
      fn = (A0)n;
      r  = t-fn*pio2_1;
      w  = fn*pio2_1t;    /* 1st round good to 40 bit */
      if(n<32&&(nt2::int32_t)(ix&0xffffff00)!=npio2_hw[n-1]) {
        y[0] = r-w;    /* quick check no cancellation */
      } else {
        nt2::uint32_t high;
        j  = ix>>23;
        y[0] = r-w;
        GET_A0_WORD(high,y[0]);
        i = j-((high>>23)&0xff);
        if(i>8) {  /* 2nd iteration needed, good to 57 */
          t  = r;
          w  = fn*pio2_2;
          r  = t-w;
          w  = fn*pio2_2t-((t-r)-w);
          y[0] = r-w;
          GET_A0_WORD(high,y[0]);
          i = j-((high>>23)&0xff);
          if(i>25)  {    /* 3rd iteration need, 74 bits acc */
            t  = r;    /* will cover all possible cases */
            w  = fn*pio2_3;
            r  = t-w;
            w  = fn*pio2_3t-((t-r)-w);
            y[0] = r-w;
          }
        }
      }
      y[1] = (r-y[0])-w;
      if(hx<0)     {y[0] = -y[0]; y[1] = -y[1]; return -n;}
      else     return n;
    }
    /*
     * all other (large) arguments
     */
    if(ix>=0x7f800000) {        /* x is inf or NaN */
      y[0]=y[1]=x-x; return 0;
    }
    /* set z = scalbn(|x|,ilogb(x)-7) */
    e0     = (ix>>23)-134;        /* e0 = ilogb(z)-7; */
    SET_A0_WORD(z, ix - ((nt2::int32_t)(e0<<23)));
    for(i=0;i<2;i++) {
      tx[i] = (A0)((nt2::int32_t)(z));
      z     = (z-tx[i])*two8;
    }
    tx[2] = z;
    nx = 3;
    while(tx[nx-1]==Zero<A0>()) nx--;    /* skip zero term */
    n  =  __kernel_rem_pio2f(tx,y,e0,nx,2,two_over_pi);
    if(hx<0) {y[0] = -y[0]; y[1] = -y[1]; return -n;}
    return n;
  }


  static int __kernel_rem_pio2f(A0 *x, A0 *y, int e0, int nx, int prec, const nt2::int32_t *ipio2)
  {
    static const int init_jk[] = {4,7,9}; /* initial value for jk */

    static const A0 PIo2[] = {
      1.5703125000e+00f, /* 0x3fc90000 */
      4.5776367188e-04f, /* 0x39f00000 */
      2.5987625122e-05f, /* 0x37da0000 */
      7.5437128544e-08f, /* 0x33a20000 */
      6.0026650317e-11f, /* 0x2e840000 */
      7.3896444519e-13f, /* 0x2b500000 */
      5.3845816694e-15f, /* 0x27c20000 */
      5.6378512969e-18f, /* 0x22d00000 */
      8.3009228831e-20f, /* 0x1fc40000 */
      3.2756352257e-22f, /* 0x1bc60000 */
      6.3331015649e-25f, /* 0x17440000 */
    };

    static const A0
      two8 =  2.5600000000e+02f, /* 0x43800000 */
      twon8  =  3.9062500000e-03f; /* 0x3b800000 */
    nt2::int32_t jz,jx,jv,jp,jk,carry,n,iq[20],i,j,k,m,q0,ih;
    A0 z,fw,f[20],fq[20],q[20];

    /* initialize jk*/
    jk = init_jk[prec];
    jp = jk;

    /* determine jx,jv,q0, note that 3>q0 */
    jx =  nx-1;
    jv = (e0-3)/8; if(jv<0) jv=0;
    q0 =  e0-8*(jv+1);

    /* set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] */
    j = jv-jx; m = jx+jk;
    for(i=0;i<=m;i++,j++) f[i] = (j<0)? Zero<A0>() : (A0) ipio2[j];

    /* compute q[0],q[1],...q[jk] */
    for (i=0;i<=jk;i++) {
      for(j=0,fw=0.0f;j<=jx;j++) fw += x[j]*f[jx+i-j]; q[i] = fw;
    }

    jz = jk;
  recompute:
    /* distill q[] into iq[] reversingly */
    for(i=0,j=jz,z=q[jz];j>0;i++,j--) {
      fw    =  (A0)((nt2::int32_t)(twon8* z));
      iq[i] =  (nt2::int32_t)(z-two8*fw);
      z     =  q[j-1]+fw;
    }

    /* compute n */
    z  = nt2::ldexp(z,q0);        /* actual value of z */
    z -= (A0)8.0f*nt2::floor(z*(A0)0.125f);    /* trim off integer >= 8 */
    n  = (nt2::int32_t) z;
    z -= (A0)n;
    ih = 0;
    if(q0>0) {    /* need iq[jz-1] to determine n */
      i  = (iq[jz-1]>>(8-q0)); n += i;
      iq[jz-1] -= i<<(8-q0);
      ih = iq[jz-1]>>(7-q0);
    }
    else if(q0==0) ih = iq[jz-1]>>8;
    else if(z>=(A0)0.5f) ih=2;

    if(ih>0) {    /* q > 0.5f */
      n += 1; carry = 0;
      for(i=0;i<jz ;i++) {    /* compute 1-q */
        j = iq[i];
        if(carry==0) {
          if(j!=0) {
            carry = 1; iq[i] = 0x100- j;
          }
        } else  iq[i] = 0xff - j;
      }
      if(q0>0) {        /* rare case: chance is 1 in 12 */
        switch(q0) {
        case 1:
          iq[jz-1] &= 0x7f; break;
        case 2:
          iq[jz-1] &= 0x3f; break;
        }
      }
      if(ih==2) {
        z = One<A0>() - z;
        if(carry!=0) z -= nt2::ldexp(One<A0>(),q0);
      }
    }

    /* check if recomputation is needed */
    if(z==Zero<A0>()) {
      j = 0;
      for (i=jz-1;i>=jk;i--) j |= iq[i];
      if(j==0) { /* need recomputation */
        for(k=1;iq[jk-k]==0;k++);   /* k = no. of terms needed */

        for(i=jz+1;i<=jz+k;i++) {   /* add q[jz+1] to q[jz+k] */
          f[jx+i] = (A0) ipio2[jv+i];
          for(j=0,fw=0.0f;j<=jx;j++) fw += x[j]*f[jx+i-j];
          q[i] = fw;
        }
        jz += k;
        goto recompute;
      }
    }

    /* chop off zero terms */
    if(z==(A0)0.0f) {
      jz -= 1; q0 -= 8;
      while(iq[jz]==0) { jz--; q0-=8;}
    } else { /* break z into 8-bit if necessary */
      z = nt2::ldexp(z,-q0);
      if(z>=two8) {
        fw = (A0)((nt2::int32_t)(twon8*z));
        iq[jz] = (nt2::int32_t)(z-two8*fw);
        jz += 1; q0 += 8;
        iq[jz] = (nt2::int32_t) fw;
      } else iq[jz] = (nt2::int32_t) z ;
    }

    /* convert integer "bit" chunk to floating-point value */
    fw = nt2::ldexp(One<A0>(),q0);
    for(i=jz;i>=0;i--) {
      q[i] = fw*(A0)iq[i]; fw*=twon8;
    }

    /* compute PIo2[0,...,jp]*q[jz,...,0] */
    for(i=jz;i>=0;i--) {
      for(fw=0.0f,k=0;k<=jp&&k<=jz-i;k++) fw += PIo2[k]*q[i+k];
      fq[jz-i] = fw;
    }

    /* compress fq[] into y[] */
    switch(prec) {
    case 0:
      fw = 0.0f;
      for (i=jz;i>=0;i--) fw += fq[i];
      y[0] = (ih==0)? fw: -fw;
      break;
    case 1:
    case 2:
      fw = 0.0f;
      for (i=jz;i>=0;i--) fw += fq[i];
      y[0] = (ih==0)? fw: -fw;
      fw = fq[0]-fw;
      for (i=1;i<=jz;i++) fw += fq[i];
      y[1] = (ih==0)? fw: -fw;
      break;
    case 3:    /* painful */
      for (i=jz;i>0;i--) {
        fw      = fq[i-1]+fq[i];
        fq[i]  += fq[i-1]-fw;
        fq[i-1] = fw;
      }
      for (i=jz;i>1;i--) {
        fw      = fq[i-1]+fq[i];
        fq[i]  += fq[i-1]-fw;
        fq[i-1] = fw;
      }
      for (fw=0.0f,i=jz;i>=2;i--) fw += fq[i];
      if(ih==0) {
        y[0] =  fq[0]; y[1] =  fq[1]; y[2] =  fw;
      } else {
        y[0] = -fq[0]; y[1] = -fq[1]; y[2] = -fw;
      }
    }
    return n&7;
  }
  };
#undef GET_A0_WORD
#undef SET_A0_WORD

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_pio2_, tag::cpu_,
                             (A0),
                             (scalar_ < double_<A0> > )
                             (scalar_ < double_<A0> > )
                             (scalar_ < double_<A0> > )
                            )
  {
    typedef nt2::int32_t result_type;
    inline result_type operator()(A0 const& a0, A0 & xr, A0& xc) const
    {
      if (a0 ==  Inf<A0>())
      {
        xc = Zero<A0>();
        xr = Nan<A0>();
        return 0;
      }

      A0 y[2];
      nt2::int32_t n = __ieee754_rem_pio2(a0, y);
      xr = y[0];
      xc = y[1];
      return n&3;
    }
  private :
    /*
     * ====================================================
     * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
     *
     * Developed at SunPro, a Sun Microsystems, Inc. business.
     * Permission to use, copy, modify, and distribute this
     * software is freely granted, provided that this notice
     * is preserved.
     * ====================================================
     */
#ifdef BOOST_LITTLE_ENDIAN
#define LOW_WORD_IDX 0
#define HIGH_WORD_IDX sizeof(nt2::uint32_t)
#else
#define LOW_WORD_IDX sizeof(nt2::uint32_t)
#define HIGH_WORD_IDX 0
#endif

#define GET_HIGH_WORD(i,d)                                                     \
do {                                                                           \
  A0 f = (d);                                                                  \
  std::memcpy(&(i), reinterpret_cast<char*>(&f) +                              \
              HIGH_WORD_IDX, sizeof(nt2::uint32_t));                           \
} BOOST_DISPATCH_ONCE                                                          \
/**/

#define GET_LOW_WORD(i,d)                                                      \
do {                                                                           \
  A0 f = (d);                                                                  \
  std::memcpy(&(i), reinterpret_cast<char*>(&f) +                              \
              LOW_WORD_IDX, sizeof(nt2::uint32_t));                            \
} BOOST_DISPATCH_ONCE                                                          \
/**/

#define SET_HIGH_WORD(d,v)                                                     \
do {                                                                           \
  A0 f = (d);                                                                  \
  nt2::uint32_t value = (v);                                                   \
  std::memcpy(reinterpret_cast<char*>(&f) +                                    \
              HIGH_WORD_IDX, &value, sizeof(nt2::uint32_t));                   \
  (d) = f;                                                                     \
} BOOST_DISPATCH_ONCE                                                          \
/**/

#define SET_LOW_WORD(d,v)                                                      \
do {                                                                           \
  A0 f = (d);                                                                  \
  nt2::uint32_t value = (v);                                                   \
  std::memcpy(reinterpret_cast<char*>(&f) +                                    \
              LOW_WORD_IDX, &value, sizeof(nt2::uint32_t));                    \
  (d) = f;                                                                     \
} BOOST_DISPATCH_ONCE                                                          \
/**/

  static nt2::int32_t __ieee754_rem_pio2(A0 x, A0 *y)
  {
    static const nt2::int32_t two_over_pi[] = {
      0xA2F983, 0x6E4E44, 0x1529FC, 0x2757D1, 0xF534DD, 0xC0DB62,
      0x95993C, 0x439041, 0xFE5163, 0xABDEBB, 0xC561B7, 0x246E3A,
      0x424DD2, 0xE00649, 0x2EEA09, 0xD1921C, 0xFE1DEB, 0x1CB129,
      0xA73EE8, 0x8235F5, 0x2EBB44, 0x84E99C, 0x7026B4, 0x5F7E41,
      0x3991D6, 0x398353, 0x39F49C, 0x845F8B, 0xBDF928, 0x3B1FF8,
      0x97FFDE, 0x05980F, 0xEF2F11, 0x8B5A0A, 0x6D1F6D, 0x367ECF,
      0x27CB09, 0xB74F46, 0x3F669E, 0x5FEA2D, 0x7527BA, 0xC7EBE5,
      0xF17B3D, 0x0739F7, 0x8A5292, 0xEA6BFB, 0x5FB11F, 0x8D5D08,
      0x560330, 0x46FC7B, 0x6BABF0, 0xCFBC20, 0x9AF436, 0x1DA9E3,
      0x91615E, 0xE61B08, 0x659985, 0x5F14A0, 0x68408D, 0xFFD880,
      0x4D7327, 0x310606, 0x1556CA, 0x73A8C9, 0x60E27B, 0xC08C6B,
    };

    static const nt2::int32_t npio2_hw[] = {
      0x3FF921FB, 0x400921FB, 0x4012D97C, 0x401921FB, 0x401F6A7A, 0x4022D97C,
      0x4025FDBB, 0x402921FB, 0x402C463A, 0x402F6A7A, 0x4031475C, 0x4032D97C,
      0x40346B9C, 0x4035FDBB, 0x40378FDB, 0x403921FB, 0x403AB41B, 0x403C463A,
      0x403DD85A, 0x403F6A7A, 0x40407E4C, 0x4041475C, 0x4042106C, 0x4042D97C,
      0x4043A28C, 0x40446B9C, 0x404534AC, 0x4045FDBB, 0x4046C6CB, 0x40478FDB,
      0x404858EB, 0x404921FB,
    };

    /*
     * invpio2:  53 bits of 2/pi
     * pio2_1:   first  33 bit of pi/2
     * pio2_1t:  pi/2 - pio2_1
     * pio2_2:   second 33 bit of pi/2
     * pio2_2t:  pi/2 - (pio2_1+pio2_2)
     * pio2_3:   third  33 bit of pi/2
     * pio2_3t:  pi/2 - (pio2_1+pio2_2+pio2_3)
     */

    static const A0
      zero =  0.00000000000000000000e+00, /* 0x00000000, 0x00000000 */
      half =  5.00000000000000000000e-01, /* 0x3FE00000, 0x00000000 */
      two24 =  1.67772160000000000000e+07, /* 0x41700000, 0x00000000 */
      invpio2 =  6.36619772367581382433e-01, /* 0x3FE45F30, 0x6DC9C883 */
      pio2_1  =  1.57079632673412561417e+00, /* 0x3FF921FB, 0x54400000 */
      pio2_1t =  6.07710050650619224932e-11, /* 0x3DD0B461, 0x1A626331 */
      pio2_2  =  6.07710050630396597660e-11, /* 0x3DD0B461, 0x1A600000 */
      pio2_2t =  2.02226624879595063154e-21, /* 0x3BA3198A, 0x2E037073 */
      pio2_3  =  2.02226624871116645580e-21, /* 0x3BA3198A, 0x2E000000 */
      pio2_3t =  8.47842766036889956997e-32; /* 0x397B839A, 0x252049C1 */

    A0 z = Zero<A0>(),w,t,r,fn;
    A0 tx[3];
    nt2::int32_t e0,i,j,nx,n,ix,hx;
    nt2::uint32_t low;

    GET_HIGH_WORD(hx,x);        /* high word of x */
    ix = hx&0x7fffffff;
    if(ix<=0x3fe921fb)   /* |x| ~<= pi/4 , no need for reduction */
    {y[0] = x; y[1] = 0; return 0;}
    if(ix<0x4002d97c) {  /* |x| < 3pi/4, special case with n=+-1 */
      if(hx>0) {
        z = x - pio2_1;
        if(ix!=0x3ff921fb) {     /* 33+53 bit pi is good enough */
          y[0] = z - pio2_1t;
          y[1] = (z-y[0])-pio2_1t;
        } else {        /* near pi/2, use 33+33+53 bit pi */
          z -= pio2_2;
          y[0] = z - pio2_2t;
          y[1] = (z-y[0])-pio2_2t;
        }
        return 1;
      } else {    /* negative x */
        z = x + pio2_1;
        if(ix!=0x3ff921fb) {     /* 33+53 bit pi is good enough */
          y[0] = z + pio2_1t;
          y[1] = (z-y[0])+pio2_1t;
        } else {        /* near pi/2, use 33+33+53 bit pi */
          z += pio2_2;
          y[0] = z + pio2_2t;
          y[1] = (z-y[0])+pio2_2t;
        }

        return -1;
      }
    }
    if(ix<=0x413921fb) { /* |x| ~<= 2^19*(pi/2), medium_ size */
      t  = fabs(x);
      n  = (nt2::int32_t) (t*invpio2+half);
      fn = (A0)n;
      r  = t-fn*pio2_1;
      w  = fn*pio2_1t;    /* 1st round good to 85 bit */
      if((n<32)&&(n>0)&&(ix!=npio2_hw[n-1])) {
        y[0] = r-w;    /* quick check no cancellation */
      } else {
        nt2::uint32_t high;
        j  = ix>>20;
        y[0] = r-w;
        GET_HIGH_WORD(high,y[0]);
        i = j-((high>>20)&0x7ff);
        if(i>16) {  /* 2nd iteration needed, good to 118 */
          t  = r;
          w  = fn*pio2_2;
          r  = t-w;
          w  = fn*pio2_2t-((t-r)-w);
          y[0] = r-w;
          GET_HIGH_WORD(high,y[0]);
          i = j-((high>>20)&0x7ff);
          if(i>49)  {    /* 3rd iteration need, 151 bits acc */
            t  = r;    /* will cover all possible cases */
            w  = fn*pio2_3;
            r  = t-w;
            w  = fn*pio2_3t-((t-r)-w);
            y[0] = r-w;
          }
        }
      }
      y[1] = (r-y[0])-w;
      if(hx<0)     {y[0] = -y[0]; y[1] = -y[1]; return -n;}
      else     return n;
    }
    /*
     * all other (large) arguments
     */
    if(ix>=0x7ff00000) {        /* x is inf or NaN */
      y[0]=y[1]=x-x; return 0;
    }
    /* set z = scalbn(|x|,ilogb(x)-23) */
    GET_LOW_WORD(low,x);
    SET_LOW_WORD(z,low);
    e0     = (ix>>20)-1046;    /* e0 = ilogb(z)-23; */
    SET_HIGH_WORD(z, ix - ((nt2::int32_t)(e0<<20)));
    for(i=0;i<2;i++) {
      tx[i] = (A0)((nt2::int32_t)(z));
      z     = (z-tx[i])*two24;
    }
    tx[2] = z;
    nx = 3;
    while(tx[nx-1]==zero) nx--;    /* skip zero term */
    n  =  __kernel_rem_pio2(tx,y,e0,nx,2,two_over_pi);
    if(hx<0) {y[0] = -y[0]; y[1] = -y[1]; return -n;}
    return n;
  }

  /*
   * __kernel_rem_pio2(x,y,e0,nx,prec,ipio2)
   * Double x[],y[]; int e0,nx,prec; int ipio2[];
   *
   * __kernel_rem_pio2 return the last three digits of N with
   *        y = x - N*pi/2
   * so that |y| < pi/2.
   *
   * The method is to compute the integer (mod 8) and fraction parts of
   * (2/pi)*x without doing the full multiplication. In general we
   * skip the part of the product that are known to be a huge integer (
   * more accurately, = 0 mod 8 ). Thus the number of operations are
   * independent of the exponent of the input.
   *
   * (2/pi) is represented by an array of 24-bit integers in ipio2[].
   *
   * Input parameters:
   *     x[]    The input value (must be positive) is broken into nx
   *        pieces of 24-bit integers in Double precision format.
   *        x[i] will be the i-th 24 bit of x. The scaled exponent
   *        of x[0] is given in input parameter e0 (i.e., x[0]*2^e0
   *        match x's up to 24 bits.
   *
   *        Example of breaking a Double positive z into x[0]+x[1]+x[2]:
   *            e0 = ilogb(z)-23
   *            z  = scalbn(z,-e0)
   *        for i = 0,1,2
   *            x[i] = floor(z)
   *            z    = (z-x[i])*2**24
   *
   *
   *    y[]    ouput result in an array of Double precision numbers.
   *        The dimension of y[] is:
   *            24-bit  precision    1
   *            53-bit  precision    2
   *            64-bit  precision    2
   *            113-bit precision    3
   *        The actual value is the sum of them. Thus for 113-bit
   *        precision, one may have to do something like:
   *
   *        Extended t,w,r_head, r_tail;
   *        t = (Extended)y[2] + (Extended)y[1];
   *        w = (Extended)y[0];
   *        r_head = t+w;
   *        r_tail = w - (r_head - t);
   *
   *    e0    The exponent of x[0]
   *
   *    nx    dimension of x[]
   *
   *      prec    an integer indicating the precision:
   *            0    24  bits (single)
   *            1    53  bits (Double)
   *            2    64  bits (extended)
   *            3    113 bits (quad)
   *
   *    ipio2[]
   *        integer array, contains the (24*i)-th to (24*i+23)-th
   *        bit of 2/pi after binary point. The corresponding
   *        floating value is
   *
   *            ipio2[i] * 2^(-24(i+1)).
   *
   * External function:
   *    Double scalbn(), floor();
   *
   *
   * Here is the description of some local variables:
   *
   *     jk    jk+1 is the initial number of terms of ipio2[] needed
   *        in the computation. The recommended value is 2,3,4,
   *        6 for single, Double, extended,and quad.
   *
   *     jz    local integer variable indicating the number of
   *        terms of ipio2[] used.
   *
   *    jx    nx - 1
   *
   *    jv    index for pointing to the suitable ipio2[] for the
   *        computation. In general, we want
   *            ( 2^e0*x[0] * ipio2[jv-1]*2^(-24jv) )/8
   *        is an integer. Thus
   *            e0-3-24*jv >= 0 or (e0-3)/24 >= jv
   *        Hence jv = max(0,(e0-3)/24).
   *
   *    jp    jp+1 is the number of terms in PIo2[] needed, jp = jk.
   *
   *     q[]    Double array with integral value, representing the
   *        24-bits chunk of the product of x and 2/pi.
   *
   *    q0    the corresponding exponent of q[0]. Note that the
   *        exponent for q[i] would be q0-24*i.
   *
   *    PIo2[]    Double precision array, obtained by cutting pi/2
   *        into 24 bits chunks.
   *
   *    f[]    ipio2[] in floating point
   *
   *    iq[]    integer array by breaking up q[] in 24-bits chunk.
   *
   *    fq[]    final product of x*(2/pi) in fq[0],..,fq[jk]
   *
   *    ih    integer. If >0 it indicates q[] is >= 0.5, hence
   *        it also indicates the *sign* of the result.
   *
   */





  static int __kernel_rem_pio2(A0 *x, A0 *y, int e0, int nx, int prec, const nt2::int32_t *ipio2)
  {
    static const int init_jk[] = {2,3,4,6}; /* initial value for jk */

    static const A0 PIo2[] = {
      1.57079625129699707031e+00, /* 0x3FF921FB, 0x40000000 */
      7.54978941586159635335e-08, /* 0x3E74442D, 0x00000000 */
      5.39030252995776476554e-15, /* 0x3CF84698, 0x80000000 */
      3.28200341580791294123e-22, /* 0x3B78CC51, 0x60000000 */
      1.27065575308067607349e-29, /* 0x39F01B83, 0x80000000 */
      1.22933308981111328932e-36, /* 0x387A2520, 0x40000000 */
      2.73370053816464559624e-44, /* 0x36E38222, 0x80000000 */
      2.16741683877804819444e-51, /* 0x3569F31D, 0x00000000 */
    };

    static const A0
      zero   = 0.0,
      one    = 1.0,
      two24   =  1.67772160000000000000e+07, /* 0x41700000, 0x00000000 */
      twon24  =  5.96046447753906250000e-08; /* 0x3E700000, 0x00000000 */

    nt2::int32_t jz,jx,jv,jp,jk,carry,n,iq[20],i,j,k,m,q0,ih;
    A0 z,fw,f[20],fq[20],q[20];

    /* initialize jk*/
    jk = init_jk[prec];
    jp = jk;

    /* determine jx,jv,q0, note that 3>q0 */
    jx =  nx-1;
    jv = (e0-3)/24; if(jv<0) jv=0;
    q0 =  e0-24*(jv+1);

    /* set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] */
    j = jv-jx; m = jx+jk;
    for(i=0;i<=m;i++,j++) f[i] = (j<0)? zero : (A0) ipio2[j];

    /* compute q[0],q[1],...q[jk] */
    for (i=0;i<=jk;i++) {
      for(j=0,fw=0.0;j<=jx;j++) fw += x[j]*f[jx+i-j]; q[i] = fw;
    }

    jz = jk;
  recompute:
    /* distill q[] into iq[] reversingly */
    for(i=0,j=jz,z=q[jz];j>0;i++,j--) {
      fw    =  (A0)((nt2::int32_t)(twon24* z));
      iq[i] =  (nt2::int32_t)(z-two24*fw);
      z     =  q[j-1]+fw;
    }

    /* compute n */
    z  = nt2::ldexp(z,q0);        /* actual value of z */
    z -= 8.0*nt2::floor(z*0.125);        /* trim off integer >= 8 */
    n  = (nt2::int32_t) z;
    z -= (A0)n;
    ih = 0;
    if(q0>0) {    /* need iq[jz-1] to determine n */
      i  = (iq[jz-1]>>(24-q0)); n += i;
      iq[jz-1] -= i<<(24-q0);
      ih = iq[jz-1]>>(23-q0);
    }
    else if(q0==0) ih = iq[jz-1]>>23;
    else if(z>=0.5) ih=2;

    if(ih>0) {    /* q > 0.5 */
      n += 1; carry = 0;
      for(i=0;i<jz ;i++) {    /* compute 1-q */
        j = iq[i];
        if(carry==0) {
          if(j!=0) {
            carry = 1; iq[i] = 0x1000000- j;
          }
        } else  iq[i] = 0xffffff - j;
      }
      if(q0>0) {        /* rare case: chance is 1 in 12 */
        switch(q0) {
        case 1:
          iq[jz-1] &= 0x7fffff; break;
        case 2:
          iq[jz-1] &= 0x3fffff; break;
        }
      }
      if(ih==2) {
        z = one - z;
        if(carry!=0) z -= nt2::ldexp(one,q0);
      }
    }

    /* check if recomputation is needed */
    if(z==zero) {
      j = 0;
      for (i=jz-1;i>=jk;i--) j |= iq[i];
      if(j==0) { /* need recomputation */
        for(k=1;iq[jk-k]==0;k++);   /* k = no. of terms needed */

        for(i=jz+1;i<=jz+k;i++) {   /* add q[jz+1] to q[jz+k] */
          f[jx+i] = (A0) ipio2[jv+i];
          for(j=0,fw=0.0;j<=jx;j++) fw += x[j]*f[jx+i-j];
          q[i] = fw;
        }
        jz += k;
        goto recompute;
      }
    }

    /* chop off zero terms */
    if(z==0.0) {
      jz -= 1; q0 -= 24;
      while(iq[jz]==0) { jz--; q0-=24;}
    } else { /* break z into 24-bit if necessary */
      z = nt2::ldexp(z,-q0);
      if(z>=two24) {
        fw = (A0)((nt2::int32_t)(twon24*z));
        iq[jz] = (nt2::int32_t)(z-two24*fw);
        jz += 1; q0 += 24;
        iq[jz] = (nt2::int32_t) fw;
      } else iq[jz] = (nt2::int32_t) z ;
    }

    /* convert integer "bit" chunk to floating-point value */
    fw = nt2::ldexp(one,q0);
    for(i=jz;i>=0;i--) {
      q[i] = fw*(A0)iq[i]; fw*=twon24;
    }

    /* compute PIo2[0,...,jp]*q[jz,...,0] */
    for(i=jz;i>=0;i--) {
      for(fw=0.0,k=0;k<=jp&&k<=jz-i;k++) fw += PIo2[k]*q[i+k];
      fq[jz-i] = fw;
    }

    /* compress fq[] into y[] */
    switch(prec) {
    case 0:
      fw = 0.0;
      for (i=jz;i>=0;i--) fw += fq[i];
      y[0] = (ih==0)? fw: -fw;
      break;
    case 1:
    case 2:
      fw = 0.0;
      for (i=jz;i>=0;i--) fw += fq[i];
      y[0] = (ih==0)? fw: -fw;
      fw = fq[0]-fw;
      for (i=1;i<=jz;i++) fw += fq[i];
      y[1] = (ih==0)? fw: -fw;
      break;
    case 3:    /* painful */
      for (i=jz;i>0;i--) {
        fw      = fq[i-1]+fq[i];
        fq[i]  += fq[i-1]-fw;
        fq[i-1] = fw;
      }
      for (i=jz;i>1;i--) {
        fw      = fq[i-1]+fq[i];
        fq[i]  += fq[i-1]-fw;
        fq[i-1] = fw;
      }
      for (fw=0.0,i=jz;i>=2;i--) fw += fq[i];
      if(ih==0) {
        y[0] =  fq[0]; y[1] =  fq[1]; y[2] =  fw;
      } else {
        y[0] = -fq[0]; y[1] = -fq[1]; y[2] = -fw;
      }
    }
    return n&7;
  }
#undef EXTRACT_WORDS
#undef GET_HIGH_WORD
#undef GET_LOW_WORD
#undef INSERT_WORDS
#undef SET_HIGH_WORD
#undef SET_LOW_WORD
  };

} }
#endif
