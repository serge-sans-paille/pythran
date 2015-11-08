//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_ILOG2_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_ILOG2_HPP_INCLUDED

#include <boost/simd/bitwise/functions/ilog2.hpp>
#include <boost/simd/include/functions/scalar/clz.hpp>
#include <boost/simd/include/functions/scalar/exponent.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/mpl/less_equal.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ilog2_, tag::cpu_, (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        return exponent(a0);
      }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ilog2_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      BOOST_ASSERT_MSG( a0 > 0, "Logarithm is not defined for zero or negative values." );
      return result_type(sizeof(A0)*8-boost::simd::clz(a0)-1);
    }
  };

#if defined(BOOST_MSVC)
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::ilog2_, tag::cpu_
                            , (A0)
                            , (mpl::less_equal< mpl::sizeof_<A0>, mpl::size_t<4> >)
                            , (scalar_< integer_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      BOOST_ASSERT_MSG( a0 > 0, "Logarithm is not defined for zero or negative values." );
      __assume( a0 > 0 );
      unsigned long index;
      BOOST_VERIFY(::_BitScanReverse(&index, a0));
      return result_type(index);
    }
  };
#endif

#if defined(BOOST_MSVC) && defined(_WIN64)
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ilog2_, tag::cpu_
                            , (A0)
                            , (scalar_< ints64_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      BOOST_ASSERT_MSG( a0 > 0, "Logarithm is not defined for zero or negative values." );
      __assume( a0 > 0 );
      unsigned long index;
      BOOST_VERIFY(::_BitScanReverse64(&index, a0));
      return index;
    }
  };
#endif

} } }

#endif

