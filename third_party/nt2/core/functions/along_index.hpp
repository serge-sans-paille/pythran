//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ALONG_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ALONG_INDEX_HPP_INCLUDED

#include <nt2/include/functor.hpp>


namespace nt2
{
  namespace tag
  {
   /*!
     @brief along_index generic tag

     Represents the along_index function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct along_index_ : ext::elementwise_<along_index_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<along_index_> parent;
    };
  }
  /*!
    Computes the linear index \c ind along the \c i-th dimension

    @par Semantic:

    For every parameters of floating types respectively T0, T1, T2:

    @code
    auto r = along_index(a0,a1,a2);
    @endcode


    \param a0 the indexer
    \param a1 the dimension on which to index
    \param a2 the size of the data being indexed

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::along_index_       , along_index, 3)
}

#endif
