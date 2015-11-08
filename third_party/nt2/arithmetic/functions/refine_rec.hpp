//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_REFINE_REC_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_REFINE_REC_HPP_INCLUDED

#include <boost/simd/arithmetic/include/functions/refine_rec.hpp>
#include <nt2/include/functor.hpp>

/* Automatically generated for module core.base */

namespace nt2
{
  namespace tag
  {
    #ifdef DOXYGEN_ONLY
    /*! \brief Same as \classref{boost::simd::tag::refine_rec_} **/
    struct refine_rec_ {};
    #endif
    using boost::simd::tag::refine_rec_;
  }

  #ifdef DOXYGEN_ONLY
  /*! \brief Same as \funcref{boost::simd::refine_rec} **/
  template<class... Args>
  details::unspecified refine_rec(Args&&... args);
  #endif
  using boost::simd::refine_rec;
}

#endif
