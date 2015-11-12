//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_TABLE_ISVECTOR_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_TABLE_ISVECTOR_HPP_INCLUDED

#include <nt2/predicates/functions/isvector.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/extent.hpp>
#include <boost/fusion/include/at.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isvector_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0) const
    {
      typename meta::call<tag::extent_(A0 const&)>::type ex = nt2::extent(a0);
      std::size_t nz = nt2::numel(ex);

      return   ( (nz > 0)
                 &&  (   ( boost::fusion::at_c<0>(ex) == nz )
                         ||  ( boost::fusion::at_c<1>(ex) == nz )
                         )
                 )
        ||   ( (nz == 0)
               && (boost::fusion::at_c<0>(ex) == 1
                   ||boost::fusion::at_c<1>(ex) == 1)
               );
        }
  };
} }

#endif
