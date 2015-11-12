//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_COMBINE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_COMBINE_HPP_INCLUDED

#include <boost/simd/swar/functions/combine.hpp>
#include <boost/simd/include/functions/simd/insert.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/meta/is_bitwise_logical.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/dispatch/meta/fusion.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::combine_
                                    , tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<unspecified_<A0>,X>))
                                      ((simd_<unspecified_<A0>,X>))
                                    )
  {
    typedef typename  meta::vector_of < typename A0::value_type
                                      , A0::static_size * 2
                                      >::type                     result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      result_type that;

      for(size_t i=0; i!=A0::static_size; ++i)
      {
        that[i]                 = a0[i];
        that[i+A0::static_size] = a1[i];
      }

      return that;
    }
  };

  // combine logical by combining internal representation
  // Only valid if native<T,X> and native<logical<T><X> has same size
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::combine_
                                    , tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<logical_<A0>,X>))
                                      ((simd_<logical_<A0>,X>))
                                    )
  {
    typedef typename  meta::vector_of < typename A0::value_type
                                      , A0::static_size * 2
                                      >::type                     result_type;


    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      return eval( a0, a1
                 , boost::mpl::bool_<   simd::meta::is_bitwise_logical<A0>::value
                                    &&  simd::meta::is_bitwise_logical<result_type>::value
                                    >()
                 );
    }

    BOOST_FORCEINLINE result_type eval(A0 const& a0, A0 const& a1, boost::mpl::true_ const&) const
    {
      typedef typename A0::type type;
      return bitwise_cast<result_type>( boost::simd::combine( bitwise_cast<type>(a0)
                                                            , bitwise_cast<type>(a1)
                                                            )
                                      );
    }

    BOOST_FORCEINLINE result_type eval(A0 const& a0, A0 const& a1, boost::mpl::false_ const&) const
    {
      result_type that;
      for(size_t i=0; i!=A0::static_size; ++i)
      {
        that[i]                 = a0[i];
        that[i+A0::static_size] = a1[i];
      }

      return that;
    }
  };

  // combine fusion sequence iteratively
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::combine_
                                    , tag::cpu_
                                    , (A0)(X)
                                    , ((simd_< fusion_sequence_<A0>, X>))
                                      ((simd_< fusion_sequence_<A0>, X>))
                                    )
  {
    typedef typename  meta::vector_of < typename A0::value_type
                                      , A0::static_size * 2
                                      >::type                     result_type;

    struct impl
    {
      BOOST_FORCEINLINE impl(result_type& that_, A0 const& a0_, A0 const& a1_)
                        : that(that_), a0(a0_), a1(a1_)
      {
      }

      template<int I> BOOST_FORCEINLINE void operator()() const
      {
        boost::fusion::at_c<I>(that) = boost::simd::combine ( boost::fusion::at_c<I>(a0)
                                                            , boost::fusion::at_c<I>(a1)
                                                            );
      }

      result_type& that;
      A0 const& a0;
      A0 const& a1;

      private:
      impl& operator=(impl const&);
    };

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      static const int N = fusion::result_of::size<A0>::type::value;
      result_type that;
      meta::iterate<N>(impl(that, a0, a1));
      return that;
    }
  };
} } }

#endif
