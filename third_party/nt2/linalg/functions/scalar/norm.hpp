//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_NORM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_NORM_HPP_INCLUDED
#include <nt2/linalg/functions/norm.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/include/functions/mnorm.hpp>
#include <nt2/include/functions/globalnorm.hpp>
#include <nt2/include/functions/isvector.hpp>
#include <nt2/include/functions/ismatrix.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/meta/property_of.hpp>
#include <nt2/table.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norm_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
    )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      BOOST_ASSERT_MSG(nt2::ismatrix(a0), "a0 is not a matrix nor a vector");
      typedef typename details::is_vector<typename A0::extent_type>::type choice_t;
      return eval(a0, choice_t());
    }
    BOOST_FORCEINLINE result_type
    eval(A0 const& a0, boost::mpl::true_ const &) const //vector
    {
      return globalnorm2(a0);
    }

    BOOST_FORCEINLINE result_type
    eval(A0 const& a0, boost::mpl::false_ const &) const // not  vector
    {
      return mnorm(a0);
    }

    BOOST_FORCEINLINE result_type
    eval(A0 const& a0, nt2::meta::indeterminate_ const &) const // statically indeterminate
    {
      if (isvector(a0))
        return  globalnorm2(a0);
      else
        return mnorm(a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norm_, tag::cpu_,
                                     (A0)(A1),
                                     ((ast_<A0, nt2::container::domain>))
                                     (unspecified_<A1>)
                                     )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      BOOST_ASSERT_MSG(nt2::ismatrix(a0), "a0 is not a matrix nor a vector");
      typedef typename details::is_vector<typename A0::extent_type>::type choice_t;
      return eval(a0, a1, choice_t());
    }
    BOOST_FORCEINLINE result_type
    eval(A0 const& a0, A1 const& a1, boost::mpl::true_ const &) const // vector
    {
      return globalnorm(a0, a1);
    }

    BOOST_FORCEINLINE result_type
    eval(A0 const& a0, A1 const& a1, boost::mpl::false_ const &) const // not vector
    {
      return mnorm(a0, a1);
    }

    BOOST_FORCEINLINE result_type
    eval(A0 const& a0, A1 const& a1, nt2::meta::indeterminate_ const &) const // statically indeterminate
    {
      if (isvector(a0))
        return globalnorm(a0, a1);
      else
        return mnorm(a0, a1);
    }
  };
} }

#endif
