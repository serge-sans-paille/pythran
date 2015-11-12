//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_BUTTERFLY_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_BUTTERFLY_HPP_INCLUDED

#include <boost/simd/include/functions/simd/shuffle.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/mpl/int.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace details
{
  // This meta-permutation implements the butterfly pattern required
  // for the log-tree based reduction algorithm.
  //
  // V is a vector of cardinal 4 :          [ v0 | v1 | v2 | v3 ]
  // The log-tree reduction will require :  [ v2 | v3 | v0 | v1 ]
  // and :                                  [ v3 | v2 | v1 | v0 ]
  //
  // Basically this requires permuting cardinal/2^n value at each iteration
  // stopping when only 1 element is left to be permuted.
  template<int Step> struct butterfly_perm
  {
    template<typename Index, typename Cardinal>
    struct  apply : boost::mpl::int_< (Index::value >= Step)
                                    ? Index::value-Step
                                    : Index::value+Step
                                    >
    {};
  };

  template<int Step, typename Type>
  struct butterfly
  {
    template<typename Op, typename V>
    BOOST_FORCEINLINE Type operator()(Op op, V const& a0) const
    {
      typename dispatch::meta::dispatch_call<Op(V const&,V const&)>::type f;
      butterfly<Step/2, Type> next;

      return next( op, f(a0, boost::simd::shuffle< butterfly_perm<Step> >(a0)) );
    }
  };

  template<typename Type>
  struct butterfly<1,Type>
  {
    template<typename Op, typename V>
    BOOST_FORCEINLINE Type operator()(Op, V const& a0) const
    {
      typename dispatch::meta::dispatch_call<Op(V const&,V const&)>::type f;
      return f(boost::simd::shuffle< butterfly_perm<1> >(a0),a0);
    }
  };
} } }

#endif
