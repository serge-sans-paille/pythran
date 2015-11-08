//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_REDUCTION_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_REDUCTION_HPP_INCLUDED

#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/core/utility/of_size/predef.hpp>

#include <boost/proto/traits.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>

namespace nt2
{
  namespace details
  {
    /// INTERNAL ONLY - Helper that computes the proper type of of_size_
    template<class T> struct of_size_reduce;

    #define M0(z, n, t)                                               \
    template<BOOST_PP_ENUM_PARAMS(n, std::ptrdiff_t D)>               \
    struct of_size_reduce< of_size_< BOOST_PP_ENUM_PARAMS(n, D) > >   \
    {                                                                 \
      typedef of_size_<1  BOOST_PP_COMMA_IF(BOOST_PP_DEC(n))          \
                          BOOST_PP_ENUM_SHIFTED_PARAMS(n, D)          \
                      >                                       type;   \
    };                                                                \
    /**/

    BOOST_PP_REPEAT(BOOST_PP_INC(NT2_MAX_DIMENSIONS), M0, ~)

    #undef M0
  }

  namespace meta
  {
    //==========================================================================
    // This is the factorized size_of for all reduction function.
    // For any given reduction function tag RED, the registration of their
    // size_of is simply :
    //
    // namespace nt2 { namespace ext
    // {
    //  template<class Domain, class Expr, int N>
    //  struct size_of<RED,Domain,N,Expr> : meta::reduction_size<Expr, N>
    //  {};
    // } }
    //
    //==========================================================================
    template<class Expr, int N> struct reduction_size;

    /// INTERNAL ONLY - Handle reduction(x,n) case
    template<class Expr> struct reduction_size<Expr,2>
    {
      typedef typename  boost::proto::result_of
                      ::child_c<Expr&, 0>::value_type           child_t;
      typedef typename child_t::extent_type                     ext_t;
      typedef typename nt2::make_size<ext_t::static_size>::type result_type;

      BOOST_FORCEINLINE result_type operator()(Expr& e) const
      {
        result_type res = boost::proto::child_c<0>(e).extent();
        std::size_t red = boost::proto::value(boost::proto::child_c<1>(e)) - 1;

        // If we reduce over the number of dimensions, do nothing
        if(red < res.size()) res[red] = 1;

        return res;
      }
    };

    /// INTERNAL ONLY - Handle reduction(x) case
    template<class Expr> struct reduction_size<Expr,1>
    {
      typedef typename  boost::proto::result_of
                      ::child_c<Expr&, 0>::value_type       child_t;
      typedef typename child_t::extent_type                 ext_t;
      typedef typename details::of_size_reduce<ext_t>::type result_type;

      BOOST_FORCEINLINE result_type operator()(Expr& e) const
      {
        ext_t sz = boost::proto::child_c<0>(e).extent();
        std::size_t d = nt2::firstnonsingleton(sz);

        result_type res;
        for(std::size_t i=0; i!=std::min(d, res.size()); ++i)
          res[i] = 1;
        for(std::size_t i=d; i<res.size(); ++i)
          res[i] = sz[i];
        return res;
      }
    };

    //==========================================================================
    // This is the factorized value_type for all reduction function.
    // For any given reduction function tag RED, the registration of their
    // value_type is simply :
    //
    // namespace nt2 { namespace ext
    // {
    //  template<class Domain, class Expr, int N>
    //  struct value_type<RED,Domain,N,Expr> : reduction_value<RED,Expr>
    //  {};
    // } }
    //
    //==========================================================================
    template<class Tag, class Expr> struct reduction_value
    {
      typedef typename  boost::proto::result_of
                      ::child_c<Expr&, 0>::value_type   expr_t;
      typedef typename expr_t::const_reference          base_t;
      typedef typename meta::call<Tag(base_t)>::type    type;
    };
  }
}

#endif
