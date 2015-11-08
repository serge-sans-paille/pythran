//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_FORWARD_SIZE_HPP_INCLUDED
#define NT2_CORE_SETTINGS_FORWARD_SIZE_HPP_INCLUDED

#include <cstddef>
#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace nt2
{
  //============================================================================
  // of_size_<D0,..,Dn> is a size value containing up to N dimensions.
  //============================================================================
  template< BOOST_PP_ENUM_BINARY_PARAMS ( NT2_MAX_DIMENSIONS
                                        , std::ptrdiff_t D
                                        , = std::ptrdiff_t(1) BOOST_PP_INTERCEPT
                                        )
          >
  struct of_size_;

  namespace tag
  {
    //==========================================================================
    /*!
     * Option tag for of_size_ options
     **/
    //==========================================================================
    struct of_size_;
  }
}

#endif
