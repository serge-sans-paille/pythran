//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_DETAILS_EXTRACT_QR_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_DETAILS_EXTRACT_QR_HPP_INCLUDED

#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/function.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/gqr.hpp>
#include <nt2/include/functions/mqr.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/eye.hpp>


namespace nt2{

/// INTERNAL ONLY - Helper for Q/R extraction
template<typename W,typename A1,typename type_t> BOOST_FORCEINLINE
void extract_qr(A1& a1, W& work, nt2::container::table<type_t>& tau, int const&)
 {
    nt2_la_int  m  = nt2::height(work);
    nt2_la_int  n  = nt2::width(work);

    // economy mode
    if (m>n) boost::proto::child_c<1>(a1) = nt2::triu( work( _(1,n), _ ) );
    else  boost::proto::child_c<1>(a1) = nt2::triu( work );

    if(m < n)
     {
      /// TODO: Remove when aliasing works
      nt2::container::table<type_t> local(work);
      work = nt2::expand(local,nt2::of_size(m,m));
     }

    nt2::gqr(boost::proto::value(work), boost::proto::value(tau));

    boost::proto::child_c<0>(a1) = work;
  }

/// INTERNAL ONLY - Helper for Q/R extraction
template<typename W,typename A1, typename type_t, typename Policy>
BOOST_FORCEINLINE
void extract_qr(A1& a1, W& work, nt2::container::table<type_t>& tau, Policy const&)
  {
     nt2_la_int  m  = nt2::height(work);
     nt2_la_int  n  = nt2::width(work);

    // R = triu(QRF(A))
    boost::proto::child_c<1>(a1) = nt2::triu( work );

    if (m>n)
      {
        nt2::container::table<type_t> complete_q = nt2::eye(m,m, nt2::meta::as_<type_t>());
        nt2::mqr( boost::proto::value(work), boost::proto::value(tau)
                , boost::proto::value(complete_q) );
        boost::proto::child_c<0>(a1) = complete_q;
      }
    else
      {
        if(m < n)
        {
          /// TODO: Remove when aliasing works
          nt2::container::table<type_t> local(work);
          work = nt2::expand(local,nt2::of_size(m,m));
        }

        nt2::gqr(boost::proto::value(work), boost::proto::value(tau));

        boost::proto::child_c<0>(a1) = work;
      }
    }

}
#endif
