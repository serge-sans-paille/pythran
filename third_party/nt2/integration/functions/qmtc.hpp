//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTEGRATION_FUNCTIONS_QMTC_HPP_INCLUDED
#define NT2_INTEGRATION_FUNCTIONS_QMTC_HPP_INCLUDED

#include <nt2/integration/interfacen.hpp>

namespace nt2
{
  namespace tag
  {
    struct qmtc_ : ext::unspecified_<qmtc_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<qmtc_> parent;
    };
  }

  // specialization of abstol for qmtc method
  template<class T, class V> struct integ_params<T, V, tag::qmtc_>
  : integ_params<T, V, void>
  {
    typedef typename nt2::integ_params<T, V, void>::real_t real_t;
    static bool enabled_singular_a()       { return false; }
    static bool enabled_singular_b()       { return false; }
    static bool enabled_abstol()           { return false; }
    static bool enabled_reltol()           { return false; }
    static bool enabled_maxintvcnt()       { return false; }
    static bool enabled_waypoints()        { return false; }
    static bool enabled_return_waypoints() { return false; }
    static bool enabled_nbextrap()         { return false; }
    static bool enabled_maxstep()          { return false; }


  };

  //============================================================================
  /*!  Apply qmtc algorithm to integrate a function over a real
    hyper-rectangle using quasi-random numbers

    \param f      Function to optimize.
                  f must be a functor taking a matrix with n rows and any
                  number of columns able to return a row values: one by
                  data column.
    \param ranges ranges of integration as a nx2xm expression.
                  Each line is an interval for a range of integration
                  and this for each page of ranges.
                  To be explicit a matrix as [0, 1; 1, 2] in matlab notation
                  will provide \f$\int_0^1 \int_1^2 f(x, y) dx dy\f$.
    \param opt   Options pack related to the tolerance handling

    \return a tuple containing the result of the integration, the last
    error value, the number of required function evaluation and a
    boolean notifying success of the whole process.

       Approximates the n superposed integrals of a scalar-valued from
       \f$R^n\f$ to \f$R\f$ or \f$C\f$ in an hyper-rectangle with a simple Monte-Carlo
       approach, but using quasi-random numbers.

    @par Notes:
     - f can have complex outputs but only real inputs.
     - there is no way to ask for a given precision. The precision
        depends of the number of evaluation points (default 10000) that can
        be set with maxfunccnt_ option value. It can be said that if you multiply
         limits::maxfunccnt_ by n,  the error will be divided by sqrt(n).
     - By default the returned error estimate is computed, but this is can be
         expansive. If you do not care for an error estimate use the
         option tolerance::compute_error_ = false

    @see @funcref{mtc}, @funcref{quasi}
   */
  //============================================================================


  template<class F, class X, class Xpr> BOOST_FORCEINLINE
  typename details::integration_n<F, X, tag::qmtc_>::result_type
  qmtc(F f, X const& ranges, nt2::details::option_expr<Xpr> const& opt)
  {
    return details::integration_n<F, X, tag::qmtc_>::call(f, ranges, opt);
  }

  /// @overload
  template<class F, class X> BOOST_FORCEINLINE
  typename details::integration_n<F, X, tag::qmtc_>::result_type
  qmtc(F f, X const& ranges)
  {
    return details::integration_n<F, X, tag::qmtc_>::call(f, ranges);
  }

}

#endif

