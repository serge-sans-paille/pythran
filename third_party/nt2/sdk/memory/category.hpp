//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_CATEGORY_HPP_INCLUDED
#define NT2_SDK_MEMORY_CATEGORY_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/dispatch/meta/property_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  /*!
    @brief Container hierarchy

    A Container hierarchy is computed from the original type T anc
    contains informations about the actual container semantic and its
    settings.
  **/
  template<typename Kind, typename T, typename Settings>
  struct container_ : container_<Kind, typename T::parent, Settings>
  {
    typedef container_<Kind, typename T::parent, Settings> parent;
  };

  /// INTERNAL ONLY
  template<typename Kind, typename T, typename Settings>
  struct  container_< Kind, unspecified_<T>, Settings >
        : generic_< typename property_of<T>::type >
  {
    typedef generic_< typename property_of<T>::type > parent;
  };
} } }

namespace nt2 { namespace ext
{
  using boost::dispatch::meta::container_;
} }

#endif
