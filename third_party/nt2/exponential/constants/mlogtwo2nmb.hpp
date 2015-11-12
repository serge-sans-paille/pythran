//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_CONSTANTS_MLOGTWO2NMB_HPP_INCLUDED
#define NT2_EXPONENTIAL_CONSTANTS_MLOGTWO2NMB_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Mlogtwo2nmb generic tag

      Represents the Mlogtwo2nmb constant in generic contexts.

      @par Models:
      Hierarchy
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Mlogtwo2nmb, double
                                , 0, 0xc17f1402UL
                                , 0xc0425e4f7b2737faULL
                                )
  }
 /*!
    Generates constant Mlogtwo2nmb.

    @par Semantic:

    @code
    T r = Mlogtwo2nmb<T>();
    @endcode

    is similar to:

    @code
      r =  -log(exp2(T(Nbmantissabits<T>())));
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Mlogtwo2nmb, Mlogtwo2nmb);
}

#endif
