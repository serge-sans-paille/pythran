//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_MNORMINF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_MNORMINF_HPP_INCLUDED
#include <nt2/linalg/functions/mnorminf.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/asum1.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/globalasum1.hpp>
#include <nt2/include/functions/iscolumn.hpp>
#include <nt2/include/functions/isrow.hpp>
#include <nt2/include/functions/ismatrix.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/functions/table/details/is_definitely_vector.hpp>
#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/static_assert.hpp>

//  infinity norm  of a matrix  (maximum row sum)
// TODO optimize mnorminf(trans(a)) as mnorm1(a)

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mnorminf_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::abs(a0);
    }

  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mnorminf_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      BOOST_ASSERT_MSG(nt2::ismatrix(a0), "a0 is not a matrix");
      typedef typename details::is_col_vector<typename A0::extent_type>::type choice_t;
      return eval(a0, choice_t());
    }

    BOOST_FORCEINLINE result_type
    eval(A0 const& a0, boost::mpl::true_ const &) const //static col vector
    {
      return nt2::globalmax(nt2::abs(a0));
    }

    BOOST_FORCEINLINE result_type
    eval(A0 const& a0, boost::mpl::false_ const &) const  // not static col vector
    {
      typedef typename details::is_row_vector<typename A0::extent_type>::type choice_t;
      return eval2(a0, choice_t());
    }

    BOOST_FORCEINLINE result_type
    eval2(A0 const& a0, boost::mpl::true_ const &) const //static row vector
    {
      return nt2::globalasum1(a0);
    }

    BOOST_FORCEINLINE result_type
    eval2(A0 const& a0, boost::mpl::false_ const &) const //not static vector
    {
      return nt2::globalmax(nt2::asum1(a0, 2));
    }

    BOOST_FORCEINLINE result_type
    eval2(A0 const& a0, nt2::meta::indeterminate_ const &) const
    {
      return  eval(a0, nt2::meta::indeterminate_());
    }

    BOOST_FORCEINLINE result_type
    eval(A0 const& a0, nt2::meta::indeterminate_ const &) const
    {
      if (iscolumn(a0)) // col vector
      {
        return eval(a0, boost::mpl::true_());
      }
      else if (isrow(a0)) //row vector
      {
        return eval2(a0, boost::mpl::true_());
      }
      else  // matrix but not vector
      {
        return eval2(a0, boost::mpl::false_());
      }
    }
  };
} }

#endif
