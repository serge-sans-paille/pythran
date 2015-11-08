//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_STORAGE_ORDER_HPP_INCLUDED
#define NT2_CORE_SETTINGS_STORAGE_ORDER_HPP_INCLUDED

#include <nt2/core/settings/forward/storage_order.hpp>

namespace nt2 { namespace tag
{
  struct storage_order_
  {
    template<class T>
    struct apply : boost::mpl::false_
    {};

    typedef nt2::column_major_ default_type;
  };

  template<>
  struct storage_order_::apply<nt2::row_major_>
                      : boost::mpl::true_
  {};

  template<>
  struct storage_order_::apply<nt2::column_major_>
                      : boost::mpl::true_
  {};
} }

#endif
