//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_TRANSFORM_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_TRANSFORM_HPP_INCLUDED

#include <boost/simd/range/segmented_aligned_range.hpp>
#include <boost/simd/function/aligned_store.hpp>
#include <boost/simd/function/store.hpp>
#include <boost/simd/pack.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/detail/is_aligned.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-algo

    Applies the given function @c f to the Contiguous Range  @range{first, last} and stores the
    result in another Contiguous Range, beginning at @c out.

    @param first  Beginning of the range of elements to transform
    @param last   End of the range of elements to transform
    @param out    Beginning of the destination range
    @param f      unary operation function object that will be applied.

    @par Requirement

      - @c first, @c last and @c out must be pointer to Vectorizable type.

      - @c f must be a polymorphic unary function object, i.e callable on generic types.
      - @c boost::simd::pack<T>::static_size @c == @c boost::simd::pack<U>::static_size

    @par Example

    The following code uses simd::transform to compute the square of the values stored in a
    @c std::vector.
    @snippet transform.unary.cpp transform-unary
    Expected output:
    @code
    1 4 9 16 25 36 49
    @endcode

    @return Pointer to the element past the last element transformed.
  **/
  template<typename T, typename U, typename UnOp>
  U* transform(T const* first, T const* last, U* out, UnOp const& f)
  {
    using vT = pack<T>;
    using vU = pack<U>;

    static_assert ( cardinal_of<vT>::value == cardinal_of<vU>::value
                  , "SIMD cardinal mismatch between T and U"
                  );

    auto pr = segmented_aligned_range(first,last);

    // prologue
    for( T e : pr.head ) *out++ = f(e);

    // main SIMD part - checks if we can store efficiently or not
    if(boost::simd::detail::is_aligned(out, vU::alignment))
    {
      for( vT e : pr.body )
      {
        aligned_store( f(e) ,out);
        out += vU::static_size;
      }
    }
    else
    {
      for( vT e : pr.body )
      {
        store( f(vT(e)) ,out);
        out += vU::static_size;
      }
    }

    // epilogue
    for( T e : pr.tail ) *out++ = f(e);

    return out;
  }

  /*!
    @ingroup group-algo

    Applies the given function @c f to pairs of elements from two ranges: one defined by
    @range{first1, last1} and the other beginning at @c first2, and stores the result in another
    Contiguous Range, beginning at @c out.

    @param first1  Beginning of the first range of elements to transform
    @param last1   End of the range of elements to transform
    @param first2  Beginning of the second range of elements to transform
    @param out     Beginning of the destination range
    @param f       unary operation function object that will be applied.

    @par Requirement

      - @c first, @c last and @c out must be pointer to Vectorizable type.

      - @c f must be a polymorphic binary function object, i.e callable on generic types.
      - @c boost::simd::pack<T1>::static_size @c == @c boost::simd::pack<T><U>::static_size
      - @c boost::simd::pack<T2>::static_size @c == @c boost::simd::pack<T><U>::static_size

    @par Example
    @snippet transform.binary.cpp transform-binary
    Possible output:
    @code
    0 0.5 0.666667 0.75 0.8 0.833333 0.857143
    @endcode

    @return Pointer to the element past the last element transformed.
  **/
  template<typename T1, typename T2, typename U, typename BinOp>
  U* transform(T1 const* first1, T1 const* last1, T2 const* first2, U* out, BinOp const& f)
  {
    using vT1 = boost::simd::pack<T1>;
    using vT2 = boost::simd::pack<T2>;
    using vU = pack<U>;

    static_assert ( cardinal_of<vT1>::value == cardinal_of<vT2>::value
                  , "SIMD cardinal mismatch between T1 and T2"
                  );

    static_assert ( cardinal_of<vT1>::value == cardinal_of<vU>::value
                  , "SIMD cardinal mismatch between T1 and U"
                  );

    static_assert ( cardinal_of<vT2>::value == cardinal_of<vU>::value
                  , "SIMD cardinal mismatch between T2 and U"
                  );

    auto pr = segmented_aligned_range(first1,last1);

    // prologue
    for( auto const& e : pr.head ) *out++ = f(e, *first2++);

    // main SIMD part - Everybody is aligned
    if(   boost::simd::detail::is_aligned(out    , vU::alignment )
      &&  boost::simd::detail::is_aligned(first2 , vT2::alignment)
      )
    {
      for( vT1 e : pr.body )
      {
        aligned_store( f(vT1(e), aligned_load<vT2>(first2) ) ,out);
        out     += vU::static_size;
        first2  += vT2::static_size;
      }
    }
    // main SIMD part - input1 and output is aligned
    else if( boost::simd::detail::is_aligned(out, vU::alignment ) )
    {
      for( vT1 e : pr.body )
      {
        aligned_store( f(vT1(e),load<vT2>(first2)) ,out);
        out     += vU::static_size;
        first2  += vT2::static_size;
      }
    }
    // main SIMD part - Both inputs is aligned
    else if( boost::simd::detail::is_aligned(first2, vT2::alignment ) )
    {
      for( vT1 e : pr.body )
      {
        store( f(vT1(e),aligned_load<vT2>(first2)) ,out);
        out     += vU::static_size;
        first2  += vT2::static_size;
      }
    }
    // main SIMD part - input1 is aligned
    else
    {
      for( vT1 e : pr.body )
      {
        store( f(vT1(e),load<vT2>(first2)) ,out);
        out     += vU::static_size;
        first2  += vT2::static_size;
      }
    }

    // epilogue
    for( auto && e : pr.tail ) *out++ = f(e, *first2++);
    return out;
  }
} }

#endif
