//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MNORMFRO_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MNORMFRO_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_mnormfro mnormfro
 *
 * \par Description
 * compute the froboenius norm of a vector or a matrix
 *
 * that is :
 *  sqrt(asum2((_))
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/mnormfro.hpp>
 * \endcode
 *
 * mnormfro can be used as
 * mnormfro(a)
 *
 * \param a the matrix or vector expression a
 *
 **/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag mnormfro_ of functor mnormfro
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct mnormfro_ :  boost::dispatch::tag::formal_
    {
      /// INTERNAL ONLY
      typedef  boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mnormfro_, mnormfro, 1)

}

#endif

