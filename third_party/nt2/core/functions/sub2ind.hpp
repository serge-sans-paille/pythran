//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SUB2IND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SUB2IND_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief sub2ind generic tag

      Represents the sub2ind function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct sub2ind_ : ext::elementwise_<sub2ind_>
    {
      typedef ext::elementwise_<sub2ind_> parent;
    };
  }


  #define M0(z,n,t)                                           \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sub2ind_, sub2ind, n) \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M0

  #if defined(DOXYGEN_ONLY)
  /*!
    @brief Convert subscripts to linear indices

    Determines the linear index equivalents to the specified subscripts for
    each dimension of an N-dimensional container of size .

    @param sz Size sequence of target container
    @param dims Subscript to convert

    @return A linear index pointing to the same element than \c pos.
  **/
  template<typename Size, typename Dims...>
  detail::unspecified sub2ind(Size const& sz, Dims const& ... dims);
  #endif
}

#endif
