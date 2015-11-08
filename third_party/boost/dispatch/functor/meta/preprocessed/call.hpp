  template<class Tag, class A0, class Site>
  struct call<Tag(A0),Site>
        : meta::result_of<typename meta::dispatch_call<Tag(typename meta::as_ref<A0>::type), Site>::type(A0)>
  {
  };
  template<class Tag, class A0 , class A1, class Site>
  struct call<Tag(A0 , A1),Site>
        : meta::result_of<typename meta::dispatch_call<Tag(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type), Site>::type(A0 , A1)>
  {
  };
  template<class Tag, class A0 , class A1 , class A2, class Site>
  struct call<Tag(A0 , A1 , A2),Site>
        : meta::result_of<typename meta::dispatch_call<Tag(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type), Site>::type(A0 , A1 , A2)>
  {
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3, class Site>
  struct call<Tag(A0 , A1 , A2 , A3),Site>
        : meta::result_of<typename meta::dispatch_call<Tag(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type , typename meta::as_ref<A3>::type), Site>::type(A0 , A1 , A2 , A3)>
  {
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3 , class A4, class Site>
  struct call<Tag(A0 , A1 , A2 , A3 , A4),Site>
        : meta::result_of<typename meta::dispatch_call<Tag(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type , typename meta::as_ref<A3>::type , typename meta::as_ref<A4>::type), Site>::type(A0 , A1 , A2 , A3 , A4)>
  {
  };
  template<class Tag, class A0 , class A1 , class A2 , class A3 , class A4 , class A5, class Site>
  struct call<Tag(A0 , A1 , A2 , A3 , A4 , A5),Site>
        : meta::result_of<typename meta::dispatch_call<Tag(typename meta::as_ref<A0>::type , typename meta::as_ref<A1>::type , typename meta::as_ref<A2>::type , typename meta::as_ref<A3>::type , typename meta::as_ref<A4>::type , typename meta::as_ref<A5>::type), Site>::type(A0 , A1 , A2 , A3 , A4 , A5)>
  {
  };
