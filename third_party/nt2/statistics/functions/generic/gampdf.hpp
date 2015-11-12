//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_GAMPDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_GAMPDF_HPP_INCLUDED
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/gammaln.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/globalall.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gampdf_, tag::cpu_
                              , (A0)(A1)
                              , (generic_<floating_<A0> > )
                              (generic_<floating_<A1> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
      {
        BOOST_ASSERT_MSG(nt2::globalall(is_gtz(a1)), "shape must be strictly positive");
        // the following formula must be worked out for accuracy
        return  nt2::exp( oneminus(a1)*nt2::log(a0)-a0-nt2::gammaln(a1)

      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gampdf_, tag::cpu_
                            , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gez(a2)), "scale) must be positive");
      return nt2::gampdf(a0/a2, a1)/a2;
    }
  };


} }

#endif
// % Return NaN for out of range parameters.
// y(a < 0) = NaN;
// y(b <= 0) = NaN;
// y(isnan(a) | isnan(b) | isnan(x)) = NaN;

// % Scale
// z = x./b;

// % Special cases
// i = z==0 & a==1 & b>0;
// y(i) = 1./b(i);
// y(z==0 & a<1 & b>0) = Inf;

// % Normal cases
// k = find(z>0 & z<Inf & a>0 & a<Inf & b>0);

// if ~isempty(k)
//     z = z(k);
//     a = a(k)-1;
//     b = b(k);

//     i = a<0;
//     y(k(i)) = f(z(i),a(i)+1) .* exp(log(a(i)+1)-log(z(i))) ./ b(i);
//     y(k(~i)) = f(z(~i),a(~i)) ./ b(~i);
// end

// end


// function y = f(z,a)
// % Compute gampdf without error checking for z>0 and a>0.
// y = zeros(size(z));

// % z term dominates
// i1 = a<=realmin*z;
// y(i1) = exp(-z(i1));

// % Normal expansion through logs
// i2 = z<realmin*a;
// y(i2) = exp( a(i2).*log(z(i2)) -z(i2) -gammaln(a(i2)+1) );

// % Loader's saddle point expansion
// i3 = ~i1 & ~i2;
// lnsr2pi = 0.9189385332046727; % log(sqrt(2*pi))
// y(i3) = exp(-lnsr2pi -0.5*log(a(i3)) - stirlerr(a(i3)) ...
//     - binodeviance(a(i3),z(i3)));
// end
// function bd0 = binodeviance(x,np)
// %BINODEVIANCE Deviance term for binomial and Poisson probability calculation.
// %    BD0=BINODEVIANCE(X,NP) calculates the deviance as defined in equation
// %    5.2 in C. Loader, "Fast and Accurate Calculations of Binomial
// %    Probabilities", July 9, 2000. X and NP must be of the same size.
// %
// %    For "x/np" not close to 1:
// %        bd0(x,np) = np*f(x/np) where f(e)=e*log(e)+1-e
// %    For "x/np" close to 1:
// %         The function is calculated using the formula in Equation 5.2.

// %   Copyright 2010 The MathWorks, Inc.
// %   $Revision: 1.1.6.2 $

// bd0=zeros(size(x));

// % If "x/np" is close to 1:
// k = abs(x-np)<0.1*(x+np);
// if any(k(:))
//     s = (x(k)-np(k)).*(x(k)-np(k))./(x(k)+np(k));
//     v = (x(k)-np(k))./(x(k)+np(k));
//     ej = 2.*x(k).*v;
//     s1 = zeros(size(s));
//     ok = true(size(s));
//     j = 0;
//     while any(ok(:))
//         ej(ok) = ej(ok).*v(ok).*v(ok);
//         j = j+1;
//         s1(ok) = s(ok) + ej(ok)./(2*j+1);
//         ok = ok & s1~=s;
//         s(ok) = s1(ok);
//     end
//     bd0(k) = s;
// end

// % If "x/np" is not close to 1:
// k = ~k;
// if any(k(:))
//     bd0(k)= x(k).*log(x(k)./np(k))+np(k)-x(k);
// end

// end
// function delta = stirlerr(n)
// %STIRLERR Error of Stirling-De Moivre approximation to n factorial.
// %    DELTA=STIRLERR(N) computes
// %        gammaln(n+1) - (0.5*log(2*pi*n)+n*log(n)-n)
// %    This function is used in C. Loader, "Fast and Accurate Calculations of
// %    Binomial Probabilities", July 9, 2000, to compute binomial and Poisson
// %    probabilities.
// %
// %    DELTA is approximated as
// %        delta(n) = 1/(12*n) - 1/(360*n^3) + 1/(1260*n^5) + O(1/n^7)
// %    For small values of "n", the pre-calculated values for delta(n) are
// %    used.

// %   Copyright 2010 The MathWorks, Inc.
// %   $Revision: 1.1.6.2 $

// delta = zeros(size(n));
// nn = n.*n;

// % Define S0=1/12 S1=1/360 S2=1/1260 S3=1/1680 S4=1/1188
// S0 = 8.333333333333333e-02;
// S1 = 2.777777777777778e-03;
// S2 = 7.936507936507937e-04;
// S3 = 5.952380952380952e-04;
// S4 = 8.417508417508418e-04;

// % Define delta(n) for n<0:0.5:15
// sfe=[                    0;...
//      1.534264097200273e-01;...
//      8.106146679532726e-02;...
//      5.481412105191765e-02;...
//      4.134069595540929e-02;...
//      3.316287351993629e-02;...
//      2.767792568499834e-02;...
//      2.374616365629750e-02;...
//      2.079067210376509e-02;...
//      1.848845053267319e-02;...
//      1.664469118982119e-02;...
//      1.513497322191738e-02;...
//      1.387612882307075e-02;...
//      1.281046524292023e-02;...
//      1.189670994589177e-02;...
//      1.110455975820868e-02;...
//      1.041126526197210e-02;...
//      9.799416126158803e-03;...
//      9.255462182712733e-03;...
//      8.768700134139385e-03;...
//      8.330563433362871e-03;...
//      7.934114564314021e-03;...
//      7.573675487951841e-03;...
//      7.244554301320383e-03;...
//      6.942840107209530e-03;...
//      6.665247032707682e-03;...
//      6.408994188004207e-03;...
//      6.171712263039458e-03;...
//      5.951370112758848e-03;...
//      5.746216513010116e-03;...
//      5.554733551962801e-03];

// k = find(n<=15);
// if any(k)
//     n1 = n(k);
//     n2 = 2*n1;
//     if n2==round(n2)
//         delta(k) = sfe(n2+1);
//     else
//         lnsr2pi = 0.9189385332046728; //log(sqrt(2*pi))
//         delta(k) = gammaln(n1+1)-(n1+0.5).*log(n1)+n1-lnsr2pi;
//     end
// end
// k = find(n>15 & n<=35);
// if any(k)
//     delta(k) = (S0-(S1-(S2-(S3-S4./nn(k))./nn(k))./nn(k))./nn(k))./n(k);
// end
// k = find(n>35 & n<=80);
// if any(k)
//     delta(k) = (S0-(S1-(S2-S3./nn(k))./nn(k))./nn(k))./n(k);
// end
// k = find(n>80 & n<=500);
// if any(k)
//     delta(k) = (S0-(S1-S2./nn(k))./nn(k))./n(k);
// end
// k = find(n>500);
// if any(k)
//     delta(k) = (S0-S1./nn(k))./n(k);
// end

// end
