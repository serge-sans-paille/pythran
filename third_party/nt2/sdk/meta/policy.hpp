//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_POLICY_HPP_INCLUDED
#define NT2_SDK_META_POLICY_HPP_INCLUDED

#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2
{
  template<typename Option>
  struct policy : boost::dispatch::meta::unspecified_< policy<Option> >
  {
    BOOST_FORCEINLINE policy() {}

    typedef boost::dispatch::meta::unspecified_< policy<Option> > parent;
    typedef Option                                                option_type;

    option_type operator()() const { return option_type(); }
  };
}

#endif
