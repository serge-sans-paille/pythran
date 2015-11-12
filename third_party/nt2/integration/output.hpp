//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTEGRATION_OUTPUT_HPP_INCLUDED
#define NT2_INTEGRATION_OUTPUT_HPP_INCLUDED

#include <cstddef>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>

namespace nt2 { namespace integration
{
  template<typename T, typename R> struct output
  {
    T            integrals;
    R               errors;
    std::size_t eval_count;
    bool        successful;
    size_t         warning;
  };
} }

BOOST_FUSION_ADAPT_TPL_STRUCT
(
  (T)(R),
  (nt2::integration::output)(T)(R),
  (T          , integrals)
  (R          , errors)
  (std::size_t, eval_count)
  (bool       , successful)
  (size_t     , warning)
);

#endif



