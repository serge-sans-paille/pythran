//==================================================================================================
/*
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_FUNCTOR_ICPC15_KLUDGE_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_FUNCTOR_ICPC15_KLUDGE_HPP_INCLUDED

#define BOOST_DISPATCH_IMPL_TAG_CALL_0(TAG,SITE,TAS,AS) \
  TAG::dispatch_to(SITE(),                              \
                   typename hierarchy_of<TAS>::type())  \
  (std::forward<TAS>(AS))                               \
  /**/

#define BOOST_DISPATCH_IMPL_TAG_CALL_1(TAG,SITE,TAS,AS,T0,A0)   \
  TAG::dispatch_to(SITE(),                                      \
                   typename hierarchy_of<TAS>::type(),          \
                   typename hierarchy_of<T0>::type())           \
  (std::forward<TAS>(AS),                                       \
   std::forward<T0>(A0))                                        \
  /**/

#define BOOST_DISPATCH_IMPL_TAG_CALL_2(TAG,SITE,TAS,AS,T0,T1,A0,A1)     \
  TAG::dispatch_to(SITE(),                                              \
                   typename hierarchy_of<TAS>::type(),                  \
                   typename hierarchy_of<T0>::type(),                   \
                   typename hierarchy_of<T1>::type())                   \
  (std::forward<TAS>(AS),                                               \
   std::forward<T0>(A0),                                                \
   std::forward<T1>(A1))                                                \
  /**/

#define BOOST_DISPATCH_IMPL_TAG_CALL_3(TAG,SITE,TAS,AS,         \
                                       T0,T1,T2,A0,A1,A2)       \
  TAG::dispatch_to(SITE(),                                      \
                   typename hierarchy_of<TAS>::type(),          \
                   typename hierarchy_of<T0>::type(),           \
                   typename hierarchy_of<T1>::type(),           \
                   typename hierarchy_of<T2>::type())           \
  (std::forward<TAS>(AS),                                       \
   std::forward<T0>(A0),                                        \
   std::forward<T1>(A1),                                        \
   std::forward<T2>(A2))                                        \
  /**/

#define BOOST_DISPATCH_IMPL_TAG_CALL_4(TAG,SITE,TAS,AS,         \
                                       T0,T1,T2,T3,A0,A1,A2,A3) \
  TAG::dispatch_to(SITE(),                                      \
                   typename hierarchy_of<TAS>::type(),          \
                   typename hierarchy_of<T0>::type(),           \
                   typename hierarchy_of<T1>::type(),           \
                   typename hierarchy_of<T2>::type(),           \
                   typename hierarchy_of<T3>::type())           \
  (std::forward<TAS>(AS),                                       \
   std::forward<T0>(A0),                                        \
   std::forward<T1>(A1),                                        \
   std::forward<T2>(A2),                                        \
   std::forward<T3>(A3))                                        \
  /**/

#define BOOST_DISPATCH_IMPL_TAG_CALL_8(TAG,SITE,TAS,AS,         \
                                       T0,T1,T2,T3,T4,T5,T6,T7, \
                                       A0,A1,A2,A3,A4,A5,A6,A7) \
  TAG::dispatch_to(SITE(),                                      \
                   typename hierarchy_of<TAS>::type(),          \
                   typename hierarchy_of<T0>::type(),           \
                   typename hierarchy_of<T1>::type(),           \
                   typename hierarchy_of<T2>::type(),           \
                   typename hierarchy_of<T3>::type(),           \
                   typename hierarchy_of<T4>::type(),           \
                   typename hierarchy_of<T5>::type(),           \
                   typename hierarchy_of<T6>::type(),           \
                   typename hierarchy_of<T7>::type())           \
  (std::forward<TAS>(AS),                                       \
   std::forward<T0>(A0),                                        \
   std::forward<T1>(A1),                                        \
   std::forward<T2>(A2),                                        \
   std::forward<T3>(A3),                                        \
   std::forward<T4>(A4),                                        \
   std::forward<T5>(A5),                                        \
   std::forward<T6>(A6),                                        \
   std::forward<T7>(A7))                                        \
  /**/

#define BOOST_DISPATCH_IMPL_TAG_CALL_16(TAG,SITE,TAS,AS,                \
                                        T0,T1,T2, T3, T4, T5, T6, T7,   \
                                        T8,T9,T10,T11,T12,T13,T14,T15,  \
                                        A0,A1,A2, A3, A4, A5, A6, A7,   \
                                        A8,A9,A10,A11,A12,A13,A14,A15)  \
  TAG::dispatch_to(SITE(),                                              \
                   typename hierarchy_of<TAS>::type(),                  \
                   typename hierarchy_of<T0>::type(),                   \
                   typename hierarchy_of<T1>::type(),                   \
                   typename hierarchy_of<T2>::type(),                   \
                   typename hierarchy_of<T3>::type(),                   \
                   typename hierarchy_of<T4>::type(),                   \
                   typename hierarchy_of<T5>::type(),                   \
                   typename hierarchy_of<T6>::type(),                   \
                   typename hierarchy_of<T7>::type(),                   \
                   typename hierarchy_of<T8>::type(),                   \
                   typename hierarchy_of<T9>::type(),                   \
                   typename hierarchy_of<T10>::type(),                  \
                   typename hierarchy_of<T11>::type(),                  \
                   typename hierarchy_of<T12>::type(),                  \
                   typename hierarchy_of<T13>::type(),                  \
                   typename hierarchy_of<T14>::type(),                  \
                   typename hierarchy_of<T15>::type())                  \
  (std::forward<TAS>(AS),                                               \
   std::forward<T0>(A0),                                                \
   std::forward<T1>(A1),                                                \
   std::forward<T2>(A2),                                                \
   std::forward<T3>(A3),                                                \
   std::forward<T4>(A4),                                                \
   std::forward<T5>(A5),                                                \
   std::forward<T6>(A6),                                                \
   std::forward<T7>(A7),                                                \
   std::forward<T8>(A8),                                                \
   std::forward<T9>(A9),                                                \
   std::forward<T10>(A10),                                              \
   std::forward<T11>(A11),                                              \
   std::forward<T12>(A12),                                              \
   std::forward<T13>(A13),                                              \
   std::forward<T14>(A14),                                              \
   std::forward<T15>(A15))                                              \
  /**/

#define BOOST_DISPATCH_IMPL_TAG_CALL_32(TAG,SITE,TAS,AS,                \
                                        T0,T1,T2,T3,T4,T5,T6,T7,        \
                                        T8,T9,T10,T11,T12,T13,T14,T15,  \
                                        T16,T17,T18,T19,T20,T21,T22,T23, \
                                        T24,T25,T26,T27,T28,T29,T30,T31, \
                                        A0,A1,A2,A3,A4,A5,A6,A7,        \
                                        A8,A9,A10,A11,A12,A13,A14,A15,  \
                                        A16,A17,A18,A19,A20,A21,A22,A23, \
                                        A24,A25,A26,A27,A28,A29,A30,A31) \
  TAG::dispatch_to(SITE(),                                              \
                   typename hierarchy_of<TAS>::type(),                  \
                   typename hierarchy_of<T0>::type(),                   \
                   typename hierarchy_of<T1>::type(),                   \
                   typename hierarchy_of<T2>::type(),                   \
                   typename hierarchy_of<T3>::type(),                   \
                   typename hierarchy_of<T4>::type(),                   \
                   typename hierarchy_of<T5>::type(),                   \
                   typename hierarchy_of<T6>::type(),                   \
                   typename hierarchy_of<T7>::type(),                   \
                   typename hierarchy_of<T8>::type(),                   \
                   typename hierarchy_of<T9>::type(),                   \
                   typename hierarchy_of<T10>::type(),                  \
                   typename hierarchy_of<T11>::type(),                  \
                   typename hierarchy_of<T12>::type(),                  \
                   typename hierarchy_of<T13>::type(),                  \
                   typename hierarchy_of<T14>::type(),                  \
                   typename hierarchy_of<T15>::type(),                  \
                   typename hierarchy_of<T16>::type(),                  \
                   typename hierarchy_of<T17>::type(),                  \
                   typename hierarchy_of<T18>::type(),                  \
                   typename hierarchy_of<T19>::type(),                  \
                   typename hierarchy_of<T20>::type(),                  \
                   typename hierarchy_of<T21>::type(),                  \
                   typename hierarchy_of<T22>::type(),                  \
                   typename hierarchy_of<T23>::type(),                  \
                   typename hierarchy_of<T24>::type(),                  \
                   typename hierarchy_of<T25>::type(),                  \
                   typename hierarchy_of<T26>::type(),                  \
                   typename hierarchy_of<T27>::type(),                  \
                   typename hierarchy_of<T28>::type(),                  \
                   typename hierarchy_of<T29>::type(),                  \
                   typename hierarchy_of<T30>::type(),                  \
                   typename hierarchy_of<T31>::type())                  \
  (std::forward<TAS>(AS),                                               \
   std::forward<T0>(A0),                                                \
   std::forward<T1>(A1),                                                \
   std::forward<T2>(A2),                                                \
   std::forward<T3>(A3),                                                \
   std::forward<T4>(A4),                                                \
   std::forward<T5>(A5),                                                \
   std::forward<T6>(A6),                                                \
   std::forward<T7>(A7),                                                \
   std::forward<T8>(A8),                                                \
   std::forward<T9>(A9),                                                \
   std::forward<T10>(A10),                                              \
   std::forward<T11>(A11),                                              \
   std::forward<T12>(A12),                                              \
   std::forward<T13>(A13),                                              \
   std::forward<T14>(A14),                                              \
   std::forward<T15>(A15),                                              \
   std::forward<T16>(A16),                                              \
   std::forward<T17>(A17),                                              \
   std::forward<T18>(A18),                                              \
   std::forward<T19>(A19),                                              \
   std::forward<T20>(A20),                                              \
   std::forward<T21>(A21),                                              \
   std::forward<T22>(A22),                                              \
   std::forward<T23>(A23),                                              \
   std::forward<T24>(A24),                                              \
   std::forward<T25>(A25),                                              \
   std::forward<T26>(A26),                                              \
   std::forward<T27>(A27),                                              \
   std::forward<T28>(A28),                                              \
   std::forward<T29>(A29),                                              \
   std::forward<T30>(A30),                                              \
   std::forward<T31>(A31))                                              \
  /**/

namespace boost{ namespace dispatch{
    /*!
      @ingroup group-function
      @brief Adaptable dispatch-enabled function object

      @tparam Tag
      @tparam Site
    **/
    template<typename Tag, typename Site = boost::dispatch::default_site<Tag> >
    struct functor
    {
      /*!
        @brief Architectural target rebinding

        Creates an instance of functor which shares current functor's tag but
        dispatched over a specific architecture hierarchy.

        @return a instance of functor dispatching specifically on architecture Other

        @tparam Other New architecture target to generate a functor for
      **/
      template<typename Other>
      static BOOST_FORCEINLINE functor<Tag,Other> rebind() BOOST_NOEXCEPT { return {}; }

      template<typename AS> BOOST_FORCEINLINE
      auto operator()(AS&& as) const
        BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(BOOST_DISPATCH_IMPL_TAG_CALL_0(Tag,Site,AS,as)))
        -> decltype (BOOST_DISPATCH_IMPL_TAG_CALL_0(Tag,Site,AS,as))
      {
        return BOOST_DISPATCH_IMPL_TAG_CALL_0(Tag,Site,AS,as);
      }

      template<typename AS, typename T> BOOST_FORCEINLINE
      auto operator()(AS&& as, T&& a0) const
        BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(BOOST_DISPATCH_IMPL_TAG_CALL_1(Tag,Site,AS,as,T,a0)))
        -> decltype (BOOST_DISPATCH_IMPL_TAG_CALL_1(Tag,Site,AS,as,T,a0))
      {
        return BOOST_DISPATCH_IMPL_TAG_CALL_1(Tag,Site,AS,as,T,a0);
      }

      template<typename AS, typename T0, typename T1> BOOST_FORCEINLINE
      auto operator()(AS&& as, T0&& a0, T1&& a1) const
        BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(BOOST_DISPATCH_IMPL_TAG_CALL_2(Tag,Site,AS,as,T0,T1,a0,a1)))
        -> decltype (BOOST_DISPATCH_IMPL_TAG_CALL_2(Tag,Site,AS,as,T0,T1,a0,a1))
      {
        return BOOST_DISPATCH_IMPL_TAG_CALL_2(Tag,Site,AS,as,T0,T1,a0,a1);
      }

      template<typename AS, typename T0, typename T1, typename T2> BOOST_FORCEINLINE
      auto operator()(AS&& as, T0&& a0, T1&& a1, T2&& a2) const
        BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(BOOST_DISPATCH_IMPL_TAG_CALL_3(Tag,Site,AS,as,T0,T1,T2,a0,a1,a2)))
        -> decltype (BOOST_DISPATCH_IMPL_TAG_CALL_3(Tag,Site,AS,as,T0,T1,T2,a0,a1,a2))
      {
        return BOOST_DISPATCH_IMPL_TAG_CALL_3(Tag,Site,AS,as,T0,T1,T2,a0,a1,a2);
      }

      template<typename AS, 
               typename T0, typename T1, typename T2, typename T3> BOOST_FORCEINLINE
      auto operator()(AS&& as, T0&& a0, T1&& a1, T2&& a2, T3&& a3) const
        BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(BOOST_DISPATCH_IMPL_TAG_CALL_4(Tag,Site,AS,as,
                                                                             T0,T1,T2,T3,a0,a1,a2,a3)))
        -> decltype (BOOST_DISPATCH_IMPL_TAG_CALL_4(Tag,Site,AS,as,T0,T1,T2,T3,a0,a1,a2,a3))
      {
        return BOOST_DISPATCH_IMPL_TAG_CALL_4(Tag,Site,AS,as,T0,T1,T2,T3,a0,a1,a2,a3);
      }


      template<typename AS, 
               typename T0, typename T1, typename T2, typename T3,
               typename T4, typename T5, typename T6, typename T7> BOOST_FORCEINLINE
      auto operator()(AS&& as,
                      T0&& a0, T1&& a1, T2&& a2, T3&& a3,
                      T4&& a4, T5&& a5, T6&& a6, T7&& a7) const
        BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(BOOST_DISPATCH_IMPL_TAG_CALL_8(Tag,Site,AS,as,
                                                                             T0,T1,T2,T3,T4,T5,T6,T7,
                                                                             a0,a1,a2,a3,a4,a5,a6,a7)))
        -> decltype (BOOST_DISPATCH_IMPL_TAG_CALL_8(Tag,Site,AS,as,
                                                    T0,T1,T2,T3,T4,T5,T6,T7,
                                                    a0,a1,a2,a3,a4,a5,a6,a7))
      {
        return BOOST_DISPATCH_IMPL_TAG_CALL_8(Tag,Site,AS,as,
                                              T0,T1,T2,T3,T4,T5,T6,T7,
                                              a0,a1,a2,a3,a4,a5,a6,a7);
      }

      template<typename AS, 
               typename T0,  typename T1,  typename T2,  typename T3,
               typename T4,  typename T5,  typename T6,  typename T7,
               typename T8,  typename T9,  typename T10, typename T11,
               typename T12, typename T13, typename T14, typename T15> BOOST_FORCEINLINE
      auto operator()(AS&& as,
                      T0&&  a0,  T1&&  a1,  T2&&  a2,  T3&&  a3,
                      T4&&  a4,  T5&&  a5,  T6&&  a6,  T7&&  a7,
                      T8&&  a8,  T9&&  a9,  T10&& a10, T11&& a11,
                      T12&& a12, T13&& a13, T14&& a14, T15&& a15) const
        BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(BOOST_DISPATCH_IMPL_TAG_CALL_16(Tag,Site,AS,as,
                                                                              T0,T1,T2,T3,T4,T5,T6,T7,
                                                                              T8,T9,T10,T11,T12,T13,T14,T15,
                                                                              a0,a1,a2,a3,a4,a5,a6,a7,
                                                                              a8,a9,a10,a11,a12,a13,a14,a15)))
        -> decltype (BOOST_DISPATCH_IMPL_TAG_CALL_16(Tag,Site,AS,as,
                                                     T0,T1,T2,T3,T4,T5,T6,T7,
                                                     T8,T9,T10,T11,T12,T13,T14,T15,
                                                     a0,a1,a2,a3,a4,a5,a6,a7,
                                                     a8,a9,a10,a11,a12,a13,a14,a15))
      {
        return BOOST_DISPATCH_IMPL_TAG_CALL_16(Tag,Site,AS,as,
                                               T0,T1,T2,T3,T4,T5,T6,T7,
                                               T8,T9,T10,T11,T12,T13,T14,T15,
                                               a0,a1,a2,a3,a4,a5,a6,a7,
                                               a8,a9,a10,a11,a12,a13,a14,a15);
      }

      template<typename AS, 
               typename T0,  typename T1,  typename T2,  typename T3,
               typename T4,  typename T5,  typename T6,  typename T7,
               typename T8,  typename T9,  typename T10, typename T11,
               typename T12, typename T13, typename T14, typename T15,
               typename T16, typename T17, typename T18, typename T19,
               typename T20, typename T21, typename T22, typename T23,
               typename T24, typename T25, typename T26, typename T27,
               typename T28, typename T29, typename T30, typename T31> BOOST_FORCEINLINE
      auto operator()(AS&& as,
                      T0&&  a0,  T1&&  a1,  T2&&  a2,  T3&&  a3,
                      T4&&  a4,  T5&&  a5,  T6&&  a6,  T7&&  a7,
                      T8&&  a8,  T9&&  a9,  T10&& a10, T11&& a11,
                      T12&& a12, T13&& a13, T14&& a14, T15&& a15,
                      T16&& a16, T17&& a17, T18&& a18, T19&& a19,
                      T20&& a20, T21&& a21, T22&& a22, T23&& a23,
                      T24&& a24, T25&& a25, T26&& a26, T27&& a27,
                      T28&& a28, T29&& a29, T30&& a30, T31&& a31) const
        BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(BOOST_DISPATCH_IMPL_TAG_CALL_32(Tag,Site,AS,as,
                                                                              T0,T1,T2,T3,T4,T5,T6,T7,
                                                                              T8,T9,T10,T11,T12,T13,T14,T15,
                                                                              T16,T17,T18,T19,T20,T21,T22,T23,
                                                                              T24,T25,T26,T27,T28,T29,T30,T31,
                                                                              a0,a1,a2,a3,a4,a5,a6,a7,
                                                                              a8,a9,a10,a11,a12,a13,a14,a15,
                                                                              a16,a17,a18,a19,a20,a21,a22,a23,
                                                                              a24,a25,a26,a27,a28,a29,a30,a31)))
        -> decltype (BOOST_DISPATCH_IMPL_TAG_CALL_32(Tag,Site,AS,as,
                                                     T0,T1,T2,T3,T4,T5,T6,T7,
                                                     T8,T9,T10,T11,T12,T13,T14,T15,
                                                     T16,T17,T18,T19,T20,T21,T22,T23,
                                                     T24,T25,T26,T27,T28,T29,T30,T31,
                                                     a0,a1,a2,a3,a4,a5,a6,a7,
                                                     a8,a9,a10,a11,a12,a13,a14,a15,
                                                     a16,a17,a18,a19,a20,a21,a22,a23,
                                                     a24,a25,a26,a27,a28,a29,a30,a31))
      {
        return BOOST_DISPATCH_IMPL_TAG_CALL_32(Tag,Site,AS,as,
                                               T0,T1,T2,T3,T4,T5,T6,T7,
                                               T8,T9,T10,T11,T12,T13,T14,T15,
                                               T16,T17,T18,T19,T20,T21,T22,T23,
                                               T24,T25,T26,T27,T28,T29,T30,T31,
                                               a0,a1,a2,a3,a4,a5,a6,a7,
                                               a8,a9,a10,a11,a12,a13,a14,a15,
                                               a16,a17,a18,a19,a20,a21,a22,a23,
                                               a24,a25,a26,a27,a28,a29,a30,a31);
      }

    };
  }}
#endif
