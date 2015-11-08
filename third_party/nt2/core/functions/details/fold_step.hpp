//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_FOLD_STEP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_FOLD_STEP_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the fold_step function
**/

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
    template<class Out, class In, class Bop>
    inline Out fold_step(Out const & out, In& in, Bop const& bop
                        ,std::size_t begin
                        ,std::size_t size
                        ,std::size_t step)
    {
      Out result = out;

      for(std::size_t i=0, i_ = begin; i < size; i++, i_+=step)
       result = bop(result, nt2::run(in, i_, meta::as_<Out>()));

      return result;
    }
  }

}

#endif
