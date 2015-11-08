//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FROM_DIAG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FROM_DIAG_HPP_INCLUDED


#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/length.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief from_diag generic tag

     Represents the from_diag function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct from_diag_ : ext::elementwise_<from_diag_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<from_diag_> parent;
    };
  }
  /*!

    Computes the square matricial expression full of zero except the
    a1-th diagonal which is given by a0.

    @par Semantic:

    For every vector expression a0 and integer a1:

    @code
    auto r = from_diag(a0{,k});
    @endcode

    computes the square matrix for which a0 is the k-th diagonal (k
    defaults to 0).

    @see @funcref{diag_of}
    @param a0
    @param a1 optional,  default to 0

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::from_diag_ , from_diag, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::from_diag_ , from_diag, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct  size_of<nt2::tag::from_diag_,Domain,1,Expr>
  {
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      std::size_t n = nt2::length(boost::proto::child_c<0>(e));
      return result_type(n,n);
    }
  };

  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct  size_of<nt2::tag::from_diag_,Domain,2,Expr>
  {
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      std::size_t n = nt2::length(boost::proto::child_c<0>(e))
                    + nt2::abs(boost::proto::value(boost::proto::child_c<1>(e)));

      return result_type(n,n);
    }
  };
} }

#endif
