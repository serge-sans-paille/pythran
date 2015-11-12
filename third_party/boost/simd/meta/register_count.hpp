//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_META_REGISTER_COUNT_HPP_INCLUDED
#define BOOST_SIMD_META_REGISTER_COUNT_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>
#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/type_traits/is_floating_point.hpp>

namespace boost { namespace simd { namespace meta
{
  /*!
    @brief SIMD register file size

    Return an @mplint containing the current architecture register file
    size for a given type.

    @par Models:

    @metafunction

    @tparam T Type to check
  **/
  template<typename T>
  struct  register_count
        : boost::mpl::size_t< boost::is_floating_point<T>::value
                            ? BOOST_SIMD_VR_COUNT
                            : BOOST_SIMD_GPR_COUNT
                            >
  {};

  template<typename T, typename X>
  struct  register_count< native<T,X> >
        : boost::mpl::size_t<BOOST_SIMD_VR_COUNT>
  {};

  template<typename T, std::size_t N>
  struct  register_count< pack<T,N> >
        : register_count< typename pack<T,N>::data_type >
  {};

  template<typename Expr, typename Result>
  struct  register_count< expression<Expr,Result> >
        : register_count<Result>
  {};
} } }

#endif
