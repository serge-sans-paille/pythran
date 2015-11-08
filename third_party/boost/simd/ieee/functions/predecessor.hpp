//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_PREDECESSOR_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_PREDECESSOR_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief predecessor generic tag

     Represents the predecessor function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct predecessor_ : ext::elementwise_<predecessor_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<predecessor_> parent;
    };
  }
  /*!
    With one parameter it is equivalent to \c prev
    It is in the type \c A0, the greatest  \c A0 elementwise strictly less than  \c a0.
    \par
    With two parameters, the second is an integer value  \c n
    and the result is equivalent to applying \c prev \c abs(n) times to  \c a0.

    @par Semantic:

    @code
    T r = predecessor(x);
    @endcode

    computes the greatest value strictly less than x in its type

    @param a0

    @return a value of same type as the inputs
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::predecessor_, predecessor, 1)
  /*!
    Returns the n-th greatest element strictly less than the parameter

    @par Semantic:

    @code
    T r = predecessor(x,n);
    @endcode

    computes the @c n-th greatest value strictly less than x in its type.
    n must be positive or null.
    For integer it saturate at Valmin, for floating point numbers Minf
    strict predecessors are Nan

    @param a0

    @param a1

    @return a value of same type as the inputs
  **/
    BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::predecessor_, predecessor, 2)
} }

#endif
