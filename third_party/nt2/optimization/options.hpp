//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPTIMIZATION_OPTIONS_HPP_INCLUDED
#define NT2_OPTIMIZATION_OPTIONS_HPP_INCLUDED

#include <cstddef>
#include <nt2/sdk/option/options.hpp>
#include <nt2/include/constants/sqrteps.hpp>

namespace nt2
{
  /**
   * Named parameter for passing number of iterations to iterative algortihms
   **/
  NT2_REGISTER_PARAMETERS(iterations_);

  namespace tolerance
  {
    /**
     * Named parameter for passing absolute tolerance to iterative algorithms
     **/
    NT2_REGISTER_PARAMETERS(absolute_);

    /**
     * Named parameter for passing relative tolerance to iterative algorithms
     **/
    NT2_REGISTER_PARAMETERS(relative_);

    /**
     * Named parameter for passing residual tolerance to iterative algorithms
     **/
    NT2_REGISTER_PARAMETERS(residual_);
  }
}

namespace nt2 { namespace details
{
  // INTERNAL ONLY
  // optimization_settings gather the classical set of settings required
  // for an optimization process from either the list of values or from an
  // options pack expressions
  template<typename T> struct optimization_settings
  {
    typedef T value_type;

    // required on MSVC for some unknown reason
    BOOST_FORCEINLINE static T Sqrteps() { return nt2::Sqrteps<T>(); }

    optimization_settings ( std::size_t it  = 100
                          , value_type at   = Sqrteps()
                          , value_type rt   = Sqrteps()
                          , value_type rst  = Sqrteps()
                          )
                          : maximum_iterations(it), absolute_tolerance(at)
                          , relative_tolerance(rt), residual_tolerance(rst)
    {}

    template<class Expr>
    optimization_settings ( nt2::details::option_expr<Expr> const& x)
        : maximum_iterations(x(nt2::iterations_         , 100               ))
        , absolute_tolerance(x(nt2::tolerance::absolute_, nt2::Sqrteps<T>() ))
        , relative_tolerance(x(nt2::tolerance::relative_, nt2::Sqrteps<T>() ))
        , residual_tolerance(x(nt2::tolerance::residual_, nt2::Sqrteps<T>() ))
    {}

    std::size_t   maximum_iterations;
    value_type    absolute_tolerance;
    value_type    relative_tolerance;
    value_type    residual_tolerance;
  };
} }

#endif
