//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTEGRATION_FUNCTIONS_ROMBERG_HPP_INCLUDED
#define NT2_INTEGRATION_FUNCTIONS_ROMBERG_HPP_INCLUDED

#include <nt2/integration/interface.hpp>

namespace nt2
{
  namespace tag
  {
    struct romberg_ : ext::unspecified_<romberg_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<romberg_> parent;
    };

    // definition  of abstol constant for romberg method
    /// INTERNAL ONLY
    BOOST_SIMD_CONSTANT_REGISTER( Rombergabstol, double
                                  , 0, 0x3a83126f             //1.0e-3
                                  , 0x3eb0c6f7a0b5ed8dll      //1.0e-6
      )
  }

  /// INTERNAL ONLY
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Rombergabstol, Rombergabstol);

  // specialization of abstol for romberg method
  /// INTERNAL ONLY
  template<class T, class V> struct integ_params<T, V, tag::romberg_>
  : integ_params<T, V, void>
  {
    typedef typename nt2::integ_params<T, V, void>::real_t real_t;
    static real_t        abstol(){return Rombergabstol<real_t>(); }
    static bool enabled_abstol()           { return true;   }
    static bool enabled_reltol()           { return false;  }
    static bool enabled_maxfunccnt()       { return false;  }
    static bool enabled_maxintvcnt()       { return false;  }
    static bool enabled_waypoints()        { return true;   }
    static bool enabled_singular_a()       { return true;   }
    static bool enabled_singular_b()       { return true;   }
    static bool enabled_return_waypoints() { return true;   }
    static bool enabled_nbextrap()         { return true;   }
    static bool enabled_maxstep()          { return true;   }
  };

  //============================================================================
  /*!
    Applies romberg algorithm to integrate a function over a real interval

    \param f  Function to optimize
    \param x    required points in the interval or 2 abscissae a and b
    \param opt   Options pack related to the tolerance handling

    \return  a tuple containing the results of the integration, the last error value,
    the number of required function evaluation and a boolean
    notifying success of the whole process.

       Tries to approximate the integral of scalar-valued function
       fun from a to b to within a default error of
       nt2::Rombergabstol<real_t>() where real_t can be float
       (1.0e-3) or double (1.0e-6) using Romberg quadrature.

       f is a functor that should accept a vector argument x and
       return a vector result y, the integrand evaluated at each
       element of x.

   */
  //============================================================================


  template<class F, class X, class Xpr> BOOST_FORCEINLINE
  typename details::integration<F, X, tag::romberg_>::result_type
  romberg(F f, X const& x, nt2::details::option_expr<Xpr> const& opt)
  {
    return details::integration<F, X, tag::romberg_>::call(f, x, opt);
  }

  /// @overload
  template<class F, class X> BOOST_FORCEINLINE
  typename details::integration<F, X, tag::romberg_>::result_type
  romberg(F f, X const& x)
  {
    return details::integration<F, X, tag::romberg_>::call(f, x);
  }

  /// @overload
  template<class F, class A> BOOST_FORCEINLINE
  typename details::integration<F, typename details::h2_t<A>::ab_t, tag::romberg_>::result_type
  romberg(F f, A a, A b)
  {
    typedef typename details::h2_t<A>::ab_t ab_t;
    return details::integration<F, ab_t, tag::romberg_>::call(f, nt2::cath(a, b));
  }

  /// @overload
  template<class F, class A, class Xpr> BOOST_FORCEINLINE
  typename details::integration<F, typename details::h2_t<A>::ab_t, tag::romberg_>::result_type
  romberg(F f, A a, A b, nt2::details::option_expr<Xpr> const& opt)
  {
    typedef typename details::h2_t<A>::ab_t ab_t;
    return details::integration<F, ab_t, tag::romberg_>::call(f, nt2::cath(a, b), opt);
  }


}

#endif

