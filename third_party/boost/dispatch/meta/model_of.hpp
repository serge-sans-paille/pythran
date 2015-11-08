//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_MODEL_OF_HPP_INCLUDED
#define BOOST_DISPATCH_META_MODEL_OF_HPP_INCLUDED

#include <boost/mpl/apply.hpp>

/*!
 * \file
 * \brief Defines the \c model_of extension point
 */

namespace boost { namespace dispatch { namespace details
{
  template<class T, class Enable = void>
  struct model_of
  {
    struct type
    {
      template<class X>
      struct apply
      {
        typedef X type;
      };
    };
  };
}

namespace meta
{
  template<class T>
  struct model_of : details::model_of<T> {};

  template<class T>
  struct model_of<T&> : model_of<T>
  {
  };

  template<class T>
  struct model_of<T const> : model_of<T>
  {
  };
} } }

#endif
