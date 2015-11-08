//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_AS_PACK_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_AS_PACK_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack.hpp>

namespace boost { namespace simd { namespace meta
{
  /*!
    @brief Generic pack type generator

    Generates the proper pack or scalar type of a given @c Cardinal.

    @par Semantic:

    For any given type @c Type and cardinal @c Cardinal, the following code:

    @code
    typedef as_pack<Type,Cardinal>::type r;
    @endcode

    is equivalent to:

    @code
    typedef pack<Type,Cardinal> r;
    @endcode

    if @c Cardinal is greater than one and to:

    @code
    typedef Type r;
    @endcode

    if @c Cardinal is equal to 1.

    @tparam Type     Type of the pack to be generated
    @tparam Cardinal Number of element in the pack to be built
  **/
  template<typename Type, std::size_t Cardinal>
  struct as_pack
  {
    typedef boost::simd::pack<Type,Cardinal> type;
  };

  /// INTERNAL ONLY
  template<typename Type>
  struct as_pack<Type,1u>
  {
    typedef Type type;
  };
} } }

#endif
