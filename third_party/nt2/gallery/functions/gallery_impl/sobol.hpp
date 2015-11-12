//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_SOBOL_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_SOBOL_HPP_INCLUDED

#include <nt2/gallery/functions/sobol.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/constants/nbmantissabits.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sobol_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<integer_<A0> >)
                              (target_<scalar_<integer_<A1> > >)
                            )
  {
    typedef typename A1::type itype_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::sobol_
                                          , container::domain
                                          , itype_t
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return  boost::proto::
              make_expr < nt2::tag::sobol_
                        , container::domain
                        >
                        ( itype_t(a0)
                        , _2D(23,a0)
                        );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::sobol_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                         result_type;
    typedef typename A0::value_type                                       uint_type;
    typedef typename meta::as_floating<uint_type>::type                      f_type;

//#define INDEX(k, j) [(k) + (j-1) * maxdim]

    result_type operator()(A0& out, const A1& in) const
    {
      static const uint_type ip[]
        = { 0,
            1,
            1, 2,
            1, 4,
            2, 4, 7, 11, 13, 14,
            1, 13, 16, 19, 22, 25,
            1, 4, 7, 8, 14, 19, 21, 28, 31, 32, 37, 41, 42, 50, 55, 56, 59, 62,
            14, 21, 22, 38, 47, 49, 50, 52, 56, 67, 70, 84, 97, 103, 115, 122,
            8, 13, 16, 22, 25, 44, 47, 52, 55, 59,
            62, 67, 74, 81, 82, 87, 91, 94, 103, 104, 109, 122, 124, 137, 138, 143, 145, 152, 157, 167,
            173, 176, 181, 182, 185, 191, 194, 199, 218, 220, 227, 229, 230, 234, 236, 241, 244, 253
          };
      static const uint_type mdeg[]
        = { 1, 2, 3, 3, 4, 4, 5, 5, 5, 5, 5, 5,
            6, 6, 6, 6, 6, 6,
            7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
           };
      uint_type maxdim =  boost::proto::child_c<0>(in);
      uint_type maxbit = nt2::Nbmantissabits<f_type>();
      uint_type niv = maxbit*maxdim;
      out = nt2::zeros(maxdim,maxbit, nt2::meta::as_<uint_type>());
      out(nt2::_(1, maxdim)) = One<uint_type>();
      uint_type mval = 4;
      uint_type ipp = 1;

      for (uint_type k = maxdim, j = 0; k < niv-1; k += 2)
      {
        out(k+1) = ipp;
        if (++j == maxdim)
        {
          mval *= 2;
          ipp += 2;
          j = 0;
        }
        if ( ipp > mval ) ipp = 1;
        out(k+2) = ipp;
        if (++j == maxdim)
        {
          mval *= 2;
          ipp += 2;
          j = 0;
        }
        else
        {
          ipp += 2;
          if ( ipp > mval ) ipp = 1;
        }
      }
      for (uint_type k = 1; k <= maxdim; ++k)
      {
        // normalize the set out values
        out(k, nt2::_(1, mdeg[k-1])) <<=  maxbit-nt2::_(1, mdeg[k-1]);
        // calculate the rest of the out values
        for (uint_type j = mdeg[k-1] + 1; j <= maxbit; ++j)
        {
          ipp = ip[k-1];
          // calculate Gray code of out
          uint_type i = out(k, j - mdeg[k-1]);
          i ^= i >> mdeg[k-1];
          for (uint_type l = mdeg[k-1] - 1; l >= 1; --l)
          {
            if ( ipp & 1 ) i ^= out(k, j-l);
            ipp >>= 1;
          }
          out(k,j) = i;
        }
      }
      return out;
    }
  };
} }

#endif
