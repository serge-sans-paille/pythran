//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_ADAPTED_ARRAY_BUFFER_HPP_INCLUDED
#define NT2_SDK_MEMORY_ADAPTED_ARRAY_BUFFER_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>

namespace nt2 {  namespace memory
{
  //============================================================================
  // Forward declaration
  //============================================================================
  template<typename T, typename Size> class array_buffer;
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================
  template<typename T, typename Size>
  struct value_of< nt2::memory::array_buffer<T,Size> > : value_of<T>
  {};

  //============================================================================
  // model_of specialization
  //============================================================================
  template<typename T, typename Size>
  struct model_of< nt2::memory::array_buffer<T,Size> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef typename  boost::mpl::
                          apply<typename model_of<T>::type,X>::type base_t;
        typedef nt2::memory::array_buffer<base_t,Size>              type;
      };
    };
  };
} } }

#endif
