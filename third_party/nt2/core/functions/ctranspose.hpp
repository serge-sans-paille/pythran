//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_CTRANSPOSE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_CTRANSPOSE_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief ctranspose generic tag

     Represents the ctranspose function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct ctranspose_ : ext::elementwise_<ctranspose_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<ctranspose_> parent;
    };
  }
  /*!
    Transpose and conjugate a matrix expression.

    @par Semantic:

    For every matricial expression

    @code
    auto r = ctranspose(a0);
    @endcode

    produces r such that for every valid couple of indices i, j:

    @code
    r(j, i) = conj(a0(i, j))
    @endcode

    @see @funcref{transpose}
    @par alias: @c ctrans, @c ct
    @param a0

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ctranspose_, ctranspose, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ctranspose_, ctrans, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ctranspose_, ct    , 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct size_of<tag::ctranspose_,Domain,N,Expr>
  {
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      //BOOST_ASSERT(ndims(boost::proto::child_c<0>(e)) <= 2);
      return _2D( boost::fusion::at_c<1>(boost::proto::child_c<0>(e).extent())
                , boost::fusion::at_c<0>(boost::proto::child_c<0>(e).extent())
                );
    }
  };
} }

#endif
