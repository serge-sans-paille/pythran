//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_IS_SEQUENCE_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_IS_SEQUENCE_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>

namespace nt2 { namespace details
{
  template<class A, class IsSeq=void>
  struct is_sequence : boost::mpl::false_
  {};

  template<class A>
  struct  is_sequence
          < A
          , typename  boost::dispatch::meta::
                      enable_if_type<typename A::const_iterator>::type
          > : boost::mpl::true_
  {};
} }

#endif
