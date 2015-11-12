//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_CONSTRUCT_HPP_INCLUDED
#define NT2_SDK_MEMORY_CONSTRUCT_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <nt2/sdk/memory/copy.hpp>
#include <boost/type_traits/has_trivial_copy.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>

namespace nt2 { namespace details
{
  template<class In, class Alloc> inline
  void default_construct(In, In, Alloc&, boost::mpl::true_ const&) {}

  template<class In, class Alloc> inline
  void default_construct(In begin, In end, Alloc&, boost::mpl::false_ const&)
  {
    typedef typename Alloc::value_type value_type;

    while(begin != end)
    {
      begin = new (begin) value_type;
      begin++;
    }
  }

  template<class In, class Out, class Alloc> inline
  void copy_construct ( In b, In e, Out d, Alloc const&
                      , boost::mpl::true_ const&
                      )
  {
    nt2::memory::copy(b,e,d);
  }

  template<class In, class Out, class Alloc> inline
  void copy_construct ( In begin, In end, Out dst
                      , Alloc& alloc, boost::mpl::false_ const&
                      )
  {
    while(begin != end) alloc.construct(dst++, *begin++);
  }
} }

namespace nt2 { namespace memory
{
  /*!
   * Wrapper around potential idem-potent default constructor calls
   **/
  template<class In, class Alloc> inline
  void default_construct(In begin, In end, Alloc& alloc)
  {
    typedef typename Alloc::value_type value_type;
    typename boost::has_trivial_default_constructor<value_type>::type status;
    nt2::details::default_construct(begin,end,alloc,status);
  }

  /*!
   * Wrapper around in-place copy-constructor
   **/
  template<class In, class Out, class Alloc> inline
  void copy_construct(In begin, In end, Out dst, Alloc alloc)
  {
    typedef typename Alloc::value_type value_type;
    typename boost::has_trivial_copy_constructor<value_type>::type status;
    nt2::details::copy_construct(begin,end,dst,alloc,status);
  }
} }

#endif
