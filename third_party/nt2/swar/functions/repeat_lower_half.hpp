//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SWAR_FUNCTIONS_REPEAT_LOWER_HALF_HPP_INCLUDED
#define NT2_SWAR_FUNCTIONS_REPEAT_LOWER_HALF_HPP_INCLUDED

#include <boost/simd/swar/include/functions/repeat_lower_half.hpp>
#include <nt2/include/functor.hpp>

/* Automatically generated for module core.base */

namespace nt2
{
  namespace tag
  {
    #ifdef DOXYGEN_ONLY
    /*! \brief Same as \classref{boost::simd::tag::repeat_lower_half_} **/
    struct repeat_lower_half_ {};
    #endif
    using boost::simd::tag::repeat_lower_half_;
  }

  #ifdef DOXYGEN_ONLY
  /*! \brief Same as \funcref{boost::simd::repeat_lower_half} **/
  template<class... Args>
  details::unspecified repeat_lower_half(Args&&... args);
  #endif
  using boost::simd::repeat_lower_half;
}

#endif
