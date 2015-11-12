//==============================================================================
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_STORAGE_SIZE_HPP_INCLUDED
#define NT2_CORE_SETTINGS_STORAGE_SIZE_HPP_INCLUDED

#include <nt2/sdk/parameters.hpp>
#include <nt2/core/settings/forward/size.hpp>
#include <nt2/core/settings/forward/storage_size.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <cstddef>

namespace nt2 { namespace tag
{
  struct storage_size_
  {
    template<class T>
    struct apply : boost::mpl::false_
    {};

    typedef nt2::storage_size_<-1> default_type;
  };

  template<std::ptrdiff_t Size>
  struct storage_size_::apply< nt2::storage_size_<Size> >
                      : boost::mpl::true_
  {};

  template<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D)>
  struct  storage_size_
        ::apply<nt2::of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,D)> >
        : boost::mpl::true_
  {};
} }

#endif
