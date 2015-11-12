//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SCALAR_ALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SCALAR_ALIGNED_STORE_HPP_INCLUDED

#include <boost/simd/memory/functions/aligned_store.hpp>
#include <boost/simd/memory/functions/scalar/store.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/mpl.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - masked Regular scalar store with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_, tag::cpu_
                                    , (A0)(A1)(A2)(A3)
                                    , (unspecified_<A0>)
                                      (iterator_< unspecified_<A1> >)
                                      (scalar_< integer_<A2> >)
                                      (scalar_< fundamental_<A3> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 a1, A2 a2, A3 const& a3) const
    {
      if (a3)
        *(a1+a2) = a0;
    }
  };

  /// INTERNAL ONLY - Regular scalar store with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_, tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (unspecified_<A0>)
                                      (iterator_< unspecified_<A1> >)
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 a1, A2 a2) const
    {
      *(a1+a2) = a0;
    }
  };

  /// INTERNAL ONLY - mask Regular scalar store without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_, tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (unspecified_<A0>)
                                      (iterator_< unspecified_<A1> >)
                                      (scalar_< fundamental_<A2> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 a1, A2 const& a2) const
    {
      if (a2)
        *a1 = a0;
    }
  };

  /// INTERNAL ONLY - Regular scalar store without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_, tag::cpu_
                                    , (A0)(A1)
                                    , (unspecified_<A0>)
                                      (iterator_< unspecified_<A1> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 a1) const
    {
      *a1 = a0;
    }
  };

  /// INTERNAL ONLY - Fusion sequence store with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_, tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (fusion_sequence_<A0>)
                                      (fusion_sequence_<A1>)
                                      (generic_< integer_<A2> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 const& a1, A2 a2) const
    {
      boost::simd::store(a0,a1,a2);
    }
  };

  /// INTERNAL ONLY - Fusion sequence store without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_, tag::cpu_
                                    , (A0)(A1)
                                    , (fusion_sequence_<A0>)
                                      (fusion_sequence_<A1>)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 const& a1) const
    {
      boost::simd::store(a0,a1);
    }
  };
} } }

#endif
