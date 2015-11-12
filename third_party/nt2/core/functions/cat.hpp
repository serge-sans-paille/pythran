//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_CAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_CAT_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <boost/mpl/assert.hpp>

namespace nt2
{
  namespace tag
  {
    /// Tag for @c cat functor
    struct cat_ : ext::elementwise_<cat_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<cat_> parent;
    };
  }

  /*!
    Concatenates tables along specified dimension

    @param dim Dimension along which to concatenate
    @param a0  First table to concatenate
    @param a1  Second table to concatenate

    @return A lazy expression that will evaluate as the concatenation of a0 and a1

  **/
  template<class Dimension, class A0, class A1>
  BOOST_FORCEINLINE
  typename meta::call<tag::cat_(Dimension const&, A0 const&, A1 const&)>::type
  cat(Dimension const& dim, A0 const& a0, A1 const& a1)
  {
    return typename make_functor<tag::cat_, A0>::type()(dim,a0,a1);
  }
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  /// Computes the extent of a cat expression as being the "concatenation" of
  /// the initial tables' size
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::cat_,Domain,N,Expr>
  {
    // Can't be anything else as along is defined at runtime
    // TODO: Support cat<N>(a0,a1) and computes exact of_size in this case
    typedef of_size_max result_type;

    BOOST_FORCEINLINE result_type operator ()(Expr& e) const
    {
      // cat with empty matrix return the other matrix
      if( !numel(boost::proto::child_c<1>(e).extent()) )
      {
        return boost::proto::child_c<2>(e).extent();
      }
      else if( !numel(boost::proto::child_c<2>(e).extent()) )
      {
        return boost::proto::child_c<1>(e).extent();
      }
      // otherwise cat the size properly
      else
      {
        // Direction of concatenation
        std::size_t along = boost::proto::child_c<0>(e);

        // Build return size
        result_type sizee(boost::proto::child_c<1>(e).extent());
        sizee[along] += nt2::size(boost::proto::child_c<2>(e),along+1);

        return sizee;
      }


    }
  };

  /// INTERNAL ONLY
  /// Computes the value type of a cat expression as being the same than first
  /// child if both children have the same value type
  template<class Domain, int N, class Expr>
  struct value_type<nt2::tag::cat_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of
                    ::child_c<Expr&,1>::value_type::value_type  type;
    typedef typename  boost::proto::result_of
                    ::child_c<Expr&,2>::value_type::value_type  other_type;

    BOOST_MPL_ASSERT_MSG
    ( (boost::is_same<type,other_type>::value)
    , NT2_INCOMPATIBLE_TYPE_IN_CAT_EXPRESSION
    , (type,other_type)
    );
  };
} }

#endif
