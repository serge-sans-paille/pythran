//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_OPTION_OPTION_SPEC_HPP_INCLUDED
#define NT2_SDK_OPTION_OPTION_SPEC_HPP_INCLUDED

#include <nt2/sdk/option/option_term.hpp>
#include <nt2/sdk/option/option_domain.hpp>
#include <boost/proto/transform/arg.hpp>
#include <boost/proto/matches.hpp>
#include <boost/proto/domain.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace nt2 { namespace details
{
  struct get_value : boost::proto::callable
  {
    template<class Sig> struct result;

    template<class This, class Value>
    struct result<This(Value)>
    {
      typedef typename boost::remove_reference<Value>::type val_t;
      typedef typename boost::proto::domain_of<val_t>::type dom_t;
      typedef typename  boost::mpl::
                        eval_if < boost::is_same< dom_t
                                                , option_domain
                                                >
                                , boost::proto::result_of::value<Value>
                                , boost::mpl::identity<Value>
                                >::type type;
    };

    template<class Value>
    typename result<get_value(Value&)>::type
    operator()(Value& v) const
    {
      typedef typename boost::proto::domain_of<Value>::type dom_t;

      return eval(v, typename boost::is_same<dom_t, option_domain>::type());
    }

    template<class Value>
    typename result<get_value(Value&)>::type
    eval(Value& v, boost::mpl::false_ const&) const
    {
      return v;
    }

    template<class Value>
    typename result<get_value(Value&)>::type
    eval(Value& v, boost::mpl::true_ const&) const
    {
      return boost::proto::value(v);
    }
  };

  struct option_spec
      : boost::proto::when<
          boost::proto::assign<
              option_term
            , boost::proto::_
          >
        , get_value(boost::proto::_right)
      >
  {};
} }

#endif
