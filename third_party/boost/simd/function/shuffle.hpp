//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SHUFFLE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-swar

    Shuffle the elements of a boost::simd::pack using an index permutation described by compile-time
    integral constants.


    @par Header <boost/simd/function/shuffle.hpp>

    @par Semantic:

    For any boost::simd::pack @c x of base type @c T and cardinal @c N and @c N compile-time
    integral constants @c I1...In with value comprised between @c -1 and @c N-1, the following code:

    @code
    boost::simd::pack<T,N> r = shuffle<I1,...,In>(x);
    @endcode

    is equivalent to:

    @code
    boost::simd::pack<T,N> r{ I1 != -1 ? x[I1] : 0, ..., In != -1 ? x[In] : 0 };
    @endcode

    The actual integral constants is mapped at compile-time to the optimal sequence of
    intrinsics to apply the desired permutation.

    The special index value @c -1 is used to specify that, instead of fetching a data from inside
    the shuffled boost::simd::pack, the value @c 0 has to be inserted in the result.

    @par Example:

      @snippet shuffle.unary.cpp shuffle.unary

    @par Possible output:

      @snippet shuffle.unary.txt shuffle.unary

    @param  x  boost::simd::pack to shuffle
  **/
  template<int P0, int ... Ps, typename T>  T shuffle(T const& x);

  /*!
    @ingroup group-swar

    Shuffle the elements of two boost::simd::pack using an index permutation described by
    compile-time integral constants.

    @par Semantic:

    For any boost::simd::pack @c x and @c y of base type @c T and cardinal @c N and @c N
    compile-time integral constants @c I1...In with value comprised between @c -1 and @c 2*N-1,
    the following code:

    @code
    boost::simd::pack<T,N> r = shuffle<I1,...,In>(x,y);
    @endcode

    is equivalent to:

    @code
    boost::simd::pack<T,N> r{ I1 != -1 ? (I1<N ? x[I1] : y[I1-N]) : 0, ..., In != -1 ? (In<N ? x[In] : y[In-N]) : 0 };
    @endcode

    The actual integral constants is mapped at compile-time to the optimal sequence of
    intrinsics to apply the desired permutation.

    The special index value @c -1 is used to specify that, instead of fetching a data from inside
    the shuffled boost::simd::pack, the value @c 0 has to be inserted in the result.

    @par Example:

      @snippet shuffle.binary.cpp shuffle.binary

    @par Possible output:

      @snippet shuffle.binary.txt shuffle.binary

    @param  x  boost::simd::pack to shuffle
    @param  y  boost::simd::pack to shuffle
  **/
  template<int P0, int ... Ps, typename T>  T shuffle(T const& x, T const& y);

  /*!
    @ingroup group-swar

    Shuffle the elements of a boost::simd::pack using an index permutation described by compile-time
    meta-function.

    @par Semantic:

    For any boost::simd::pack @c x of base type @c T and cardinal @c N and a meta-function @c Perm,
    the following code:

    @code
    boost::simd::pack<T,N> r = shuffle<Perm>(x);
    @endcode

    is equivalent to:

    @code
    boost::simd::pack<T,N> r = shuffle<Perm::apply<0,N>::value,...,Perm::apply<N-1,N>::value>(x);
    @endcode

    The permutation computed by the meta-function @c Perm is mapped at compile-time to the
    optimal sequence of intrinsics to apply the desired permutation.

    @par Defining a permutation meta-function

    Permutation meta-function can be built in two different ways:

    - Define a Permutation meta-function as a struct with an internal @c apply structure that
      proceed to compute a given permutation index at compile-time. This @c apply internal
      structure takes two integral constant types as parameter: @c C the cardinal of the
      boost::simd::pack to be shuffled and @c I the index of the permutation index computed.

    - Define a @c constexpr function taking two integers: @c c the cardinal of the boost::simd::pack
      to be shuffled and @c i the index of the permutation index computed. This function returns the
      computed value of the permutation index computed. Said function is then wrapped inside the
      boost::simd::pattern template type before being used with boost::simd::shuffle.

    The special index value @c -1 can be returned to specify that, instead of fetching a data from
    inside the shuffled boost::simd::pack, the value @c 0 has to be inserted in the result.

    @notebox{Using permutation expressed as a metafunction has the advantage to be cardinal agnostic,
    thus making a given shuffle calls independant of the actual pack cardinal, leading to a more
    generic code}

    @par Example:

      @snippet shuffle.perm.cpp shuffle.perm

    @par Possible output:

      @snippet shuffle.perm.txt shuffle.perm

    @tparam Permutation Permutation meta-function generating the permutation index
    @param  x           boost::simd::pack to shuffle
  **/
  template<typename Permutation, typename T>  T shuffle(T const& x);

  /*!
    @ingroup group-swar

    Shuffle the elements of two boost::simd::pack using an index permutation described by
    compile-time meta-function.

    @par Semantic:

    For any boost::simd::pack @c x and @c y of base type @c T and cardinal @c N and a
    meta-function @c Perm, the following code:

    @code
    boost::simd::pack<T,N> r = shuffle<Perm>(x,y);
    @endcode

    is equivalent to:

    @code
    boost::simd::pack<T,N> r = shuffle<Perm::apply<0,N>::value,...,Perm::apply<N-1,N>::value>(x,y);
    @endcode

    The permutation computed by the meta-function @c Perm is mapped at compile-time to the
    optimal sequence of intrinsics to apply the desired permutation.

    @par Defining a permutation meta-function

    Permutation meta-function can be built in two different ways:

    - Define a Permutation meta-function as a struct with an internal @c apply structure that
      proceed to compute a given permutation index at compile-time. This @c apply internal
      structure takes two integral constant types as parameter: @c C the cardinal of the
      boost::simd::pack to be shuffled and @c I the index of the permutation index computed.

    - Define a @c constexpr function taking two integers: @c c the cardinal of the boost::simd::pack
      to be shuffled and @c i the index of the permutation index computed. This function returns the
      computed value of the permutation index computed. Said function is then wrapped inside the
      boost::simd::pattern template type before being used with boost::simd::shuffle.

    The special index value @c -1 can be returned to specify that, instead of fetching a data from
    inside the shuffled boost::simd::pack, the value @c 0 has to be inserted in the result.

    @notebox{Using permutation expressed as a metafunction has the advantage to be cardinal agnostic,
    thus making a given shuffle calls independant of the actual pack cardinal, leading to a more
    generic code}

    @par Example:

      @snippet shuffle.perm2.cpp shuffle.perm2

    @par Possible output:

      @snippet shuffle.perm2.txt shuffle.perm2

    @tparam Permutation Permutation meta-function generating the permutation index
    @param  x           boost::simd::pack to shuffle
    @param  y           boost::simd::pack to shuffle
  **/
  template<typename Permutation, typename T>  T shuffle(T const& x,T const& y);
} }
#endif

#include <boost/simd/function/scalar/shuffle.hpp>
#include <boost/simd/function/simd/shuffle.hpp>

#endif
