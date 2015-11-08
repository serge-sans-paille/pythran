#if !BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_OF_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_OF_SIZE_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the of_size functions
 */

#include <nt2/core/utility/of_size.hpp>
#include <nt2/core/utility/of_size/mpl_value.hpp>
#include <nt2/sdk/meta/is_iterator.hpp>
#include <nt2/sdk/parameters.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace nt2
{
  #if defined(DOXYGEN_ONLY)
  //============================================================================
  /*!
   * Builds a nD extent from a list of \c n dimension values.
   *
   * \param d Values to use as dimensions
   *
   * \code
   * #include <iostream>
   * #include <nt2/core/functions/of_size.hpp>
   *
   * int main()
   * {
   *   std::cout << nt2::of_size(3,3,4) << "\n";
   * }
   * \endcode
   */
  //============================================================================
  template<class ...Dims> _nD of_size(Dims const& d...);
  #endif

  _0D BOOST_FORCEINLINE  of_size() { return _0D(); }

  #define   BOOST_PP_FILENAME_1 "nt2/core/functions/of_size.hpp"
  #define   BOOST_PP_ITERATION_LIMITS (1, NT2_MAX_DIMENSIONS)
  #include  BOOST_PP_ITERATE()

  //============================================================================
  /*!
   * Builds a nD extent from a Range of dimensions
   *
   * \param begin Iterator to the start of the Sequence containing the dimension
   * values
   * \param end Iterator to the end of the Sequence containing the dimension
   * values
   *
   * \return an extent of the maximum number of dimensions allowed which value
   * have been set accordingly to the Range values.
   * \code
   * #include <iostream>
   * #include <nt2/core/functions/of_size.hpp>
   *
   * int main()
   * {
   *   int d[3] = { 3,3,4 };
   *   std::cout << nt2::of_size(&d[0], &d[0]+3) << "\n";
   * }
   * \endcode
   */
  //============================================================================
  template<class Iterator> BOOST_FORCEINLINE
  typename boost::
           enable_if< meta::is_iterator<Iterator>
                    , BOOST_PP_CAT(BOOST_PP_CAT(_,NT2_MAX_DIMENSIONS),D)
                    >::type
  of_size(Iterator const& begin, Iterator const& end)
  {
    BOOST_PP_CAT(BOOST_PP_CAT(_,NT2_MAX_DIMENSIONS),D) that(begin,end);
    return that;
  }
}

#endif

#else
#define N BOOST_PP_ITERATION()
#define M0(z,n,t) nt2::mpl_value<D##n>::value

  template<BOOST_PP_ENUM_PARAMS(N,class D)>
  BOOST_FORCEINLINE of_size_<BOOST_PP_ENUM(N,M0,~)>
  of_size(BOOST_PP_ENUM_BINARY_PARAMS(N,const D, &d))
  {
    of_size_<BOOST_PP_ENUM(N,M0,~)> that(BOOST_PP_ENUM_PARAMS(N,d));
    return that;
  }

#undef M0
#undef N

#endif
