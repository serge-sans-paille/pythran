//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_DESTRUCT_HPP_INCLUDED
#define NT2_SDK_MEMORY_DESTRUCT_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>

namespace nt2 { namespace details
{
  template<class In, class Alloc> inline
  void destruct(In, In, Alloc& , boost::mpl::true_ const&) {}

  template<class In, class Alloc> inline
  void destruct(In begin, In end, Alloc& alloc, boost::mpl::false_ const&)
  {
    while(begin != end) alloc.destroy(begin++);
  }
} }

namespace nt2 { namespace memory
{
  /*!
   * Wrapper around potential idem-potent destructor calls
   **/
  template<class In, class Alloc> inline
  void destruct(In begin, In end, Alloc& alloc)
  {
    typedef typename Alloc::value_type value_type;
    typename boost::has_trivial_destructor<value_type>::type status;
    nt2::details::destruct(begin,end,alloc,status);
  }
} }

#endif
