//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ALONG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ALONG_HPP_INCLUDED

#include <nt2/include/functor.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief along generic tag

     Represents the along function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct along_ : ext::elementwise_<along_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<along_> parent;
    };
  }
  /*!
    Applies an index \c ind on \c expr along the \c i-th dimension
    by default \c i is the first non-singleton dimension of expr

    @par Semantic:

    For every parameters of types respectively T0, T1, T2:

    @code
    auto r = along(a0,a1{,a2});
    @endcode

    is similar to:

    @code
    auto r = a0(_, ..., a1, ..., _);//where a1 is in a2-th slot of a0
    @endcode

    a2 default to the @funcref{firstnonsingleton} dimension of a0.

    @param a0 the expression to index
    @param a1 the indexer
    @param a2 the dimension on which to index, optional, default to firstnonsingleton(a0)

    @return a0(_, ..., a1, ..., _) with @c a1 at the @c a2-th argument


    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::along_       , along, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::along_       , along, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION_SELF(nt2::tag::along_  , along, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION_SELF(nt2::tag::along_  , along, 3)
}

#endif
