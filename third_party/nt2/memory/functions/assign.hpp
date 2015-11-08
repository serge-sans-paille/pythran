//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_MEMORY_FUNCTIONS_ASSIGN_HPP_INCLUDED
#define NT2_MEMORY_FUNCTIONS_ASSIGN_HPP_INCLUDED

#include <boost/simd/memory/include/functions/assign.hpp>
#include <nt2/include/functor.hpp>

/* Automatically generated for module core.sdk */

namespace nt2
{
  namespace tag
  {
    #ifdef DOXYGEN_ONLY
    /*! \brief Same as \classref{boost::simd::tag::assign_} **/
    struct assign_ {};
    #endif
    using boost::simd::tag::assign_;
  }

  #ifdef DOXYGEN_ONLY
  /*! \brief Same as \funcref{boost::simd::assign} **/
  template<class... Args>
  details::unspecified assign(Args&&... args);
  #endif
  using boost::simd::assign;
}

#endif
