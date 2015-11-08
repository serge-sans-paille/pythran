//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTEGRATION_FUNCTIONS_QUADGK_HPP_INCLUDED
#define NT2_INTEGRATION_FUNCTIONS_QUADGK_HPP_INCLUDED

#include <nt2/integration/interface.hpp>

namespace nt2
{
  namespace tag
  {
    struct quadgk_ : ext::unspecified_<quadgk_>
    {
      typedef ext::unspecified_<quadgk_> parent;
    };
    // definition  of abstol constant for quadgk method
    /// INTERNAL ONLY
    BOOST_SIMD_CONSTANT_REGISTER( Quadgkabstol, double
                                  , 0, 0x3727c5ac             //1.0e-5
                                  , 0x3ddb7cdfd9d7bdbbll      //1.0e-10
      )
    // definition  of reltol constant for quadgk method
    /// INTERNAL ONLY
    BOOST_SIMD_CONSTANT_REGISTER( Quadgkreltol, double
                                  , 0, 0x38d1b717             //1.0e-4
                                  , 0x3eb0c6f7a0b5ed8dll      //1.0e-6
      )
  }
  /// INTERNAL ONLY
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Quadgkabstol, Quadgkabstol);
  /// INTERNAL ONLY
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Quadgkreltol, Quadgkreltol);

  // specialization of abstol/reltol for quadgk method
  /// INTERNAL ONLY
  template<class T, class V> struct integ_params<T, V, tag::quadgk_>
  : integ_params<T, V, void>
  {
    typedef typename nt2::integ_params<T, V, void>::real_t real_t;
    static real_t           abstol(){return Quadgkabstol<real_t>(); }
    static real_t           reltol(){return Quadgkreltol<real_t>(); }
    static bool enabled_singular_a(){ return false;                 }
    static bool enabled_singular_b(){ return false;                 }

  };

  //============================================================================
  /*!
    Applies quadgk algorithm to integrate a function over a real
    interval using adaptive Gauss-Kronrod quadrature.

    \param f    Function to integrate
    \param x    required points in the interval in ascending order
                (x can be replaced by 2 abscissae a and b)
    \param opt   Options pack related to the tolerance handling

    \return  a tuple containing the results of the integration, the last error value,
    the number of required function evaluation and a boolean
    notifying success of the whole process.

       Tries to approximates the integral of scalar-valued
       function f from a to b to within a default error of max(AbsTol,RelTol*|q|).
       where q is the integration result.

       This is absolute error control when |q| is sufficiently small
       and relative error control when |q| is larger. A default
       tolerance value is used when a tolerance is not specified.

       The default values :
         - of nt2::Quadgkabstol<real_t>() is 1.e-10 (double), 1.e-5 (single).
         - of nt2::Quadgkreltol<real_t>() is 1.e-6 (double), 1.e-4 (single).

       f is a functor that should accept a vector argument x and
       return a vector result y, the integrand evaluated at each
       element of x.

    This routine mimics Matlab quadgk, but has some behavioural differences.
    including options passing and obtaining results

     - a and b can be singular for f.

       Contrarily to matlab, there is no automatic detection and the
       options singular_a_ and singular_b_ are by default set to false

     - as in matlab on can give way points through the computation must go
       a and b are always added (but never duplicated).

       The way points mustn't be singular and must be in proper order.

       If the option return_waypoints is set to true the result is a vector of
       cumulated integrals from a to each waypoint. Peculiarly result(begin_) is 0 and
       result(end_) is the integral from a to b.

     - the abscissae can be complex and the integral a path integral through the
       lines following the way points in their given order.
   */
  //============================================================================

  template<class F, class X, class Xpr> BOOST_FORCEINLINE
  typename details::integration<F, X, tag::quadgk_>::result_type
  quadgk(F f, X const& x, nt2::details::option_expr<Xpr> const& opt)
  {
    return details::integration<F, X, tag::quadgk_>::call(f, x, opt);
  }


  /// @overload
  template<class F, class X> BOOST_FORCEINLINE
  typename details::integration<F, X, tag::quadgk_>::result_type
  quadgk(F f, X const& x)
  {
    return details::integration<F, X, tag::quadgk_>::call(f, x);
  }

  /// @overload
  template<class F, class A> BOOST_FORCEINLINE
  typename details::integration<F, typename details::h2_t<A>::ab_t, tag::quadgk_>::result_type
  quadgk(F f, A a, A b)
  {
    typedef typename details::h2_t<A>::ab_t ab_t;
    return details::integration<F, ab_t, tag::quadgk_>::call(f, nt2::cath(a, b));
  }

  /// @overload
  template<class F, class A, class Xpr> BOOST_FORCEINLINE
  typename details::integration<F, typename details::h2_t<A>::ab_t, tag::quadgk_>::result_type
  quadgk(F f, A a, A b, nt2::details::option_expr<Xpr> const& opt)
  {
    typedef typename details::h2_t<A>::ab_t ab_t;
    return details::integration<F, ab_t, tag::quadgk_>::call(f, nt2::cath(a, b), opt);
  }
}

#endif

