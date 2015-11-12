//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_CONCRETE_HPP_INCLUDED
#define NT2_SDK_META_CONCRETE_HPP_INCLUDED

#include <boost/proto/traits.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace nt2
{
  namespace meta
  {
    template< typename Expr
            , int Arity = boost::proto::arity_of<Expr>::value
            >
    struct concrete
    {
      typedef typename  boost::dispatch::meta::
                        terminal_of < typename boost::dispatch::meta::
                                              semantic_of<Expr&>::type
                                    >::type                             type;

      static BOOST_FORCEINLINE type call(Expr& a0)
      {
        return a0;
      }

      template<typename Values>
      static BOOST_FORCEINLINE type shallow_call(Expr&, Values const& v)
      {
        type that = v;
        return that;
      }
    };

    template<typename Expr>
    struct concrete<Expr,0>
    {
      typedef typename boost::add_reference<Expr>::type type;

      static BOOST_FORCEINLINE type call(Expr& a0) { return a0; }

      template<typename Values>
      static BOOST_FORCEINLINE type shallow_call(Expr& a0, Values const& v)
      {
        a0 = v;
        return a0;
      }
    };
  }

  template<typename Expr>
  BOOST_FORCEINLINE typename meta::concrete<Expr>::type
  concrete( Expr& xpr )
  {
    return meta::concrete<Expr>::call(xpr);
  }

  template<typename Expr, typename Values>
  BOOST_FORCEINLINE typename meta::concrete<Expr>::type
  shallow_concrete( Expr& xpr, Values const& v )
  {
    return meta::concrete<Expr>::shallow_call(xpr,v);
  }
}

#endif
