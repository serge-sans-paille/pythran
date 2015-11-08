//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PACK_EXPRESSION_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_EXPRESSION_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/sdk/simd/pack/domain.hpp>
#include <boost/simd/include/functions/evaluate.hpp>
#include <boost/simd/include/functions/assign.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/proto/extends.hpp>
#include <boost/config.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4610) // custom constructor required
#pragma warning(disable: 4510) // custom constructor required
#endif

namespace boost { namespace simd
{
  template<class Expr, class ResultType>
  struct expression
  {
    BOOST_PROTO_BASIC_EXTENDS(Expr, expression, domain)

    // Assignment operators force evaluation
    BOOST_FORCEINLINE
    expression& operator=(expression const& xpr)
    {
      boost::simd::evaluate(
        boost::simd::assign(*this, xpr)
      );
      return *this;
    }

    template<class Xpr>
    BOOST_FORCEINLINE
    typename boost::disable_if< boost::is_base_of<expression, Xpr>
                              , expression&
                              >::type
    operator=(Xpr const& xpr)
    {
      boost::simd::evaluate(
        boost::simd::assign(*this, xpr)
      );
      return *this;
    }

    // operator[] forces evaluation and return element
    BOOST_FORCEINLINE typename meta::scalar_of<ResultType>::type
    operator[](std::size_t i) const
    {
      return boost::simd::evaluate(*this)[i];
    }

    // Conversion operator forces evaluation
    BOOST_FORCEINLINE operator ResultType() const
    {
      return boost::simd::evaluate(*this);
    }
  };

  // avoid warnings about unusable conversion operator
  template<class Expr>
  struct expression<Expr, void>
  {
    BOOST_PROTO_BASIC_EXTENDS(Expr, expression, domain)
  };
} }

namespace boost { namespace dispatch { namespace meta
{
  /// INTERNAL ONLY
  /// terminal_fo of a SIMD expression is the terminal_of of its ResultType
  template<typename Expr, typename ResultType>
  struct terminal_of< boost::simd::expression<Expr, ResultType> >
  {
    typedef typename terminal_of<ResultType>::type type;
  };
} } }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif
