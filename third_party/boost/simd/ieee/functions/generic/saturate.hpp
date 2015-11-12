//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_GENERIC_SATURATE_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_GENERIC_SATURATE_HPP_INCLUDED

#include <boost/simd/ieee/functions/saturate.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/simd/min.hpp>
#include <boost/simd/include/functions/simd/max.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::saturate_, tag::cpu_
                                       , (A0)(T)
                                       , (is_same<typename meta::scalar_of<typename T::type>::type, typename meta::scalar_of<A0>::type>)
                                       , (generic_< arithmetic_<A0> >)
                                         (target_< generic_<arithmetic_<T> > >)
                                       )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& ) const
    {
      return a0;
    }
  };

  // any->any, only works if target is strictly smaller
  // FIXME: is Valmax<target_t>/Valmin<target_t> representable with A0 if floating-point?
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::saturate_, tag::cpu_
                                    , (A0)(T)
                                    , (generic_< unspecified_<A0> >)
                                      (target_< generic_< arithmetic_<T> > >)
                                    )
  {
    typedef A0 result_type;
    typedef typename meta::scalar_of<typename T::type>::type target_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& ) const
    {
      const A0 vma = splat<A0>(Inf<target_t>());
      const A0 vmi = splat<A0>(Minf<target_t>());
      return min(vma, max(vmi, a0));
    }
  };

  // unsigned->any, only works if target is smaller or equal
  // FIXME: is Valmax<target_t> representable with A0 if floating-point?
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::saturate_, tag::cpu_
                                    , (A0)(T)
                                    , (generic_<unsigned_<A0> >)
                                      (target_< generic_< arithmetic_<T> > >)
                                    )
  {
    typedef A0 result_type;
    typedef typename meta::scalar_of<typename T::type>::type target_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& ) const
    {
      const A0 vma = splat<A0>(Valmax<target_t>());
      return min(vma, a0);
    }
  };

  // if target is greater or equal and signed->unsigned, just need to check if negative
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::saturate_, tag::cpu_
                                       , (A0)(T)
                                       , (mpl::greater_equal< mpl::sizeof_<typename meta::scalar_of<typename T::type>::type>, mpl::sizeof_<typename meta::scalar_of<A0>::type> >)
                                       , (generic_< int_<A0> >)
                                         (target_< generic_< uint_<T> > >)
                                       )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& ) const
    {
      return max(Zero<A0>(), a0);
    }
  };

  // if target is strictly greater, nothing to saturate
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::saturate_, tag::cpu_
                                       , (A0)(T)
                                       , (mpl::greater< mpl::sizeof_<typename meta::scalar_of<typename T::type>::type>, mpl::sizeof_<typename meta::scalar_of<A0>::type> >)
                                       , (generic_< integer_<A0> >)
                                         (target_< generic_< arithmetic_<T> > >)
                                       )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& ) const
    {
      return a0;
    }
  };
} } }

#endif
