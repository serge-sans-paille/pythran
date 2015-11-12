namespace boost { namespace dispatch { namespace meta
{
  struct adl_helper {};
  //==============================================================================
  // dispatch_call finds the proper call overload for evaluating a given
  // functor over a set of types on a given site
  //==============================================================================
  template<class Sig, class Site = void>
  struct dispatch_call;
  //==============================================================================
  // What the fuck with adl_helper ? Well, as pointed out by Johannes Schaub
  // it is mandated by the standard so ADL kicks in on resolving calls to
  // dispatching without having to order them BEFORE the actual dispatch_call
  // class definitions. Without it, the whole system brittles.
  //==============================================================================
  template< class Tag, class Site
           
          >
  BOOST_FORCEINLINE
  boost::dispatch::meta::
  implement<tag::unknown_, Site, Tag()>
  dispatching ( meta::unknown_<Tag>, meta::unknown_<Site>
              
              , adl_helper = adl_helper()
              )
  {
    boost::dispatch::meta::implement< tag::unknown_, Site
                                    , Tag()
                                    > that;
    return that;
  }
  template< class Tag, class Site_
           
          >
  struct dispatch_call<Tag(), Site_>
  {
    typedef typename boost::mpl::
            eval_if< is_void<Site_>
                   , default_site<Tag>
                   , mpl::identity<Site_>
                   >::type Site;
    BOOST_DISPATCH_TYPEOF_
    ( dispatching ( (typename meta::hierarchy_of<Tag>::type())
                  , (typename meta::hierarchy_of<Site>::type())
                  
                  , adl_helper()
                  )
    , type
    )
  };
  template< class Tag, class Site
          , class A0
          >
  BOOST_FORCEINLINE
  boost::dispatch::meta::
  implement<tag::unknown_, Site, Tag(A0)>
  dispatching ( meta::unknown_<Tag>, meta::unknown_<Site>
              , meta::unknown_<A0>
              , adl_helper = adl_helper()
              )
  {
    boost::dispatch::meta::implement< tag::unknown_, Site
                                    , Tag(A0)
                                    > that;
    return that;
  }
  template< class Tag, class Site_
          , class A0
          >
  struct dispatch_call<Tag(A0), Site_>
  {
    typedef typename boost::mpl::
            eval_if< is_void<Site_>
                   , default_site<Tag>
                   , mpl::identity<Site_>
                   >::type Site;
    BOOST_DISPATCH_TYPEOF_
    ( dispatching ( (typename meta::hierarchy_of<Tag>::type())
                  , (typename meta::hierarchy_of<Site>::type())
                  , (typename meta::hierarchy_of<A0>::type())
                  , adl_helper()
                  )
    , type
    )
  };
  template< class Tag, class Site
          , class A0 , class A1
          >
  BOOST_FORCEINLINE
  boost::dispatch::meta::
  implement<tag::unknown_, Site, Tag(A0 , A1)>
  dispatching ( meta::unknown_<Tag>, meta::unknown_<Site>
              , meta::unknown_<A0> , meta::unknown_<A1>
              , adl_helper = adl_helper()
              )
  {
    boost::dispatch::meta::implement< tag::unknown_, Site
                                    , Tag(A0 , A1)
                                    > that;
    return that;
  }
  template< class Tag, class Site_
          , class A0 , class A1
          >
  struct dispatch_call<Tag(A0 , A1), Site_>
  {
    typedef typename boost::mpl::
            eval_if< is_void<Site_>
                   , default_site<Tag>
                   , mpl::identity<Site_>
                   >::type Site;
    BOOST_DISPATCH_TYPEOF_
    ( dispatching ( (typename meta::hierarchy_of<Tag>::type())
                  , (typename meta::hierarchy_of<Site>::type())
                  , (typename meta::hierarchy_of<A0>::type()) , (typename meta::hierarchy_of<A1>::type())
                  , adl_helper()
                  )
    , type
    )
  };
  template< class Tag, class Site
          , class A0 , class A1 , class A2
          >
  BOOST_FORCEINLINE
  boost::dispatch::meta::
  implement<tag::unknown_, Site, Tag(A0 , A1 , A2)>
  dispatching ( meta::unknown_<Tag>, meta::unknown_<Site>
              , meta::unknown_<A0> , meta::unknown_<A1> , meta::unknown_<A2>
              , adl_helper = adl_helper()
              )
  {
    boost::dispatch::meta::implement< tag::unknown_, Site
                                    , Tag(A0 , A1 , A2)
                                    > that;
    return that;
  }
  template< class Tag, class Site_
          , class A0 , class A1 , class A2
          >
  struct dispatch_call<Tag(A0 , A1 , A2), Site_>
  {
    typedef typename boost::mpl::
            eval_if< is_void<Site_>
                   , default_site<Tag>
                   , mpl::identity<Site_>
                   >::type Site;
    BOOST_DISPATCH_TYPEOF_
    ( dispatching ( (typename meta::hierarchy_of<Tag>::type())
                  , (typename meta::hierarchy_of<Site>::type())
                  , (typename meta::hierarchy_of<A0>::type()) , (typename meta::hierarchy_of<A1>::type()) , (typename meta::hierarchy_of<A2>::type())
                  , adl_helper()
                  )
    , type
    )
  };
  template< class Tag, class Site
          , class A0 , class A1 , class A2 , class A3
          >
  BOOST_FORCEINLINE
  boost::dispatch::meta::
  implement<tag::unknown_, Site, Tag(A0 , A1 , A2 , A3)>
  dispatching ( meta::unknown_<Tag>, meta::unknown_<Site>
              , meta::unknown_<A0> , meta::unknown_<A1> , meta::unknown_<A2> , meta::unknown_<A3>
              , adl_helper = adl_helper()
              )
  {
    boost::dispatch::meta::implement< tag::unknown_, Site
                                    , Tag(A0 , A1 , A2 , A3)
                                    > that;
    return that;
  }
  template< class Tag, class Site_
          , class A0 , class A1 , class A2 , class A3
          >
  struct dispatch_call<Tag(A0 , A1 , A2 , A3), Site_>
  {
    typedef typename boost::mpl::
            eval_if< is_void<Site_>
                   , default_site<Tag>
                   , mpl::identity<Site_>
                   >::type Site;
    BOOST_DISPATCH_TYPEOF_
    ( dispatching ( (typename meta::hierarchy_of<Tag>::type())
                  , (typename meta::hierarchy_of<Site>::type())
                  , (typename meta::hierarchy_of<A0>::type()) , (typename meta::hierarchy_of<A1>::type()) , (typename meta::hierarchy_of<A2>::type()) , (typename meta::hierarchy_of<A3>::type())
                  , adl_helper()
                  )
    , type
    )
  };
  template< class Tag, class Site
          , class A0 , class A1 , class A2 , class A3 , class A4
          >
  BOOST_FORCEINLINE
  boost::dispatch::meta::
  implement<tag::unknown_, Site, Tag(A0 , A1 , A2 , A3 , A4)>
  dispatching ( meta::unknown_<Tag>, meta::unknown_<Site>
              , meta::unknown_<A0> , meta::unknown_<A1> , meta::unknown_<A2> , meta::unknown_<A3> , meta::unknown_<A4>
              , adl_helper = adl_helper()
              )
  {
    boost::dispatch::meta::implement< tag::unknown_, Site
                                    , Tag(A0 , A1 , A2 , A3 , A4)
                                    > that;
    return that;
  }
  template< class Tag, class Site_
          , class A0 , class A1 , class A2 , class A3 , class A4
          >
  struct dispatch_call<Tag(A0 , A1 , A2 , A3 , A4), Site_>
  {
    typedef typename boost::mpl::
            eval_if< is_void<Site_>
                   , default_site<Tag>
                   , mpl::identity<Site_>
                   >::type Site;
    BOOST_DISPATCH_TYPEOF_
    ( dispatching ( (typename meta::hierarchy_of<Tag>::type())
                  , (typename meta::hierarchy_of<Site>::type())
                  , (typename meta::hierarchy_of<A0>::type()) , (typename meta::hierarchy_of<A1>::type()) , (typename meta::hierarchy_of<A2>::type()) , (typename meta::hierarchy_of<A3>::type()) , (typename meta::hierarchy_of<A4>::type())
                  , adl_helper()
                  )
    , type
    )
  };
  template< class Tag, class Site
          , class A0 , class A1 , class A2 , class A3 , class A4 , class A5
          >
  BOOST_FORCEINLINE
  boost::dispatch::meta::
  implement<tag::unknown_, Site, Tag(A0 , A1 , A2 , A3 , A4 , A5)>
  dispatching ( meta::unknown_<Tag>, meta::unknown_<Site>
              , meta::unknown_<A0> , meta::unknown_<A1> , meta::unknown_<A2> , meta::unknown_<A3> , meta::unknown_<A4> , meta::unknown_<A5>
              , adl_helper = adl_helper()
              )
  {
    boost::dispatch::meta::implement< tag::unknown_, Site
                                    , Tag(A0 , A1 , A2 , A3 , A4 , A5)
                                    > that;
    return that;
  }
  template< class Tag, class Site_
          , class A0 , class A1 , class A2 , class A3 , class A4 , class A5
          >
  struct dispatch_call<Tag(A0 , A1 , A2 , A3 , A4 , A5), Site_>
  {
    typedef typename boost::mpl::
            eval_if< is_void<Site_>
                   , default_site<Tag>
                   , mpl::identity<Site_>
                   >::type Site;
    BOOST_DISPATCH_TYPEOF_
    ( dispatching ( (typename meta::hierarchy_of<Tag>::type())
                  , (typename meta::hierarchy_of<Site>::type())
                  , (typename meta::hierarchy_of<A0>::type()) , (typename meta::hierarchy_of<A1>::type()) , (typename meta::hierarchy_of<A2>::type()) , (typename meta::hierarchy_of<A3>::type()) , (typename meta::hierarchy_of<A4>::type()) , (typename meta::hierarchy_of<A5>::type())
                  , adl_helper()
                  )
    , type
    )
  };
  template< class Tag, class Site
          , class A0 , class A1 , class A2 , class A3 , class A4 , class A5 , class A6
          >
  BOOST_FORCEINLINE
  boost::dispatch::meta::
  implement<tag::unknown_, Site, Tag(A0 , A1 , A2 , A3 , A4 , A5 , A6)>
  dispatching ( meta::unknown_<Tag>, meta::unknown_<Site>
              , meta::unknown_<A0> , meta::unknown_<A1> , meta::unknown_<A2> , meta::unknown_<A3> , meta::unknown_<A4> , meta::unknown_<A5> , meta::unknown_<A6>
              , adl_helper = adl_helper()
              )
  {
    boost::dispatch::meta::implement< tag::unknown_, Site
                                    , Tag(A0 , A1 , A2 , A3 , A4 , A5 , A6)
                                    > that;
    return that;
  }
  template< class Tag, class Site_
          , class A0 , class A1 , class A2 , class A3 , class A4 , class A5 , class A6
          >
  struct dispatch_call<Tag(A0 , A1 , A2 , A3 , A4 , A5 , A6), Site_>
  {
    typedef typename boost::mpl::
            eval_if< is_void<Site_>
                   , default_site<Tag>
                   , mpl::identity<Site_>
                   >::type Site;
    BOOST_DISPATCH_TYPEOF_
    ( dispatching ( (typename meta::hierarchy_of<Tag>::type())
                  , (typename meta::hierarchy_of<Site>::type())
                  , (typename meta::hierarchy_of<A0>::type()) , (typename meta::hierarchy_of<A1>::type()) , (typename meta::hierarchy_of<A2>::type()) , (typename meta::hierarchy_of<A3>::type()) , (typename meta::hierarchy_of<A4>::type()) , (typename meta::hierarchy_of<A5>::type()) , (typename meta::hierarchy_of<A6>::type())
                  , adl_helper()
                  )
    , type
    )
  };
} } }
