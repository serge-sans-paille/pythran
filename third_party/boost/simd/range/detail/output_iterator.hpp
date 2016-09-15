//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_DETAIL_OUTPUT_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_RANGE_DETAIL_OUTPUT_ITERATOR_HPP_INCLUDED

#include <boost/simd/function/store.hpp>
#include <boost/simd/pack.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/range/detail/output_iterator_base.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <iterator>

namespace boost { namespace simd { namespace detail
{
  template< typename Iterator
          , std::size_t C = boost::simd::cardinal_of
                            < pack< typename std::iterator_traits<Iterator>
                                                ::value_type
                                  >
                            >::value
          >
  struct  output_iterator
        : details::output_iterator_base
                  < Iterator
                  , C
                  , typename std::iterator_traits<Iterator>::value_type
                  , tag::store_
                  >
  {
    typedef details::output_iterator_base
                  < Iterator
                  , C
                  , typename std::iterator_traits<Iterator>::value_type
                  , tag::store_
                  >                                           parent;

    BOOST_FORCEINLINE output_iterator() : parent() {}
    BOOST_FORCEINLINE output_iterator( parent const& src ) : parent(src) {}
    explicit BOOST_FORCEINLINE output_iterator(Iterator p) : parent(p) {}
  };

  template<typename Iterator>
  BOOST_FORCEINLINE output_iterator<Iterator> output_begin(Iterator p)
  {
    return output_iterator<Iterator>(p);
  }

  template<std::size_t C, typename Iterator>
  BOOST_FORCEINLINE output_iterator<Iterator, C> output_begin(Iterator p)
  {
    return output_iterator<Iterator, C>(p);
  }

  template<typename Iterator>
  BOOST_FORCEINLINE output_iterator<Iterator> output_end(Iterator p)
  {
    return output_iterator<Iterator>(p);
  }

  template<std::size_t C, typename Iterator>
  BOOST_FORCEINLINE output_iterator<Iterator,C> output_end(Iterator p)
  {
    return output_iterator<Iterator, C>(p);
  }
} } }

#endif
