//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_DETAILS_UNCHECK_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_DETAILS_UNCHECK_ITERATOR_HPP_INCLUDED

#include <boost/dispatch/meta/enable_if_type.hpp>
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
                  , typename  boost::dispatch::meta::
                              enable_if_type< typename  Iterator
                                                        ::_Unchecked_type
                                            >::type
                  >
  {
    typedef typename Iterator::_Unchecked_type type;

    static type call(Iterator i) { return i._Unchecked(); }
  };


} } }

#endif
