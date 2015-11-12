//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SCALAR_ENUMERATE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SCALAR_ENUMERATE_HPP_INCLUDED

#include <boost/simd/swar/functions/enumerate.hpp>
#include <boost/simd/include/constants/zero.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_, tag::cpu_
                                    , (T)
                                    , (target_< scalar_< unspecified_<T> > >)
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(T const& ) const
    {
      return Zero<result_type>();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_, tag::cpu_
                                    , (A0)(T)
                                    , (scalar_< unspecified_<A0> >)
                                      (target_< scalar_< unspecified_<T> > >)
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(A0 const& a0, T const& ) const
    {
      return static_cast<result_type>(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_, tag::cpu_
                                    , (A0)(A1)(T)
                                    , (scalar_< arithmetic_<A0> >)
                                      (scalar_< arithmetic_<A1> >)
                                      (target_< scalar_< arithmetic_<T> > >)
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(A0 const& a0, A1 const&, T const& ) const
    {
      return static_cast<result_type>(a0);
    }
  };
} } }

#endif
