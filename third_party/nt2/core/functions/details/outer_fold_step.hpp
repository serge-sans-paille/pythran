//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_OUTER_FOLD_STEP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_OUTER_FOLD_STEP_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the outer_fold_step function
**/

#include <nt2/sdk/config/cache.hpp>

namespace nt2
{
  /*!
    @brief PreFold over a dimension

    Folds elements of @c a1 along a dimension, possibly in parallel, and
    store the result in @c a0.

    @param Out Expression to store result in
    @param In Expression to reduce
    @param Bop Function to apply for binary reduction, first argument is accumulator
  **/
  namespace details
  {
    template<class target_type, class Out, class In, class Neutral, class Bop>
    inline void outer_fold_step(Out& out, In& in
                               ,Neutral const & neutral
                               ,Bop const & bop
                               ,std::size_t begin
                               ,std::size_t size
                               ,std::size_t oout
                               ,std::size_t oin)
    {
      typedef typename boost::remove_reference<In>::type::extent_type extent_type;

      extent_type ext = in.extent();
      std::size_t ibound = boost::fusion::at_c<0>(ext);
      std::size_t mbound = boost::fusion::at_c<1>(ext);
      std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;

      for (std::size_t i = 0, kout_ = oout + begin; i < size; i+=N, kout_+=N)
      {
        nt2::run(out, kout_, neutral(meta::as_<target_type>()));
      }

      for(std::size_t m=0, m_ = oin; m < mbound; m++, m_+=ibound)
      {
        for (std::size_t i = 0, kout_ = oout + begin, kin_ = m_ + begin;
             i < size;
             i+=N, kout_+=N, kin_+=N)
        {
            nt2::run(out, kout_,
               bop( nt2::run(out, kout_, meta::as_<target_type>())
                  , nt2::run(in,  kin_,  meta::as_<target_type>())
                  )
               );
        }
      }
    }
  }

};

#endif
