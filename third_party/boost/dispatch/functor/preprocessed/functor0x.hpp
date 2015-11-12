    template<class This, class A0>
    struct result<This(A0)>
      : meta::
        result_of< typename meta::
                   dispatch_call< Tag(typename meta::as_ref<A0>::type)
                                , EvalContext
                                >::type(typename meta::as_ref<A0>::type)
                 >
    {
    };
    template<class A0> BOOST_FORCEINLINE
    typename result<functor(typename meta::as_ref<A0>::type)>::type
    operator()(A0 && a0) const
    {
      return typename meta::
             dispatch_call< Tag(typename meta::as_ref<A0>::type)
                          , EvalContext
                          >::type()
            (static_cast<typename meta::as_ref<A0>::type>(a0));
    }
    template<class This, class A0 , class A1>
    struct result<This(A0 , A1)>
      : meta::
        result_of< typename meta::
                   dispatch_call< Tag(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type)
                                , EvalContext
                                >::type(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type)
                 >
    {
    };
    template<class A0 , class A1> BOOST_FORCEINLINE
    typename result<functor(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type)>::type
    operator()(A0 && a0 , A1 && a1) const
    {
      return typename meta::
             dispatch_call< Tag(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type)
                          , EvalContext
                          >::type()
            (static_cast<typename meta::as_ref<A0>::type>(a0) , static_cast<typename meta::as_ref<A1>::type>(a1));
    }
    template<class This, class A0 , class A1 , class A2>
    struct result<This(A0 , A1 , A2)>
      : meta::
        result_of< typename meta::
                   dispatch_call< Tag(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type)
                                , EvalContext
                                >::type(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type)
                 >
    {
    };
    template<class A0 , class A1 , class A2> BOOST_FORCEINLINE
    typename result<functor(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type)>::type
    operator()(A0 && a0 , A1 && a1 , A2 && a2) const
    {
      return typename meta::
             dispatch_call< Tag(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type)
                          , EvalContext
                          >::type()
            (static_cast<typename meta::as_ref<A0>::type>(a0) , static_cast<typename meta::as_ref<A1>::type>(a1) , static_cast<typename meta::as_ref<A2>::type>(a2));
    }
    template<class This, class A0 , class A1 , class A2 , class A3>
    struct result<This(A0 , A1 , A2 , A3)>
      : meta::
        result_of< typename meta::
                   dispatch_call< Tag(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type , typename meta::as_ref<A3>::type)
                                , EvalContext
                                >::type(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type , typename meta::as_ref<A3>::type)
                 >
    {
    };
    template<class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE
    typename result<functor(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type , typename meta::as_ref<A3>::type)>::type
    operator()(A0 && a0 , A1 && a1 , A2 && a2 , A3 && a3) const
    {
      return typename meta::
             dispatch_call< Tag(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type , typename meta::as_ref<A3>::type)
                          , EvalContext
                          >::type()
            (static_cast<typename meta::as_ref<A0>::type>(a0) , static_cast<typename meta::as_ref<A1>::type>(a1) , static_cast<typename meta::as_ref<A2>::type>(a2) , static_cast<typename meta::as_ref<A3>::type>(a3));
    }
    template<class This, class A0 , class A1 , class A2 , class A3 , class A4>
    struct result<This(A0 , A1 , A2 , A3 , A4)>
      : meta::
        result_of< typename meta::
                   dispatch_call< Tag(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type , typename meta::as_ref<A3>::type , typename meta::as_ref<A4>::type)
                                , EvalContext
                                >::type(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type , typename meta::as_ref<A3>::type , typename meta::as_ref<A4>::type)
                 >
    {
    };
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type , typename meta::as_ref<A3>::type , typename meta::as_ref<A4>::type)>::type
    operator()(A0 && a0 , A1 && a1 , A2 && a2 , A3 && a3 , A4 && a4) const
    {
      return typename meta::
             dispatch_call< Tag(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type , typename meta::as_ref<A3>::type , typename meta::as_ref<A4>::type)
                          , EvalContext
                          >::type()
            (static_cast<typename meta::as_ref<A0>::type>(a0) , static_cast<typename meta::as_ref<A1>::type>(a1) , static_cast<typename meta::as_ref<A2>::type>(a2) , static_cast<typename meta::as_ref<A3>::type>(a3) , static_cast<typename meta::as_ref<A4>::type>(a4));
    }
    template<class This, class A0 , class A1 , class A2 , class A3 , class A4 , class A5>
    struct result<This(A0 , A1 , A2 , A3 , A4 , A5)>
      : meta::
        result_of< typename meta::
                   dispatch_call< Tag(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type , typename meta::as_ref<A3>::type , typename meta::as_ref<A4>::type , typename meta::as_ref<A5>::type)
                                , EvalContext
                                >::type(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type , typename meta::as_ref<A3>::type , typename meta::as_ref<A4>::type , typename meta::as_ref<A5>::type)
                 >
    {
    };
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type , typename meta::as_ref<A3>::type , typename meta::as_ref<A4>::type , typename meta::as_ref<A5>::type)>::type
    operator()(A0 && a0 , A1 && a1 , A2 && a2 , A3 && a3 , A4 && a4 , A5 && a5) const
    {
      return typename meta::
             dispatch_call< Tag(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type , typename meta::as_ref<A3>::type , typename meta::as_ref<A4>::type , typename meta::as_ref<A5>::type)
                          , EvalContext
                          >::type()
            (static_cast<typename meta::as_ref<A0>::type>(a0) , static_cast<typename meta::as_ref<A1>::type>(a1) , static_cast<typename meta::as_ref<A2>::type>(a2) , static_cast<typename meta::as_ref<A3>::type>(a3) , static_cast<typename meta::as_ref<A4>::type>(a4) , static_cast<typename meta::as_ref<A5>::type>(a5));
    }
