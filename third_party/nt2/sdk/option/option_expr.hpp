//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_OPTION_OPTION_EXPR_HPP_INCLUDED
#define NT2_SDK_OPTION_OPTION_EXPR_HPP_INCLUDED

#include <nt2/sdk/option/option_expr_fwd.hpp>
#include <nt2/sdk/option/option_domain.hpp>
#include <nt2/sdk/option/option_not_found.hpp>
#include <nt2/sdk/option/option_term.hpp>
#include <nt2/sdk/option/option_pack.hpp>
#include <nt2/sdk/meta/result_of.hpp>

#include <boost/proto/extends.hpp>
#include <boost/proto/make_expr.hpp>
#include <boost/proto/operators.hpp>

namespace nt2 { namespace details
{
  template<class Expr> struct option_expr
  {
    BOOST_PROTO_BASIC_EXTENDS(Expr, option_expr, option_domain)
    BOOST_PROTO_EXTENDS_ASSIGN()

    template <class Sig>struct result;

    template <class Option>
    struct  has_option
          : boost::mpl::bool_<
              !boost::is_same < typename result<option_expr const(Option)>::type
                              , option_not_found
                              >::value
                            >
    {};

    template <class This, class Option>
    struct result<This(Option)> : meta::result_of<option_pack(This, Option)>
    {};

    template <class This, class Option, class Default>
    struct result<This(Option, Default)>
        : boost::mpl::if_c< has_option<Option>::value
                          , typename result<This(Option)>::type
                          , Default
                          >
    {};

    template<class Option>
    typename result<option_expr const(Option const)>::type
    operator()(Option const &opt) const
    {
      BOOST_MPL_ASSERT_MSG( (boost::proto::matches<Option const,option_term>::value)
                          , UNKNOWN_NAMED_OPTIONS
                          , (Option)
                          );

      BOOST_MPL_ASSERT_MSG( (has_option<Option const>::value)
                          , NO_SUCH_OPTION_IN_CURRENT_OPTIONS_PACK
                          , (Option)
                          );

      return option_pack()(*this, opt);
    }

      template<class Option, class Default>
      typename result<option_expr const(Option const, Default const)>::type
      operator()(Option const &opt, Default const &def) const
      {
      BOOST_MPL_ASSERT_MSG( (boost::proto::matches<Option const,option_term>::value)
                          , UNKNOWN_NAMED_OPTIONS
                          , (Option,Default)
                          );

        return this->with_default(opt, def, has_option<Option const>());
      }

    private:

    template<class Option, class Default>
    typename result<option_expr const(Option const, Default const)>::type
    with_default(Option const &opt, Default const &, boost::mpl::true_) const
    {
      return option_pack()(*this, opt);
    }

    template<class Option, class Default>
    typename result<option_expr const(Option const, Default const)>::type
    with_default(Option const &, Default const &def, boost::mpl::false_) const
    {
      return def;
    }
  };

} }

#endif
