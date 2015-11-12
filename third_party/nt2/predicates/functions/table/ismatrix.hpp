//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_TABLE_ISMATRIX_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_TABLE_ISMATRIX_HPP_INCLUDED

#include <nt2/predicates/functions/ismatrix.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/extent.hpp>
#include <boost/fusion/include/at.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ismatrix_, tag::cpu_
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

      // 4x0x1x1 is matrix but I do not know if 4x0x4x1 is ?!
      return (nz == 0) ||((nz > 0)
                          &&  (boost::fusion::at_c<0>(ex)*boost::fusion::at_c<1>(ex) == nz));
    }
  };
} }

#endif
