//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_ALL_REDUCE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_ALL_REDUCE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief all_reduce generic tag

      Represents the all_reduce function in generic contexts.
    **/
    struct all_reduce_ : ext::unspecified_<all_reduce_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<all_reduce_> parent;
    };
  }

  /*!
    @brief Broadcast reduction

    Computes a reduction across a vector values and broadcast its value into
    a full output vector.

    @par Semantic

    Depending on the type of its arguments, all_reduce exhibits different
    semantics. For any SIMD value @c v of type @c Type and any binary function tag
    @c F:

    @code
    Type r = all_reduce<F>(v);
    @endcode

    is equivalent to:

    @code
    for(int i=0;i<Type::static_size;++i)
      x[i] = reduce<F>(v);
    @endcode

    @param  value Value to reduce and broadcast
    @tparam Tag   Function tag of the reduction to apply

    @return A value containing the broadcast result of the reduction of @c value
            by the function represented by @c Tag
  */
  template<typename Tag, typename Type>
  BOOST_FORCEINLINE
  typename  boost::dispatch::meta::
            result_of < typename boost::dispatch::meta::
                        dispatch_call < tag::all_reduce_
                                      ( Type const&
                                      , boost::dispatch::meta::as_<Tag> const
                                      )
                                      >::type
                        ( Type const&
                        , boost::dispatch::meta::as_<Tag> const
                        )
                      >::type
  all_reduce(Type const& value)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::all_reduce_
                                  ( Type const&
                                  , boost::dispatch::meta::as_<Tag> const
                                  )>::type          callee;
    return callee(value,boost::dispatch::meta::as_<Tag>());
  }
} }

#endif
