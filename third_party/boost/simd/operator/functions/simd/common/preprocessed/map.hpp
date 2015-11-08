namespace boost { namespace simd { namespace ext
{
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > ) , tag::cpu_ > dispatching( boost::simd::tag::map_, tag::cpu_ , unspecified_<Func> const , generic_< unspecified_<A0> > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > ) , tag::cpu_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > ) , tag::cpu_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( typename meta::scalar_of<A0>::type )
             >::type
    rtype;
    static const std::size_t N = meta::cardinal_of<A0>::value;
    typedef typename meta::
            vector_of< rtype
                     , N
                     >::type result_type;
    template<std::size_t N, class Dummy = void>
    struct impl
    {
      static result_type call(Func const& f, A0 const & a0)
      {
        result_type that;
        for(std::size_t i=0; i!=N; ++i)
          insert(f(extract(a0, i)), that, i);
        return that;
      }
    };
    template<class Dummy>
    struct impl<2, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0)
      {
        return make<result_type>(f(extract< 0>(a0)) , f(extract< 1>(a0)));
      }
    };
    template<class Dummy>
    struct impl<4, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0)
      {
        return make<result_type>(f(extract< 0>(a0)) , f(extract< 1>(a0)) , f(extract< 2>(a0)) , f(extract< 3>(a0)));
      }
    };
    template<class Dummy>
    struct impl<8, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0)
      {
        return make<result_type>(f(extract< 0>(a0)) , f(extract< 1>(a0)) , f(extract< 2>(a0)) , f(extract< 3>(a0)) , f(extract< 4>(a0)) , f(extract< 5>(a0)) , f(extract< 6>(a0)) , f(extract< 7>(a0)));
      }
    };
    BOOST_FORCEINLINE result_type operator()(Func const& f, A0 const & a0) const
    {
      return impl<N>::call(f, a0);
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > ) , tag::cpu_ > dispatching( boost::simd::tag::map_, tag::cpu_ , unspecified_<Func> const , generic_< unspecified_<A0> > const , generic_< unspecified_<A1> > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > ) , tag::cpu_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 , class A1 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > ) , tag::cpu_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( typename meta::scalar_of<A0>::type , typename meta::scalar_of<A1>::type )
             >::type
    rtype;
    static const std::size_t N = cardinal_common< meta::cardinal_of<A0>::value , meta::cardinal_of<A1>::value >::value;
    typedef typename meta::
            vector_of< rtype
                     , N
                     >::type result_type;
    template<std::size_t N, class Dummy = void>
    struct impl
    {
      static result_type call(Func const& f, A0 const & a0 , A1 const & a1)
      {
        result_type that;
        for(std::size_t i=0; i!=N; ++i)
          insert(f(extract(a0, i) , extract(a1, i)), that, i);
        return that;
      }
    };
    template<class Dummy>
    struct impl<2, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0 , A1 const & a1)
      {
        return make<result_type>(f(extract< 0>(a0) , extract< 0>(a1)) , f(extract< 1>(a0) , extract< 1>(a1)));
      }
    };
    template<class Dummy>
    struct impl<4, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0 , A1 const & a1)
      {
        return make<result_type>(f(extract< 0>(a0) , extract< 0>(a1)) , f(extract< 1>(a0) , extract< 1>(a1)) , f(extract< 2>(a0) , extract< 2>(a1)) , f(extract< 3>(a0) , extract< 3>(a1)));
      }
    };
    template<class Dummy>
    struct impl<8, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0 , A1 const & a1)
      {
        return make<result_type>(f(extract< 0>(a0) , extract< 0>(a1)) , f(extract< 1>(a0) , extract< 1>(a1)) , f(extract< 2>(a0) , extract< 2>(a1)) , f(extract< 3>(a0) , extract< 3>(a1)) , f(extract< 4>(a0) , extract< 4>(a1)) , f(extract< 5>(a0) , extract< 5>(a1)) , f(extract< 6>(a0) , extract< 6>(a1)) , f(extract< 7>(a0) , extract< 7>(a1)));
      }
    };
    BOOST_FORCEINLINE result_type operator()(Func const& f, A0 const & a0 , A1 const & a1) const
    {
      return impl<N>::call(f, a0 , a1);
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 , class A2 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > ) , tag::cpu_ > dispatching( boost::simd::tag::map_, tag::cpu_ , unspecified_<Func> const , generic_< unspecified_<A0> > const , generic_< unspecified_<A1> > const , generic_< unspecified_<A2> > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > ) , tag::cpu_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 , class A1 , class A2 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > ) , tag::cpu_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( typename meta::scalar_of<A0>::type , typename meta::scalar_of<A1>::type , typename meta::scalar_of<A2>::type )
             >::type
    rtype;
    static const std::size_t N = cardinal_common< meta::cardinal_of<A0>::value , cardinal_common< meta::cardinal_of<A1>::value , meta::cardinal_of<A2>::value >::value >::value;
    typedef typename meta::
            vector_of< rtype
                     , N
                     >::type result_type;
    template<std::size_t N, class Dummy = void>
    struct impl
    {
      static result_type call(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2)
      {
        result_type that;
        for(std::size_t i=0; i!=N; ++i)
          insert(f(extract(a0, i) , extract(a1, i) , extract(a2, i)), that, i);
        return that;
      }
    };
    template<class Dummy>
    struct impl<2, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2)
      {
        return make<result_type>(f(extract< 0>(a0) , extract< 0>(a1) , extract< 0>(a2)) , f(extract< 1>(a0) , extract< 1>(a1) , extract< 1>(a2)));
      }
    };
    template<class Dummy>
    struct impl<4, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2)
      {
        return make<result_type>(f(extract< 0>(a0) , extract< 0>(a1) , extract< 0>(a2)) , f(extract< 1>(a0) , extract< 1>(a1) , extract< 1>(a2)) , f(extract< 2>(a0) , extract< 2>(a1) , extract< 2>(a2)) , f(extract< 3>(a0) , extract< 3>(a1) , extract< 3>(a2)));
      }
    };
    template<class Dummy>
    struct impl<8, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2)
      {
        return make<result_type>(f(extract< 0>(a0) , extract< 0>(a1) , extract< 0>(a2)) , f(extract< 1>(a0) , extract< 1>(a1) , extract< 1>(a2)) , f(extract< 2>(a0) , extract< 2>(a1) , extract< 2>(a2)) , f(extract< 3>(a0) , extract< 3>(a1) , extract< 3>(a2)) , f(extract< 4>(a0) , extract< 4>(a1) , extract< 4>(a2)) , f(extract< 5>(a0) , extract< 5>(a1) , extract< 5>(a2)) , f(extract< 6>(a0) , extract< 6>(a1) , extract< 6>(a2)) , f(extract< 7>(a0) , extract< 7>(a1) , extract< 7>(a2)));
      }
    };
    BOOST_FORCEINLINE result_type operator()(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2) const
    {
      return impl<N>::call(f, a0 , a1 , a2);
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 , class A2 , class A3 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > ) , tag::cpu_ > dispatching( boost::simd::tag::map_, tag::cpu_ , unspecified_<Func> const , generic_< unspecified_<A0> > const , generic_< unspecified_<A1> > const , generic_< unspecified_<A2> > const , generic_< unspecified_<A3> > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > ) , tag::cpu_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 , class A1 , class A2 , class A3 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > ) , tag::cpu_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( typename meta::scalar_of<A0>::type , typename meta::scalar_of<A1>::type , typename meta::scalar_of<A2>::type , typename meta::scalar_of<A3>::type )
             >::type
    rtype;
    static const std::size_t N = cardinal_common< meta::cardinal_of<A0>::value , cardinal_common< meta::cardinal_of<A1>::value , cardinal_common< meta::cardinal_of<A2>::value , meta::cardinal_of<A3>::value >::value >::value >::value;
    typedef typename meta::
            vector_of< rtype
                     , N
                     >::type result_type;
    template<std::size_t N, class Dummy = void>
    struct impl
    {
      static result_type call(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3)
      {
        result_type that;
        for(std::size_t i=0; i!=N; ++i)
          insert(f(extract(a0, i) , extract(a1, i) , extract(a2, i) , extract(a3, i)), that, i);
        return that;
      }
    };
    template<class Dummy>
    struct impl<2, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3)
      {
        return make<result_type>(f(extract< 0>(a0) , extract< 0>(a1) , extract< 0>(a2) , extract< 0>(a3)) , f(extract< 1>(a0) , extract< 1>(a1) , extract< 1>(a2) , extract< 1>(a3)));
      }
    };
    template<class Dummy>
    struct impl<4, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3)
      {
        return make<result_type>(f(extract< 0>(a0) , extract< 0>(a1) , extract< 0>(a2) , extract< 0>(a3)) , f(extract< 1>(a0) , extract< 1>(a1) , extract< 1>(a2) , extract< 1>(a3)) , f(extract< 2>(a0) , extract< 2>(a1) , extract< 2>(a2) , extract< 2>(a3)) , f(extract< 3>(a0) , extract< 3>(a1) , extract< 3>(a2) , extract< 3>(a3)));
      }
    };
    template<class Dummy>
    struct impl<8, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3)
      {
        return make<result_type>(f(extract< 0>(a0) , extract< 0>(a1) , extract< 0>(a2) , extract< 0>(a3)) , f(extract< 1>(a0) , extract< 1>(a1) , extract< 1>(a2) , extract< 1>(a3)) , f(extract< 2>(a0) , extract< 2>(a1) , extract< 2>(a2) , extract< 2>(a3)) , f(extract< 3>(a0) , extract< 3>(a1) , extract< 3>(a2) , extract< 3>(a3)) , f(extract< 4>(a0) , extract< 4>(a1) , extract< 4>(a2) , extract< 4>(a3)) , f(extract< 5>(a0) , extract< 5>(a1) , extract< 5>(a2) , extract< 5>(a3)) , f(extract< 6>(a0) , extract< 6>(a1) , extract< 6>(a2) , extract< 6>(a3)) , f(extract< 7>(a0) , extract< 7>(a1) , extract< 7>(a2) , extract< 7>(a3)));
      }
    };
    BOOST_FORCEINLINE result_type operator()(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3) const
    {
      return impl<N>::call(f, a0 , a1 , a2 , a3);
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 , class A2 , class A3 , class A4 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > , generic_< unspecified_<A4> > ) , tag::cpu_ > dispatching( boost::simd::tag::map_, tag::cpu_ , unspecified_<Func> const , generic_< unspecified_<A0> > const , generic_< unspecified_<A1> > const , generic_< unspecified_<A2> > const , generic_< unspecified_<A3> > const , generic_< unspecified_<A4> > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > , generic_< unspecified_<A4> > ) , tag::cpu_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 , class A1 , class A2 , class A3 , class A4 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > , generic_< unspecified_<A4> > ) , tag::cpu_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( typename meta::scalar_of<A0>::type , typename meta::scalar_of<A1>::type , typename meta::scalar_of<A2>::type , typename meta::scalar_of<A3>::type , typename meta::scalar_of<A4>::type )
             >::type
    rtype;
    static const std::size_t N = cardinal_common< meta::cardinal_of<A0>::value , cardinal_common< meta::cardinal_of<A1>::value , cardinal_common< meta::cardinal_of<A2>::value , cardinal_common< meta::cardinal_of<A3>::value , meta::cardinal_of<A4>::value >::value >::value >::value >::value;
    typedef typename meta::
            vector_of< rtype
                     , N
                     >::type result_type;
    template<std::size_t N, class Dummy = void>
    struct impl
    {
      static result_type call(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4)
      {
        result_type that;
        for(std::size_t i=0; i!=N; ++i)
          insert(f(extract(a0, i) , extract(a1, i) , extract(a2, i) , extract(a3, i) , extract(a4, i)), that, i);
        return that;
      }
    };
    template<class Dummy>
    struct impl<2, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4)
      {
        return make<result_type>(f(extract< 0>(a0) , extract< 0>(a1) , extract< 0>(a2) , extract< 0>(a3) , extract< 0>(a4)) , f(extract< 1>(a0) , extract< 1>(a1) , extract< 1>(a2) , extract< 1>(a3) , extract< 1>(a4)));
      }
    };
    template<class Dummy>
    struct impl<4, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4)
      {
        return make<result_type>(f(extract< 0>(a0) , extract< 0>(a1) , extract< 0>(a2) , extract< 0>(a3) , extract< 0>(a4)) , f(extract< 1>(a0) , extract< 1>(a1) , extract< 1>(a2) , extract< 1>(a3) , extract< 1>(a4)) , f(extract< 2>(a0) , extract< 2>(a1) , extract< 2>(a2) , extract< 2>(a3) , extract< 2>(a4)) , f(extract< 3>(a0) , extract< 3>(a1) , extract< 3>(a2) , extract< 3>(a3) , extract< 3>(a4)));
      }
    };
    template<class Dummy>
    struct impl<8, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4)
      {
        return make<result_type>(f(extract< 0>(a0) , extract< 0>(a1) , extract< 0>(a2) , extract< 0>(a3) , extract< 0>(a4)) , f(extract< 1>(a0) , extract< 1>(a1) , extract< 1>(a2) , extract< 1>(a3) , extract< 1>(a4)) , f(extract< 2>(a0) , extract< 2>(a1) , extract< 2>(a2) , extract< 2>(a3) , extract< 2>(a4)) , f(extract< 3>(a0) , extract< 3>(a1) , extract< 3>(a2) , extract< 3>(a3) , extract< 3>(a4)) , f(extract< 4>(a0) , extract< 4>(a1) , extract< 4>(a2) , extract< 4>(a3) , extract< 4>(a4)) , f(extract< 5>(a0) , extract< 5>(a1) , extract< 5>(a2) , extract< 5>(a3) , extract< 5>(a4)) , f(extract< 6>(a0) , extract< 6>(a1) , extract< 6>(a2) , extract< 6>(a3) , extract< 6>(a4)) , f(extract< 7>(a0) , extract< 7>(a1) , extract< 7>(a2) , extract< 7>(a3) , extract< 7>(a4)));
      }
    };
    BOOST_FORCEINLINE result_type operator()(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4) const
    {
      return impl<N>::call(f, a0 , a1 , a2 , a3 , a4);
    }
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 , class A2 , class A3 , class A4 , class A5 > BOOST_FORCEINLINE :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > , generic_< unspecified_<A4> > , generic_< unspecified_<A5> > ) , tag::cpu_ > dispatching( boost::simd::tag::map_, tag::cpu_ , unspecified_<Func> const , generic_< unspecified_<A0> > const , generic_< unspecified_<A1> > const , generic_< unspecified_<A2> > const , generic_< unspecified_<A3> > const , generic_< unspecified_<A4> > const , generic_< unspecified_<A5> > const , adl_helper = adl_helper() ) { return :: boost :: simd :: ext :: implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > , generic_< unspecified_<A4> > , generic_< unspecified_<A5> > ) , tag::cpu_ >(); } } } } namespace boost { namespace simd { namespace ext { template< class Func , class A0 , class A1 , class A2 , class A3 , class A4 , class A5 > struct implement< boost::simd::tag::map_ ( unspecified_<Func> , generic_< unspecified_<A0> > , generic_< unspecified_<A1> > , generic_< unspecified_<A2> > , generic_< unspecified_<A3> > , generic_< unspecified_<A4> > , generic_< unspecified_<A5> > ) , tag::cpu_ >
  {
    typedef typename dispatch::meta::
    result_of< Func const( typename meta::scalar_of<A0>::type , typename meta::scalar_of<A1>::type , typename meta::scalar_of<A2>::type , typename meta::scalar_of<A3>::type , typename meta::scalar_of<A4>::type , typename meta::scalar_of<A5>::type )
             >::type
    rtype;
    static const std::size_t N = cardinal_common< meta::cardinal_of<A0>::value , cardinal_common< meta::cardinal_of<A1>::value , cardinal_common< meta::cardinal_of<A2>::value , cardinal_common< meta::cardinal_of<A3>::value , cardinal_common< meta::cardinal_of<A4>::value , meta::cardinal_of<A5>::value >::value >::value >::value >::value >::value;
    typedef typename meta::
            vector_of< rtype
                     , N
                     >::type result_type;
    template<std::size_t N, class Dummy = void>
    struct impl
    {
      static result_type call(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4 , A5 const & a5)
      {
        result_type that;
        for(std::size_t i=0; i!=N; ++i)
          insert(f(extract(a0, i) , extract(a1, i) , extract(a2, i) , extract(a3, i) , extract(a4, i) , extract(a5, i)), that, i);
        return that;
      }
    };
    template<class Dummy>
    struct impl<2, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4 , A5 const & a5)
      {
        return make<result_type>(f(extract< 0>(a0) , extract< 0>(a1) , extract< 0>(a2) , extract< 0>(a3) , extract< 0>(a4) , extract< 0>(a5)) , f(extract< 1>(a0) , extract< 1>(a1) , extract< 1>(a2) , extract< 1>(a3) , extract< 1>(a4) , extract< 1>(a5)));
      }
    };
    template<class Dummy>
    struct impl<4, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4 , A5 const & a5)
      {
        return make<result_type>(f(extract< 0>(a0) , extract< 0>(a1) , extract< 0>(a2) , extract< 0>(a3) , extract< 0>(a4) , extract< 0>(a5)) , f(extract< 1>(a0) , extract< 1>(a1) , extract< 1>(a2) , extract< 1>(a3) , extract< 1>(a4) , extract< 1>(a5)) , f(extract< 2>(a0) , extract< 2>(a1) , extract< 2>(a2) , extract< 2>(a3) , extract< 2>(a4) , extract< 2>(a5)) , f(extract< 3>(a0) , extract< 3>(a1) , extract< 3>(a2) , extract< 3>(a3) , extract< 3>(a4) , extract< 3>(a5)));
      }
    };
    template<class Dummy>
    struct impl<8, Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4 , A5 const & a5)
      {
        return make<result_type>(f(extract< 0>(a0) , extract< 0>(a1) , extract< 0>(a2) , extract< 0>(a3) , extract< 0>(a4) , extract< 0>(a5)) , f(extract< 1>(a0) , extract< 1>(a1) , extract< 1>(a2) , extract< 1>(a3) , extract< 1>(a4) , extract< 1>(a5)) , f(extract< 2>(a0) , extract< 2>(a1) , extract< 2>(a2) , extract< 2>(a3) , extract< 2>(a4) , extract< 2>(a5)) , f(extract< 3>(a0) , extract< 3>(a1) , extract< 3>(a2) , extract< 3>(a3) , extract< 3>(a4) , extract< 3>(a5)) , f(extract< 4>(a0) , extract< 4>(a1) , extract< 4>(a2) , extract< 4>(a3) , extract< 4>(a4) , extract< 4>(a5)) , f(extract< 5>(a0) , extract< 5>(a1) , extract< 5>(a2) , extract< 5>(a3) , extract< 5>(a4) , extract< 5>(a5)) , f(extract< 6>(a0) , extract< 6>(a1) , extract< 6>(a2) , extract< 6>(a3) , extract< 6>(a4) , extract< 6>(a5)) , f(extract< 7>(a0) , extract< 7>(a1) , extract< 7>(a2) , extract< 7>(a3) , extract< 7>(a4) , extract< 7>(a5)));
      }
    };
    BOOST_FORCEINLINE result_type operator()(Func const& f, A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4 , A5 const & a5) const
    {
      return impl<N>::call(f, a0 , a1 , a2 , a3 , a4 , a5);
    }
  };
} } }
