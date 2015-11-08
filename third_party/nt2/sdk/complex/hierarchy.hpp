//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_COMPLEX_HIERARCHY_HPP_INCLUDED
#define NT2_SDK_COMPLEX_HIERARCHY_HPP_INCLUDED

#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/property_of.hpp>
#include <boost/dispatch/meta/fusion.hpp>
#include <nt2/sdk/complex/meta/real_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct complex_ : complex_<typename T::parent>
  {
    typedef complex_<typename T::parent>  parent;
  };

  template<class T>
  struct complex_< unspecified_<T> > : fusion_sequence_<T>
  {
    typedef fusion_sequence_<T> parent;
  };

  template<class T>
  struct dry_ : dry_<typename T::parent>
  {
    typedef dry_<typename T::parent>  parent;
  };

  template<class T>
  struct dry_< unspecified_<T> > : complex_< typename property_of<typename nt2::meta::real_of<T>::type, T>::type >
  {
    typedef complex_< typename property_of<typename nt2::meta::real_of<T>::type, T>::type > parent;
  };

} } }

namespace nt2 { namespace ext
{
  using boost::dispatch::meta::complex_;
  using boost::dispatch::meta::dry_;
} }

#endif
