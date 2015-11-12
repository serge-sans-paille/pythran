//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_ADAPTED_COMPOSITE_BUFFER_HPP_INCLUDED
#define NT2_SDK_MEMORY_ADAPTED_COMPOSITE_BUFFER_HPP_INCLUDED

#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/mpl/apply.hpp>

namespace nt2 {  namespace memory
{
  //============================================================================
  // Forward declaration
  //============================================================================
  template<typename Buffer> class composite_buffer;
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specializations
  //============================================================================
  template<typename Buffer>
  struct value_of< nt2::memory::composite_buffer<Buffer> > : value_of<Buffer>
  {
  };

  template<typename Buffer>
  struct value_of< nt2::memory::composite_buffer<Buffer>& >
  {
    typedef typename nt2::memory::composite_buffer<Buffer>::reference type;
  };

   template<typename Buffer>
  struct value_of< nt2::memory::composite_buffer<Buffer> const&>
  {
    typedef typename nt2::memory::composite_buffer<Buffer>::const_reference type;
  };

  //============================================================================
  // model_of specialization
  //============================================================================
  template<typename Buffer>
  struct model_of< nt2::memory::composite_buffer<Buffer> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef typename  boost::mpl::
                          apply<typename model_of<Buffer>::type,X>::type  base_t;
        typedef nt2::memory::composite_buffer<base_t>                     type;
      };
    };
  };
} } }

#endif
