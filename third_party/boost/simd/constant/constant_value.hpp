//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANT_VALUE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANT_VALUE_HPP_INCLUDED

#include <boost/dispatch/meta/property_of.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace meta
{
  template<class Tag, class T>
  struct constant_value
       : Tag::template apply<typename boost::dispatch::meta::
                             property_of<typename boost::dispatch::meta::
                                         scalar_of<T>::type
                                        >::type
                            >
  {
  };
} } }

#endif
