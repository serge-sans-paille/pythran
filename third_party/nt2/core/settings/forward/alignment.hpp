//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_FORWARD_ALIGNMENT_HPP_INCLUDED
#define NT2_CORE_SETTINGS_FORWARD_ALIGNMENT_HPP_INCLUDED

#include <boost/mpl/bool.hpp>

namespace nt2
{
  struct aligned_
  {
    typedef boost::mpl::true_  alignment_type;
  };

  struct unaligned_
  {
    typedef boost::mpl::false_  alignment_type;
  };

  namespace tag
  {
    struct alignment_;
  }
}

#endif
