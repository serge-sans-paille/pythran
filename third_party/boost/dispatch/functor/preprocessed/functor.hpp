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
    typename result<functor(A0 &)>::type
    operator()(A0 & a0) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &)
                          , EvalContext
                          >::type()
            (a0);
    }
    template<class A0> BOOST_FORCEINLINE
    typename result<functor(A0 const&)>::type
    operator()(A0 const& a0) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&)
                          , EvalContext
                          >::type()
            (a0);
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
    typename result<functor(A0 &, A1 &)>::type
    operator()(A0 & a0 , A1 & a1) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &)
                          , EvalContext
                          >::type()
            (a0 , a1);
    }
    template<class A0 , class A1> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&)>::type
    operator()(A0 & a0 , A1 const& a1) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&)
                          , EvalContext
                          >::type()
            (a0 , a1);
    }
    template<class A0 , class A1> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &)>::type
    operator()(A0 const& a0 , A1 & a1) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &)
                          , EvalContext
                          >::type()
            (a0 , a1);
    }
    template<class A0 , class A1> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&)>::type
    operator()(A0 const& a0 , A1 const& a1) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&)
                          , EvalContext
                          >::type()
            (a0 , a1);
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
    typename result<functor(A0 &, A1 &, A2 &)>::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2);
    }
    template<class A0 , class A1 , class A2> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 const&)>::type
    operator()(A0 & a0 , A1 & a1 , A2 const& a2) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2);
    }
    template<class A0 , class A1 , class A2> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 &)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 & a2) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2);
    }
    template<class A0 , class A1 , class A2> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 const&)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 const& a2) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2);
    }
    template<class A0 , class A1 , class A2> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 &)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 & a2) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2);
    }
    template<class A0 , class A1 , class A2> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 const&)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 const& a2) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2);
    }
    template<class A0 , class A1 , class A2> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 &)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 & a2) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2);
    }
    template<class A0 , class A1 , class A2> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 const&)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 const& a2) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2);
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
    typename result<functor(A0 &, A1 &, A2 &, A3 &)>::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 &, A3 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3);
    }
    template<class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 &, A3 const&)>::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 const& a3) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 &, A3 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3);
    }
    template<class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 const&, A3 &)>::type
    operator()(A0 & a0 , A1 & a1 , A2 const& a2 , A3 & a3) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 const&, A3 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3);
    }
    template<class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 const&, A3 const&)>::type
    operator()(A0 & a0 , A1 & a1 , A2 const& a2 , A3 const& a3) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 const&, A3 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3);
    }
    template<class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 &, A3 &)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 & a2 , A3 & a3) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 &, A3 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3);
    }
    template<class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 &, A3 const&)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 & a2 , A3 const& a3) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 &, A3 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3);
    }
    template<class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 const&, A3 &)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 const& a2 , A3 & a3) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 const&, A3 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3);
    }
    template<class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 const&, A3 const&)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 const& a2 , A3 const& a3) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 const&, A3 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3);
    }
    template<class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 &, A3 &)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 & a2 , A3 & a3) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 &, A3 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3);
    }
    template<class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 &, A3 const&)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 & a2 , A3 const& a3) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 &, A3 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3);
    }
    template<class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 const&, A3 &)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 const& a2 , A3 & a3) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 const&, A3 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3);
    }
    template<class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 const&, A3 const&)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 const& a2 , A3 const& a3) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 const&, A3 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3);
    }
    template<class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 &, A3 &)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 & a2 , A3 & a3) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 &, A3 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3);
    }
    template<class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 &, A3 const&)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 & a2 , A3 const& a3) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 &, A3 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3);
    }
    template<class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 const&, A3 &)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 & a3) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 const&, A3 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3);
    }
    template<class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 const&, A3 const&)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 const&, A3 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3);
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
    typename result<functor(A0 &, A1 &, A2 &, A3 &, A4 &)>::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 &, A3 &, A4 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 &, A3 &, A4 const&)>::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 const& a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 &, A3 &, A4 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 &, A3 const&, A4 &)>::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 const& a3 , A4 & a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 &, A3 const&, A4 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 &, A3 const&, A4 const&)>::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 const& a3 , A4 const& a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 &, A3 const&, A4 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 const&, A3 &, A4 &)>::type
    operator()(A0 & a0 , A1 & a1 , A2 const& a2 , A3 & a3 , A4 & a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 const&, A3 &, A4 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 const&, A3 &, A4 const&)>::type
    operator()(A0 & a0 , A1 & a1 , A2 const& a2 , A3 & a3 , A4 const& a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 const&, A3 &, A4 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 const&, A3 const&, A4 &)>::type
    operator()(A0 & a0 , A1 & a1 , A2 const& a2 , A3 const& a3 , A4 & a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 const&, A3 const&, A4 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 const&, A3 const&, A4 const&)>::type
    operator()(A0 & a0 , A1 & a1 , A2 const& a2 , A3 const& a3 , A4 const& a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 const&, A3 const&, A4 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 &, A3 &, A4 &)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 & a2 , A3 & a3 , A4 & a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 &, A3 &, A4 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 &, A3 &, A4 const&)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 & a2 , A3 & a3 , A4 const& a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 &, A3 &, A4 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 &, A3 const&, A4 &)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 & a2 , A3 const& a3 , A4 & a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 &, A3 const&, A4 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 &, A3 const&, A4 const&)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 & a2 , A3 const& a3 , A4 const& a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 &, A3 const&, A4 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 const&, A3 &, A4 &)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 const& a2 , A3 & a3 , A4 & a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 const&, A3 &, A4 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 const&, A3 &, A4 const&)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 const& a2 , A3 & a3 , A4 const& a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 const&, A3 &, A4 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 const&, A3 const&, A4 &)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 & a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 const&, A3 const&, A4 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 const&, A3 const&, A4 const&)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 const&, A3 const&, A4 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 &, A3 &, A4 &)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 &, A3 &, A4 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 &, A3 &, A4 const&)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 const& a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 &, A3 &, A4 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 &, A3 const&, A4 &)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 & a2 , A3 const& a3 , A4 & a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 &, A3 const&, A4 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 &, A3 const&, A4 const&)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 & a2 , A3 const& a3 , A4 const& a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 &, A3 const&, A4 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 const&, A3 &, A4 &)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 const& a2 , A3 & a3 , A4 & a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 const&, A3 &, A4 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 const&, A3 &, A4 const&)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 const& a2 , A3 & a3 , A4 const& a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 const&, A3 &, A4 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 const&, A3 const&, A4 &)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 const& a2 , A3 const& a3 , A4 & a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 const&, A3 const&, A4 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 const&, A3 const&, A4 const&)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 const& a2 , A3 const& a3 , A4 const& a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 const&, A3 const&, A4 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 &, A3 &, A4 &)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 & a2 , A3 & a3 , A4 & a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 &, A3 &, A4 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 &, A3 &, A4 const&)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 & a2 , A3 & a3 , A4 const& a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 &, A3 &, A4 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 &, A3 const&, A4 &)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 & a2 , A3 const& a3 , A4 & a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 &, A3 const&, A4 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 &, A3 const&, A4 const&)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 & a2 , A3 const& a3 , A4 const& a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 &, A3 const&, A4 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 const&, A3 &, A4 &)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 & a3 , A4 & a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 const&, A3 &, A4 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 const&, A3 &, A4 const&)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 & a3 , A4 const& a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 const&, A3 &, A4 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 const&, A3 const&, A4 &)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 & a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 const&, A3 const&, A4 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 const&, A3 const&, A4 const&)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 const&, A3 const&, A4 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4);
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
    typename result<functor(A0 &, A1 &, A2 &, A3 &, A4 &, A5 &)>::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 &, A3 &, A4 &, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 &, A3 &, A4 &, A5 const&)>::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 &, A3 &, A4 &, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 &, A3 &, A4 const&, A5 &)>::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 const& a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 &, A3 &, A4 const&, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 &, A3 &, A4 const&, A5 const&)>::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 const& a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 &, A3 &, A4 const&, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 &, A3 const&, A4 &, A5 &)>::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 const& a3 , A4 & a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 &, A3 const&, A4 &, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 &, A3 const&, A4 &, A5 const&)>::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 const& a3 , A4 & a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 &, A3 const&, A4 &, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 &, A3 const&, A4 const&, A5 &)>::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 const& a3 , A4 const& a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 &, A3 const&, A4 const&, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 &, A3 const&, A4 const&, A5 const&)>::type
    operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 const& a3 , A4 const& a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 &, A3 const&, A4 const&, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 const&, A3 &, A4 &, A5 &)>::type
    operator()(A0 & a0 , A1 & a1 , A2 const& a2 , A3 & a3 , A4 & a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 const&, A3 &, A4 &, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 const&, A3 &, A4 &, A5 const&)>::type
    operator()(A0 & a0 , A1 & a1 , A2 const& a2 , A3 & a3 , A4 & a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 const&, A3 &, A4 &, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 const&, A3 &, A4 const&, A5 &)>::type
    operator()(A0 & a0 , A1 & a1 , A2 const& a2 , A3 & a3 , A4 const& a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 const&, A3 &, A4 const&, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 const&, A3 &, A4 const&, A5 const&)>::type
    operator()(A0 & a0 , A1 & a1 , A2 const& a2 , A3 & a3 , A4 const& a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 const&, A3 &, A4 const&, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 const&, A3 const&, A4 &, A5 &)>::type
    operator()(A0 & a0 , A1 & a1 , A2 const& a2 , A3 const& a3 , A4 & a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 const&, A3 const&, A4 &, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 const&, A3 const&, A4 &, A5 const&)>::type
    operator()(A0 & a0 , A1 & a1 , A2 const& a2 , A3 const& a3 , A4 & a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 const&, A3 const&, A4 &, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 const&, A3 const&, A4 const&, A5 &)>::type
    operator()(A0 & a0 , A1 & a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 const&, A3 const&, A4 const&, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 &, A2 const&, A3 const&, A4 const&, A5 const&)>::type
    operator()(A0 & a0 , A1 & a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 &, A2 const&, A3 const&, A4 const&, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 &, A3 &, A4 &, A5 &)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 &, A3 &, A4 &, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 &, A3 &, A4 &, A5 const&)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 &, A3 &, A4 &, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 &, A3 &, A4 const&, A5 &)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 & a2 , A3 & a3 , A4 const& a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 &, A3 &, A4 const&, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 &, A3 &, A4 const&, A5 const&)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 & a2 , A3 & a3 , A4 const& a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 &, A3 &, A4 const&, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 &, A3 const&, A4 &, A5 &)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 & a2 , A3 const& a3 , A4 & a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 &, A3 const&, A4 &, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 &, A3 const&, A4 &, A5 const&)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 & a2 , A3 const& a3 , A4 & a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 &, A3 const&, A4 &, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 &, A3 const&, A4 const&, A5 &)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 & a2 , A3 const& a3 , A4 const& a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 &, A3 const&, A4 const&, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 &, A3 const&, A4 const&, A5 const&)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 & a2 , A3 const& a3 , A4 const& a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 &, A3 const&, A4 const&, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 const&, A3 &, A4 &, A5 &)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 const& a2 , A3 & a3 , A4 & a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 const&, A3 &, A4 &, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 const&, A3 &, A4 &, A5 const&)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 const& a2 , A3 & a3 , A4 & a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 const&, A3 &, A4 &, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 const&, A3 &, A4 const&, A5 &)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 const& a2 , A3 & a3 , A4 const& a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 const&, A3 &, A4 const&, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 const&, A3 &, A4 const&, A5 const&)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 const& a2 , A3 & a3 , A4 const& a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 const&, A3 &, A4 const&, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 const&, A3 const&, A4 &, A5 &)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 & a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 const&, A3 const&, A4 &, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 const&, A3 const&, A4 &, A5 const&)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 & a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 const&, A3 const&, A4 &, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 const&, A3 const&, A4 const&, A5 &)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 const&, A3 const&, A4 const&, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 &, A1 const&, A2 const&, A3 const&, A4 const&, A5 const&)>::type
    operator()(A0 & a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 &, A1 const&, A2 const&, A3 const&, A4 const&, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 &, A3 &, A4 &, A5 &)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 &, A3 &, A4 &, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 &, A3 &, A4 &, A5 const&)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 &, A3 &, A4 &, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 &, A3 &, A4 const&, A5 &)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 const& a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 &, A3 &, A4 const&, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 &, A3 &, A4 const&, A5 const&)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 const& a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 &, A3 &, A4 const&, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 &, A3 const&, A4 &, A5 &)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 & a2 , A3 const& a3 , A4 & a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 &, A3 const&, A4 &, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 &, A3 const&, A4 &, A5 const&)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 & a2 , A3 const& a3 , A4 & a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 &, A3 const&, A4 &, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 &, A3 const&, A4 const&, A5 &)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 & a2 , A3 const& a3 , A4 const& a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 &, A3 const&, A4 const&, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 &, A3 const&, A4 const&, A5 const&)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 & a2 , A3 const& a3 , A4 const& a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 &, A3 const&, A4 const&, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 const&, A3 &, A4 &, A5 &)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 const& a2 , A3 & a3 , A4 & a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 const&, A3 &, A4 &, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 const&, A3 &, A4 &, A5 const&)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 const& a2 , A3 & a3 , A4 & a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 const&, A3 &, A4 &, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 const&, A3 &, A4 const&, A5 &)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 const& a2 , A3 & a3 , A4 const& a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 const&, A3 &, A4 const&, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 const&, A3 &, A4 const&, A5 const&)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 const& a2 , A3 & a3 , A4 const& a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 const&, A3 &, A4 const&, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 const&, A3 const&, A4 &, A5 &)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 const& a2 , A3 const& a3 , A4 & a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 const&, A3 const&, A4 &, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 const&, A3 const&, A4 &, A5 const&)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 const& a2 , A3 const& a3 , A4 & a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 const&, A3 const&, A4 &, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 const&, A3 const&, A4 const&, A5 &)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 const&, A3 const&, A4 const&, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 &, A2 const&, A3 const&, A4 const&, A5 const&)>::type
    operator()(A0 const& a0 , A1 & a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 &, A2 const&, A3 const&, A4 const&, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 &, A3 &, A4 &, A5 &)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 &, A3 &, A4 &, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 &, A3 &, A4 &, A5 const&)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 &, A3 &, A4 &, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 &, A3 &, A4 const&, A5 &)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 & a2 , A3 & a3 , A4 const& a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 &, A3 &, A4 const&, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 &, A3 &, A4 const&, A5 const&)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 & a2 , A3 & a3 , A4 const& a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 &, A3 &, A4 const&, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 &, A3 const&, A4 &, A5 &)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 & a2 , A3 const& a3 , A4 & a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 &, A3 const&, A4 &, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 &, A3 const&, A4 &, A5 const&)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 & a2 , A3 const& a3 , A4 & a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 &, A3 const&, A4 &, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 &, A3 const&, A4 const&, A5 &)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 & a2 , A3 const& a3 , A4 const& a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 &, A3 const&, A4 const&, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 &, A3 const&, A4 const&, A5 const&)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 & a2 , A3 const& a3 , A4 const& a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 &, A3 const&, A4 const&, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 const&, A3 &, A4 &, A5 &)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 & a3 , A4 & a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 const&, A3 &, A4 &, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 const&, A3 &, A4 &, A5 const&)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 & a3 , A4 & a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 const&, A3 &, A4 &, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 const&, A3 &, A4 const&, A5 &)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 & a3 , A4 const& a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 const&, A3 &, A4 const&, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 const&, A3 &, A4 const&, A5 const&)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 & a3 , A4 const& a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 const&, A3 &, A4 const&, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 const&, A3 const&, A4 &, A5 &)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 & a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 const&, A3 const&, A4 &, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 const&, A3 const&, A4 &, A5 const&)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 & a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 const&, A3 const&, A4 &, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 const&, A3 const&, A4 const&, A5 &)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 & a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 const&, A3 const&, A4 const&, A5 &)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE
    typename result<functor(A0 const&, A1 const&, A2 const&, A3 const&, A4 const&, A5 const&)>::type
    operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5) const
    {
      return typename meta::
             dispatch_call< Tag(A0 const&, A1 const&, A2 const&, A3 const&, A4 const&, A5 const&)
                          , EvalContext
                          >::type()
            (a0 , a1 , a2 , a3 , a4 , a5);
    }
