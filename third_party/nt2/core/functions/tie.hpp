//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TIE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TIE_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::tie function
 */

#include <nt2/include/functor.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/core/container/dsl/expression.hpp>

#include <boost/mpl/transform.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/fusion/include/as_vector.hpp>

#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>

namespace nt2
{
  namespace tag
  {
    struct tie_ : ext::elementwise_<tie_>
    {
      typedef ext::elementwise_<tie_> parent;
    };
  }

  //============================================================================
  /*!
   * Tie terminals for multi-return function handling
   */
  //============================================================================
  #define param(r,_,i,b) (BOOST_PP_CAT(A,i) BOOST_PP_CAT(c,b) &)

  #define c0
  #define c1 const
  #define bits(z, n, _) ((0)(1))

  #define call_operator(r, constness)                                          \
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::tie_, tie, BOOST_PP_SEQ_FOR_EACH_I_R(r,param,~,constness), BOOST_PP_SEQ_SIZE(constness))
  /**/

  #define M0(z,n,t)                                                            \
  BOOST_PP_SEQ_FOR_EACH_PRODUCT_R(                                             \
      z,                                                                       \
      call_operator                                                            \
    , BOOST_PP_REPEAT(n, bits, ~)                                              \
  )                                                                            \
  /**/
  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY),M0,~)

  #undef M0
  #undef bits
  #undef c1
  #undef c0
  #undef param
  #undef call_operator
}

//==============================================================================
// Specify tie node generation processs
//==============================================================================
namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::tie_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::value_type child0;
    typedef typename child0::extent_type const& result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& expr) const
    {
      return boost::proto::child_c<0>(expr).extent();
    }
  };
} }

namespace nt2 { namespace details
{
  //============================================================================
  // INTERNAL ONLY
  // tie semantic is a fusion sequence and don't carry any special meaning.
  //============================================================================
  template<class Domain, int N, class Expr>
  struct  generator<nt2::tag::tie_,Domain,N,Expr>
  {
    typedef typename boost::remove_const<Expr>::type                    base_t;
    typedef typename boost::fusion::result_of::as_vector<base_t>::type  sem_t;
    typedef typename boost::mpl::transform< sem_t
                                          , boost::dispatch::meta
                                                 ::semantic_of<boost::mpl::_>
                                          >::type                   semantic_t;

    typedef container::expression<base_t, semantic_t>               result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };
} }

#endif
