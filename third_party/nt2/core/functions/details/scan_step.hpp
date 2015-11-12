//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_SCAN_STEP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_SCAN_STEP_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the inner_scan_step function
**/

namespace nt2
{
  /*!
    @brief PreScan over inner dimension

    Folds elements of @c a2 along inner dimension, possibly in parallel, and
    conditionnaly store the result in @c a1.

    @param Summary Value containing the updated summary
    @param Out Expression to store result in
    @param In Expression to reduce
    @param Bop Function to apply for binary reduction, first argument is accumulator
  **/
  namespace details
  {
    template<class Summary, class Out, class In, class Bop>
    inline Summary scan_step( Summary summary
                            , Out& out, In& in
                            , Bop const& bop
                            , std::size_t begin
                            , std::size_t size
                            , std::size_t step
                            , bool prescan
                            )
    {
      for(std::size_t i = 0, i_ = begin; i<size; i++, i_+=step)
      {
       summary = bop(summary, nt2::run(in, i_, meta::as_<Summary>()));
       if(!prescan) nt2::run(out, i_, summary);
      }

      return summary;
    }
  }

};

#endif
