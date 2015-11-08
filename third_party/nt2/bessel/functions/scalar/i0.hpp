//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BESSEL_FUNCTIONS_SCALAR_I0_HPP_INCLUDED
#define NT2_BESSEL_FUNCTIONS_SCALAR_I0_HPP_INCLUDED
#include <nt2/bessel/functions/i0.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/polynomials/include/functions/tchebeval.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/is_inf.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <boost/array.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::i0_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return i0(result_type(a0));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::i0_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      static const boost::array<double, 30> A =
      {{
        -4.41534164647933937950E-18,
        3.33079451882223809783E-17,
        -2.43127984654795469359E-16,
        1.71539128555513303061E-15,
        -1.16853328779934516808E-14,
        7.67618549860493561688E-14,
        -4.85644678311192946090E-13,
        2.95505266312963983461E-12,
        -1.72682629144155570723E-11,
        9.67580903537323691224E-11,
        -5.18979560163526290666E-10,
        2.65982372468238665035E-9,
        -1.30002500998624804212E-8,
        6.04699502254191894932E-8,
        -2.67079385394061173391E-7,
        1.11738753912010371815E-6,
        -4.41673835845875056359E-6,
        1.64484480707288970893E-5,
        -5.75419501008210370398E-5,
        1.88502885095841655729E-4,
        -5.76375574538582365885E-4,
        1.63947561694133579842E-3,
        -4.32430999505057594430E-3,
        1.05464603945949983183E-2,
        -2.37374148058994688156E-2,
        4.93052842396707084878E-2,
        -9.49010970480476444210E-2,
        1.71620901522208775349E-1,
        -3.04682672343198398683E-1,
        6.76795274409476084995E-1
        }};
      static const boost::array<double, 25> B =
      {{
        -7.23318048787475395456E-18,
        -4.83050448594418207126E-18,
        4.46562142029675999901E-17,
        3.46122286769746109310E-17,
        -2.82762398051658348494E-16,
        -3.42548561967721913462E-16,
        1.77256013305652638360E-15,
        3.81168066935262242075E-15,
        -9.55484669882830764870E-15,
        -4.15056934728722208663E-14,
        1.54008621752140982691E-14,
        3.85277838274214270114E-13,
        7.18012445138366623367E-13,
        -1.79417853150680611778E-12,
        -1.32158118404477131188E-11,
        -3.14991652796324136454E-11,
        1.18891471078464383424E-11,
        4.94060238822496958910E-10,
        3.39623202570838634515E-9,
        2.26666899049817806459E-8,
        2.04891858946906374183E-7,
        2.89137052083475648297E-6,
        6.88975834691682398426E-5,
        3.36911647825569408990E-3,
        8.04490411014108831608E-1
      }};
      A0 x =  nt2::abs(a0);
      if (is_inf(x)) return x;
      if( x <= 8.0 )
      {
        A0 y = x*Half<A0>() - Two<A0>();
        return( nt2::exp(x) * tchebeval( y, A) );
      }
      return(  nt2::exp(x) * tchebeval( 32.0/x - 2.0, B) / nt2::sqrt(x) );
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::i0_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      /* Chebyshev coefficients for exp(-x) I0(x)
       * in the interval [0,8].
       *
       * lim(x->0){ exp(-x) I0(x) } = 1.
       */
      static const boost::array<float, 18> A =
      {{
          -1.30002500998624804212E-8f,
          6.04699502254191894932E-8f,
          -2.67079385394061173391E-7f,
          1.11738753912010371815E-6f,
          -4.41673835845875056359E-6f,
          1.64484480707288970893E-5f,
          -5.75419501008210370398E-5f,
          1.88502885095841655729E-4f,
          -5.76375574538582365885E-4f,
          1.63947561694133579842E-3f,
          -4.32430999505057594430E-3f,
          1.05464603945949983183E-2f,
          -2.37374148058994688156E-2f,
          4.93052842396707084878E-2f,
          -9.49010970480476444210E-2f,
          1.71620901522208775349E-1f,
          -3.04682672343198398683E-1f,
          6.76795274409476084995E-1f
        }};


       /* Chebyshev coefficients for exp(-x) sqrt(x) I0(x)
        * in the inverted interval [8,infinity].
        *
        * lim(x->inf){ exp(-x) sqrt(x) I0(x) } = 1/sqrt(2pi).
        */

       static const boost::array<float, 7> B =
         {{
         3.39623202570838634515E-9f,
         2.26666899049817806459E-8f,
         2.04891858946906374183E-7f,
         2.89137052083475648297E-6f,
         6.88975834691682398426E-5f,
         3.36911647825569408990E-3f,
         8.04490411014108831608E-1f
           }};
      A0 x =  nt2::abs(a0);
      if (is_inf(x)) return x;
      if( x <= 8.0f )
      {
        A0 y = x*Half<A0>() - Two<A0>();
        return( exp(x) * tchebeval( y, A) );
      }
      return(  exp(x) * tchebeval( 32.0f/x - 2.0f, B) / sqrt(x) );
    }
  };
} }


#endif
