//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PACK_META_CARDINAL_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_META_CARDINAL_OF_HPP_INCLUDED

#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/mpl/size_t.hpp>

namespace boost { namespace simd { namespace meta
{
  template< class Type
          , std::size_t Cardinal
          >
  struct cardinal_of< boost::simd::pack<Type, Cardinal> >
    : mpl::size_t<Cardinal>
  {
  };

  // cardinal of an expression of pack is the cardinal of its ResultType
  template< class Expression, class ResultType>
  struct  cardinal_of< boost::simd::expression<Expression,ResultType> >
        : cardinal_of<ResultType>
  {
  };
} } }

#endif
