//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_PACK_ENUMERATE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_PACK_ENUMERATE_HPP_INCLUDED

#include <boost/simd/swar/functions/enumerate.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/sdk/simd/category.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_, tag::cpu_
                                    , (T)
                                    , ((target_ < ast_< T
                                                      , boost::simd::domain
                                                      >
                                                >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    BOOST_FORCEINLINE result_type operator()(T const&) const
    {
      return boost::simd::enumerate<typename result_type::data_type>();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_, tag::cpu_
                                    , (A0)(T)
                                    , (scalar_< arithmetic_<A0> >)
                                      ((target_ < ast_< T
                                                      , boost::simd::domain
                                                      >
                                                >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const&) const
    {
      return boost::simd::enumerate<typename result_type::data_type>(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_, tag::cpu_
                                    , (A0)(T)(X)
                                    , ((simd_< arithmetic_<A0>, X >))
                                      ((target_ < ast_< T
                                                      , boost::simd::domain
                                                      >
                                                >
                                      ))
                                    )
  {
    typedef typename T::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& ) const
    {
      return boost::simd::enumerate<typename result_type::data_type>(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_, tag::cpu_
                                    , (A0)(A1)(T)
                                    , (scalar_< arithmetic_<A0> >)
                                      (scalar_< arithmetic_<A1> >)
                                      ((target_ < ast_< T
                                                      , boost::simd::domain
                                                      >
                                                >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 const& a1, T const& ) const
    {
      return boost::simd::enumerate<typename result_type::data_type>(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_, tag::cpu_
                                    , (A0)(A1)(X)(T)
                                    , ((simd_< arithmetic_<A0>, X >))
                                      (generic_< arithmetic_<A1> >)
                                      ((target_ < ast_< T
                                                      , boost::simd::domain
                                                      >
                                                >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 const&, T const& ) const
    {
      return boost::simd::enumerate<typename result_type::data_type>(a0);
    }
  };
} } }

#endif
