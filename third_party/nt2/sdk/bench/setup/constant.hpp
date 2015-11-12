//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_SETUP_CONSTANT_HPP_INCLUDED
#define NT2_SDK_BENCH_SETUP_CONSTANT_HPP_INCLUDED

#include <nt2/sdk/bench/setup/arithmetic.hpp>

namespace nt2 { namespace bench
{
  /*!
    @brief Constant progression setup

    constant generates a setup object that always return the same value and is
    never flagged as done. Its main use-case is to allow combination between
    fixed value and other progression.
  **/
  template<typename Value>
  arithmetic constant(Value const& v)
  {
    return arithmetic(v,v,0);
  }
} }

#endif
