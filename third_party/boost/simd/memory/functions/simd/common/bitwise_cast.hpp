//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_BITWISE_CAST_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_BITWISE_CAST_HPP_INCLUDED

#include <boost/simd/memory/functions/bitwise_cast.hpp>
#include <boost/simd/sdk/details/aliasing.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace simd { namespace ext
{
#ifndef BOOST_SIMD_NO_STRICT_ALIASING

  // logical <-> non-logical are normally the same type inside (or castable to it)
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_cast_, tag::cpu_
                                   , (A0)(A1)(X)
                                   , ((simd_< logical_<A0>, X >))
                                     ((target_< simd_< unspecified_<A1>, X > >))
                                   )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      typename A0::type arith0 = (typename A0::type::native_type)a0();
      return bitwise_cast<result_type>(arith0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_cast_, tag::cpu_
                                   , (A0)(A1)(X)
                                   , ((simd_< unspecified_<A0>, X >))
                                     ((target_< simd_< logical_<A1>, X > >))
                                   )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return (typename result_type::native_type)bitwise_cast<typename result_type::type>(a0)();
    }
  };

  // the next two specializations apparently allow to generate better code with MSVC
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::bitwise_cast_, tag::cpu_
                                      , (A0)(A1)(X)
                                      , (is_same<typename A0::type, typename A1::type>)
                                      , ((simd_< logical_<A0>, X >))
                                        ((target_< simd_< arithmetic_<A1>, X > >))
                                      )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return (typename A1::type::native_type)a0();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::bitwise_cast_, tag::cpu_
                                      , (A0)(A1)(X)
                                      , (is_same<A0, typename A1::type::type>)
                                      , ((simd_< arithmetic_<A0>, X >))
                                        ((target_< simd_< logical_<A1>, X > >))
                                      )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return (typename A1::type::native_type)a0();
    }
  };

  // logical<->logical, call bitwise_cast three times
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_cast_, tag::cpu_
                                   , (A0)(A1)(X)
                                   , ((simd_< logical_<A0>, X >))
                                     ((target_< simd_< logical_<A1>, X > >))
                                   )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return bitwise_cast<result_type>(bitwise_cast<typename result_type::type>(bitwise_cast<typename A0::type>(a0)));
    }
  };

  // the different arithmetic types on the same extension are usually aliasable
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_cast_, tag::cpu_
                                   , (A0)(A1)(X)
                                   , ((simd_< arithmetic_<A0>, X >))
                                     ((target_< simd_< arithmetic_<A1>, X > >))
                                   )
  {
    typedef typename A1::type result_type;

    BOOST_MPL_ASSERT_MSG
    ( (sizeof(A0) == sizeof(typename A1::type))
    , BOOST_SIMD_TARGET_IS_NOT_SAME_SIZE_AS_SOURCE_IN_BITWISE_CAST
    , (A0&,typename A1::type&)
    );

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      //return (typename result_type::native_type)a0();
      return reinterpret_cast<typename result_type::native_type const&>(a0());
    }
  };

#endif
} } }

#endif
