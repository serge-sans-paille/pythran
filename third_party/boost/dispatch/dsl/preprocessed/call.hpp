namespace boost { namespace dispatch { namespace meta
{
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 > BOOST_FORCEINLINE typename boost::enable_if< mpl::and_< mpl::not_< is_formal<Func> > , any < boost::proto:: is_expr<boost::mpl::_> , A0 > > , implement<Func(tag::ast_), tag::formal_> >::type dispatching( unspecified_<Func>, tag::formal_ , unspecified_<A0> const , adl_helper = adl_helper() ) { return implement<Func(tag::ast_), tag::formal_>(); } } } } namespace boost { namespace dispatch { namespace meta {
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 > BOOST_FORCEINLINE typename boost::enable_if< mpl::and_< mpl::not_< is_formal<Func> > , any < boost::proto:: is_expr<boost::mpl::_> , A0 , A1 > > , implement<Func(tag::ast_), tag::formal_> >::type dispatching( unspecified_<Func>, tag::formal_ , unspecified_<A0> const , unspecified_<A1> const , adl_helper = adl_helper() ) { return implement<Func(tag::ast_), tag::formal_>(); } } } } namespace boost { namespace dispatch { namespace meta {
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 , class A2 > BOOST_FORCEINLINE typename boost::enable_if< mpl::and_< mpl::not_< is_formal<Func> > , any < boost::proto:: is_expr<boost::mpl::_> , A0 , A1 , A2 > > , implement<Func(tag::ast_), tag::formal_> >::type dispatching( unspecified_<Func>, tag::formal_ , unspecified_<A0> const , unspecified_<A1> const , unspecified_<A2> const , adl_helper = adl_helper() ) { return implement<Func(tag::ast_), tag::formal_>(); } } } } namespace boost { namespace dispatch { namespace meta {
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 , class A2 , class A3 > BOOST_FORCEINLINE typename boost::enable_if< mpl::and_< mpl::not_< is_formal<Func> > , any < boost::proto:: is_expr<boost::mpl::_> , A0 , A1 , A2 , A3 > > , implement<Func(tag::ast_), tag::formal_> >::type dispatching( unspecified_<Func>, tag::formal_ , unspecified_<A0> const , unspecified_<A1> const , unspecified_<A2> const , unspecified_<A3> const , adl_helper = adl_helper() ) { return implement<Func(tag::ast_), tag::formal_>(); } } } } namespace boost { namespace dispatch { namespace meta {
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 , class A2 , class A3 , class A4 > BOOST_FORCEINLINE typename boost::enable_if< mpl::and_< mpl::not_< is_formal<Func> > , any < boost::proto:: is_expr<boost::mpl::_> , A0 , A1 , A2 , A3 , A4 > > , implement<Func(tag::ast_), tag::formal_> >::type dispatching( unspecified_<Func>, tag::formal_ , unspecified_<A0> const , unspecified_<A1> const , unspecified_<A2> const , unspecified_<A3> const , unspecified_<A4> const , adl_helper = adl_helper() ) { return implement<Func(tag::ast_), tag::formal_>(); } } } } namespace boost { namespace dispatch { namespace meta {
  } } } namespace boost { namespace dispatch { namespace meta { template< class Func , class A0 , class A1 , class A2 , class A3 , class A4 , class A5 > BOOST_FORCEINLINE typename boost::enable_if< mpl::and_< mpl::not_< is_formal<Func> > , any < boost::proto:: is_expr<boost::mpl::_> , A0 , A1 , A2 , A3 , A4 , A5 > > , implement<Func(tag::ast_), tag::formal_> >::type dispatching( unspecified_<Func>, tag::formal_ , unspecified_<A0> const , unspecified_<A1> const , unspecified_<A2> const , unspecified_<A3> const , unspecified_<A4> const , unspecified_<A5> const , adl_helper = adl_helper() ) { return implement<Func(tag::ast_), tag::formal_>(); } } } } namespace boost { namespace dispatch { namespace meta {
  template<class Func,class Dummy>
  struct implement<Func(tag::ast_),tag::formal_,Dummy>
  {
    template<class Sig>
    struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename boost::proto::result_of::
      make_expr < typename meta::proto_tag<Func>::type
                , typename meta:: as_ref<A0 >::type
                >::type type;
    };
    template<class A0>
    BOOST_FORCEINLINE
    typename result<implement
                    (A0 & a0)
                   >::type
    operator()(A0 & a0) const
    {
      return boost::proto::
      make_expr< typename meta::proto_tag<Func>::type >
               ( boost::reference_wrapper<A0>(a0) );
    }
    template<class This,class A0 , class A1>
    struct result<This(A0 , A1)>
    {
      typedef typename boost::proto::result_of::
      make_expr < typename meta::proto_tag<Func>::type
                , typename meta:: as_ref<A0 >::type , typename meta:: as_ref<A1 >::type
                >::type type;
    };
    template<class A0 , class A1>
    BOOST_FORCEINLINE
    typename result<implement
                    (A0 & a0 , A1 & a1)
                   >::type
    operator()(A0 & a0 , A1 & a1) const
    {
      return boost::proto::
      make_expr< typename meta::proto_tag<Func>::type >
               ( boost::reference_wrapper<A0>(a0) , boost::reference_wrapper<A1>(a1) );
    }
    template<class This,class A0 , class A1 , class A2>
    struct result<This(A0 , A1 , A2)>
    {
      typedef typename boost::proto::result_of::
      make_expr < typename meta::proto_tag<Func>::type
                , typename meta:: as_ref<A0 >::type , typename meta:: as_ref<A1 >::type , typename meta:: as_ref<A2 >::type
                >::type type;
    };
    template<class A0 , class A1 , class A2>
    BOOST_FORCEINLINE
    typename result<implement
                    (A0 & a0 , A1 & a1 , A2 & a2)
                   >::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2) const
    {
      return boost::proto::
      make_expr< typename meta::proto_tag<Func>::type >
               ( boost::reference_wrapper<A0>(a0) , boost::reference_wrapper<A1>(a1) , boost::reference_wrapper<A2>(a2) );
    }
    template<class This,class A0 , class A1 , class A2 , class A3>
    struct result<This(A0 , A1 , A2 , A3)>
    {
      typedef typename boost::proto::result_of::
      make_expr < typename meta::proto_tag<Func>::type
                , typename meta:: as_ref<A0 >::type , typename meta:: as_ref<A1 >::type , typename meta:: as_ref<A2 >::type , typename meta:: as_ref<A3 >::type
                >::type type;
    };
    template<class A0 , class A1 , class A2 , class A3>
    BOOST_FORCEINLINE
    typename result<implement
                    (A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3)
                   >::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3) const
    {
      return boost::proto::
      make_expr< typename meta::proto_tag<Func>::type >
               ( boost::reference_wrapper<A0>(a0) , boost::reference_wrapper<A1>(a1) , boost::reference_wrapper<A2>(a2) , boost::reference_wrapper<A3>(a3) );
    }
    template<class This,class A0 , class A1 , class A2 , class A3 , class A4>
    struct result<This(A0 , A1 , A2 , A3 , A4)>
    {
      typedef typename boost::proto::result_of::
      make_expr < typename meta::proto_tag<Func>::type
                , typename meta:: as_ref<A0 >::type , typename meta:: as_ref<A1 >::type , typename meta:: as_ref<A2 >::type , typename meta:: as_ref<A3 >::type , typename meta:: as_ref<A4 >::type
                >::type type;
    };
    template<class A0 , class A1 , class A2 , class A3 , class A4>
    BOOST_FORCEINLINE
    typename result<implement
                    (A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4)
                   >::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4) const
    {
      return boost::proto::
      make_expr< typename meta::proto_tag<Func>::type >
               ( boost::reference_wrapper<A0>(a0) , boost::reference_wrapper<A1>(a1) , boost::reference_wrapper<A2>(a2) , boost::reference_wrapper<A3>(a3) , boost::reference_wrapper<A4>(a4) );
    }
    template<class This,class A0 , class A1 , class A2 , class A3 , class A4 , class A5>
    struct result<This(A0 , A1 , A2 , A3 , A4 , A5)>
    {
      typedef typename boost::proto::result_of::
      make_expr < typename meta::proto_tag<Func>::type
                , typename meta:: as_ref<A0 >::type , typename meta:: as_ref<A1 >::type , typename meta:: as_ref<A2 >::type , typename meta:: as_ref<A3 >::type , typename meta:: as_ref<A4 >::type , typename meta:: as_ref<A5 >::type
                >::type type;
    };
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5>
    BOOST_FORCEINLINE
    typename result<implement
                    (A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5)
                   >::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5) const
    {
      return boost::proto::
      make_expr< typename meta::proto_tag<Func>::type >
               ( boost::reference_wrapper<A0>(a0) , boost::reference_wrapper<A1>(a1) , boost::reference_wrapper<A2>(a2) , boost::reference_wrapper<A3>(a3) , boost::reference_wrapper<A4>(a4) , boost::reference_wrapper<A5>(a5) );
    }
  };
} } }
