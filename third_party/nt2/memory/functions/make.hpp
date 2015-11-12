//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_MEMORY_FUNCTIONS_MAKE_HPP_INCLUDED
#define NT2_MEMORY_FUNCTIONS_MAKE_HPP_INCLUDED

#include <boost/simd/memory/include/functions/make.hpp>
#include <nt2/include/functor.hpp>

/* Automatically generated for module core.sdk */

namespace nt2
{
  namespace tag
  {
    #ifdef DOXYGEN_ONLY
    /*! \brief Same as \classref{boost::simd::tag::make_} **/
    struct make_ {};
    #endif
    using boost::simd::tag::make_;
  }

  #ifdef DOXYGEN_ONLY
  /*! \brief Same as \funcref{boost::simd::make} **/
  template<class... Args>
  details::unspecified make(Args&&... args);
  #endif
  using boost::simd::make;
}

#endif
