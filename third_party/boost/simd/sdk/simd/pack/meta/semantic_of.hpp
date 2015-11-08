//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PACK_META_SEMANTIC_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_META_SEMANTIC_OF_HPP_INCLUDED

#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/simd/sdk/simd/pack/forward.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template< class Expression
          , class ResultType
          >
  struct semantic_of< simd::expression<Expression, ResultType> >
  {
    typedef ResultType type;
  };

  template< class Type
          , std::size_t Cardinal
          >
  struct semantic_of< simd::pack<Type, Cardinal> >
  {
    typedef typename simd::pack<Type, Cardinal>::data_type type;
  };

} } }

#endif
