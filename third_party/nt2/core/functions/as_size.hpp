//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_AS_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_AS_SIZE_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the as_size function
**/

#include <nt2/sdk/parameters.hpp>
#include <nt2/include/functor.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for depth function
    **/
    struct as_size_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Build a Size
  **/
  #define M0(z,n,t)                                           \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::as_size_, as_size, n) \
  /**/
  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)
  #undef M0
}

#endif
