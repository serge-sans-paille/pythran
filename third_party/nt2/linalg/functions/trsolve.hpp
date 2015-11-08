//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TRSOLVE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TRSOLVE_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief trsolve generic tag

      Represents the trsolve function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct trsolve_ : ext::unspecified_<trsolve_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<trsolve_> parent;
    };
  }

  /*!
    @brief Triangular resolution

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::trsolve_, trsolve, 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::trsolve_, trsolve, 4)

  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::trsolve_, trsolve, 2)

  /// INTERNAL ONLY
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::trsolve_, trsolve, 7)

}


#endif

