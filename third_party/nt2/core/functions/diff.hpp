//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DIFF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DIFF_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief tag for diff functor
    **/
    struct diff_ : ext::elementwise_<diff_>
    {
      /// @brief Parent hierarchy
      typedef  ext::elementwise_<diff_> parent;
    };
  }
  /*!
    Computes diferences along a dimension

    @par Semantic:

    For every table expressions n and p

    @code
    auto x = cdiff(a, order, n);
    @endcode

    is similar to:

    @code
    for(int i=1;i <= order;++in)
    {
      for(int in=1;in<=size(x,n);++in)
        ...
          for(int ik=2;ik<=size(x,k)-1;++ik)
            ...
              for(int i1=1;in<=size(x,1);++i1)
                x(i1,...,ik,...,in) = a(i1,...,ik+1,...,in)-a(i1,...,ik-1,...,in);
      a = x;
    }

    @endcode


    @param a0
    @param a1
    @param a2

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::diff_       , diff, 3)
  /// overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::diff_       , diff, 1)
  /// overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::diff_       , diff, 2)
}
namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct size_of<nt2::tag::diff_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of
                    ::child_c<Expr&,0>::value_type::extent_type result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee = boost::proto::child_c<0>(e).extent();
      std::size_t along = boost::proto::value(boost::proto::child_c<1>(e));
      if(sizee[along]) sizee[along]--;

      return sizee;
    }
  };

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::diff_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
