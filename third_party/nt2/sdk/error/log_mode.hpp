//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_LOG_MODE_HPP_INCLUDED
#define NT2_SDK_ERROR_LOG_MODE_HPP_INCLUDED

namespace nt2
{
  enum log_mode_t
  {
    LOG_IGNORE    = 0,
    LOG_PRINT     = 1,
    LOG_ABORT     = 1 << 1,
    LOG_TRAP      = 1 << 2,
    LOG_STACKDUMP = 1 << 3,
    LOG_EXCEPT    = 1 << 4
  };
}

#endif
