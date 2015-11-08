//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_IS_COLON_HPP_INCLUDED
#define NT2_SDK_META_IS_COLON_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/proto/traits.hpp>
#include <boost/utility/enable_if.hpp>

namespace nt2
{
  namespace container { struct colon_; }

  namespace meta
  {
    template<class T, class Enable = void>
    struct is_colon
      : boost::mpl::false_
    {
    };

    template<class T>
    struct is_colon<T, typename boost::enable_if_c< boost::proto::arity_of<T>::value == 0 >::type>
      : boost::
        is_same< typename boost::dispatch::meta::
                 strip< typename boost::proto::result_of::
                        value<T>::type
                      >::type
               , container::colon_
               >
    {
    };
  }
}

#endif
