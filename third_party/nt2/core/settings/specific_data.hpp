//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_SPECIFIC_DATA_HPP_INCLUDED
#define NT2_CORE_SETTINGS_SPECIFIC_DATA_HPP_INCLUDED

namespace nt2
{
  template <typename Tag, typename Type> struct specific_data
  {
    struct type
    {
      inline void swap(type&)    {}
      inline void synchronize()  {}
    };
  };
}

#endif
