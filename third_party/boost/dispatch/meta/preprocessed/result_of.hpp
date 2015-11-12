  template<class F >
  struct result_of<F(), typename boost::enable_if< is_function<F> >::type>
    : boost::function_types::result_type<typename boost::remove_pointer<typename meta::strip<F>::type>::type>
  {
  };
  template<class F >
  struct result_of<F(), typename enable_if_type< typename F::result_type >::type>
  {
    typedef typename F::result_type type;
  };
  template<class F >
  struct result_of<F(), typename enable_if_type< typename F::template result<F()>::type >::type>
  {
    typedef typename F::template result<F()>::type type;
  };
  template<class F , class A0>
  struct result_of<F(A0), typename boost::enable_if< is_function<F> >::type>
    : boost::function_types::result_type<typename boost::remove_pointer<typename meta::strip<F>::type>::type>
  {
  };
  template<class F , class A0>
  struct result_of<F(A0), typename enable_if_type< typename F::result_type >::type>
  {
    typedef typename F::result_type type;
  };
  template<class F , class A0>
  struct result_of<F(A0), typename enable_if_type< typename F::template result<F(A0)>::type >::type>
  {
    typedef typename F::template result<F(A0)>::type type;
  };
  template<class F , class A0 , class A1>
  struct result_of<F(A0 , A1), typename boost::enable_if< is_function<F> >::type>
    : boost::function_types::result_type<typename boost::remove_pointer<typename meta::strip<F>::type>::type>
  {
  };
  template<class F , class A0 , class A1>
  struct result_of<F(A0 , A1), typename enable_if_type< typename F::result_type >::type>
  {
    typedef typename F::result_type type;
  };
  template<class F , class A0 , class A1>
  struct result_of<F(A0 , A1), typename enable_if_type< typename F::template result<F(A0 , A1)>::type >::type>
  {
    typedef typename F::template result<F(A0 , A1)>::type type;
  };
  template<class F , class A0 , class A1 , class A2>
  struct result_of<F(A0 , A1 , A2), typename boost::enable_if< is_function<F> >::type>
    : boost::function_types::result_type<typename boost::remove_pointer<typename meta::strip<F>::type>::type>
  {
  };
  template<class F , class A0 , class A1 , class A2>
  struct result_of<F(A0 , A1 , A2), typename enable_if_type< typename F::result_type >::type>
  {
    typedef typename F::result_type type;
  };
  template<class F , class A0 , class A1 , class A2>
  struct result_of<F(A0 , A1 , A2), typename enable_if_type< typename F::template result<F(A0 , A1 , A2)>::type >::type>
  {
    typedef typename F::template result<F(A0 , A1 , A2)>::type type;
  };
  template<class F , class A0 , class A1 , class A2 , class A3>
  struct result_of<F(A0 , A1 , A2 , A3), typename boost::enable_if< is_function<F> >::type>
    : boost::function_types::result_type<typename boost::remove_pointer<typename meta::strip<F>::type>::type>
  {
  };
  template<class F , class A0 , class A1 , class A2 , class A3>
  struct result_of<F(A0 , A1 , A2 , A3), typename enable_if_type< typename F::result_type >::type>
  {
    typedef typename F::result_type type;
  };
  template<class F , class A0 , class A1 , class A2 , class A3>
  struct result_of<F(A0 , A1 , A2 , A3), typename enable_if_type< typename F::template result<F(A0 , A1 , A2 , A3)>::type >::type>
  {
    typedef typename F::template result<F(A0 , A1 , A2 , A3)>::type type;
  };
  template<class F , class A0 , class A1 , class A2 , class A3 , class A4>
  struct result_of<F(A0 , A1 , A2 , A3 , A4), typename boost::enable_if< is_function<F> >::type>
    : boost::function_types::result_type<typename boost::remove_pointer<typename meta::strip<F>::type>::type>
  {
  };
  template<class F , class A0 , class A1 , class A2 , class A3 , class A4>
  struct result_of<F(A0 , A1 , A2 , A3 , A4), typename enable_if_type< typename F::result_type >::type>
  {
    typedef typename F::result_type type;
  };
  template<class F , class A0 , class A1 , class A2 , class A3 , class A4>
  struct result_of<F(A0 , A1 , A2 , A3 , A4), typename enable_if_type< typename F::template result<F(A0 , A1 , A2 , A3 , A4)>::type >::type>
  {
    typedef typename F::template result<F(A0 , A1 , A2 , A3 , A4)>::type type;
  };
  template<class F , class A0 , class A1 , class A2 , class A3 , class A4 , class A5>
  struct result_of<F(A0 , A1 , A2 , A3 , A4 , A5), typename boost::enable_if< is_function<F> >::type>
    : boost::function_types::result_type<typename boost::remove_pointer<typename meta::strip<F>::type>::type>
  {
  };
  template<class F , class A0 , class A1 , class A2 , class A3 , class A4 , class A5>
  struct result_of<F(A0 , A1 , A2 , A3 , A4 , A5), typename enable_if_type< typename F::result_type >::type>
  {
    typedef typename F::result_type type;
  };
  template<class F , class A0 , class A1 , class A2 , class A3 , class A4 , class A5>
  struct result_of<F(A0 , A1 , A2 , A3 , A4 , A5), typename enable_if_type< typename F::template result<F(A0 , A1 , A2 , A3 , A4 , A5)>::type >::type>
  {
    typedef typename F::template result<F(A0 , A1 , A2 , A3 , A4 , A5)>::type type;
  };
  template<class F , class A0 , class A1 , class A2 , class A3 , class A4 , class A5 , class A6>
  struct result_of<F(A0 , A1 , A2 , A3 , A4 , A5 , A6), typename boost::enable_if< is_function<F> >::type>
    : boost::function_types::result_type<typename boost::remove_pointer<typename meta::strip<F>::type>::type>
  {
  };
  template<class F , class A0 , class A1 , class A2 , class A3 , class A4 , class A5 , class A6>
  struct result_of<F(A0 , A1 , A2 , A3 , A4 , A5 , A6), typename enable_if_type< typename F::result_type >::type>
  {
    typedef typename F::result_type type;
  };
  template<class F , class A0 , class A1 , class A2 , class A3 , class A4 , class A5 , class A6>
  struct result_of<F(A0 , A1 , A2 , A3 , A4 , A5 , A6), typename enable_if_type< typename F::template result<F(A0 , A1 , A2 , A3 , A4 , A5 , A6)>::type >::type>
  {
    typedef typename F::template result<F(A0 , A1 , A2 , A3 , A4 , A5 , A6)>::type type;
  };
