//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_META_VECTOR_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_META_VECTOR_OF_HPP_INCLUDED

#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/details/max_value.hpp>
#include <boost/simd/sdk/meta/cardinal_as.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace simd { namespace meta
{
  template<class T, std::size_t Card>
  struct vector_of;
}

namespace details
{
  template<class T, std::size_t Card, bool Sequence = false, class Enable = void>
  struct vector_of2
  {
    typedef typename dispatch::meta::primitive_of<T>::type base_t;
    typedef simd::native<T, tag::simd_emulation_< sizeof(base_t)*Card > > type;
  };

  template<class T, std::size_t Card>
  struct vector_of2<T, Card, true>
  {
    typedef typename max_value<T, mpl::sizeof_<mpl::_> >::type mT;
    typedef typename meta::vector_of<mT, Card>::type nT;
    typedef simd::native<T, typename nT::extension_type> type;
  };

#ifdef BOOST_SIMD_DETECTED
  /* We use boost::mpl::sizeof_ rather than sizeof because MSVC has trouble
   * with sizeof of dependent names in SFINAE contexts */
  #define BOOST_SIMD_LOCAL(z,d,r)                                                                  \
  template<class T,std::size_t Card>                                                               \
  struct vector_of2< T, Card, false                                                                \
                   , typename boost::                                                              \
                     enable_if_c < meta::cardinal_as<T, r>::value == Card >::type                  \
                   >                                                                               \
  {                                                                                                \
    typedef simd::native<T,r> type;                                                                \
  };                                                                                               \
  /**/
  BOOST_PP_SEQ_FOR_EACH(BOOST_SIMD_LOCAL,~,BOOST_SIMD_TAG_SEQ)
  #undef BOOST_SIMD_LOCAL
#endif

  template<class T, std::size_t Card>
  struct vector_of : vector_of2<T, Card, fusion::traits::is_sequence<T>::value>
  {
  };

  // vectors must have at least 2 elements, vectors of 1 elements are scalar values
  template<class T>
  struct vector_of<T, 1u>
  {
    typedef T type;
  };
} } }

namespace boost { namespace simd { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // vector_of<T,N> computes the proper type for pack of N elements of types T
  // Either <T,N> maps onto a SIMD types, either to array<T,N>
  //////////////////////////////////////////////////////////////////////////////
  template<class T, std::size_t Card>
  struct vector_of
   : details::vector_of<T, Card>
  {
  };

  template<class T, std::size_t Card>
  struct vector_of<T&, Card>
  {
    typedef typename meta::vector_of<T, Card>::type& type;
  };

  template<class T, std::size_t Card>
  struct vector_of<T const, Card>
  {
    typedef typename meta::vector_of<T, Card>::type const type;
  };

} } }

#endif
