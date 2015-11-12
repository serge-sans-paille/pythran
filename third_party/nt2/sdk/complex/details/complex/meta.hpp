//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_COMPLEX_DETAILS_COMPLEX_META_HPP_INCLUDED
#define NT2_SDK_COMPLEX_DETAILS_COMPLEX_META_HPP_INCLUDED

#include <nt2/sdk/complex/details/complex/fusion_adapt.hpp>
#include <nt2/sdk/complex/hierarchy.hpp>
#include <boost/dispatch/meta/property_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/type_traits/has_trivial_copy.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct model_of< std::complex<T> >
  {
    struct type
    {
      template<class U> struct apply
      {
        typedef std::complex<U> type;
      };
    };
  };

  template<class T, class Origin>
  struct property_of< std::complex<T>, Origin >
  {
    typedef complex_< typename property_of<T, Origin>::type > type;
  };

  template<class T, class Origin>
  struct hierarchy_of< std::complex<T>, Origin >
  {
    typedef typename remove_const<Origin>::type stripped;
    typedef typename mpl::if_< is_same< std::complex<T>, stripped >, stripped, Origin >::type origin_;
    typedef scalar_< complex_< typename property_of<T, origin_>::type > > type;
  };

  template<class T>
  struct scalar_of< std::complex<T> >
  {
    typedef std::complex<T> type;
  };

  template<class T>
  struct value_of< std::complex<T> >
  {
    typedef T type;
  };

} } }

namespace boost { namespace simd
{
  template<class T>
  struct is_value;

  template<class T>
  struct is_value< std::complex<T> >
       : boost::mpl::true_
  {
  };
} }

namespace boost
{
  template<class T>
  struct has_trivial_copy< std::complex<T> >
       : boost::mpl::true_
  {
  };

  template<class T>
  struct has_trivial_default_constructor< std::complex<T> >
       : boost::mpl::true_
  {
  };

  template<class T>
  struct has_trivial_destructor< std::complex<T> >
       : boost::mpl::true_
  {
  };
}

#endif
