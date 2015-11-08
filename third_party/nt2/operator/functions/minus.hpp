//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPERATOR_FUNCTIONS_MINUS_HPP_INCLUDED
#define NT2_OPERATOR_FUNCTIONS_MINUS_HPP_INCLUDED

#include <boost/simd/operator/include/functions/minus.hpp>
#include <nt2/include/functor.hpp>

/* Automatically generated for module core.base */

namespace nt2
{
  namespace tag
  {
    #ifdef DOXYGEN_ONLY
    /*! \brief Same as \classref{boost::simd::tag::minus_} **/
    struct minus_ {};
    #endif
    using boost::simd::tag::minus_;
  }

  #ifdef DOXYGEN_ONLY
  /*! \brief Same as \funcref{boost::simd::minus} **/
  template<class... Args>
  details::unspecified minus(Args&&... args);
  #endif
  using boost::simd::minus;
}

#endif
