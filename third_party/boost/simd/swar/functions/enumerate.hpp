//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_ENUMERATE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_ENUMERATE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag enumerate_ of functor enumerate
     *        in namespace boost::simd::tag for toolbox boost.simd.enumerate
    **/
    struct enumerate_ : ext::unspecified_<enumerate_>
    {
      typedef ext::unspecified_<enumerate_> parent;
    };
  }

  /*!
    @brief Linear enumeration of value

    Return a SIMD register containing a linear enumeration of value defined
    by a seed value and a step.

    @par Semantic:

    For any given SIMD type @c T, and any value @c seed and @c step of a scalar
    type @c S, the following  code :

    @code
    T r = enumerate<T>(seed, step);
    @endcode

    is equivalent to

    @code
    T r = make<T>(seed, seed + step, ... ,  seed + (N-1)*step);
    @endcode

    where @c N is the equal to <tt>cardinal_of<T>::value</tt>.

    For any given SIMD type @c T, and any value @c seed and @c step of a SIMD
    type @c S, the following  code :

    @code
    T r = enumerate<T>(seed, step);
    @endcode

    is equivalent to

    @code
    T r = splat<T>(seed) + splat<T>(step)*enumerate<T>();
    @endcode

    @tparam T Result type of the enumeration

    @param seed Initial value of the enumeration. By default, @c seed is equals
                to 0.

    @param step Scaling factor of the enumeration step. By default, @c step is
                equals to 1.

    @return A SIMD register of scalar type @c T
  **/
  template<class T,class A0, class A1> BOOST_FORCEINLINE
  typename  boost::dispatch::meta::
            call<tag::enumerate_( A0 const&,
                                  A1 const&,
                                  boost::dispatch::meta::as_<T>
                                )
                            >::type
  enumerate(A0 const& seed, A1 const& step)
  {
    typename boost::dispatch::make_functor<tag::enumerate_, A0>::type callee;
    return callee(seed,step,boost::dispatch::meta::as_<T>());
  }

  /// @overload
  template<class T,class A0> BOOST_FORCEINLINE
  typename  boost::dispatch::meta::
            call<tag::enumerate_( A0 const&
                                , boost::dispatch::meta::as_<T>
                                )
                            >::type
  enumerate(A0 const& seed)
  {
    typename boost::dispatch::make_functor<tag::enumerate_, A0>::type callee;
    return callee(seed,boost::dispatch::meta::as_<T>());
  }

  /// @overload
  template<class T> BOOST_FORCEINLINE
  typename  boost::dispatch::meta::
            call<tag::enumerate_( boost::dispatch::meta::as_<T> )
                            >::type
  enumerate()
  {
    typename boost::dispatch::make_functor<tag::enumerate_, T>::type callee;
    return callee(boost::dispatch::meta::as_<T>());
  }
} }

#endif
