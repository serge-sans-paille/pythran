//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_TRIBOOL_HPP_INCLUDED
#define NT2_SDK_META_TRIBOOL_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/logical.hpp>

namespace nt2
{
  namespace meta
  {
    struct indeterminate_
    {
      typedef indeterminate_ type;
    };

    typedef boost::mpl::true_ true_;
    typedef boost::mpl::false_ false_;

    template<bool C>
    struct indeterminate_false : indeterminate_ {};

    template<>
    struct indeterminate_false<false> : false_ {};

    template<bool C>
    struct indeterminate_true : indeterminate_ {};

    template<>
    struct indeterminate_true<true> : true_ {};
  }

  namespace details
  {
    template<class A, class B>
    struct and_ : boost::mpl::and_<A, B> {};

    template<class A>
    struct and_< A, meta::indeterminate_ > : meta::indeterminate_ {};

    template<class B>
    struct and_< meta::indeterminate_, B > : meta::indeterminate_ {};

    template <>
    struct and_< meta::indeterminate_, meta::indeterminate_ > : meta::indeterminate_ {};

    template<class A, class B>
    struct or_ : boost::mpl::or_<A, B> {};

    template<class A>
    struct or_< A, meta::indeterminate_ > : A {};

    template<class B>
    struct or_< meta::indeterminate_, B > : B {};

    template <>
    struct or_< meta::indeterminate_, meta::indeterminate_ > : meta::indeterminate_ {};

    template<class A>
    struct not_ : boost::mpl::not_<A> {};

    template<>
    struct not_< meta::indeterminate_ > : meta::indeterminate_ {};
  }

  namespace meta
  {
    template<class A, class B>
    struct and_ : details::and_<typename A::type, typename B::type> {};

    template<class A, class B>
    struct or_ : details::or_<typename A::type, typename B::type> {};

    template<class A>
    struct not_ : details::not_<typename A::type> {};
  }
}

#endif
