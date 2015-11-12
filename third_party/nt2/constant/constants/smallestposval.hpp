//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CONSTANT_CONSTANTS_SMALLESTPOSVAL_HPP_INCLUDED
#define NT2_CONSTANT_CONSTANTS_SMALLESTPOSVAL_HPP_INCLUDED

#include <boost/simd/constant/include/constants/smallestposval.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    #ifdef DOXYGEN_ONLY
    /*! \brief Same as \classref{boost::simd::tag::Smallestposval_} **/
    struct smallestposval_ {};
    #endif
    using boost::simd::tag::Smallestposval;
  }

  #ifdef DOXYGEN_ONLY
  /*! \brief Same as \funcref{boost::simd::Smallestposval} **/
  template<class... Args>
  details::unspecified smallestposval(Args&&... args);
  #endif
  using boost::simd::Smallestposval;
}

#include <nt2/constant/common.hpp>

#endif
