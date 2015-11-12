//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_META_UNROLL_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_META_UNROLL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Specializations for unroll (Duff's devices optimization)
////////////////////////////////////////////////////////////////////////////////

namespace boost{ namespace simd{ namespace meta{

  template<int N>
  struct unroll
  {};

  template<>
  struct unroll<0>
  {
    template<class SimdInputIterator, class SimdOutputIterator, class UnOp>
    inline static void
    apply( SimdInputIterator& in, SimdInputIterator const& end
         , SimdOutputIterator& out, UnOp f)
    {
      while(in != end)
      *out++ = f(*in++);
    }

    template<class SimdInputIterator, class SimdOutputIterator, class BinOp>
    inline static void
    apply( SimdInputIterator& in1, SimdInputIterator& in2
         , SimdInputIterator const& end, SimdOutputIterator& out, BinOp f)
    {
      while(in1 != end)
      *out++ = f(*in1++,*in2++);
    }

  };

  template<>
  struct unroll<2>
  {
    template<class SimdInputIterator, class SimdOutputIterator, class UnOp>
    inline static void
    apply( SimdInputIterator& in, SimdInputIterator const& end
         , SimdOutputIterator& out, UnOp f)
    {
      typename SimdInputIterator::difference_type distance = end - in;
      typename SimdInputIterator::difference_type n = (distance + 1) / 2;

      switch(distance % 2)
      {
        case 0 : do{
          *out++ = f(*in++);
        case 1 : *out++ = f(*in++);
        } while(--n > 0);
      }
    }

    template<class SimdInputIterator, class SimdOutputIterator, class BinOp>
    inline static void
    apply( SimdInputIterator& in1, SimdInputIterator& in2
         , SimdInputIterator const& end, SimdOutputIterator& out, BinOp f)
    {
      typename SimdInputIterator::difference_type distance = end - in1;
      typename SimdInputIterator::difference_type n = (distance + 1) / 2;

      switch(distance % 2)
      {
        case 0 : do{
          *out++ = f(*in1++,*in2++);
        case 1 : *out++ = f(*in1++,*in2++);
        } while(--n > 0);
      }
    }
  };

  template<>
  struct unroll<4>
  {
    template<class SimdInputIterator, class SimdOutputIterator, class UnOp>
    inline static void
    apply( SimdInputIterator& in, SimdInputIterator const& end
         , SimdOutputIterator& out, UnOp f)
    {
      typename SimdInputIterator::difference_type distance = end - in;
      typename SimdInputIterator::difference_type n = (distance + 3) / 4;

      switch(distance % 4)
      {
        case 0 : do{
          *out++ = f(*in++);
        case 3 : *out++ = f(*in++);
        case 2 : *out++ = f(*in++);
        case 1 : *out++ = f(*in++);
        } while(--n > 0);
      }
    }

    template<class SimdInputIterator, class SimdOutputIterator, class BinOp>
    inline static void
    apply( SimdInputIterator& in1, SimdInputIterator& in2
         , SimdInputIterator const& end, SimdOutputIterator& out, BinOp f)
    {
      typename SimdInputIterator::difference_type distance = end - in1;
      typename SimdInputIterator::difference_type n = (distance + 3) / 4;

      switch(distance % 4)
      {
        case 0 : do{
          *out++ = f(*in1++,*in2++);
        case 3 : *out++ = f(*in1++,*in2++);
        case 2 : *out++ = f(*in1++,*in2++);
        case 1 : *out++ = f(*in1++,*in2++);
        } while(--n > 0);
      }
    }

  };

  template<>
  struct unroll<8>
  {
    template<class SimdInputIterator, class SimdOutputIterator, class UnOp>
    inline static void
    apply( SimdInputIterator& in, SimdInputIterator const& end
         , SimdOutputIterator& out, UnOp f)
    {
      typename SimdInputIterator::difference_type distance = end - in;
      typename SimdInputIterator::difference_type n = (distance + 7) / 8;

      switch(distance % 8)
      {
        case 0 : do{
          *out++ = f(*in++);
        case 7 : *out++ = f(*in++);
        case 6 : *out++ = f(*in++);
        case 5 : *out++ = f(*in++);
        case 4 : *out++ = f(*in++);
        case 3 : *out++ = f(*in++);
        case 2 : *out++ = f(*in++);
        case 1 : *out++ = f(*in++);
        } while(--n > 0);
      }
    }

    template<class SimdInputIterator, class SimdOutputIterator, class BinOp>
    inline static void
    apply( SimdInputIterator& in1, SimdInputIterator& in2
         , SimdInputIterator const& end, SimdOutputIterator& out, BinOp f)
    {
      typename SimdInputIterator::difference_type distance = end - in1;
      typename SimdInputIterator::difference_type n = (distance + 7) / 8;

      switch(distance % 8)
      {
        case 0 : do{
          *out++ = f(*in1++,*in2++);
        case 7 : *out++ = f(*in1++,*in2++);
        case 6 : *out++ = f(*in1++,*in2++);
        case 5 : *out++ = f(*in1++,*in2++);
        case 4 : *out++ = f(*in1++,*in2++);
        case 3 : *out++ = f(*in1++,*in2++);
        case 2 : *out++ = f(*in1++,*in2++);
        case 1 : *out++ = f(*in1++,*in2++);
        } while(--n > 0);
      }
    }
  };

  template<>
  struct unroll<16>
  {
    template<class SimdInputIterator, class SimdOutputIterator, class UnOp>
    inline static void
    apply( SimdInputIterator& in, SimdInputIterator const& end
         , SimdOutputIterator& out, UnOp f)
    {
      typename SimdInputIterator::difference_type distance = end - in;
      typename SimdInputIterator::difference_type n = (distance + 15) / 16;

      switch(distance % 16)
      {
        case 0 : do{
          *out++ = f(*in++);
        case 15 : *out++ = f(*in++);
        case 14 : *out++ = f(*in++);
        case 13 : *out++ = f(*in++);
        case 12 : *out++ = f(*in++);
        case 11 : *out++ = f(*in++);
        case 10 : *out++ = f(*in++);
        case 9  : *out++ = f(*in++);
        case 8  : *out++ = f(*in++);
        case 7  : *out++ = f(*in++);
        case 6  : *out++ = f(*in++);
        case 5  : *out++ = f(*in++);
        case 4  : *out++ = f(*in++);
        case 3  : *out++ = f(*in++);
        case 2  : *out++ = f(*in++);
        case 1  : *out++ = f(*in++);
        } while(--n > 0);
      }
    }

    template<class SimdInputIterator, class SimdOutputIterator, class BinOp>
    inline static void
    apply( SimdInputIterator& in1, SimdInputIterator& in2
         , SimdInputIterator const& end, SimdOutputIterator& out, BinOp f)
    {
      typename SimdInputIterator::difference_type distance = end - in1;
      typename SimdInputIterator::difference_type n = (distance + 15) / 16;

      switch(distance % 16)
      {
        case 0 : do{
          *out++ = f(*in1++,*in2++);
        case 15 : *out++ = f(*in1++,*in2++);
        case 14 : *out++ = f(*in1++,*in2++);
        case 13 : *out++ = f(*in1++,*in2++);
        case 12 : *out++ = f(*in1++,*in2++);
        case 11 : *out++ = f(*in1++,*in2++);
        case 10 : *out++ = f(*in1++,*in2++);
        case 9  : *out++ = f(*in1++,*in2++);
        case 8  : *out++ = f(*in1++,*in2++);
        case 7  : *out++ = f(*in1++,*in2++);
        case 6  : *out++ = f(*in1++,*in2++);
        case 5  : *out++ = f(*in1++,*in2++);
        case 4  : *out++ = f(*in1++,*in2++);
        case 3  : *out++ = f(*in1++,*in2++);
        case 2  : *out++ = f(*in1++,*in2++);
        case 1  : *out++ = f(*in1++,*in2++);
        } while(--n > 0);
      }
    }
  };

} } }



#endif
