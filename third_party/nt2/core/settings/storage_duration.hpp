//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_STORAGE_DURATION_HPP_INCLUDED
#define NT2_CORE_SETTINGS_STORAGE_DURATION_HPP_INCLUDED

#include <nt2/sdk/parameters.hpp>
#include <nt2/core/settings/forward/size.hpp>
#include <nt2/core/settings/forward/storage_duration.hpp>
#include <nt2/core/settings/forward/storage_size.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <cstddef>


namespace nt2 { namespace tag
{
  struct storage_duration_
  {
    template<class T>
    struct apply : boost::mpl::false_
    {};

    typedef nt2::dynamic_ default_type;
  };

  template<>
  struct storage_duration_::apply<nt2::dynamic_>
                          : boost::mpl::true_
  {};

  template<>
  struct storage_duration_::apply<nt2::automatic_>
                          : boost::mpl::true_
  {};

  template<std::ptrdiff_t Size>
  struct storage_duration_::apply< nt2::storage_size_<Size> >
                           : boost::mpl::true_
  {};

  template<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D)>
  struct  storage_duration_
        ::apply<nt2::of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,D)> >
        : boost::mpl::true_
  {};
} }

#include <nt2/core/settings/details/storage_duration.hpp>

#endif
