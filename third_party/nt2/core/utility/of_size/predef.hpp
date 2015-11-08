//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_OF_SIZE_PREDEF_HPP_INCLUDED
#define NT2_CORE_UTILITY_OF_SIZE_PREDEF_HPP_INCLUDED

#include <nt2/core/settings/forward/size.hpp>
#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace nt2
{
  //============================================================================
  // Defines some usual short-cuts for runtime of_size_
  //============================================================================
  #define M0(z,n,t)                                                 \
  typedef of_size_<BOOST_PP_ENUM_PARAMS(n, std::ptrdiff_t(-1) BOOST_PP_INTERCEPT)> \
  BOOST_PP_CAT(BOOST_PP_CAT(_, n), D);                              \
  /**/
  BOOST_PP_REPEAT(BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)
  #undef M0

  //============================================================================
  // Defines the type of largest of_size available
  //============================================================================
  typedef of_size_<BOOST_PP_ENUM_PARAMS ( NT2_MAX_DIMENSIONS
                                        , std::ptrdiff_t(-1) BOOST_PP_INTERCEPT
                                        )
                  >                                                 of_size_max;

  //============================================================================
  // Maps a constant to the proper of_size specialization
  //============================================================================
  template<std::size_t D> struct make_size
  {
    typedef of_size_max type;
  };

  #define M0(z,n,t)                                     \
  template<> struct make_size<n>                        \
  { typedef BOOST_PP_CAT(BOOST_PP_CAT(_,n),D) type; };  \
  /**/
  BOOST_PP_REPEAT(BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)
  #undef M0
}

#endif
