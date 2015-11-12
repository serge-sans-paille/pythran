//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_FORWARD_SETTINGS_HPP_INCLUDED
#define NT2_CORE_SETTINGS_FORWARD_SETTINGS_HPP_INCLUDED

namespace nt2
{
  //===========================================================================
  /*!
   * settings is a seed type that allow contruction of multiple options pack.
   * If a given container needs to have options A and B set, settings(A,B) will
   * perform such a task.
   **/
  //============================================================================
  struct settings {};
}

#endif
