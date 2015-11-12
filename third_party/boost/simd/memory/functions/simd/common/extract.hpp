//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_EXTRACT_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_EXTRACT_HPP_INCLUDED

#include <boost/simd/memory/functions/extract.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/details/aliasing.hpp>
#include <boost/simd/sdk/simd/native_tuple.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/include/copy.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/sizeof.hpp>

#if defined(__INTEL_COMPILER)
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , tag::cpu_
                                    , (A0)(A1)(X)
                                    , ((simd_< arithmetic_<A0>, X >))
                                      (scalar_< integer_<A1> >)
                                    )
  {
    typedef typename meta::scalar_of<A0>::type   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1) const
    {
      return reinterpret_cast<typename meta::may_alias<result_type const>::type*>(&a0.data_)[a1];
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::extract_
                                      , tag::cpu_
                                      , (A0)(A1)(X)
                                      , (mpl::equal_to
                                              < mpl::sizeof_<A0>
                                              , mpl::sizeof_<typename A0::type>
                                              >
                                        )
                                      , ((simd_< logical_<A0>, X >))
                                        (scalar_< integer_<A1> >)
                                      )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1) const
    {
      #if defined(__GNUC__)
        typedef typename A0::type::value_type stype;
        return result_type(reinterpret_cast<typename meta::may_alias<stype const>::type*>(&a0.data_)[a1]);
      #else
        return result_type(extract(bitwise_cast<typename A0::type>(a0), a1));
      #endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , tag::cpu_
                                    , (A0)(A1)(X)
                                    , ((simd_< fusion_sequence_<A0>, X >))
                                      (scalar_< integer_<A1> >)
                                    )
  {
    struct extract_fusion
    {
      extract_fusion(A1 a1_) : a1(a1_) {}

      template<class Sig> struct result;

      template<class This, class T>
      struct  result<This(T)>
            : dispatch::meta::strip<typename meta::scalar_of<T>::type>
      {};

      template<class T>
      typename meta::scalar_of<T>::type operator()(T const& a0) const
      {
        return extract(a0, a1);
      }

      A1 a1;
    };

    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1) const
    {
      return simd::as_tuple<result_type>(a0, extract_fusion(a1));
    }
  };
} } }

#endif
