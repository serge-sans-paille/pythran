//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CONSTANT_CONSTANTS_MTEN_HPP_INCLUDED
#define NT2_CONSTANT_CONSTANTS_MTEN_HPP_INCLUDED

#include <boost/simd/constant/include/constants/mten.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    #ifdef DOXYGEN_ONLY
    /*! \brief Same as \classref{boost::simd::tag::Mten_} **/
    struct mten_ {};
    #endif
    using boost::simd::tag::Mten;
  }

  #ifdef DOXYGEN_ONLY
  /*! \brief Same as \funcref{boost::simd::Mten} **/
  template<class... Args>
  details::unspecified mten(Args&&... args);
  #endif
  using boost::simd::Mten;
}

#include <nt2/constant/common.hpp>

#endif
