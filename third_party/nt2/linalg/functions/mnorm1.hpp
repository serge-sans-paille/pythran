//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MNORM1_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MNORM1_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_mnorm1 mnorm1
 *
 * \par Description
 * compute the 1-norm of a vector or a matrix
 *
 * that is :
 *  sum(abs(a)) for a vector
 *  max(sum(abs(a), 1)) for a matrix
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/mnorm1.hpp>
 * \endcode
 *
 * mnorm1 can be used as
 * mnorm1(a)
 *
 * \param a the matrix or vector expression a
 *
 **/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag mnorm1_ of functor mnorm1
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct mnorm1_ :  boost::dispatch::tag::formal_
    {
      /// INTERNAL ONLY
      typedef  boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mnorm1_, mnorm1, 1)

}

#endif

