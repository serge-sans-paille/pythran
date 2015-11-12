//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ADJFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ADJFUN_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for adjfun functor
    **/
    struct adjfun_ : ext::elementwise_<adjfun_>
    {
      /// @brief Parent hierarchy
      typedef  ext::elementwise_<adjfun_> parent;
    };
  }

  /*!
    @brief Apply a function to adjacent element of a table

    adjfun computes the application of a binary functor @c f to all elements of
    @c a0.

    @par Semantic:

    For any given table expression @c a of size @c [d1,...,dn] which
    first non singleton dimension is @c k and any binary functor @c f:

    @code
    x = adjfun(f,a);
    @endcode

    is equivalent to:

    @code
    for(int in=1;in<=size(x,n);++in)
      ...
        for(int ik=1;ik<=size(x,k)-1;++ik)
          ...
            for(int i1=1;in<=size(x,1);++i1)
              x(i1,...,ik,...,in) = f(a(i1,...,ik+1,...,in),a(i1,...,ik,...,in));
    @endcode

    This semantic implies that if @c a is of size @c [s1 ... sn] then the size
    of @c adjfun(f,a) is equal to @c [s1 ... sk -1 ... sn].

    @param f  Binary functor to apply to a
    @param a Table expression to process

    @par Example:
  **/
  template<class Functor, class A0> BOOST_FORCEINLINE
  typename meta::call<tag::adjfun_(Functor const&, A0 const&)>::type
  adjfun(Functor const& f, A0 const& a)
  {
    return typename make_functor<tag::adjfun_, A0>::type()(f,a);
  }

  /*!
    @brief Apply a function to adjacent element of a table along some dimension

    adjfun computes the application of a binary functor @c f to all elements of
    @c a0.

    @par Semantic:

    For any given table @c a of size @c [d1,d2,...,dn], any binary
    functor @c f and a dimension index @c k:

    @code
    x = adjfun(f,a,k);
    @endcode

    is equivalent to:

    @code
    for(int in=1;in<=size(x,n);++in)
     ...
      for(int ik=1;ik<=size(x,k)-1;++ik)
       ...
        for(int i1=1;in<=size(x,1);++i1)
         x(i1,...,ik,...,in) = f(a(i1,...,ik+1,...,in),a(i1,...,ik,...,in));
    @endcode

    This semantic implies that if @c a is of size @c [s1 ... sn] then the size
    of @c adjfun(f,a,k) is equal to @c [s1 ... sk -1 ... sn].

    @param f  Binary functor to apply to a0
    @param a  Table to process
    @param k  Dimension along which to process @c a0

    @par Example:

  **/
  template<class Functor, class A0, class Along> BOOST_FORCEINLINE
  typename meta::call<tag::adjfun_(Functor const&, A0 const&, Along const&)>::type
  adjfun(Functor const& f, A0 const& a, Along const& k)
  {
    return typename make_functor<tag::adjfun_, A0>::type()(f,a,k);
  }
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct size_of<nt2::tag::adjfun_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of
                    ::child_c<Expr&,0>::value_type::extent_type result_type;

    BOOST_FORCEINLINE result_type operator ()(Expr& e) const
    {
      result_type that = nt2::extent(boost::proto::child_c<0>(e));
      std::size_t along = boost::proto::child_c<1>(e);

      // If non-0 dimension along chosen direction, decrements it
      if(along >= result_type::static_size)
      {
        fix_size(that, boost::mpl::bool_< !(result_type::static_size <= 0) >());
      }
      else
      {
        if(that[along]) --that[along];
      }

      return that;
    }

    BOOST_FORCEINLINE
    void fix_size(result_type& that, boost::mpl::true_ const&) const
    {
      that[result_type::static_size-1] = 0;
    }

    BOOST_FORCEINLINE
    void fix_size(result_type&, boost::mpl::false_ const&) const {}
  };

  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  value_type<nt2::tag::adjfun_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::
                      child_c<Expr&, 0>::value_type::value_type value_t;
    typedef typename  boost::proto::result_of::
                      child_c<Expr&, 2>::value_type::value_type func_t;
    typedef typename  boost::dispatch::meta::
                      result_of<func_t(value_t,value_t)>::type  type;
  };
} }

#endif
