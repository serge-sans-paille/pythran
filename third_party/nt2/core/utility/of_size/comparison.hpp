//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_OF_SIZE_COMPARISON_HPP_INCLUDED
#define NT2_CORE_UTILITY_OF_SIZE_COMPARISON_HPP_INCLUDED

#include <nt2/core/utility/fusion.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>


namespace nt2
{
  //============================================================================
  // Equality comparison for of_size_
  //============================================================================
  template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D1)
          , BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D2)>
  bool operator==( of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D1)> const& a0
                 , of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D2)> const& a1
                 )
  {
    static const std::size_t
    a = of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D1)>::static_size;

    static const std::size_t
    b = of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D2)>::static_size;

    return details::compare_equal(a0,a1,boost::mpl::size_t<(a < b) ? b : a>());
  }

  //============================================================================
  // Inequality comparison for of_size_
  //============================================================================
  template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D1)
          , BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D2)>
  bool operator!=( of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D1)> const& a0
                 , of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D2)> const& a1
                 )
  {
    static const std::size_t
    a = of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D1)>::static_size;

    static const std::size_t
    b = of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D2)>::static_size;

    return details::compare_not_equal(a0,a1,boost::mpl::size_t<(a < b) ? b : a>());
  }
}

#endif
