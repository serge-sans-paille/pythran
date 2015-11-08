////////////////////////////////////////////////////////////////////////////////
// Register all tag and extension agnostic call for common code sharing
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  template<class A0, class X, std::size_t N, class Callee, class Result = boost::dispatch::meta::result_of<Callee(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type const&)>, class Enable = void>
  struct splat_impl1
  {
  };
  template<class A0, class X, std::size_t N, class Callee, class Result>
  struct splat_impl1<A0, X, N, Callee, Result, typename boost::dispatch::meta::enable_if_type<typename Result::type>::type>
  {
    typedef typename Result::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0) const
    {
      return Callee()(splat<typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type>(a0));
    }
  };
  template<class Tag, class A0, class X, std::size_t N, bool B = N != 1
                                      && !is_same<X, dispatch::meta::na_>::value
                                      && ((meta::cardinal_of<A0>::value == 1u))>
  struct splat_or_map_choose1;
  template<class Tag, class A0, class X, std::size_t N>
  struct splat_or_map_choose1<Tag, A0, X, N, true>
       : splat_impl1< A0
                                    , X, N
                                    , typename boost::dispatch::meta::
                                      dispatch_call<Tag(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type const&)>::type
                                    >
  {
  };
  template<class Tag, class A0, class SResult, class Enable = void>
  struct map_impl1
  {
  };
  template<class Tag, class A0, class SResult>
  struct map_impl1<Tag, A0, SResult, typename boost::dispatch::meta::enable_if_type<typename SResult::type>::type>
  {
    BOOST_SIMD_MAP_LOG(Tag)
    typedef typename boost::dispatch::meta::
            call<tag::map_( boost::dispatch::functor<Tag>
                          , A0 const &
                          )
                >::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0) const
    {
      return map( dispatch::functor<Tag>(), a0 );
    }
  };
  template<class Tag, class A0, class X, std::size_t N>
  struct splat_or_map_choose1<Tag, A0, X, N, false>
       : map_impl1< Tag, A0
                                  , boost::dispatch::meta::
                                    call<Tag(typename meta::scalar_of<A0>::type)>
                                  >
  {
  };
  template<class Tag, class A0>
  struct splat_or_map1
       : splat_or_map_choose1< Tag, A0
                                             , typename meta::extension_of<A0>::type
                                             , meta::cardinal_of<A0>::value
                                             >
  {
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Tag , class A0 > BOOST_FORCEINLINE typename boost::enable_if< mpl::not_< any < mpl::or_ < boost::proto:: is_expr<mpl::_> , boost::dispatch:: meta::is_proxy<mpl::_> > , A0 > > , boost::simd::ext::splat_or_map1< Tag, A0 > >::type dispatching( elementwise_<Tag>, tag::formal_ , unspecified_<A0> const , adl_helper = adl_helper() ) { return boost::simd::ext::splat_or_map1< Tag, A0 >(); } } } } namespace boost { namespace simd { namespace ext {
  template<class A0 , class A1, class X, std::size_t N, class Callee, class Result = boost::dispatch::meta::result_of<Callee(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type const&)>, class Enable = void>
  struct splat_impl2
  {
  };
  template<class A0 , class A1, class X, std::size_t N, class Callee, class Result>
  struct splat_impl2<A0 , A1, X, N, Callee, Result, typename boost::dispatch::meta::enable_if_type<typename Result::type>::type>
  {
    typedef typename Result::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0 , A1 const & a1) const
    {
      return Callee()(splat<typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type>(a0) , splat<typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type>(a1));
    }
  };
  template<class Tag, class A0 , class A1, class X, std::size_t N, bool B = N != 1
                                      && !is_same<X, dispatch::meta::na_>::value
                                      && ((meta::cardinal_of<A0>::value == 1u) || (meta::cardinal_of<A1>::value == 1u))>
  struct splat_or_map_choose2;
  template<class Tag, class A0 , class A1, class X, std::size_t N>
  struct splat_or_map_choose2<Tag, A0 , A1, X, N, true>
       : splat_impl2< A0 , A1
                                    , X, N
                                    , typename boost::dispatch::meta::
                                      dispatch_call<Tag(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type const&)>::type
                                    >
  {
  };
  template<class Tag, class A0 , class A1, class SResult, class Enable = void>
  struct map_impl2
  {
  };
  template<class Tag, class A0 , class A1, class SResult>
  struct map_impl2<Tag, A0 , A1, SResult, typename boost::dispatch::meta::enable_if_type<typename SResult::type>::type>
  {
    BOOST_SIMD_MAP_LOG(Tag)
    typedef typename boost::dispatch::meta::
            call<tag::map_( boost::dispatch::functor<Tag>
                          , A0 const & , A1 const &
                          )
                >::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0 , A1 const & a1) const
    {
      return map( dispatch::functor<Tag>(), a0 , a1 );
    }
  };
  template<class Tag, class A0 , class A1, class X, std::size_t N>
  struct splat_or_map_choose2<Tag, A0 , A1, X, N, false>
       : map_impl2< Tag, A0 , A1
                                  , boost::dispatch::meta::
                                    call<Tag(typename meta::scalar_of<A0>::type , typename meta::scalar_of<A1>::type)>
                                  >
  {
  };
  template<class Tag, class A0 , class A1>
  struct splat_or_map2
       : splat_or_map_choose2< Tag, A0 , A1
                                             , typename ext_common< typename meta::extension_of<A0>::type , typename meta::extension_of<A1>::type >::type
                                             , cardinal_common< meta::cardinal_of<A0>::value , meta::cardinal_of<A1>::value >::value
                                             >
  {
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Tag , class A0 , class A1 > BOOST_FORCEINLINE typename boost::enable_if< mpl::not_< any < mpl::or_ < boost::proto:: is_expr<mpl::_> , boost::dispatch:: meta::is_proxy<mpl::_> > , A0 , A1 > > , boost::simd::ext::splat_or_map2< Tag, A0 , A1 > >::type dispatching( elementwise_<Tag>, tag::formal_ , unspecified_<A0> const , unspecified_<A1> const , adl_helper = adl_helper() ) { return boost::simd::ext::splat_or_map2< Tag, A0 , A1 >(); } } } } namespace boost { namespace simd { namespace ext {
  template<class A0 , class A1 , class A2, class X, std::size_t N, class Callee, class Result = boost::dispatch::meta::result_of<Callee(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type const&)>, class Enable = void>
  struct splat_impl3
  {
  };
  template<class A0 , class A1 , class A2, class X, std::size_t N, class Callee, class Result>
  struct splat_impl3<A0 , A1 , A2, X, N, Callee, Result, typename boost::dispatch::meta::enable_if_type<typename Result::type>::type>
  {
    typedef typename Result::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0 , A1 const & a1 , A2 const & a2) const
    {
      return Callee()(splat<typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type>(a0) , splat<typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type>(a1) , splat<typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type>(a2));
    }
  };
  template<class Tag, class A0 , class A1 , class A2, class X, std::size_t N, bool B = N != 1
                                      && !is_same<X, dispatch::meta::na_>::value
                                      && ((meta::cardinal_of<A0>::value == 1u) || (meta::cardinal_of<A1>::value == 1u) || (meta::cardinal_of<A2>::value == 1u))>
  struct splat_or_map_choose3;
  template<class Tag, class A0 , class A1 , class A2, class X, std::size_t N>
  struct splat_or_map_choose3<Tag, A0 , A1 , A2, X, N, true>
       : splat_impl3< A0 , A1 , A2
                                    , X, N
                                    , typename boost::dispatch::meta::
                                      dispatch_call<Tag(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type const&)>::type
                                    >
  {
  };
  template<class Tag, class A0 , class A1 , class A2, class SResult, class Enable = void>
  struct map_impl3
  {
  };
  template<class Tag, class A0 , class A1 , class A2, class SResult>
  struct map_impl3<Tag, A0 , A1 , A2, SResult, typename boost::dispatch::meta::enable_if_type<typename SResult::type>::type>
  {
    BOOST_SIMD_MAP_LOG(Tag)
    typedef typename boost::dispatch::meta::
            call<tag::map_( boost::dispatch::functor<Tag>
                          , A0 const & , A1 const & , A2 const &
                          )
                >::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0 , A1 const & a1 , A2 const & a2) const
    {
      return map( dispatch::functor<Tag>(), a0 , a1 , a2 );
    }
  };
  template<class Tag, class A0 , class A1 , class A2, class X, std::size_t N>
  struct splat_or_map_choose3<Tag, A0 , A1 , A2, X, N, false>
       : map_impl3< Tag, A0 , A1 , A2
                                  , boost::dispatch::meta::
                                    call<Tag(typename meta::scalar_of<A0>::type , typename meta::scalar_of<A1>::type , typename meta::scalar_of<A2>::type)>
                                  >
  {
  };
  template<class Tag, class A0 , class A1 , class A2>
  struct splat_or_map3
       : splat_or_map_choose3< Tag, A0 , A1 , A2
                                             , typename ext_common< typename meta::extension_of<A0>::type , typename ext_common< typename meta::extension_of<A1>::type , typename meta::extension_of<A2>::type >::type >::type
                                             , cardinal_common< meta::cardinal_of<A0>::value , cardinal_common< meta::cardinal_of<A1>::value , meta::cardinal_of<A2>::value >::value >::value
                                             >
  {
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Tag , class A0 , class A1 , class A2 > BOOST_FORCEINLINE typename boost::enable_if< mpl::not_< any < mpl::or_ < boost::proto:: is_expr<mpl::_> , boost::dispatch:: meta::is_proxy<mpl::_> > , A0 , A1 , A2 > > , boost::simd::ext::splat_or_map3< Tag, A0 , A1 , A2 > >::type dispatching( elementwise_<Tag>, tag::formal_ , unspecified_<A0> const , unspecified_<A1> const , unspecified_<A2> const , adl_helper = adl_helper() ) { return boost::simd::ext::splat_or_map3< Tag, A0 , A1 , A2 >(); } } } } namespace boost { namespace simd { namespace ext {
  template<class A0 , class A1 , class A2 , class A3, class X, std::size_t N, class Callee, class Result = boost::dispatch::meta::result_of<Callee(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type const&)>, class Enable = void>
  struct splat_impl4
  {
  };
  template<class A0 , class A1 , class A2 , class A3, class X, std::size_t N, class Callee, class Result>
  struct splat_impl4<A0 , A1 , A2 , A3, X, N, Callee, Result, typename boost::dispatch::meta::enable_if_type<typename Result::type>::type>
  {
    typedef typename Result::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3) const
    {
      return Callee()(splat<typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type>(a0) , splat<typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type>(a1) , splat<typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type>(a2) , splat<typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type>(a3));
    }
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3, class X, std::size_t N, bool B = N != 1
                                      && !is_same<X, dispatch::meta::na_>::value
                                      && ((meta::cardinal_of<A0>::value == 1u) || (meta::cardinal_of<A1>::value == 1u) || (meta::cardinal_of<A2>::value == 1u) || (meta::cardinal_of<A3>::value == 1u))>
  struct splat_or_map_choose4;
  template<class Tag, class A0 , class A1 , class A2 , class A3, class X, std::size_t N>
  struct splat_or_map_choose4<Tag, A0 , A1 , A2 , A3, X, N, true>
       : splat_impl4< A0 , A1 , A2 , A3
                                    , X, N
                                    , typename boost::dispatch::meta::
                                      dispatch_call<Tag(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type const&)>::type
                                    >
  {
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3, class SResult, class Enable = void>
  struct map_impl4
  {
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3, class SResult>
  struct map_impl4<Tag, A0 , A1 , A2 , A3, SResult, typename boost::dispatch::meta::enable_if_type<typename SResult::type>::type>
  {
    BOOST_SIMD_MAP_LOG(Tag)
    typedef typename boost::dispatch::meta::
            call<tag::map_( boost::dispatch::functor<Tag>
                          , A0 const & , A1 const & , A2 const & , A3 const &
                          )
                >::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3) const
    {
      return map( dispatch::functor<Tag>(), a0 , a1 , a2 , a3 );
    }
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3, class X, std::size_t N>
  struct splat_or_map_choose4<Tag, A0 , A1 , A2 , A3, X, N, false>
       : map_impl4< Tag, A0 , A1 , A2 , A3
                                  , boost::dispatch::meta::
                                    call<Tag(typename meta::scalar_of<A0>::type , typename meta::scalar_of<A1>::type , typename meta::scalar_of<A2>::type , typename meta::scalar_of<A3>::type)>
                                  >
  {
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3>
  struct splat_or_map4
       : splat_or_map_choose4< Tag, A0 , A1 , A2 , A3
                                             , typename ext_common< typename meta::extension_of<A0>::type , typename ext_common< typename meta::extension_of<A1>::type , typename ext_common< typename meta::extension_of<A2>::type , typename meta::extension_of<A3>::type >::type >::type >::type
                                             , cardinal_common< meta::cardinal_of<A0>::value , cardinal_common< meta::cardinal_of<A1>::value , cardinal_common< meta::cardinal_of<A2>::value , meta::cardinal_of<A3>::value >::value >::value >::value
                                             >
  {
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Tag , class A0 , class A1 , class A2 , class A3 > BOOST_FORCEINLINE typename boost::enable_if< mpl::not_< any < mpl::or_ < boost::proto:: is_expr<mpl::_> , boost::dispatch:: meta::is_proxy<mpl::_> > , A0 , A1 , A2 , A3 > > , boost::simd::ext::splat_or_map4< Tag, A0 , A1 , A2 , A3 > >::type dispatching( elementwise_<Tag>, tag::formal_ , unspecified_<A0> const , unspecified_<A1> const , unspecified_<A2> const , unspecified_<A3> const , adl_helper = adl_helper() ) { return boost::simd::ext::splat_or_map4< Tag, A0 , A1 , A2 , A3 >(); } } } } namespace boost { namespace simd { namespace ext {
  template<class A0 , class A1 , class A2 , class A3 , class A4, class X, std::size_t N, class Callee, class Result = boost::dispatch::meta::result_of<Callee(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A4>::type, N, X >::type const&)>, class Enable = void>
  struct splat_impl5
  {
  };
  template<class A0 , class A1 , class A2 , class A3 , class A4, class X, std::size_t N, class Callee, class Result>
  struct splat_impl5<A0 , A1 , A2 , A3 , A4, X, N, Callee, Result, typename boost::dispatch::meta::enable_if_type<typename Result::type>::type>
  {
    typedef typename Result::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4) const
    {
      return Callee()(splat<typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type>(a0) , splat<typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type>(a1) , splat<typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type>(a2) , splat<typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type>(a3) , splat<typename vector_on_ext< typename meta::scalar_of<A4>::type, N, X >::type>(a4));
    }
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3 , class A4, class X, std::size_t N, bool B = N != 1
                                      && !is_same<X, dispatch::meta::na_>::value
                                      && ((meta::cardinal_of<A0>::value == 1u) || (meta::cardinal_of<A1>::value == 1u) || (meta::cardinal_of<A2>::value == 1u) || (meta::cardinal_of<A3>::value == 1u) || (meta::cardinal_of<A4>::value == 1u))>
  struct splat_or_map_choose5;
  template<class Tag, class A0 , class A1 , class A2 , class A3 , class A4, class X, std::size_t N>
  struct splat_or_map_choose5<Tag, A0 , A1 , A2 , A3 , A4, X, N, true>
       : splat_impl5< A0 , A1 , A2 , A3 , A4
                                    , X, N
                                    , typename boost::dispatch::meta::
                                      dispatch_call<Tag(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A4>::type, N, X >::type const&)>::type
                                    >
  {
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3 , class A4, class SResult, class Enable = void>
  struct map_impl5
  {
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3 , class A4, class SResult>
  struct map_impl5<Tag, A0 , A1 , A2 , A3 , A4, SResult, typename boost::dispatch::meta::enable_if_type<typename SResult::type>::type>
  {
    BOOST_SIMD_MAP_LOG(Tag)
    typedef typename boost::dispatch::meta::
            call<tag::map_( boost::dispatch::functor<Tag>
                          , A0 const & , A1 const & , A2 const & , A3 const & , A4 const &
                          )
                >::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4) const
    {
      return map( dispatch::functor<Tag>(), a0 , a1 , a2 , a3 , a4 );
    }
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3 , class A4, class X, std::size_t N>
  struct splat_or_map_choose5<Tag, A0 , A1 , A2 , A3 , A4, X, N, false>
       : map_impl5< Tag, A0 , A1 , A2 , A3 , A4
                                  , boost::dispatch::meta::
                                    call<Tag(typename meta::scalar_of<A0>::type , typename meta::scalar_of<A1>::type , typename meta::scalar_of<A2>::type , typename meta::scalar_of<A3>::type , typename meta::scalar_of<A4>::type)>
                                  >
  {
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3 , class A4>
  struct splat_or_map5
       : splat_or_map_choose5< Tag, A0 , A1 , A2 , A3 , A4
                                             , typename ext_common< typename meta::extension_of<A0>::type , typename ext_common< typename meta::extension_of<A1>::type , typename ext_common< typename meta::extension_of<A2>::type , typename ext_common< typename meta::extension_of<A3>::type , typename meta::extension_of<A4>::type >::type >::type >::type >::type
                                             , cardinal_common< meta::cardinal_of<A0>::value , cardinal_common< meta::cardinal_of<A1>::value , cardinal_common< meta::cardinal_of<A2>::value , cardinal_common< meta::cardinal_of<A3>::value , meta::cardinal_of<A4>::value >::value >::value >::value >::value
                                             >
  {
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Tag , class A0 , class A1 , class A2 , class A3 , class A4 > BOOST_FORCEINLINE typename boost::enable_if< mpl::not_< any < mpl::or_ < boost::proto:: is_expr<mpl::_> , boost::dispatch:: meta::is_proxy<mpl::_> > , A0 , A1 , A2 , A3 , A4 > > , boost::simd::ext::splat_or_map5< Tag, A0 , A1 , A2 , A3 , A4 > >::type dispatching( elementwise_<Tag>, tag::formal_ , unspecified_<A0> const , unspecified_<A1> const , unspecified_<A2> const , unspecified_<A3> const , unspecified_<A4> const , adl_helper = adl_helper() ) { return boost::simd::ext::splat_or_map5< Tag, A0 , A1 , A2 , A3 , A4 >(); } } } } namespace boost { namespace simd { namespace ext {
  template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5, class X, std::size_t N, class Callee, class Result = boost::dispatch::meta::result_of<Callee(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A4>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A5>::type, N, X >::type const&)>, class Enable = void>
  struct splat_impl6
  {
  };
  template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5, class X, std::size_t N, class Callee, class Result>
  struct splat_impl6<A0 , A1 , A2 , A3 , A4 , A5, X, N, Callee, Result, typename boost::dispatch::meta::enable_if_type<typename Result::type>::type>
  {
    typedef typename Result::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4 , A5 const & a5) const
    {
      return Callee()(splat<typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type>(a0) , splat<typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type>(a1) , splat<typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type>(a2) , splat<typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type>(a3) , splat<typename vector_on_ext< typename meta::scalar_of<A4>::type, N, X >::type>(a4) , splat<typename vector_on_ext< typename meta::scalar_of<A5>::type, N, X >::type>(a5));
    }
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3 , class A4 , class A5, class X, std::size_t N, bool B = N != 1
                                      && !is_same<X, dispatch::meta::na_>::value
                                      && ((meta::cardinal_of<A0>::value == 1u) || (meta::cardinal_of<A1>::value == 1u) || (meta::cardinal_of<A2>::value == 1u) || (meta::cardinal_of<A3>::value == 1u) || (meta::cardinal_of<A4>::value == 1u) || (meta::cardinal_of<A5>::value == 1u))>
  struct splat_or_map_choose6;
  template<class Tag, class A0 , class A1 , class A2 , class A3 , class A4 , class A5, class X, std::size_t N>
  struct splat_or_map_choose6<Tag, A0 , A1 , A2 , A3 , A4 , A5, X, N, true>
       : splat_impl6< A0 , A1 , A2 , A3 , A4 , A5
                                    , X, N
                                    , typename boost::dispatch::meta::
                                      dispatch_call<Tag(typename vector_on_ext< typename meta::scalar_of<A0>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A1>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A2>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A3>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A4>::type, N, X >::type const& , typename vector_on_ext< typename meta::scalar_of<A5>::type, N, X >::type const&)>::type
                                    >
  {
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3 , class A4 , class A5, class SResult, class Enable = void>
  struct map_impl6
  {
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3 , class A4 , class A5, class SResult>
  struct map_impl6<Tag, A0 , A1 , A2 , A3 , A4 , A5, SResult, typename boost::dispatch::meta::enable_if_type<typename SResult::type>::type>
  {
    BOOST_SIMD_MAP_LOG(Tag)
    typedef typename boost::dispatch::meta::
            call<tag::map_( boost::dispatch::functor<Tag>
                          , A0 const & , A1 const & , A2 const & , A3 const & , A4 const & , A5 const &
                          )
                >::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const & a0 , A1 const & a1 , A2 const & a2 , A3 const & a3 , A4 const & a4 , A5 const & a5) const
    {
      return map( dispatch::functor<Tag>(), a0 , a1 , a2 , a3 , a4 , a5 );
    }
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3 , class A4 , class A5, class X, std::size_t N>
  struct splat_or_map_choose6<Tag, A0 , A1 , A2 , A3 , A4 , A5, X, N, false>
       : map_impl6< Tag, A0 , A1 , A2 , A3 , A4 , A5
                                  , boost::dispatch::meta::
                                    call<Tag(typename meta::scalar_of<A0>::type , typename meta::scalar_of<A1>::type , typename meta::scalar_of<A2>::type , typename meta::scalar_of<A3>::type , typename meta::scalar_of<A4>::type , typename meta::scalar_of<A5>::type)>
                                  >
  {
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3 , class A4 , class A5>
  struct splat_or_map6
       : splat_or_map_choose6< Tag, A0 , A1 , A2 , A3 , A4 , A5
                                             , typename ext_common< typename meta::extension_of<A0>::type , typename ext_common< typename meta::extension_of<A1>::type , typename ext_common< typename meta::extension_of<A2>::type , typename ext_common< typename meta::extension_of<A3>::type , typename ext_common< typename meta::extension_of<A4>::type , typename meta::extension_of<A5>::type >::type >::type >::type >::type >::type
                                             , cardinal_common< meta::cardinal_of<A0>::value , cardinal_common< meta::cardinal_of<A1>::value , cardinal_common< meta::cardinal_of<A2>::value , cardinal_common< meta::cardinal_of<A3>::value , cardinal_common< meta::cardinal_of<A4>::value , meta::cardinal_of<A5>::value >::value >::value >::value >::value >::value
                                             >
  {
  };
  } } } namespace boost { namespace dispatch { namespace meta { template< class Tag , class A0 , class A1 , class A2 , class A3 , class A4 , class A5 > BOOST_FORCEINLINE typename boost::enable_if< mpl::not_< any < mpl::or_ < boost::proto:: is_expr<mpl::_> , boost::dispatch:: meta::is_proxy<mpl::_> > , A0 , A1 , A2 , A3 , A4 , A5 > > , boost::simd::ext::splat_or_map6< Tag, A0 , A1 , A2 , A3 , A4 , A5 > >::type dispatching( elementwise_<Tag>, tag::formal_ , unspecified_<A0> const , unspecified_<A1> const , unspecified_<A2> const , unspecified_<A3> const , unspecified_<A4> const , unspecified_<A5> const , adl_helper = adl_helper() ) { return boost::simd::ext::splat_or_map6< Tag, A0 , A1 , A2 , A3 , A4 , A5 >(); } } } } namespace boost { namespace simd { namespace ext {
} } }
