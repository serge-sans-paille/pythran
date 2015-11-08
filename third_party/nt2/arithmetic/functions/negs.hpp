//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_NEGS_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_NEGS_HPP_INCLUDED

#include <boost/simd/arithmetic/include/functions/negs.hpp>
#include <nt2/include/functor.hpp>

/* Automatically generated for module core.base */

namespace nt2
{
  namespace tag
  {
    #ifdef DOXYGEN_ONLY
    /*! \brief Same as \classref{boost::simd::tag::negs_} **/
    struct negs_ {};
    #endif
    using boost::simd::tag::negs_;
  }

  #ifdef DOXYGEN_ONLY
  /*! \brief Same as \funcref{boost::simd::negs} **/
  template<class... Args>
  details::unspecified negs(Args&&... args);
  #endif
  using boost::simd::negs;
}

#endif
