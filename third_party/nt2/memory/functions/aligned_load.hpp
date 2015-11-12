//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_MEMORY_FUNCTIONS_ALIGNED_LOAD_HPP_INCLUDED
#define NT2_MEMORY_FUNCTIONS_ALIGNED_LOAD_HPP_INCLUDED

#include <boost/simd/memory/include/functions/aligned_load.hpp>
#include <nt2/include/functor.hpp>

/* Automatically generated for module core.sdk */

namespace nt2
{
  namespace tag
  {
    #ifdef DOXYGEN_ONLY
    /*! \brief Same as \classref{boost::simd::tag::aligned_load_} **/
    struct aligned_load_ {};
    #endif
    using boost::simd::tag::aligned_load_;
  }

  #ifdef DOXYGEN_ONLY
  /*! \brief Same as \funcref{boost::simd::aligned_load} **/
  template<class... Args>
  details::unspecified aligned_load(Args&&... args);
  #endif
  using boost::simd::aligned_load;
}

#endif
