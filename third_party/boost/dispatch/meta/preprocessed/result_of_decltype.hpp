  template<class F >
  struct result_of_decltype<F(), typename enable_if_type< decltype( boost::declval<F>()() ) >::type>
  {
    typedef decltype( boost::declval<F>()() ) type;
  };
  template<class F , class A0>
  struct result_of_decltype<F(A0), typename enable_if_type< decltype( boost::declval<F>()(boost::declval<A0>()) ) >::type>
  {
    typedef decltype( boost::declval<F>()(boost::declval<A0>()) ) type;
  };
  template<class F , class A0 , class A1>
  struct result_of_decltype<F(A0 , A1), typename enable_if_type< decltype( boost::declval<F>()(boost::declval<A0>() , boost::declval<A1>()) ) >::type>
  {
    typedef decltype( boost::declval<F>()(boost::declval<A0>() , boost::declval<A1>()) ) type;
  };
  template<class F , class A0 , class A1 , class A2>
  struct result_of_decltype<F(A0 , A1 , A2), typename enable_if_type< decltype( boost::declval<F>()(boost::declval<A0>() , boost::declval<A1>() , boost::declval<A2>()) ) >::type>
  {
    typedef decltype( boost::declval<F>()(boost::declval<A0>() , boost::declval<A1>() , boost::declval<A2>()) ) type;
  };
  template<class F , class A0 , class A1 , class A2 , class A3>
  struct result_of_decltype<F(A0 , A1 , A2 , A3), typename enable_if_type< decltype( boost::declval<F>()(boost::declval<A0>() , boost::declval<A1>() , boost::declval<A2>() , boost::declval<A3>()) ) >::type>
  {
    typedef decltype( boost::declval<F>()(boost::declval<A0>() , boost::declval<A1>() , boost::declval<A2>() , boost::declval<A3>()) ) type;
  };
  template<class F , class A0 , class A1 , class A2 , class A3 , class A4>
  struct result_of_decltype<F(A0 , A1 , A2 , A3 , A4), typename enable_if_type< decltype( boost::declval<F>()(boost::declval<A0>() , boost::declval<A1>() , boost::declval<A2>() , boost::declval<A3>() , boost::declval<A4>()) ) >::type>
  {
    typedef decltype( boost::declval<F>()(boost::declval<A0>() , boost::declval<A1>() , boost::declval<A2>() , boost::declval<A3>() , boost::declval<A4>()) ) type;
  };
  template<class F , class A0 , class A1 , class A2 , class A3 , class A4 , class A5>
  struct result_of_decltype<F(A0 , A1 , A2 , A3 , A4 , A5), typename enable_if_type< decltype( boost::declval<F>()(boost::declval<A0>() , boost::declval<A1>() , boost::declval<A2>() , boost::declval<A3>() , boost::declval<A4>() , boost::declval<A5>()) ) >::type>
  {
    typedef decltype( boost::declval<F>()(boost::declval<A0>() , boost::declval<A1>() , boost::declval<A2>() , boost::declval<A3>() , boost::declval<A4>() , boost::declval<A5>()) ) type;
  };
  template<class F , class A0 , class A1 , class A2 , class A3 , class A4 , class A5 , class A6>
  struct result_of_decltype<F(A0 , A1 , A2 , A3 , A4 , A5 , A6), typename enable_if_type< decltype( boost::declval<F>()(boost::declval<A0>() , boost::declval<A1>() , boost::declval<A2>() , boost::declval<A3>() , boost::declval<A4>() , boost::declval<A5>() , boost::declval<A6>()) ) >::type>
  {
    typedef decltype( boost::declval<F>()(boost::declval<A0>() , boost::declval<A1>() , boost::declval<A2>() , boost::declval<A3>() , boost::declval<A4>() , boost::declval<A5>() , boost::declval<A6>()) ) type;
  };
