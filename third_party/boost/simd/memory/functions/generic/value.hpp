//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_GENERIC_VALUE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_GENERIC_VALUE_HPP_INCLUDED

#include <boost/simd/memory/functions/value.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/mpl.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::value_, tag::cpu_
                                    , (A0)
                                    , (unspecified_<A0>)
                                    )
  {
    template<class Sig> struct result;

    template<class This, class T>
    struct result<This(T)> : boost::add_reference<T>
    {};

    template<class T> BOOST_FORCEINLINE T& operator()(T& a0) const
    {

      return a0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::value_, tag::cpu_
                                    , (A0)
                                    , (scalar_< logical_<A0> >)
                                    )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0.value();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::value_, tag::cpu_
                                    , (A0)
                                    , (mpl_integral_< unspecified_<A0> >)
                                    )
  {
    typedef typename A0::value_type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return A0::value;
    }
  };
} } }

#endif
