//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPERATOR_FUNCTIONS_UNARY_PLUS_HPP_INCLUDED
#define NT2_OPERATOR_FUNCTIONS_UNARY_PLUS_HPP_INCLUDED

#include <boost/simd/operator/include/functions/unary_plus.hpp>
#include <nt2/include/functor.hpp>

/* Automatically generated for module core.base */

namespace nt2
{
  namespace tag
  {
    #ifdef DOXYGEN_ONLY
    /*! \brief Same as \classref{boost::simd::tag::unary_plus_} **/
    struct unary_plus_ {};
    #endif
    using boost::simd::tag::unary_plus_;
  }

  #ifdef DOXYGEN_ONLY
  /*! \brief Same as \funcref{boost::simd::unary_plus} **/
  template<class... Args>
  details::unspecified unary_plus(Args&&... args);
  #endif
  using boost::simd::unary_plus;
}

#endif
