namespace boost { namespace simd { namespace ext
{
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ > dispatching( boost::simd::tag::map_, boost::simd::tag::avx_ , unspecified_<Func> const , simd_< unspecified_<A0>, boost::simd::tag::avx_ > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( simd::native<typename meta::scalar_of<A0>::type, tag::sse_> const& )>::type base;
    typedef simd::native< typename meta::scalar_of<base>::type
                        , boost::simd::tag::avx_
                        > result_type;
    BOOST_FORCEINLINE result_type
    operator()( Func const& f
              , A0 const& a0
              ) const
    {
      native<typename meta::scalar_of<A0>::type,tag::sse_> a00,a10; boost::simd::slice(a0,a00,a10);
      return boost::simd::combine ( f(a00 )
                                  , f(a10 )
                                  );
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > , simd_< unspecified_<A1>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ > dispatching( boost::simd::tag::map_, boost::simd::tag::avx_ , unspecified_<Func> const , simd_< unspecified_<A0>, boost::simd::tag::avx_ > const , simd_< unspecified_<A1>, boost::simd::tag::avx_ > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > , simd_< unspecified_<A1>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 , class A1 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > , simd_< unspecified_<A1>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( simd::native<typename meta::scalar_of<A0>::type, tag::sse_> const& , simd::native<typename meta::scalar_of<A1>::type, tag::sse_> const& )>::type base;
    typedef simd::native< typename meta::scalar_of<base>::type
                        , boost::simd::tag::avx_
                        > result_type;
    BOOST_FORCEINLINE result_type
    operator()( Func const& f
              , A0 const& a0 , A1 const& a1
              ) const
    {
      native<typename meta::scalar_of<A0>::type,tag::sse_> a00,a10; boost::simd::slice(a0,a00,a10); native<typename meta::scalar_of<A1>::type,tag::sse_> a01,a11; boost::simd::slice(a1,a01,a11);
      return boost::simd::combine ( f(a00 , a01 )
                                  , f(a10 , a11 )
                                  );
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 , class A2 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > , simd_< unspecified_<A1>, boost::simd::tag::avx_ > , simd_< unspecified_<A2>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ > dispatching( boost::simd::tag::map_, boost::simd::tag::avx_ , unspecified_<Func> const , simd_< unspecified_<A0>, boost::simd::tag::avx_ > const , simd_< unspecified_<A1>, boost::simd::tag::avx_ > const , simd_< unspecified_<A2>, boost::simd::tag::avx_ > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > , simd_< unspecified_<A1>, boost::simd::tag::avx_ > , simd_< unspecified_<A2>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 , class A1 , class A2 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > , simd_< unspecified_<A1>, boost::simd::tag::avx_ > , simd_< unspecified_<A2>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( simd::native<typename meta::scalar_of<A0>::type, tag::sse_> const& , simd::native<typename meta::scalar_of<A1>::type, tag::sse_> const& , simd::native<typename meta::scalar_of<A2>::type, tag::sse_> const& )>::type base;
    typedef simd::native< typename meta::scalar_of<base>::type
                        , boost::simd::tag::avx_
                        > result_type;
    BOOST_FORCEINLINE result_type
    operator()( Func const& f
              , A0 const& a0 , A1 const& a1 , A2 const& a2
              ) const
    {
      native<typename meta::scalar_of<A0>::type,tag::sse_> a00,a10; boost::simd::slice(a0,a00,a10); native<typename meta::scalar_of<A1>::type,tag::sse_> a01,a11; boost::simd::slice(a1,a01,a11); native<typename meta::scalar_of<A2>::type,tag::sse_> a02,a12; boost::simd::slice(a2,a02,a12);
      return boost::simd::combine ( f(a00 , a01 , a02 )
                                  , f(a10 , a11 , a12 )
                                  );
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 , class A2 , class A3 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > , simd_< unspecified_<A1>, boost::simd::tag::avx_ > , simd_< unspecified_<A2>, boost::simd::tag::avx_ > , simd_< unspecified_<A3>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ > dispatching( boost::simd::tag::map_, boost::simd::tag::avx_ , unspecified_<Func> const , simd_< unspecified_<A0>, boost::simd::tag::avx_ > const , simd_< unspecified_<A1>, boost::simd::tag::avx_ > const , simd_< unspecified_<A2>, boost::simd::tag::avx_ > const , simd_< unspecified_<A3>, boost::simd::tag::avx_ > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > , simd_< unspecified_<A1>, boost::simd::tag::avx_ > , simd_< unspecified_<A2>, boost::simd::tag::avx_ > , simd_< unspecified_<A3>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 , class A1 , class A2 , class A3 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > , simd_< unspecified_<A1>, boost::simd::tag::avx_ > , simd_< unspecified_<A2>, boost::simd::tag::avx_ > , simd_< unspecified_<A3>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( simd::native<typename meta::scalar_of<A0>::type, tag::sse_> const& , simd::native<typename meta::scalar_of<A1>::type, tag::sse_> const& , simd::native<typename meta::scalar_of<A2>::type, tag::sse_> const& , simd::native<typename meta::scalar_of<A3>::type, tag::sse_> const& )>::type base;
    typedef simd::native< typename meta::scalar_of<base>::type
                        , boost::simd::tag::avx_
                        > result_type;
    BOOST_FORCEINLINE result_type
    operator()( Func const& f
              , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3
              ) const
    {
      native<typename meta::scalar_of<A0>::type,tag::sse_> a00,a10; boost::simd::slice(a0,a00,a10); native<typename meta::scalar_of<A1>::type,tag::sse_> a01,a11; boost::simd::slice(a1,a01,a11); native<typename meta::scalar_of<A2>::type,tag::sse_> a02,a12; boost::simd::slice(a2,a02,a12); native<typename meta::scalar_of<A3>::type,tag::sse_> a03,a13; boost::simd::slice(a3,a03,a13);
      return boost::simd::combine ( f(a00 , a01 , a02 , a03 )
                                  , f(a10 , a11 , a12 , a13 )
                                  );
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 , class A2 , class A3 , class A4 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > , simd_< unspecified_<A1>, boost::simd::tag::avx_ > , simd_< unspecified_<A2>, boost::simd::tag::avx_ > , simd_< unspecified_<A3>, boost::simd::tag::avx_ > , simd_< unspecified_<A4>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ > dispatching( boost::simd::tag::map_, boost::simd::tag::avx_ , unspecified_<Func> const , simd_< unspecified_<A0>, boost::simd::tag::avx_ > const , simd_< unspecified_<A1>, boost::simd::tag::avx_ > const , simd_< unspecified_<A2>, boost::simd::tag::avx_ > const , simd_< unspecified_<A3>, boost::simd::tag::avx_ > const , simd_< unspecified_<A4>, boost::simd::tag::avx_ > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > , simd_< unspecified_<A1>, boost::simd::tag::avx_ > , simd_< unspecified_<A2>, boost::simd::tag::avx_ > , simd_< unspecified_<A3>, boost::simd::tag::avx_ > , simd_< unspecified_<A4>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 , class A1 , class A2 , class A3 , class A4 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > , simd_< unspecified_<A1>, boost::simd::tag::avx_ > , simd_< unspecified_<A2>, boost::simd::tag::avx_ > , simd_< unspecified_<A3>, boost::simd::tag::avx_ > , simd_< unspecified_<A4>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( simd::native<typename meta::scalar_of<A0>::type, tag::sse_> const& , simd::native<typename meta::scalar_of<A1>::type, tag::sse_> const& , simd::native<typename meta::scalar_of<A2>::type, tag::sse_> const& , simd::native<typename meta::scalar_of<A3>::type, tag::sse_> const& , simd::native<typename meta::scalar_of<A4>::type, tag::sse_> const& )>::type base;
    typedef simd::native< typename meta::scalar_of<base>::type
                        , boost::simd::tag::avx_
                        > result_type;
    BOOST_FORCEINLINE result_type
    operator()( Func const& f
              , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4
              ) const
    {
      native<typename meta::scalar_of<A0>::type,tag::sse_> a00,a10; boost::simd::slice(a0,a00,a10); native<typename meta::scalar_of<A1>::type,tag::sse_> a01,a11; boost::simd::slice(a1,a01,a11); native<typename meta::scalar_of<A2>::type,tag::sse_> a02,a12; boost::simd::slice(a2,a02,a12); native<typename meta::scalar_of<A3>::type,tag::sse_> a03,a13; boost::simd::slice(a3,a03,a13); native<typename meta::scalar_of<A4>::type,tag::sse_> a04,a14; boost::simd::slice(a4,a04,a14);
      return boost::simd::combine ( f(a00 , a01 , a02 , a03 , a04 )
                                  , f(a10 , a11 , a12 , a13 , a14 )
                                  );
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 , class A2 , class A3 , class A4 , class A5 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > , simd_< unspecified_<A1>, boost::simd::tag::avx_ > , simd_< unspecified_<A2>, boost::simd::tag::avx_ > , simd_< unspecified_<A3>, boost::simd::tag::avx_ > , simd_< unspecified_<A4>, boost::simd::tag::avx_ > , simd_< unspecified_<A5>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ > dispatching( boost::simd::tag::map_, boost::simd::tag::avx_ , unspecified_<Func> const , simd_< unspecified_<A0>, boost::simd::tag::avx_ > const , simd_< unspecified_<A1>, boost::simd::tag::avx_ > const , simd_< unspecified_<A2>, boost::simd::tag::avx_ > const , simd_< unspecified_<A3>, boost::simd::tag::avx_ > const , simd_< unspecified_<A4>, boost::simd::tag::avx_ > const , simd_< unspecified_<A5>, boost::simd::tag::avx_ > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > , simd_< unspecified_<A1>, boost::simd::tag::avx_ > , simd_< unspecified_<A2>, boost::simd::tag::avx_ > , simd_< unspecified_<A3>, boost::simd::tag::avx_ > , simd_< unspecified_<A4>, boost::simd::tag::avx_ > , simd_< unspecified_<A5>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 , class A1 , class A2 , class A3 , class A4 , class A5 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , simd_< unspecified_<A0>, boost::simd::tag::avx_ > , simd_< unspecified_<A1>, boost::simd::tag::avx_ > , simd_< unspecified_<A2>, boost::simd::tag::avx_ > , simd_< unspecified_<A3>, boost::simd::tag::avx_ > , simd_< unspecified_<A4>, boost::simd::tag::avx_ > , simd_< unspecified_<A5>, boost::simd::tag::avx_ > ) , boost::simd::tag::avx_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( simd::native<typename meta::scalar_of<A0>::type, tag::sse_> const& , simd::native<typename meta::scalar_of<A1>::type, tag::sse_> const& , simd::native<typename meta::scalar_of<A2>::type, tag::sse_> const& , simd::native<typename meta::scalar_of<A3>::type, tag::sse_> const& , simd::native<typename meta::scalar_of<A4>::type, tag::sse_> const& , simd::native<typename meta::scalar_of<A5>::type, tag::sse_> const& )>::type base;
    typedef simd::native< typename meta::scalar_of<base>::type
                        , boost::simd::tag::avx_
                        > result_type;
    BOOST_FORCEINLINE result_type
    operator()( Func const& f
              , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5
              ) const
    {
      native<typename meta::scalar_of<A0>::type,tag::sse_> a00,a10; boost::simd::slice(a0,a00,a10); native<typename meta::scalar_of<A1>::type,tag::sse_> a01,a11; boost::simd::slice(a1,a01,a11); native<typename meta::scalar_of<A2>::type,tag::sse_> a02,a12; boost::simd::slice(a2,a02,a12); native<typename meta::scalar_of<A3>::type,tag::sse_> a03,a13; boost::simd::slice(a3,a03,a13); native<typename meta::scalar_of<A4>::type,tag::sse_> a04,a14; boost::simd::slice(a4,a04,a14); native<typename meta::scalar_of<A5>::type,tag::sse_> a05,a15; boost::simd::slice(a5,a05,a15);
      return boost::simd::combine ( f(a00 , a01 , a02 , a03 , a04 , a05 )
                                  , f(a10 , a11 , a12 , a13 , a14 , a15 )
                                  );
    }
  };
} } }
