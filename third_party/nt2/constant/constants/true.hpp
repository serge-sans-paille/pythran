//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CONSTANT_CONSTANTS_TRUE_HPP_INCLUDED
#define NT2_CONSTANT_CONSTANTS_TRUE_HPP_INCLUDED

#include <boost/simd/constant/include/constants/true.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    #ifdef DOXYGEN_ONLY
    /*! \brief Same as \classref{boost::simd::tag::True_} **/
    struct true_ {};
    #endif
    using boost::simd::tag::True;
  }

  #ifdef DOXYGEN_ONLY
  /*! \brief Same as \funcref{boost::simd::True} **/
  template<class... Args>
  details::unspecified true(Args&&... args);
  #endif
  using boost::simd::True;
}

#include <nt2/constant/common.hpp>

#endif
