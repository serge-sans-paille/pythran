//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_CAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_CAT_HPP_INCLUDED

#include <nt2/core/functions/cat.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates cat from 2 scalar
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cat_, tag::cpu_,
                              (Dimension)(A1)(A2),
                              (scalar_<integer_<Dimension> >)
                              (scalar_< unspecified_<A1> >)
                              (scalar_< unspecified_<A2> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::cat_
                                          , container::domain
                                          , std::size_t
                                          , A1
                                          , A2
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(Dimension const& dim,A1 const& a1,A2 const& a2) const
    {
       BOOST_ASSERT_MSG ( arecatcompatible(a1, a2, dim)
                        , "cat arguments dimensions are not consistent."
                        );

      return  boost::proto::make_expr < nt2::tag::cat_
                                      , container::domain
                                      >(std::size_t(dim - 1u), a1,a2);
    }
  };
} }

#endif
