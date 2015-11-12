#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_CONS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_CONS_HPP_INCLUDED

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/core/functions/scalar/numel.hpp>
#include <nt2/core/settings/storage_size.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <boost/assert.hpp>

#ifdef NT2_DONT_USE_PREPROCESSED_FILES
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#endif

namespace nt2
{

#if !defined(NT2_DONT_USE_PREPROCESSED_FILES)
#include <nt2/core/functions/preprocessed/cons.hpp>
#else
#if defined(__WAVE__) && defined(NT2_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/cons.hpp")
#undef BOOST_FORCEINLINE
#undef BOOST_ASSERT_MSG
#endif

#define BOOST_PP_ITERATION_PARAMS_1 (3, ( 1, BOOST_PP_LIMIT_ITERATION-1, "nt2/core/functions/cons.hpp"))
#include BOOST_PP_ITERATE()

#if defined(__WAVE__) && defined(NT2_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

}

#endif
#else /* BOOST_PP_IS_ITERATING */

#define N BOOST_PP_ITERATION()

template<class T>
BOOST_FORCEINLINE nt2::container::table<T,nt2::of_size_<N> >
cons(BOOST_PP_ENUM_PARAMS(N, T const& a))
{
  T const data[] = { BOOST_PP_ENUM_PARAMS(N, a) };
  return nt2::container::
  table<T,nt2::of_size_<N> >
  (
    nt2::of_size(N)
  , &data[0]
  , &data[0] + N
  );
}

template<class T>
BOOST_FORCEINLINE nt2::container::table<T, nt2::storage_size_<N> >
cons(nt2::of_size_max const& sz, BOOST_PP_ENUM_PARAMS(N, T const& a))
{
  BOOST_ASSERT_MSG( nt2::numel(sz) <= N, "Incompatible size in cons");

  T const data[] = { BOOST_PP_ENUM_PARAMS(N, a) };
  return nt2::container::
         table<T, nt2::storage_size_<N> >
  (
    sz
  , &data[0]
  , &data[0] + N
  );
}

#undef N

#endif
