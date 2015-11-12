//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014               MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_ALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_ALIGNED_LOAD_HPP_INCLUDED

#include <boost/simd/memory/functions/aligned_load.hpp>
#include <boost/simd/memory/functions/details/load.hpp>
#include <boost/simd/memory/functions/details/check_ptr.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/mpl/equal_to.hpp>
#include <iterator>

#include <boost/simd/memory/functions/load.hpp>
#include <boost/simd/constant/constants/zero.hpp>
#include <boost/simd/constant/constants/false.hpp>

#include <boost/simd/memory/functions/details/zero_or_false.hpp>


namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - Regular SIMD mask load with offset, zero
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_, tag::cpu_
                                    , (A0)(A1)(A2)(A3)(X)
                                    , (iterator_<unspecified_<A0> >)
                                      ((target_< simd_<unspecified_<A1>,X> >))
                                      (scalar_< integer_<A2> >)
                                      ((simd_< logical_<A3>
                                             , X
                                             >
                                      ))
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0,A1 const&,const A2& a2, const A3& a3) const
    {
      return aligned_load<result_type>(a0+a2,a3);
    }
  };

  /// INTERNAL ONLY - Regular SIMD mask load with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_, tag::cpu_
                                    , (A0)(A1)(A2)(A3)(A4)(X)
                                    , (iterator_<unspecified_<A0> >)
                                      ((target_< simd_<unspecified_<A1>,X> >))
                                      (scalar_< integer_<A2> >)
                                      ((simd_< logical_<A3>
                                             , X
                                             >
                                      ))
                                      ((simd_< unspecified_<A4>, X>))
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0,A1 const&,const A2& a2, const A3& a3, const A4& a4) const
    {
      return aligned_load<result_type>(a0+a2,a3,a4);
    }
  };

  /// INTERNAL ONLY - Regular SIMD load with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_, tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , (iterator_<unspecified_<A0> >)
                                      ((target_< simd_<unspecified_<A1>,X> >))
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0,A1 const& ,const A2& a2) const
    {
      return aligned_load<result_type>(a0+a2);
    }
  };

  /// INTERNAL ONLY - Misaligned mask load with offset, zero
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_, tag::cpu_
                                    , (A0)(A1)(A2)(A3)(A4)(X)
                                    , (iterator_<scalar_< unspecified_<A0> > >)
                                      ((target_<simd_< unspecified_<A1>, X> >))
                                      (scalar_<integer_<A2> >)
                                      (mpl_integral_<scalar_< integer_<A3> > >)
                                      ((simd_< logical_<A4>
                                             , X
                                             >
                                      ))
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A1 const&, const A2& a2, const A3&, const A4& a4) const
    {
      return boost::simd::aligned_load<result_type,A3::value>( a0+a2, a4);
    }
  };

    /// INTERNAL ONLY - Misaligned mask load with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_, tag::cpu_
                                    , (A0)(A1)(A2)(A3)(A4)(A5)(X)
                                    , (iterator_<scalar_< unspecified_<A0> > >)
                                      ((target_<simd_< unspecified_<A1>, X> >))
                                      (scalar_<integer_<A2> >)
                                      (mpl_integral_<scalar_< integer_<A3> > >)
                                      ((simd_< logical_<A4>
                                             , X
                                             >
                                      ))
                                      ((simd_< unspecified_<A5>, X>))
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A1 const&, const A2& a2, const A3&, const A4& a4, const A5& a5) const
    {
      return boost::simd::aligned_load<result_type,A3::value>( a0+a2, a4, a5 );
    }
  };

  /// INTERNAL ONLY - Misaligned load with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_, tag::cpu_
                                    , (A0)(A1)(A2)(A3)(X)
                                    , (iterator_<scalar_< unspecified_<A0> > >)
                                      ((target_<simd_< unspecified_<A1>, X> >))
                                      (scalar_<integer_<A2> >)
                                      (mpl_integral_<scalar_< integer_<A3> > >)
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A1 const&, const A2& a2, const A3&) const
    {
      return boost::simd::aligned_load<result_type,A3::value>( a0+a2 );
    }
  };

 /// INTERNAL ONLY - Regular SIMD mask load without offset, mask
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , tag::cpu_
                                    , (A0)(A2)(A3)(X)
                                    , (iterator_< scalar_<arithmetic_<A0> > >)
                                      ((target_< simd_<arithmetic_<A2>,X> >))
                                      ((simd_< logical_<A3>
                                             , X
                                             >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0,const A2&, const A3& a3) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR_CVT(a0, result_type, typename std::iterator_traits<A0>::value_type);
      return load<result_type>(a0, a3, Zero<result_type>());
    }
  };

  /// INTERNAL ONLY - Regular SIMD mask load without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , tag::cpu_
                                    , (A0)(A2)(A3)(A4)(X)
                                    , (iterator_< scalar_<arithmetic_<A0> > >)
                                      ((target_< simd_<arithmetic_<A2>,X> >))
                                      ((simd_< logical_<A3>
                                             , X
                                             >
                                      ))
                                      ((simd_< unspecified_<A4>, X>))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0,const A2&, const A3& a3, const A4& a4) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR_CVT(a0, result_type, typename std::iterator_traits<A0>::value_type);
      return load<result_type>(a0, a3, a4);
    }
  };

  /// INTERNAL ONLY - Regular SIMD load without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , tag::cpu_
                                    , (A0)(A2)(X)
                                    , (iterator_< scalar_<arithmetic_<A0> > >)
                                      ((target_< simd_<arithmetic_<A2>,X> >))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0,const A2&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR_CVT(a0, result_type, typename std::iterator_traits<A0>::value_type);
      return load<result_type>(a0);
    }
  };

/// INTERNAL ONLY - SIMD mask load with misalignment without offset, zero
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , tag::cpu_
                                    , (A0)(A2)(A3)(A4)(X)
                                    , (iterator_< scalar_< arithmetic_<A0> > >)
                                      ((target_<simd_< arithmetic_<A2>, X > >))
                                      (mpl_integral_< scalar_< integer_<A3> > >)
                                      ((simd_< logical_<A4>
                                             , X
                                             >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 a0, const A2&, const A3&, const A4& a4) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR_CVT(a0-A3::value, result_type, typename std::iterator_traits<A0>::value_type);
      return load<result_type>(a0, a4, Zero<result_type>());
    }
  };

  /// INTERNAL ONLY - SIMD mask load with misalignment without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , tag::cpu_
                                    , (A0)(A2)(A3)(A4)(A5)(X)
                                    , (iterator_< scalar_< arithmetic_<A0> > >)
                                      ((target_<simd_< arithmetic_<A2>, X > >))
                                      (mpl_integral_< scalar_< integer_<A3> > >)
                                      ((simd_< logical_<A4>
                                             , X
                                             >
                                      ))
                                      ((simd_< unspecified_<A5>, X>))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 a0, const A2&, const A3&, const A4& a4, const A5& a5) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR_CVT(a0-A3::value, result_type, typename std::iterator_traits<A0>::value_type);
      return load<result_type>(a0, a4, a5);
    }
  };

  /// INTERNAL ONLY - SIMD load with misalignment without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , tag::cpu_
                                    , (A0)(A2)(A3)(X)
                                    , (iterator_< scalar_< arithmetic_<A0> > >)
                                      ((target_<simd_< arithmetic_<A2>, X > >))
                                      (mpl_integral_< scalar_< integer_<A3> > >)
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 a0, const A2&, const A3&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR_CVT(a0-A3::value, result_type, typename std::iterator_traits<A0>::value_type);
      return load<result_type>(a0);
    }
  };

  /// INTERNAL ONLY - SIMD mask load with gather - gather means SIMD offset, zero
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::aligned_load_, tag::cpu_
                                       , (A0)(A1)(A2)(A3)(X)(Y)
                                       , ( mpl::equal_to
                                         < boost::simd::meta
                                                ::cardinal_of<typename A1::type>
                                         , boost::simd::meta
                                                ::cardinal_of<A2>
                                         >
                                         )
                                       , (iterator_< unspecified_<A0> >)
                                         ((target_<simd_<unspecified_<A1>,Y> >))
                                         ((simd_< integer_<A2>, X >))
                                         ((simd_< logical_<A3>
                                                , X
                                                >
                                         ))
                                       )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, const A1&, const A2& a2, const A3& a3) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR_CVT(a0, result_type, typename std::iterator_traits<A0>::value_type);
      return load<result_type>(a0, a2, a3, details::Zero_or_False<result_type>());
    }
  };

  /// INTERNAL ONLY - SIMD mask load with gather - gather means SIMD offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::aligned_load_, tag::cpu_
                                       , (A0)(A1)(A2)(A3)(A4)(X)(Y)
                                       , ( mpl::equal_to
                                         < boost::simd::meta
                                                ::cardinal_of<typename A1::type>
                                         , boost::simd::meta
                                                ::cardinal_of<A2>
                                         >
                                         )
                                       , (iterator_< unspecified_<A0> >)
                                         ((target_<simd_<unspecified_<A1>,Y> >))
                                         ((simd_< fundamental_<A2>, X >))
                                         ((simd_< logical_<A3>
                                                , X
                                                >
                                         ))
                                         ((simd_< unspecified_<A4>, X>))
                                       )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, const A1&, const A2& a2, const A3& a3, const A4& a4) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR_CVT(a0, result_type, typename std::iterator_traits<A0>::value_type);
      return load<result_type>(a0, a2, a3, a4);
    }
  };

  /// INTERNAL ONLY - SIMD load with gather - gather means SIMD offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::aligned_load_, tag::cpu_
                                       , (A0)(A1)(A2)(X)(Y)
                                       , ( mpl::equal_to
                                         < boost::simd::meta
                                                ::cardinal_of<typename A1::type>
                                         , boost::simd::meta
                                                ::cardinal_of<A2>
                                         >
                                         )
                                       , (iterator_< unspecified_<A0> >)
                                         ((target_<simd_<unspecified_<A1>,Y> >))
                                         ((simd_< fundamental_<A2>, X >))
                                       )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, const A1&, const A2& a2) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR_CVT(a0, result_type, typename std::iterator_traits<A0>::value_type);
      return load<result_type>(a0, a2);
    }
  };

 // INTERNAL ONLY - SIMD mask load for deinterlacing or logical, mask
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , tag::cpu_
                                    , (A0)(A2)(A3)(X)
                                    , (iterator_<unspecified_<A0> >)
                                      ((target_< simd_<unspecified_<A2>,X> >))
                                      ((simd_< logical_<A3>
                                             , X
                                             >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0,const A2&, const A3& a3) const
    {
      return load<result_type>(a0, a3, details::Zero_or_False<result_type>());
    }
  };

  // INTERNAL ONLY - SIMD mask load for deinterlacing or logical
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , tag::cpu_
                                    , (A0)(A2)(A3)(A4)(X)
                                    , (iterator_<unspecified_<A0> >)
                                      ((target_< simd_<unspecified_<A2>,X> >))
                                      ((simd_< logical_<A3>
                                             , X
                                             >
                                      ))
                                      ((simd_< unspecified_<A4>, X>))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0,const A2&, const A3& a3, const A4& a4) const
    {
      return load<result_type>(a0, a3, a4);
    }
  };

  // INTERNAL ONLY - SIMD load for deinterlacing or logical
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , tag::cpu_
                                    , (A0)(A2)(X)
                                    , (iterator_<unspecified_<A0> >)
                                      ((target_< simd_<unspecified_<A2>,X> >))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0,const A2&) const
    {
      return load<result_type>(a0);
    }
  };

 /// INTERNAL ONLY - SIMD mask load with misalignment without offset, zero
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , tag::cpu_
                                    , (A0)(A2)(A3)(A4)(X)
                                    , (iterator_<unspecified_<A0> >)
                                      ((target_<simd_< unspecified_<A2>, X > >))
                                      (mpl_integral_< scalar_< integer_<A3> > >)
                                      ((simd_< logical_<A4>
                                             , X
                                             >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 a0, const A2&, const A3&, const A4& a4) const
    {
      return load<result_type>(a0, a4, details::Zero_or_False<result_type>());
    }
  };

  /// INTERNAL ONLY - SIMD mask load with misalignment without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , tag::cpu_
                                    , (A0)(A2)(A3)(A4)(A5)(X)
                                    , (iterator_<unspecified_<A0> >)
                                      ((target_<simd_< unspecified_<A2>, X > >))
                                      (mpl_integral_< scalar_< integer_<A3> > >)
                                      ((simd_< logical_<A4>
                                             , X
                                             >
                                      ))
                                      ((simd_< unspecified_<A5>, X>))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 a0, const A2&, const A3&, const A4& a4, const A5& a5) const
    {
      return load<result_type>(a0, a4, a5);
    }
  };

  /// INTERNAL ONLY - SIMD load with misalignment without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , tag::cpu_
                                    , (A0)(A2)(A3)(X)
                                    , (iterator_<unspecified_<A0> >)
                                      ((target_<simd_< unspecified_<A2>, X > >))
                                      (mpl_integral_< scalar_< integer_<A3> > >)
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 a0, const A2&, const A3&) const
    {
      return load<result_type>(a0);
    }
  };

  /// INTERNAL ONLY - SIMD fusion sequence load with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_, tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , (fusion_sequence_<A0>)
                                      ((target_<simd_<fusion_sequence_<A1>,X> >))
                                      (generic_< integer_<A2> >)
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 a0, const A1&, const A2& a2) const
    {
      result_type that;
      meta::iterate < fusion::result_of::size<A0>::type::value>
                    ( details::loader < boost::simd::
                                        tag::aligned_load_(A0, result_type, A2)
                                      >(a0, that, a2)
                    );
      return that;
    }
  };

  /// INTERNAL ONLY - SIMD fusion sequence load without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_, tag::cpu_
                                    , (A0)(A2)(X)
                                    , (fusion_sequence_<A0>)
                                      ((target_<simd_<fusion_sequence_<A2>,X> >))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 a0, const A2&) const
    {
      result_type that;
      meta::iterate < fusion::result_of::size<A0>::type::value>
                    ( details::loader < boost::simd::
                                        tag::aligned_load_(A0, result_type)
                                      >(a0, that)
                    );
      return that;
    }
  };
} } }

#include <boost/simd/include/functions/simd/load.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/false.hpp>

#endif
