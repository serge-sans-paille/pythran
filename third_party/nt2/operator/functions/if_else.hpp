//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPERATOR_FUNCTIONS_IF_ELSE_HPP_INCLUDED
#define NT2_OPERATOR_FUNCTIONS_IF_ELSE_HPP_INCLUDED

#include <boost/simd/operator/include/functions/if_else.hpp>
#include <nt2/include/functor.hpp>

/* Automatically generated for module core.base */

namespace nt2
{
  namespace tag
  {
    #ifdef DOXYGEN_ONLY
    /*! \brief Same as \classref{boost::simd::tag::if_else_} **/
    struct if_else_ {};
    #endif
    using boost::simd::tag::if_else_;
  }

  #ifdef DOXYGEN_ONLY
  /*! \brief Same as \funcref{boost::simd::if_else} **/
  template<class... Args>
  details::unspecified if_else(Args&&... args);
  #endif
  using boost::simd::if_else;
}

#endif
