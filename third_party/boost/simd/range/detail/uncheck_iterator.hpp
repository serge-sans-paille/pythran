//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_DETAIL_UNCHECK_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_RANGE_DETAIL_UNCHECK_ITERATOR_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace details
{
  template<typename Iterator, typename Enable=void>
  struct unchecker
  {
    typedef Iterator type;

    static type call(Iterator i) { return i; }
  };

  template<typename Iterator>
  struct unchecker< Iterator
                  , typename  boost::enable_if_has_type<typename  Iterator::_Unchecked_type>::type
                  >
  {
    typedef typename Iterator::_Unchecked_type type;

    static type call(Iterator i) { return i._Unchecked(); }
  };
} } }

#endif
