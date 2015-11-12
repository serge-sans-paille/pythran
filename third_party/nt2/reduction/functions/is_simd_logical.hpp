//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_REDUCTION_FUNCTIONS_IS_SIMD_LOGICAL_HPP_INCLUDED
#define NT2_REDUCTION_FUNCTIONS_IS_SIMD_LOGICAL_HPP_INCLUDED

#include <boost/simd/reduction/include/functions/is_simd_logical.hpp>
#include <nt2/include/functor.hpp>

/* Automatically generated for module core.base */

namespace nt2
{
  namespace tag
  {
    #ifdef DOXYGEN_ONLY
    /*! \brief Same as \classref{boost::simd::tag::is_simd_logical_} **/
    struct is_simd_logical_ {};
    #endif
    using boost::simd::tag::is_simd_logical_;
  }

  #ifdef DOXYGEN_ONLY
  /*! \brief Same as \funcref{boost::simd::is_simd_logical} **/
  template<class... Args>
  details::unspecified is_simd_logical(Args&&... args);
  #endif
  using boost::simd::is_simd_logical;
}

#endif
