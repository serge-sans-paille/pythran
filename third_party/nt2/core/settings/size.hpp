//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_SIZE_HPP_INCLUDED
#define NT2_CORE_SETTINGS_SIZE_HPP_INCLUDED

#include <nt2/core/utility/of_size/predef.hpp>
#include <nt2/sdk/parameters.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <cstddef>

namespace nt2 { namespace tag
{
  //==========================================================================
  // Make options extracting the ID from id_
  //==========================================================================
  struct of_size_
  {
    template<class T>
    struct apply : boost::mpl::false_
    {};

    typedef nt2::of_size_max default_type;
  };

  template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D)>
  struct  of_size_
        ::apply< nt2::of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,D)> >
          : boost::mpl::true_
  {};
} }


#endif
