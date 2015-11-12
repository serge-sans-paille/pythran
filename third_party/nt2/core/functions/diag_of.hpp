//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DIAG_OF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DIAG_OF_HPP_INCLUDED


#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/size.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief diag_of generic tag

      Represents the diag_of function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct diag_of_ : ext::elementwise_<diag_of_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<diag_of_> parent;
    };

    struct offset_diag_of_ : ext::elementwise_<offset_diag_of_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<offset_diag_of_>  parent;
    };
  }

  /*!
    Extracts diagonal.

    @par Semantic:

    For every matrix expression

    @code
    auto r = diag_of(a0{, k});
    @endcode

    Retrieves the k-th sub or super diagonal of an
    expression. Contrary to diagonal, this is an extraction of data
    and not a simple masking operation. (k defaults to 0)

    The code is similar to

    @code
    auto r = tril(triu(a0, k), k);
    @endcode

    k defaults to 0.

    @see @funcref{from_diag}
    @param a0
    @param a1 optional, default to 0

    @return an expression which eventually will evaluate to the result
  **/

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::offset_diag_of_, diag_of, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::diag_of_       , diag_of, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::diag_of_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::diag_of_,Domain,N,Expr>
  {
    typedef nt2::_1D result_type;
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type c0_t;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      c0_t a0 = boost::proto::child_c<0>(e);
      return result_type(std::min(nt2::size(a0,1),nt2::size(a0,2)));
    }
  };

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::offset_diag_of_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::offset_diag_of_,Domain,N,Expr>
  {
    typedef nt2::_1D result_type;
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type c0_t;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      c0_t a0 = boost::proto::child_c<0>(e);
      std::ptrdiff_t w  = nt2::width(a0);
      std::ptrdiff_t h  = nt2::height(a0);
      std::ptrdiff_t m  = boost::proto::child_c<3>(e);

      if(m < -h || m > w) return result_type(0);

      if(h <= w)
      {
        if(m <= 0)        return result_type(h+m);
        else if(m <= w-h) return result_type(h);
      }
      else
      {
        if(m <= w-h)    return result_type(h+m);
        else if(m <= 0) return result_type(w);
      }

      return result_type(w-m);
    }
  };
} }

#endif
