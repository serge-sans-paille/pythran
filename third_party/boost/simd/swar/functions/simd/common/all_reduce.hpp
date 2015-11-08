//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_ALL_REDUCE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_ALL_REDUCE_HPP_INCLUDED

#include <boost/simd/swar/functions/all_reduce.hpp>
#include <boost/simd/swar/functions/details/butterfly.hpp>
#include <boost/simd/include/functions/insert.hpp>
#include <boost/simd/include/functions/extract.hpp>
#include <boost/simd/sdk/simd/category.hpp>

namespace boost { namespace simd { namespace ext
{
  // Regular, generic SIMD version
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::all_reduce_
                                    , boost::simd::tag::simd_
                                    , (Tag)(A0)(X)
                                    , ((simd_< unspecified_<A0>, X >))
                                      ((target_< unspecified_<Tag> >))
                                    )
  {
    typedef typename Tag::type                              base;
    typedef typename dispatch::meta::call<base( A0 const&
                                              , A0 const&
                                              )>::type      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, Tag const&) const
    {
      typedef typename boost::simd::meta::cardinal_of<result_type>::type card;
      details::butterfly<card::value/2,result_type> callee;
      return callee(base(),a0);
    }
  };

  // SIMD Emulation version
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::all_reduce_
                                    , tag::cpu_
                                    , (Tag)(A0)(X)
                                    , ((simd_< unspecified_<A0>, X >))
                                      ((target_< unspecified_<Tag> >))
                                    )
  {
    typedef typename Tag::type                              base;
    typedef typename dispatch::meta::call<base( A0 const&
                                              , A0 const&
                                              )>::type      result_type;
    typedef typename meta::scalar_of<result_type>::type     stype;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, Tag const&) const
    {
      result_type that;
      boost::dispatch::functor<base> callee;

      // initialize the seed
      that[0] = callee(a0[0],a0[1]);

      // Roll over a loop to save cycles
      for(std::size_t i=2;i<A0::static_size;++i)
        that[0] = callee( static_cast<stype>(that[0]), a0[i] );

      //  Splat manually
      for(std::size_t i=1;i<A0::static_size;++i)
        that[i] = static_cast<stype>(that[0]);

      return that;
    }
  };
} } }

#endif
