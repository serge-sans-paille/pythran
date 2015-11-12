//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_COMPARE_GREATER_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_COMPARE_GREATER_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief compare_greater generic tag

     Represents the compare_greater function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct compare_greater_ : ext::unspecified_<compare_greater_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<compare_greater_> parent;
    };
  }
  /*!
    return a bool that is the result of the lexicographic
    test for > on all elements of the entries

    It is probably not what you wish. Have a look to is_greater

    @par Semantic:

    For every parameters of type T0:

    @code
    as_logical<scalar_of<T0>> r = compare_greater(a0,a1);
    @endcode

    is similar to:

    @code
      as_logical<scalar_of<T0>> r = False;
      for(std::size_t i=0;i<cardinal_of<A0>;++i)
      {
        if (a0[i] > a1[i])  {r =  True; break;}
        if (a1[i] > a0[i])  {r = False; break;}
      }
    @endcode

    @par Alias:
    @c compare_gt

    @see @funcref{is_greater}
    @param a0

    @param a1

    @return a value of the scalar logical type associated to the parameters
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::compare_greater_, compare_greater , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::compare_greater_, compare_gt      , 2 )
} }
#endif
