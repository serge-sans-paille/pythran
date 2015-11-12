//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_INSERT_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_INSERT_HPP_INCLUDED

#include <boost/simd/memory/functions/insert.hpp>
#include <boost/simd/include/functions/scalar/genmask.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/details/aliasing.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/sizeof.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::insert_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , (scalar_< arithmetic_<A0> >)
                                      ((simd_< arithmetic_<A1>, X >))
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 a0, A1& a1, A2 a2) const
    {
      typedef typename meta::scalar_of<A1>::type      stype;
      typedef typename meta::may_alias<stype>::type*  rtype;

      reinterpret_cast<rtype>(&a1.data_)[a2] = a0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::insert_
                                      , tag::cpu_
                                      , (A0)(A1)(A2)(X)
                                      , (mpl::equal_to
                                              < mpl::sizeof_<A1>
                                              , mpl::sizeof_<typename A1::type>
                                              >
                                        )
                                      , (scalar_< logical_<A0> >)
                                        ((simd_< logical_<A1>, X >))
                                        (scalar_< integer_<A2> >)
                                      )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1& a1, A2 a2) const
    {
      typedef typename meta::scalar_of<typename A1::type>::type stype;
      typedef typename meta::may_alias<stype>::type*            rtype;

      reinterpret_cast<rtype>(&a1.data_)[a2] = genmask(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::insert_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , (fusion_sequence_<A0>)
                                      ((simd_< fusion_sequence_<A1>, X >))
                                      (scalar_< integer_<A2> >)
                                    )
  {
    struct insert_fusion
    {
      insert_fusion(A0 const& a0_, A1& a1_, A2 a2_)
        : a0(a0_), a1(a1_), a2(a2_)
      {}

      template<int I> BOOST_FORCEINLINE void operator()() const
      {
        insert(fusion::at_c<I>(a0), fusion::at_c<I>(a1), a2);
      }

      A0 const& a0;
      A1& a1;
      A2 a2;

      private:
      insert_fusion& operator=(insert_fusion const&);
    };

    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1& a1, A2 const& a2) const
    {
      static const bool check =   fusion::result_of::size<A0>::value
                              ==  fusion::result_of::size<A1>::value;

      BOOST_MPL_ASSERT_MSG( check
                          , BOOST_SIMD_INSERT_FUSION_SEQUENCE_SIZE_MISMATCH
                          , (A0&, A1&)
                          );

      static const int N = fusion::result_of::size<A0>::type::value;
      meta::iterate<N>(insert_fusion(a0, a1, a2));
    }
  };
} } }

#endif
