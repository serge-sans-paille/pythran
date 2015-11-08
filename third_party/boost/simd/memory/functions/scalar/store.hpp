//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SCALAR_STORE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SCALAR_STORE_HPP_INCLUDED

#include <boost/simd/memory/functions/store.hpp>
#include <boost/simd/sdk/functor/preprocessor/dispatch.hpp>
#include <boost/simd/memory/functions/details/store.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/simd/sdk/simd/meta/is_native.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - Scalar store and store are equivalent
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::store_
                                    , tag::cpu_
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

  /// INTERNAL ONLY - Scalar store and store are equivalent
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::store_
                                    , tag::cpu_
                                    , (A0)(A1)
                                    , (unspecified_<A0>)
                                      (iterator_< unspecified_<A1> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1) const
    {
      *a1 = a0;
    }
  };

  /// INTERNAL ONLY - scalar masked store
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::store_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (unspecified_<A0>)
                                      (iterator_< unspecified_<A1> >)
                                      (scalar_< fundamental_<A2> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1, A2 const& a2) const
    {
      if (a2)
        *a1 = a0;
    }
  };

  /// INTERNAL ONLY - Scalar masked offset store
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::store_
                                    , tag::cpu_
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

  /// INTERNAL ONLY - Fusion sequence store with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::store_
                                    , tag::cpu_
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
      meta::iterate < fusion::result_of::size<A1>::type::value>
                    ( details::storer < boost::simd::
                                        tag::store_(A0, A1, A2)
                                      >(a0, a1, a2)
                    );
    }
  };

  /// INTERNAL ONLY - Scalar store and store are equivalent
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::store_
                                    , tag::cpu_
                                    , (A0)(A1)
                                    , (fusion_sequence_<A0>)
                                      (fusion_sequence_<A1>)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 const& a1) const
    {
      meta::iterate < fusion::result_of::size<A1>::type::value>
                    ( details::storer < boost::simd::
                                        tag::store_(A0, A1)
                                      >(a0, a1)
                    );
    }
  };

  /// Handles store( seq, seq'*)
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::store_
                                      , tag::cpu_
                                      , (A0)(A1)
                                      , (mpl::not_< simd::meta::is_native<A0> >)
                                      , (fusion_sequence_<A0>)
                                        (iterator_< fusion_sequence_<A1> >)
                                      )
  {
    typedef void result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      static const int N = fusion::result_of::size<A0>::type::value;
      meta::iterate<N>( details::extractor<A0,A1>(a0,a1) );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::store_
                                      , tag::cpu_
                                      , (A0)(A1)(A2)
                                      , (mpl::not_< simd::meta::is_native<A0> >)
                                      , (fusion_sequence_<A0>)
                                        (iterator_< fusion_sequence_<A1> >)
                                        (scalar_< integer_<A2> >)
                                      )
  {
    typedef void result_type;
    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      static const int N = fusion::result_of::size<A0>::type::value;
      meta::iterate<N>( details::extractor<A0,A1,A2>(a0,a1,a2) );
    }
  };
} } }

#endif
