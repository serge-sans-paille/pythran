//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CONSTANT_CONSTANTS_ZERO_HPP_INCLUDED
#define NT2_CONSTANT_CONSTANTS_ZERO_HPP_INCLUDED

#include <boost/simd/constant/include/constants/zero.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    #ifdef DOXYGEN_ONLY
    /*! \brief Same as \classref{boost::simd::tag::Zero_} **/
    struct zero_ {};
    #endif
    using boost::simd::tag::Zero;
  }

  #ifdef DOXYGEN_ONLY
  /*! \brief Same as \funcref{boost::simd::Zero} **/
  template<class... Args>
  details::unspecified zero(Args&&... args);
  #endif
  using boost::simd::Zero;
}

#include <nt2/constant/common.hpp>

#endif
