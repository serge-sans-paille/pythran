//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_MLOG10TWO2NMB_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_MLOG10TWO2NMB_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Mlog10two2nmb generic tag

      Represents the Mlog10two2nmb constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Mlog10two2nmb, double
                                , 0, 0xc0dd8edeUL
                                , 0xc02fe8bffd88220cULL
                                )
  }
 /*!
    Generates constant Mlog10two2nmb.

    @par Semantic:

    @code
    T r = Mlog10two2nmb<T>();
    @endcode

    is similar to:

    @code
      r =  -log10(exp2(T(Nbmantissabits<T>())));
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Mlog10two2nmb, Mlog10two2nmb);
}

#endif
