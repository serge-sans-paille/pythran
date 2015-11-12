//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SHUFFLE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>
#include <boost/simd/swar/functions/details/random_permute.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/mpl/vector/vector10_c.hpp>
#include <boost/mpl/vector/vector20_c.hpp>
#include <boost/mpl/vector/vector40_c.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief shuffle generic tag

      Represents the shuffle function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct shuffle_ : ext::unspecified_<shuffle_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<shuffle_> parent;
    };
  }

#if defined(DOXYGEN_ONLY)

/*!
  @brief SIMD register shuffling

  Shuffle the elements of one SIMD register following a compile-time
  permutation pattern passed as a static list of integral constants.

  @par Semantic:

  Let's @c T be a SIMD register type of cardinal @c N and <tt>I1,...,In</tt> be
  @c N integral constant in \f$[-1, N[\f$. For any SIMD register @c v of type
  @c T, the following code :

  @code
  T r = shuffle<I1, ..., Ic>(v);
  @endcode

  is equivalent to

  @code
  r[0]   = I1 == -1 ? 0 : v[I1];
  r[1]   = I2 == -1 ? 0 : v[I2];
  ...
  r[C-1] = Ic == -1 ? 0 : v[Ic];
  @endcode

  @usage{shuffle_idx1.cpp}

  @tparam Indices Integral constant defining the permutation pattern
  @param  a0 First register to shuffle

  @return A SIMD register shuffled as per the permutation pattern
**/
template<int Indices..., class A0>
details::unspecified shuffle(A0 const& a0)
{}

/*!
  @brief SIMD register shuffling

  Shuffle the elements of two SIMD registers following a compile-time
  permutation pattern passed as a static list of integral constants.

  @par Semantic:

  Let's @c T be a SIMD register type of cardinal @c N and <tt>I1,...,In</tt> be
  @c N integral constant in \f$[-1, N[\f$. For any SIMD register @c v1 and @c v2
  of type @c T, the following code :

  @code
  T r = shuffle<I1, ..., Ic>(v1,v2);
  @endcode

  is equivalent to shuffling the agglomeration of @c v1 and @c v2 and extracting
  the lower part of the resulting vector.

  @code
  r[0]   = shuffle<I1,...,Ic>( combine(v1,v2) )[0]
  r[0]   = shuffle<I1,...,Ic>( combine(v1,v2) )[1]
  ...
  r[C-1] = shuffle<I1,...,Ic>( combine(v1,v2) )[C-1]
  @endcode

  @usage{shuffle_idx2.cpp}

  @tparam Indices Integral constant defining the permutation pattern
  @param  a0 First register to shuffle
  @param  a1 Second register to shuffle.

  @return A SIMD register shuffled as per the permutation pattern
**/
template<int Indices..., class A0, class A1>
details::unspecified shuffle(A0 const& a0, A1 const& a1)
{}

#else

#define M0(z,n,arg)                                                            \
template<BOOST_PP_ENUM_PARAMS(n, int I),class A0>                              \
BOOST_FORCEINLINE                                                              \
typename boost::dispatch::meta                                                 \
::call<tag::shuffle_(A0 const&                                                 \
                    ,boost::dispatch::meta::                                   \
                     as_<details::random_permute                               \
                         <boost::mpl::                                         \
                          BOOST_PP_CAT(vector                                  \
                                      , BOOST_PP_CAT(n, _c))                   \
                                        <int,BOOST_PP_ENUM_PARAMS(n, I)>       \
                         >                                                     \
                        >                                                      \
                    )                                                          \
      >::type                                                                  \
shuffle(A0 const& a0)                                                          \
{                                                                              \
  typename boost::dispatch::make_functor<tag::shuffle_, A0>::type callee;      \
  return callee( a0                                                            \
               , boost::dispatch::meta::                                       \
                 as_< details::                                                \
                      random_permute< boost::mpl::                             \
                                      BOOST_PP_CAT( vector                     \
                                                  , BOOST_PP_CAT(n, _c))       \
                                                    < int                      \
                                                    ,BOOST_PP_ENUM_PARAMS(n,I) \
                                                    >                          \
                                    >                                          \
                    >()                                                        \
               );                                                              \
}                                                                              \
template<BOOST_PP_ENUM_PARAMS(n, int I),class A0, class A1>                    \
BOOST_FORCEINLINE                                                              \
typename boost::dispatch::meta                                                 \
::call<tag::shuffle_( A0 const&                                                \
                    , A1 const&                                                \
                    , boost::dispatch::meta::                                  \
                      as_<details::random_permute                              \
                          <boost::mpl::                                        \
                           BOOST_PP_CAT(vector, BOOST_PP_CAT(n, _c))           \
                           <int                                                \
                           ,BOOST_PP_ENUM_PARAMS(n, I)                         \
                           >                                                   \
                          >                                                    \
                         >                                                     \
                    )                                                          \
      >::type                                                                  \
shuffle(A0 const& a0, A1 const& a1)                                            \
{                                                                              \
  typename boost::dispatch::make_functor<tag::shuffle_, A0>::type callee;      \
  return callee( a0                                                            \
               , a1                                                            \
               , boost::dispatch::meta::                                       \
                 as_< details::                                                \
                      random_permute                                           \
                      <boost::mpl::                                            \
                       BOOST_PP_CAT(vector, BOOST_PP_CAT(n, _c))<int           \
                               ,BOOST_PP_ENUM_PARAMS(n, I)                     \
                               >                                               \
                      >                                                        \
                    >()                                                        \
               );                                                              \
}                                                                              \
/**/

  BOOST_SIMD_PP_REPEAT_POWER_OF_2(M0, ~)
  #undef M0
#endif

  /*!
    @brief SIMD register shuffling

    Shuffle the elements of two SIMD registers following a compile-time
    permutation pattern passed as a @metafunction.

    @par Semantic:

    Let's @c T be a SIMD register type of cardinal @c N, @c Perm be a
    binary @metafunction. For any SIMD register @c v1 and  @c v2 of type @c T,
    the following code:

    @code
    T r = shuffle<Perm>(v1,v2);
    @endcode

    is equivalent to

    @code
    T r = shuffle< mpl::apply<Perm, int_<0>, int_<C> >::type::value
                 , ...
                 , mpl::apply<Perm, int_<C-1>, int_<C> >::type::value
                 >(v1,v2);
    @endcode

    @usage{shuffle_perm1.cpp}

    @tparam Perm Permutation pattern @metafunction
    @param  a0 First register to shuffle
    @param  a1 Second register to shuffle.

    @return A SIMD register shuffled as per the permutation pattern
  **/
  template<class Perm,class A0, class A1>   BOOST_FORCEINLINE
#if defined(DOXYGEN_ONLY)
  details::unspecified_
#else
  typename  boost::dispatch::meta
          ::call< tag::shuffle_ ( A0 const&, A1 const&
                                , boost::dispatch::meta::as_<Perm>
                                )
                >::type
#endif
  shuffle(A0 const& a0, A1 const& a1)
  {
    typename boost::dispatch::make_functor<tag::shuffle_, A0>::type callee;
    return callee(a0,a1,boost::dispatch::meta::as_<Perm>());
  }

  /*!
    @brief SIMD register shuffling

    Shuffle the elements of one SIMD register following a compile-time
    permutation pattern passed as a @metafunction.

    @par Semantic:

    Let's @c T be a SIMD register type of cardinal @c N, @c Perm be a
    binary @metafunction. For any SIMD register @c v of type @c T, the following
    code:

    @code
    T r = shuffle<Perm>(v);
    @endcode

    is respectively equivalent to

    @code
    T r = shuffle< mpl::apply<Perm, int_<0>, int_<C> >::type::value
                 , ...
                 , mpl::apply<Perm, int_<C-1>, int_<C> >::type::value
                 >(v);
    @endcode

    @usage{shuffle_perm2.cpp}

    @tparam Perm Permutation pattern @metafunction
    @param  a0 First register to shuffle

    @return A SIMD register shuffled as per the permutation pattern
  **/
  template<class Perm,class A0> BOOST_FORCEINLINE
#if defined(DOXYGEN_ONLY)
  details::unspecified_
#else
  typename  boost::dispatch::meta
          ::call< tag::shuffle_ ( A0 const&
                                , boost::dispatch::meta::as_<Perm>
                                )
                >::type
#endif
  shuffle(A0 const& a0)
  {
    typename boost::dispatch::make_functor<tag::shuffle_, A0>::type callee;
    return callee(a0,boost::dispatch::meta::as_<Perm>());
  }
} }

#endif
