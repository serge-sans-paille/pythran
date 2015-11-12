//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_UNIFCDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_UNIFCDF_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/size.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief unifcdf generic tag

     Represents the unifcdf function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct unifcdf_ : ext::elementwise_<unifcdf_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<unifcdf_> parent;
    };
  }
  /*!
    uniform cumulative distribution

    @par Semantic:

    For every table expression and interval bounds a and b

    @code
    auto r = unifcdf(a0, a, b);
    @endcode

    is similar to:

    @code
    auto r = (a0<a) ? 0 : ((a0 >= b) ? 1 : (b-a0)/(b-a));
    @endcode

    @param a0
    @param a1
    @param a2

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::unifcdf_, unifcdf, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::unifcdf_, unifcdf, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::unifcdf_, unifcdf, 1)
}

#endif
