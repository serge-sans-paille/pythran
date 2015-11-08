//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_PERMUTED_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_PERMUTED_HPP_INCLUDED

namespace boost { namespace simd { namespace details
{
  /*
    permuted computes a value of a single shuffle pattern idnex
  */
  template<typename P, int I, int C>
  struct permuted : boost::mpl::apply < P
                                      , boost::mpl::int_<I>
                                      , boost::mpl::int_<C>
                                      >::type
  {};
} } }

#endif
