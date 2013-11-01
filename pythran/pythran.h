#ifndef PYTHRAN_H
#define PYTHRAN_H

#ifdef USE_GMP
#include <gmpxx.h>
typedef mpz_class pythran_long_t;
#define pythran_long(a) pythran_long_t(#a)
#else
typedef long long pythran_long_t;
#define pythran_long(a) pythran_long_t(a)
#endif



#include <pythonic++.h>
#include <type_traits>

using namespace pythonic;

/* specialization for callable types */
template <class T0, class T1>
typename std::enable_if< is_callable<T0>::value and is_callable<T1>::value, variant<T0,T1> >::type operator+(T0 , T1 );

template <class T>
typename std::enable_if< is_callable<T>::value, T>::type operator+(T , T);

/* type inference stuff {*/
template<class T0, class T1, class... Types>
struct __combined {
    typedef typename __combined< T0, typename __combined<T1, Types...>::type >::type type;
};

template<class T0, class T1>
struct __combined<T0,T1> {
    typedef decltype(std::declval<T0>()+std::declval<T1>()) type;
};

template<class T>
struct assignable{
    typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type type;
};

template<class T>
struct lazy{
    typedef typename assignable<T>::type type;  // very conservative :-)
};

template<class T>
struct assignable<none<T> >{
    typedef none<typename assignable<T>::type > type;
};

template<class... Types>
struct assignable<std::tuple<Types...>>{
    typedef std::tuple<typename assignable<Types>::type...> type;
};

template<class T, size_t N>
struct assignable<pythonic::core::array<T,N> >{
    typedef pythonic::core::array<typename assignable<T>::type, N> type;
};

template<class T>
struct assignable<pythonic::core::set<T> >{
    typedef pythonic::core::set<typename assignable<T>::type > type;
};

template<class K,class V>
struct assignable<pythonic::core::dict<K,V> >{
    typedef pythonic::core::dict<typename assignable<K>::type,typename assignable<V>::type > type;
};

template<class T>
struct assignable<pythonic::core::list<T> >{
    typedef pythonic::core::list<typename assignable<T>::type > type;
};

template<class Op, class Arg0, class Arg1>
struct assignable<pythonic::core::numpy_expr<Op, Arg0, Arg1>>
{
    typedef typename pythonic::core::numpy_expr_to_ndarray<pythonic::core::numpy_expr<Op, Arg0, Arg1>>::type type;
};
template<class Op, class Arg0>
struct assignable<pythonic::core::numpy_uexpr<Op, Arg0>>
{
    typedef typename pythonic::core::numpy_expr_to_ndarray<pythonic::core::numpy_uexpr<Op, Arg0>>::type type;
};

template<class T>
struct content_of {
    typedef typename T::value_type type;
};

template<class T>
struct content_of< std::tuple<T> > {
    typedef T type;
};
template<class T, size_t N>
struct content_of< core::array<T,N> > {
    typedef T type;
};
template<class T, class... Types>
struct content_of< std::tuple<T, Types...> > {
    typedef typename std::enable_if<
        std::is_same<
        T,
        typename content_of< std::tuple<Types...> >::type
            >::value,
        T
            >::type	type;
};

template<class K, class V>
struct content_of< core::dict<K,V> > {
    typedef V type;
};



/* for type inference too */
template<class T>
class container {
    public:
        typedef typename std::remove_cv< typename std::remove_reference<T>::type>::type value_type;
    private:
        container();
};
template<class T>
class dict_container {
    public:
        typedef typename std::remove_cv< typename std::remove_reference<T>::type>::type value_type;
    private:
        dict_container();
};

template <class A>
struct __combined<container<A>, core::empty_list> {
    typedef core::list<A> type;
};

template <class A>
struct __combined<core::empty_list , container<A> > {
    typedef core::list<A> type;
};

template <class A, class B>
struct __combined<container<A> , core::list<B> > {
    typedef core::list<typename __combined<A,B>::type> type;
};
template <class A, class B>
struct __combined<core::list<B> , container<A> > {
    typedef core::list<typename __combined<A,B>::type> type;
};

template <class A, class B>
struct __combined<container<A> , core::set<B> > {
    typedef core::set<typename __combined<A,B>::type> type;
};
template <class A, class B>
struct __combined<core::set<B> , container<A> > {
    typedef core::set<typename __combined<A,B>::type> type;
};

template <class A, class B>
struct __combined<core::list<A> , core::set<B> > {
    typedef core::set<typename __combined<A,B>::type> type;
};

template <class A, class B>
struct __combined<core::set<B> , core::list<A> > {
    typedef core::set<typename __combined<A,B>::type> type;
};


template <class A>
struct __combined<core::list<A> , core::empty_set > {
    typedef core::set<A> type;
};

template <class A>
struct __combined<core::empty_set , core::list<A> > {
    typedef core::set<A> type;
};


template <class A, class B, class C>
struct __combined<container<A> , core::dict<C,B> > {
    typedef core::dict<C, typename __combined<A,B>::type > type;
};

template <class A, class B, class C>
struct __combined<core::dict<C,B> , container<A> > {
    typedef core::dict<C, typename __combined<A,B>::type > type;
};


template <class A, class B>
struct __combined<container<A> , dict_container<B> > {
    typedef dict_container<typename __combined<A,B>::type > type;
};

template <class A, class B>
struct __combined<dict_container<B> , container<A> > {
    typedef dict_container<typename __combined<A,B>::type > type;
};


template <class A>
struct __combined<dict_container<A> , dict_container<A> > {
    typedef dict_container<A> type;
};

template <class A>
struct __combined<container<A> , core::empty_dict > {
    typedef dict_container<A> type;
};

template <class A>
struct __combined<core::empty_dict , container<A> > {
    typedef dict_container<A> type;
};


template <class T>
struct __combined<core::empty_dict, core::list<T>> {
    typedef core::dict<typename std::tuple_element<0,T>::type, typename std::tuple_element<1,T>::type> type;
};
template <class T>
struct __combined<core::list<T>, core::empty_dict> {
    typedef core::dict<typename std::tuple_element<0,T>::type, typename std::tuple_element<1,T>::type> type;
};

template <class K0, class V0, class T>
struct __combined<core::dict<K0,V0> , core::list<T> > {
    typedef core::dict<typename __combined<K0,typename std::tuple_element<0,T>::type>::type, typename __combined<V0, typename std::tuple_element<1,T>::type>::type > type;
};

template <class K0, class V0, class T>
struct __combined<core::list<T>, core::dict<K0,V0>> {
    typedef core::dict<typename __combined<K0,typename std::tuple_element<0,T>::type>::type, typename __combined<V0, typename std::tuple_element<1,T>::type>::type > type;
};



template <class A>
struct __combined<container<A> , none_type > {
    typedef typename __combined<core::list<A>, none_type>::type type;
};

template <class A>
struct __combined<none_type , container<A> > {
    typedef typename __combined<core::list<A>, none_type>::type type;
};


template <class A, class B>
struct __combined<container<A> , container<B> > {
    typedef container<typename __combined<A,B>::type> type;
};


template<class T>
class indexable {
    public:
        typedef typename std::remove_cv< typename std::remove_reference<T>::type>::type type;
    private:
        indexable();
};
template<class T>
class indexable_dict {
    public:
        typedef typename std::remove_cv< typename std::remove_reference<T>::type>::type type;
    private:
        indexable_dict();
};

template<class K>
struct __combined<indexable_dict<K>, indexable_dict<K>> {
    typedef indexable_dict<K> type;
};

template<class K0, class K1>
struct __combined<indexable<K0>, indexable<K1>> {
    typedef indexable<typename __combined<K0,K1>::type> type;
};

template<class K>
struct __combined<indexable<K>, core::empty_list> {
    typedef indexable<K> type;
};

template<class K>
struct __combined<core::empty_list, indexable<K>> {
    typedef indexable<K> type;
};

template<class K>
struct __combined<indexable<K>, core::empty_set> {
    typedef indexable<K> type;
};

template<class K>
struct __combined<core::empty_set, indexable<K>> {
    typedef indexable<K> type;
};

template<class K>
struct __combined<indexable<K>, core::empty_dict> {
    typedef indexable_dict<K> type;
};

template<class K>
struct __combined<core::empty_dict, indexable_dict<K>> {
    typedef indexable_dict<K> type;
};

template<class K>
struct __combined<indexable_dict<K>, core::empty_dict> {
    typedef indexable_dict<K> type;
};

template<class K0, class K1, class V1>
struct __combined<core::dict<K1,V1>, indexable_dict<K0>> {
    typedef core::dict<typename __combined<K0,K1>::type, V1> type;
};

template<class K0, class K1, class V1>
struct __combined<indexable_dict<K0>, core::dict<K1,V1>> {
    typedef core::dict<typename __combined<K0,K1>::type, V1> type;
};

template<class K>
struct __combined<core::empty_dict, indexable<K>> {
    typedef indexable_dict<K> type;
};

template<class K0, class V, class K1>
struct __combined<core::dict<K0,V>, indexable<K1>> {
    typedef core::dict<typename __combined<K0,K1>::type, V> type;
};

template<class K0, class V, class K1>
struct __combined<indexable<K1>, core::dict<K0,V>> {
    typedef core::dict<typename __combined<K0,K1>::type, V> type;
};

template<class K, class... Types>
struct __combined<indexable<K>, std::tuple<Types...>> {
    typedef std::tuple<Types...> type;
};

template<class K, class... Types>
struct __combined<std::tuple<Types...>, indexable<K>> {
    typedef std::tuple<Types...> type;
};

template<class K, class T, size_t N>
struct __combined<indexable<K>, core::array<T,N>> {
    typedef core::array<T,N> type;
};

template<class K, class T, size_t N>
struct __combined<core::array<T,N>, indexable<K>> {
    typedef core::array<T,N> type;
};

template<class K, class T, size_t N>
struct __combined<container<K>, core::array<T,N>> {
    typedef core::array<typename __combined<T,K>::type ,N> type;
};

template<class K, class T, size_t N>
struct __combined<core::array<T,N>, container<K>> {
    typedef core::array<typename __combined<T,K>::type ,N> type;
};

template<class T, size_t N>
struct __combined<core::array<T,N>, core::array<T,N>> {
    typedef core::array<T ,N> type;
};

template<class K>
struct __combined<indexable<K>, std::complex<double>> {
    typedef std::complex<double> type;
};

template<class K>
struct __combined<std::complex<double>, indexable<K>> {
    typedef std::complex<double> type;
};


template<class K, class V>
class indexable_container {
    public:
        typedef typename std::remove_cv< typename std::remove_reference<K>::type>::type key_type;
        typedef typename std::remove_cv< typename std::remove_reference<V>::type>::type value_type;
    private:
        indexable_container();
};
template<class K0, class V0, class K1, class V1>
struct __combined<indexable_container<K0,V0>, indexable_container<K1,V1>> {
    typedef indexable_container<typename __combined<K0,K1>::type, typename __combined<V0,V1>::type> type;
};


template <class K, class V>
struct __combined<indexable<K>, container<V>> {
    typedef indexable_container<K,V> type;
};

template <class V, class K>
struct __combined<container<V>, indexable<K>> {
    typedef indexable_container<K,V> type;
};


template <class K, class V, class W>
struct __combined<indexable_container<K,V>, container<W>> {
    typedef indexable_container<K, typename __combined<V,W>::type> type;
};

template <class V, class K, class W>
struct __combined<container<W>, indexable_container<K,V>> {
    typedef indexable_container<K, typename __combined<V,W>::type> type;
};


template <class K, class V>
struct __combined<indexable<K>, core::list<V>> {
    typedef core::list<V> type;
};

template <class V, class K>
struct __combined<core::list<V>, indexable<K>> {
    typedef core::list<V> type;
};


template <class K, class V>
struct __combined<indexable<K>, core::set<V>> {
    typedef core::set<V> type;
};

template <class K, class V>
struct __combined<core::set<V>, indexable<K>> {
    typedef core::set<V> type;
};


template <class K1, class V1, class K2>
struct __combined<indexable_container<K1,V1>, indexable<K2>> {
    typedef indexable_container<typename __combined<K1,K2>::type,V1> type;
};

template <class K1, class V1, class K2>
struct __combined<indexable<K2>, indexable_container<K1,V1>> {
    typedef indexable_container<typename __combined<K1,K2>::type,V1> type;
};


template <class K, class V0, class V1>
struct __combined<indexable_container<K,V0>, core::list<V1>> {
    typedef core::list<typename __combined<V0,V1>::type> type;
};

template <class K, class V0, class V1>
struct __combined<core::list<V1>, indexable_container<K,V0>> {
    typedef core::list<typename __combined<V0,V1>::type> type;
};


template <class K, class V, class T, size_t N>
struct __combined<indexable_container<K,V>,core::array<T,N>> {
    typedef core::array<typename __combined<V,T>::type, N> type;
};

template <class K, class V, class T, size_t N>
struct __combined<core::array<T,N>, indexable_container<K,V>> {
    typedef core::array<typename __combined<T,V>::type, N> type;
};

template <class K, class V>
struct __combined<indexable_container<K,V>, core::empty_list> {
    typedef core::list<V> type;
};

template <class K, class V>
struct __combined<core::empty_list, indexable_container<K,V>> {
    typedef core::list<V> type;
};


struct dummy {};

template<size_t N, class T, size_t M>
struct __combined<core::ndarray<T,N>, core::ndarray<T,M>> {
    typedef core::ndarray<T,N> type;
};
template<size_t N, class T, class O>
struct __combined<core::ndarray<T,N>, O> {
    typedef core::ndarray<T,N> type;
};
template<size_t N, class T, class O>
struct __combined<O, core::ndarray<T,N>> {
    typedef core::ndarray<T,N> type;
};

template<class T, size_t N>
struct __combined<core::indexed_ndarray<T,N>, core::indexed_ndarray<T,N>> {
    typedef core::indexed_ndarray<T,N> type;
};
template<class T, class O, size_t N>
struct __combined<core::indexed_ndarray<T,N>, O> {
    typedef core::indexed_ndarray<T,N> type;
};
template<class T, class O, size_t N>
struct __combined<O, core::indexed_ndarray<T,N>> {
    typedef core::indexed_ndarray<T,N> type;
};

template<class Arg0, class Op, class K>
struct __combined<core::numpy_uexpr<Op, Arg0>, indexable<K>> {
    typedef core::numpy_uexpr<Op, Arg0> type;
};

template<class Arg0, class Arg1, class Op, class K>
struct __combined<core::numpy_expr<Op, Arg0, Arg1>, indexable<K>> {
    typedef core::numpy_expr<Op, Arg0, Arg1> type;
};

template<class Arg0, class Op, class K>
struct __combined<indexable<K>, core::numpy_uexpr<Op, Arg0>> {
    typedef core::numpy_uexpr<Op, Arg0> type;
};

template<class Arg0, class Arg1, class Op, class K>
struct __combined<indexable<K>, core::numpy_expr<Op, Arg0, Arg1>> {
    typedef core::numpy_expr<Op, Arg0, Arg1> type;
};

template<class Arg0, class Op, class K, class V>
struct __combined<core::numpy_uexpr<Op, Arg0>, indexable_container<K,V>> {
    typedef core::numpy_uexpr<Op, Arg0> type;
};

template<class Arg0, class Arg1, class Op, class K, class V>
struct __combined<core::numpy_expr<Op, Arg0, Arg1>, indexable_container<K,V>> {
    typedef core::numpy_expr<Op, Arg0, Arg1> type;
};

template<class Arg0, class Op, class K, class V>
struct __combined<indexable_container<K,V>, core::numpy_uexpr<Op, Arg0>> {
    typedef core::numpy_uexpr<Op, Arg0> type;
};

template<class Arg0, class Arg1, class Op, class K, class V>
struct __combined<indexable_container<K,V>, core::numpy_expr<Op, Arg0, Arg1>> {
    typedef core::numpy_expr<Op, Arg0, Arg1> type;
};


template<class Arg0, class Op, class K>
struct __combined<container<K>, core::numpy_uexpr<Op, Arg0>> {
    typedef core::numpy_uexpr<Op, Arg0> type;
};

template<class Arg0, class Arg1, class Op, class K>
struct __combined<container<K>, core::numpy_expr<Op, Arg0, Arg1>> {
    typedef core::numpy_expr<Op, Arg0, Arg1> type;
};

template<class Arg0, class Op, class K>
struct __combined<core::numpy_uexpr<Op, Arg0>, container<K>> {
    typedef core::numpy_uexpr<Op, Arg0> type;
};

template<class Arg0, class Arg1, class Op, class K>
struct __combined<core::numpy_expr<Op, Arg0, Arg1>, container<K>> {
    typedef core::numpy_expr<Op, Arg0, Arg1> type;
};

template <class K, class V1, class V2>
struct __combined<indexable_container<K,V1>, core::set<V2>> {
    typedef core::set<decltype(std::declval<V1>()+std::declval<V2>())> type;
};

template <class K, class V1, class V2>
struct __combined<core::set<V2>, indexable_container<K,V1>> {
    typedef core::set<decltype(std::declval<V1>()+std::declval<V2>())> type;
};


template< class K, class V>
struct __combined<core::empty_dict, indexable_container<K,V>> {
    typedef core::dict<K,V> type;
};

template< class K0, class V0, class K1, class V1>
struct __combined<core::dict<K0,V0>, indexable_container<K1,V1>> {
    typedef core::dict<typename __combined<K0,K1>::type, typename __combined<V0,V1>::type> type;
};

template< class K0, class V0, class K1, class V1>
struct __combined<indexable_container<K1,V1>, core::dict<K0,V0>> {
    typedef core::dict<typename __combined<K0,K1>::type, typename __combined<V0,V1>::type> type;
};

template< class K, class V>
struct __combined<indexable_container<K,V>, core::empty_dict> {
    typedef core::dict<K,V> type;
};


template <class K, class V>
struct __combined<indexable<K>, dict_container<V>> {
    typedef core::dict<K,V> type;
};

template <class V, class K>
struct __combined<dict_container<V>, indexable<K>> {
    typedef core::dict<K,V> type;
};

template <class V, class K, class W>
struct __combined<dict_container<V>, indexable_container<K,W>> {
    typedef core::dict<K,typename __combined<V,W>::type> type;
};

template <class V, class K, class W>
struct __combined<indexable_container<K,W>, dict_container<V>> {
    typedef core::dict<K,typename __combined<V,W>::type> type;
};

template <class K, class V, class W>
struct __combined<core::dict<K,V>, dict_container<W>> {
    typedef core::dict<K,typename __combined<V,W>::type> type;
};

template <class V, class K, class W>
struct __combined<dict_container<W>, core::dict<K,V>> {
    typedef core::dict<K,typename __combined<V,W>::type> type;
};


template <class K, class V>
struct __combined<indexable_dict<K>, container<V>> {
    typedef core::dict<K,V> type;
};

template <class K0, class K1>
struct __combined<indexable_dict<K0>, indexable<K1>> {
    typedef indexable_dict<typename __combined<K0,K1>::type> type;
};

template <class K0, class K1>
struct __combined<indexable<K0>, indexable_dict<K1>> {
    typedef indexable_dict<typename __combined<K0,K1>::type> type;
};

template <class V, class K>
struct __combined<container<V>, indexable_dict<K>> {
    typedef core::dict<K,V> type;
};


template<class T0, class T1>
struct __combined<core::list<T0>, core::list<T1>> {
    typedef core::list<typename __combined<T0,T1>::type> type;
};
template<class T0, class T1>
struct __combined<core::set<T0>, core::set<T1>> {
    typedef core::set<typename __combined<T0,T1>::type> type;
};
template<class T0, class T1>
struct __combined<__builtin__::_iter<T0>, __builtin__::_iter<T1>> {
    typedef __builtin__::_iter<typename __combined<T0,T1>::type> type;
};
template<class T0, class T1>
struct __combined<__builtin__::_iter<T0>&, __builtin__::_iter<T1>&> {
    typedef __builtin__::_iter<typename __combined<T0,T1>::type> type;
};
template<class T0, class T1>
struct __combined<__builtin__::_iter<T0>&, __builtin__::_iter<T1>> {
    typedef __builtin__::_iter<typename __combined<T0,T1>::type> type;
};
template<class T0, class T1>
struct __combined<__builtin__::_iter<T0>, __builtin__::_iter<T1>&> {
    typedef __builtin__::_iter<typename __combined<T0,T1>::type> type;
};
template<class T0, class T1, size_t N0, size_t N1>
struct __combined<core::array<T0,N0>, core::array<T1,N1>> {
    typedef core::array<typename __combined<T0,T1>::type, N0> type;
};
template<class... T0, class... T1>
struct __combined<std::tuple<T0...>, std::tuple<T1...>> {
    typedef std::tuple<typename __combined<T0,T1>::type ...> type;  // no further combination
};
template<class T, size_t N, class... Types>
struct __combined<core::array<T,N>, std::tuple<Types...>> {
    typedef std::tuple<Types...> type;
};
template<class T, size_t N, class... Types>
struct __combined<std::tuple<Types...>, core::array<T,N>> {
    typedef std::tuple<Types...> type;
};
template<class T00, class T01, class T10, class T11>
struct __combined<std::pair<T00, T01>, std::pair<T10, T11>> {
    typedef std::pair<typename __combined<T00,T10>::type, typename __combined<T01,T11>::type> type;  // no further combination
};
template<class K0, class V0, class K1, class V1>
struct __combined<core::dict<K0, V0>, core::dict<K1, V1>> {
    typedef core::dict<typename __combined<K0,K1>::type, typename __combined<V0,V1>::type> type;
};

template<>
struct __combined<void, void> {
    typedef void type;
};


template<class T0, class T1>
struct __combined<none<T0>, T1> : std::enable_if<!is_none<T1>::value, dummy>::type {
    typedef none<typename __combined<T0,T1>::type> type;
};
template<class T0, class T1>
struct __combined<T1, none<T0>> : std::enable_if<!is_none<T0>::value, dummy>::type {
    typedef none<typename __combined<T0,T1>::type> type;
};
template<class T0, class T1>
struct __combined<none<T1>, none<T0>>  {
    typedef none<typename __combined<T0,T1>::type> type;
};

template<class T>
struct __combined<typename std::enable_if<!is_none<T>::value, none_type>::type, T> {
    typedef none<T> type;
};

template<class T>
struct __combined<T, typename std::enable_if<!is_none<T>::value, none_type>::type> {
    typedef none<T> type;
};

template<>
struct __combined<none_type, none_type>  {
    typedef none_type type;
};



/* some overloads */
namespace std {

    /* for remove_cv */
    template <class K, class V>
        struct remove_cv< std::pair<const K, V> > {
            typedef std::pair<K, V> type;
        };

    /* for core::ndarray */
    template <size_t i, class t, size_t n>
        auto get( core::ndarray<t,n>& a) -> decltype(a[i]) { return a[i]; }
    template <size_t i, class t, size_t n>
        auto get( core::ndarray<t,n> const& a) -> decltype(a[i]) { return a[i]; }

    template <size_t i, class t>
        auto get( core::sliced_ndarray<t>& a) -> decltype(a[i]) { return a[i]; }
    template <size_t i, class t>
        auto get( core::sliced_ndarray<t> const& a) -> decltype(a[i]) { return a[i]; }

    template <size_t i, class t, size_t n>
        auto get( core::indexed_ndarray<t,n>& a) -> decltype(a[i]) { return a[i]; }
    template <size_t i, class t, size_t n>
        auto get( core::indexed_ndarray<t,n> const& a) -> decltype(a[i]) { return a[i]; }

    template <size_t I, class O, class A0, class A1>
        auto get( core::numpy_expr<O,A0,A1> const& a) -> decltype(a[I]) { return a[I]; }
    template <size_t I, class O, class A>
        auto get( core::numpy_uexpr<O,A> const& a) -> decltype(a[I]) { return a[I]; }

    template <size_t I, class T, size_t N>
        struct tuple_element<I, core::ndarray<T,N> > {
            typedef typename core::ndarray<T,N>::value_type type;
        };
    template <size_t I, class T, size_t N>
        struct tuple_element<I, core::indexed_ndarray<T,N> > {
            typedef typename core::ndarray<T,N>::value_type type;
        };
    template <size_t I, class T>
        struct tuple_element<I, core::sliced_ndarray<T> > {
            typedef typename T::value_type type;
        };
    template <size_t I, class Op, class Arg0, class Arg1>
        struct tuple_element<I, core::numpy_expr<Op,Arg0, Arg1> > {
            typedef typename core::numpy_expr_to_ndarray<core::numpy_expr<Op,Arg0, Arg1>>::type::value_type type;
        };

    /* for containers */
    template <size_t I, class T>
        struct tuple_element<I, container<T> > {
            typedef typename container<T>::value_type type;
        };
}

/* attributes */
template <int I, class T>
struct attribute_element
{
    typedef T& type;
};

/* For files */

template <>
    struct attribute_element<0, core::file> {typedef bool type;};
template <>
    struct attribute_element<1, core::file> {typedef core::string const& type;};
template <>
    struct attribute_element<2, core::file> {typedef core::string const& type;};
template <>
    struct attribute_element<3, core::file> {typedef none_type type;};

template<int I>
    typename attribute_element<I, core::file>::type getattr(core::file const& f);
template<>
    bool getattr<0>(core::file const& f) {return f.closed();}
template<>
    core::string const& getattr<1>(core::file const& f) {return f.getmode();}
template<>
    core::string const& getattr<2>(core::file const& f) {return f.getname();}
template<>
    // Python seems to always return none... Doing the same.
    none_type getattr<3>(core::file const& f) {return __builtin__::None;}

/* for finfo */
template <class T>
    struct attribute_element<0, core::finfo<T>> {
        typedef T type;
    };

template<size_t I, class T>
    struct finfo_attr {
    };

template<class T>
    struct finfo_attr<0,T> {
        typename attribute_element<0, core::finfo<T>>::type operator()(core::finfo<T> const& f) const {
            return f.eps();
        }
    };

template <size_t I, class T>
    typename attribute_element<I, core::finfo<T>>::type getattr(core::finfo<T> const& f)
    {
        return finfo_attr<I,T>()(f);
    }

/* for ndarrays */
template <class T, size_t N>
    struct attribute_element<0, pythonic::core::ndarray<T,N> > {
        typedef core::array<long,N> type;
    };
template <class Op, class Arg>
    struct attribute_element<0, pythonic::core::numpy_uexpr<Op, Arg> > {
        typedef core::array<long, pythonic::core::numpy_uexpr<Op, Arg>::value> type;
    };
template <class T>
    struct attribute_element<0, pythonic::core::sliced_ndarray<T> > {
        typedef core::array<long, T::value> type;
    };

template <class T, size_t N>
    struct attribute_element<1, pythonic::core::ndarray<T,N> > {
        typedef long type;
    };

template <class T, size_t N>
    struct attribute_element<2, pythonic::core::ndarray<T,N> > {
        typedef core::array<long,N> type;
    };

template <class T, size_t N>
    struct attribute_element<3, pythonic::core::ndarray<T,N> > {
        typedef long type;
    };

template <class T, size_t N>
    struct attribute_element<4, pythonic::core::ndarray<T,N> > {
        typedef long type;
    };

template <class T, size_t N>
    struct attribute_element<5, pythonic::core::ndarray<T,N> > {
        typedef long type;
    };

template <class T, size_t N>
    struct attribute_element<6, pythonic::core::ndarray<T,N> > {
        typedef pythonic::core::ndarray<T,1> type;
    };

template <class T, size_t N>
    struct attribute_element<7, pythonic::core::ndarray<T,N> > {
        typedef T type;
    };

template <class T, size_t N>
    struct attribute_element<8, pythonic::core::ndarray<T,N> > {
        typedef pythonic::core::ndarray<T,N> type;
    };

template <unsigned int I, class T, size_t N>
    struct ndarray_attr;

template <class T, size_t N>
    struct ndarray_attr<0,T,N>
    {
        typename attribute_element<0,pythonic::core::ndarray<T,N>>::type const operator()(core::ndarray<T,N> const& a)
        {
            return a.shape;
        }
    };

template <class T, size_t N>
    struct ndarray_attr<1,T,N>
    {
        typename attribute_element<1,pythonic::core::ndarray<T,N>>::type const operator()(core::ndarray<T,N> const& a)
        {
            return N;
        }
    };

template <class T, size_t N>
    struct ndarray_attr<2,T,N>
    {
        typename attribute_element<2,pythonic::core::ndarray<T,N>>::type const operator()(core::ndarray<T,N> const& a)
        {
            core::array<long,N> strides;
            strides[N-1] = sizeof(T);
            auto shape = a.shape;
            std::transform(strides.rbegin(), strides.rend() -1, shape.rbegin(), strides.rbegin()+1, std::multiplies<long>());
            return strides;
        }
    };

template <class T, size_t N>
    struct ndarray_attr<3,T,N>
    {
        typename attribute_element<3,pythonic::core::ndarray<T,N>>::type const operator()(core::ndarray<T,N> const& a)
        {
            return a.size();
        }
    };

template <class T, size_t N>
    struct ndarray_attr<4,T,N>
    {
        typename attribute_element<4,pythonic::core::ndarray<T,N>>::type const operator()(core::ndarray<T,N> const& a)
        {
            return sizeof(T);
        }
    };

template <class T, size_t N>
    struct ndarray_attr<5,T,N>
    {
        typename attribute_element<5,pythonic::core::ndarray<T,N>>::type const operator()(core::ndarray<T,N> const& a)
        {
            return a.size() * sizeof(T);
        }
    };

template <class T, size_t N>
    struct ndarray_attr<6,T,N>
    {
        typename attribute_element<6,pythonic::core::ndarray<T,N>>::type const operator()(core::ndarray<T,N> const& a)
        {
            return a.flat();
        }
    };

template <class T, size_t N>
    struct ndarray_attr<7,T,N>
    {
        typename attribute_element<7,pythonic::core::ndarray<T,N>>::type const operator()(core::ndarray<T,N> const& a)
        {
            return T();
        }
    };

template <class T, size_t N>
    struct ndarray_attr<8,T,N>
    {
        typename attribute_element<8,pythonic::core::ndarray<T,N>>::type const operator()(core::ndarray<T,N> const& a)
        {
            return pythonic::numpy::transpose(a);
        }
    };

template <unsigned int I, class T, size_t N>
    typename attribute_element<I,pythonic::core::ndarray<T,N>>::type const getattr(core::ndarray<T,N> const& a)
    {
        return ndarray_attr<I,T,N>()(a);
    }
template <unsigned int I, class Op, class Arg>
    typename attribute_element<I,pythonic::core::ndarray<typename core::numpy_uexpr<Op,Arg>::value_type,  core::numpy_uexpr<Op,Arg>::value>>::type const getattr(core::numpy_uexpr<Op,Arg> const& a)
    {
        return ndarray_attr<I,typename core::numpy_uexpr<Op,Arg>::value_type,  core::numpy_uexpr<Op,Arg>::value>()(a);
    }

template <unsigned int I, class T>
    typename attribute_element<I,pythonic::core::sliced_ndarray<T>>::type const getattr(core::sliced_ndarray<T> const& a)
    {
        return ndarray_attr<I,typename T::value_type, T::value>()(a);
    }

/* for complex numbers */
template <int I, class T>
    struct attribute_element<I, std::complex<T> > {
        typedef T type;
    };

#define GET_COMPLEX(T)\
    template <int I>\
    T& getattr( std::complex<T>& );\
    template <>\
    T& getattr<0>( std::complex<T>& t) { return reinterpret_cast<T*>(&t)[0]; }\
    template <>\
    T& getattr<1>( std::complex<T>& t) { return reinterpret_cast<T*>(&t)[1]; }\
    \
    template <int I>\
    T const & getattr( std::complex<T> const & );\
    template <>\
    T const & getattr<0>( std::complex<T> const & t) { return reinterpret_cast<T const *>(&t)[0]; }\
    template <>\
    T const & getattr<1>( std::complex<T> const & t) { return reinterpret_cast<T const *>(&t)[1]; }\

GET_COMPLEX(double)

/* for exception */

#define ACCESS_EXCEPTION(name) \
        template <int I> \
        struct attribute_element<I, core::name> { \
            typedef none<typename core::BaseError::Type<I>::type> type; \
        }; \
        \
        template <int I> \
        none<typename core::BaseError::Type<I>::type> getattr( const core::name& t ); \
        template <> \
        none<typename core::BaseError::Type<0>::type> getattr<0>( const core::name& t) { return t.args; } \

ACCESS_EXCEPTION(BaseException);
ACCESS_EXCEPTION(SystemExit);
ACCESS_EXCEPTION(KeyboardInterrupt);
ACCESS_EXCEPTION(GeneratorExit);
ACCESS_EXCEPTION(Exception);
ACCESS_EXCEPTION(StopIteration);
ACCESS_EXCEPTION(StandardError);
ACCESS_EXCEPTION(Warning);
ACCESS_EXCEPTION(BytesWarning);
ACCESS_EXCEPTION(UnicodeWarning);
ACCESS_EXCEPTION(ImportWarning);
ACCESS_EXCEPTION(FutureWarning);
ACCESS_EXCEPTION(UserWarning);
ACCESS_EXCEPTION(SyntaxWarning);
ACCESS_EXCEPTION(RuntimeWarning);
ACCESS_EXCEPTION(PendingDeprecationWarning);
ACCESS_EXCEPTION(DeprecationWarning);
ACCESS_EXCEPTION(BufferError);
ACCESS_EXCEPTION(ArithmeticError);
ACCESS_EXCEPTION(AssertionError);
ACCESS_EXCEPTION(AttributeError);
ACCESS_EXCEPTION(EOFError);
ACCESS_EXCEPTION(ImportError);
ACCESS_EXCEPTION(LookupError);
ACCESS_EXCEPTION(MemoryError);
ACCESS_EXCEPTION(NameError);
ACCESS_EXCEPTION(ReferenceError);
ACCESS_EXCEPTION(RuntimeError);
ACCESS_EXCEPTION(SyntaxError);
ACCESS_EXCEPTION(SystemError);
ACCESS_EXCEPTION(TypeError);
ACCESS_EXCEPTION(ValueError);
ACCESS_EXCEPTION(FloatingPointError);
ACCESS_EXCEPTION(OverflowError);
ACCESS_EXCEPTION(ZeroDivisionError);
ACCESS_EXCEPTION(IndexError);
ACCESS_EXCEPTION(KeyError);
ACCESS_EXCEPTION(UnboundLocalError);
ACCESS_EXCEPTION(NotImplementedError);
ACCESS_EXCEPTION(IndentationError);
ACCESS_EXCEPTION(TabError);
ACCESS_EXCEPTION(UnicodeError);

#define ENVIRONMENTERROR_EXCEPTION(name)\
    template <int I> \
        struct attribute_element<I, core::name> { \
            typedef none<typename core::BaseError::Type<I>::type> type; \
        }; \
    \
    template <int I> \
        none<typename core::BaseError::Type<I>::type> getattr( const core::name& t ); \
    template <> \
        none<typename core::BaseError::Type<0>::type> getattr<0>( const core::name& t ){\
            if (t.args.size()>3 || t.args.size()<2)\
                return t.args;\
            else\
                return core::list<core::string>(t.args.begin(), t.args.begin()+2);\
    }\
    template <>\
        none<typename core::BaseError::Type<1>::type> getattr<1>( const core::name& t ){ if(t.args.size()>3 || t.args.size()<2) return __builtin__::None; else return t.args[0];}\
    template <>\
        none<typename core::BaseError::Type<2>::type> getattr<2>( const core::name& t ){ if(t.args.size()>3 || t.args.size()<2) return __builtin__::None; else return t.args[1];}\
    template <>\
        none<typename core::BaseError::Type<3>::type> getattr<3>( const core::name& t ){ if(t.args.size()==3) return t.args[2]; else return __builtin__::None; }\

ENVIRONMENTERROR_EXCEPTION(EnvironmentError)
ENVIRONMENTERROR_EXCEPTION(IOError)
ENVIRONMENTERROR_EXCEPTION(OSError)

/* } */

#ifdef ENABLE_PYTHON_MODULE
/* python <-> c++ conversion stuff { */

#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/exception_translator.hpp>

/* boost::python converters */
#include <boost/python/numeric.hpp>
// as writen here : http://docs.scipy.org/doc/numpy-dev/reference/c-api.deprecations.html
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "arrayobject.h"

template<int ...> struct seq {};

template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};

template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };


template <typename T>
struct python_to_pythran {};

template<>
struct python_to_pythran< core::string >{
    python_to_pythran(){
        static bool registered =false;
        if(not registered) {
            registered=true;
            boost::python::converter::registry::insert(&convertible,&construct,boost::python::type_id<core::string>());
        }
    }
    static void* convertible(PyObject* obj_ptr){
        if( !PyString_Check(obj_ptr) ) return 0;
        return obj_ptr;
    }
    static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
        void* storage=((boost::python::converter::rvalue_from_python_storage<core::string >*)(data))->storage.bytes;
        char* s=PyString_AS_STRING(obj_ptr);
        new (storage) core::string(s, PyString_GET_SIZE(obj_ptr));
        data->convertible=storage;
    }
};

template<typename T>
struct python_to_pythran< core::list<T> >{
    python_to_pythran(){
        python_to_pythran<T>();
        static bool registered =false;
        if(not registered) {
            registered=true;
            boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id<core::list<T> >());
        }
    }
    static void* convertible(PyObject* obj_ptr){
        // the second condition is important, for some reason otherwise there were attempted conversions of Body to list which failed afterwards.
        if( !PySequence_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr,"__len__")) return 0;
        return obj_ptr;
    }
    static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
        void* storage=((boost::python::converter::rvalue_from_python_storage<core::list<T> >*)(data))->storage.bytes;
        boost::python::extract<boost::python::numeric::array> extractor(obj_ptr);
        core::list<T>& v=*(core::list<T>*)(storage);
        if(extractor.check()) {
            Py_ssize_t l=PySequence_Size(obj_ptr);
            new (storage) core::list<T>(l);
            boost::python::numeric::array data = extractor;
            for(Py_ssize_t i=0; i<l; i++)
                v[i]=boost::python::extract<T>(data[i]);
        }
        else {
            Py_ssize_t l=PySequence_Fast_GET_SIZE(obj_ptr);
            new (storage) core::list<T>(l);
            PyObject** core = PySequence_Fast_ITEMS(obj_ptr);
            for(Py_ssize_t i=0; i<l; i++)
                v[i]=boost::python::extract<T>(*core++);
        }
        data->convertible=storage;
    }
};

template<typename T>
struct python_to_pythran< core::set<T> >{
    python_to_pythran(){
        python_to_pythran<T>();
        static bool registered =false;
        if(not registered) {
            registered=true;
            boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id<core::set<T> >());
        }
    }
    static void* convertible(PyObject* obj_ptr){
        // the second condition is important, for some reason otherwise there were attempted conversions of Body to list which failed afterwards.
        if(!PySet_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr,"__len__")) return 0;
        return obj_ptr;
    }
    static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
        void* storage=((boost::python::converter::rvalue_from_python_storage<core::set<T> >*)(data))->storage.bytes;
        new (storage) core::set<T>(core::empty_set());
        core::set<T>& v=*(core::set<T>*)(storage);
        // may be useful to reserve more space ?
        PyObject *iterator = PyObject_GetIter(obj_ptr);
        PyObject *item;
        while((item = PyIter_Next(iterator))) {
            v.add(boost::python::extract<T>(item));
            Py_DECREF(item);
        }
        Py_DECREF(iterator);
        data->convertible=storage;
    }
};

template<typename K, typename V>
struct python_to_pythran< core::dict<K,V> >{
    python_to_pythran(){
        python_to_pythran<K>();
        python_to_pythran<V>();
        static bool registered =false;
        if(not registered) {
            registered=true;
            boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id<core::dict<K,V> >());
        }
    }
    static void* convertible(PyObject* obj_ptr){
        // the second condition is important, for some reason otherwise there were attempted conversions of Body to list which failed afterwards.
        if(!PyDict_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr,"__len__")) return 0;
        return obj_ptr;
    }
    static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
        void* storage=((boost::python::converter::rvalue_from_python_storage<core::dict<K,V> >*)(data))->storage.bytes;
        new (storage) core::dict<K,V>(core::empty_dict());
        core::dict<K,V>& v=*(core::dict<K,V>*)(storage);

        PyObject *key, *value;
        Py_ssize_t pos = 0;
        while(PyDict_Next(obj_ptr, &pos, &key, &value)) {
            v[boost::python::extract<K>(key)]=boost::python::extract<V>(value);
        }
        data->convertible=storage;
    }
};

template<typename... Types>
struct python_to_pythran< std::tuple<Types...> >{
    python_to_pythran(){
        static bool registered=false;
        pythonic::fwd(python_to_pythran<Types>()...);
        if(not registered) {
            registered=true;
            boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id< std::tuple<Types...> >());
        }
    }
    static void* convertible(PyObject* obj_ptr){
        if(!PyTuple_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr,"__len__")) return 0;
        return obj_ptr;
    }

    template<int ...S>
        static void do_construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data, seq<S...>){
            void* storage=((boost::python::converter::rvalue_from_python_storage<std::tuple<Types...>>*)(data))->storage.bytes;
            new (storage) std::tuple<Types...>( boost::python::extract< typename std::tuple_element<S, std::tuple<Types...> >::type >(PyTuple_GetItem(obj_ptr,S))...);
            data->convertible=storage;
        }

    static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
        do_construct(obj_ptr, data, typename gens< std::tuple_size<std::tuple<Types...>>::value >::type());
    }
};

template<typename T, size_t N>
struct python_to_pythran< core::array<T, N> >{
    python_to_pythran(){
        static bool registered=false;
        python_to_pythran<T>();
        if(not registered) {
            registered=true;
            boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id< core::array<T,N> >());
        }
    }
    static void* convertible(PyObject* obj_ptr){
        if(!PyTuple_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr,"__len__")) return 0;
        return obj_ptr;
    }

    template<int ...S>
        static void do_construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data, seq<S...>){
            void* storage=((boost::python::converter::rvalue_from_python_storage<core::array<T,N>>*)(data))->storage.bytes;
            new (storage) core::array<T,N>{{boost::python::extract<T>(PyTuple_GetItem(obj_ptr,S))...}};
            data->convertible=storage;
        }

    static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
        do_construct(obj_ptr, data, typename gens<N>::type());
    }
};
template<class T>
struct c_type_to_numpy_type {};

template<>
struct c_type_to_numpy_type<double> {
    static const int value = NPY_DOUBLE;
};

template<>
struct c_type_to_numpy_type<float> {
    static const int value = NPY_FLOAT;
};

template<>
struct c_type_to_numpy_type<std::complex<double>> {
    static const int value = NPY_CDOUBLE;
};

template<>
struct c_type_to_numpy_type<long int> {
    static const int value = NPY_LONG;
};

template<>
struct c_type_to_numpy_type<long long int> {
    static const int value = NPY_LONGLONG;
};

template<>
struct c_type_to_numpy_type<int> {
    static const int value = NPY_INT;
};

template<>
struct c_type_to_numpy_type<unsigned int> {
    static const int value = NPY_UINT;
};

template<>
struct c_type_to_numpy_type<signed char> {
    static const int value = NPY_INT8;
};

template<>
struct c_type_to_numpy_type<unsigned char> {
    static const int value = NPY_UINT8;
};

template<>
struct c_type_to_numpy_type<bool> {
    static const int value = NPY_BOOL;
};


template<class T>
struct c_type_to_numpy_type< boost::simd::logical<T>> {
    static const int value = NPY_BOOL;
};

template<typename T, size_t N>
struct python_to_pythran< core::ndarray<T, N> >{
    python_to_pythran(){
        static bool registered=false;
        python_to_pythran<T>();
        if(not registered) {
            registered=true;
            boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id< core::ndarray<T, N> >());
        }
    }
    //reinterpret_cast needed to fit BOOST Python API. Check is done by template and PyArray_Check
    static void* convertible(PyObject* obj_ptr){
        if(!PyArray_Check(obj_ptr) or PyArray_TYPE(reinterpret_cast<PyArrayObject*>(obj_ptr)) != c_type_to_numpy_type<T>::value )
            return 0;
        return obj_ptr;
    }

    static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
        void* storage=((boost::python::converter::rvalue_from_python_storage<core::ndarray<T,N>>*)(data))->storage.bytes;
        new (storage) core::ndarray< T, N>((T*)PyArray_BYTES(reinterpret_cast<PyArrayObject*>(obj_ptr)), PyArray_DIMS(reinterpret_cast<PyArrayObject*>(obj_ptr)));
        Py_INCREF(obj_ptr);
        data->convertible=storage;
    }
};

template<typename T>
struct pythran_to_python {
};

template<class Type, class Converter>
static void register_once() {
    boost::python::type_info info = boost::python::type_id<Type >();
    const boost::python::converter::registration* reg = boost::python::converter::registry::query(info);
    if(not reg or not (*reg).m_to_python) {
        boost::python::to_python_converter< Type, Converter >();
    }
}

struct custom_none_type_to_none {
    static PyObject* convert( none_type const&) {
        return boost::python::incref(boost::python::object().ptr());
    }
};

template<>
struct pythran_to_python<none_type> {
    pythran_to_python() {
        register_once< none_type, custom_none_type_to_none >();
    }
};

struct custom_core_string_to_str{
    static PyObject* convert(const core::string& v){
        return PyString_FromStringAndSize(v.c_str(), v.size());
    }
};

template<>
struct pythran_to_python< core::string > {
    pythran_to_python() {
        register_once< core::string, custom_core_string_to_str >();
    }
};

struct custom_core_string_view_to_str{
    static PyObject* convert(const pythonic::core::string_view& v){
        return custom_core_string_to_str().convert(v);
    }
};

template<>
struct pythran_to_python< pythonic::core::string_view > {
    pythran_to_python() {
        register_once< pythonic::core::string_view, custom_core_string_view_to_str >();
    }
};

template<typename T>
struct custom_core_list_to_list{
    static PyObject* convert(const core::list<T>& v){
        Py_ssize_t n = __builtin__::len(v);
        PyObject* ret = PyList_New(n);
        for(Py_ssize_t i=0;i<n;i++)
            PyList_SET_ITEM(ret, i, boost::python::incref(boost::python::object(v[i]).ptr()));
        return ret;
    }
};

template<typename T>
struct pythran_to_python< core::list<T> > {
    pythran_to_python() {
        pythran_to_python<T>();
        register_once< core::list<T>, custom_core_list_to_list<T> >();
    }
};

template<typename T>
struct custom_core_set_to_set{
    static PyObject* convert(const core::set<T>& v){
        PyObject* obj = PySet_New(nullptr);
        for(const T& e:v)
            PySet_Add(obj, boost::python::incref(boost::python::object(e).ptr()));
        return obj;
    }
};

template<typename T>
struct pythran_to_python< core::set<T> > {
    pythran_to_python() {
        pythran_to_python<T>();
        register_once< core::set<T>, custom_core_set_to_set<T> >();
    }
};

template<typename K, typename V>
struct custom_core_dict_to_dict{
    static PyObject* convert(const core::dict<K,V>& v){
        PyObject* ret = PyDict_New();
        for(auto kv=v.item_begin(); kv != v.item_end(); ++kv)
            PyDict_SetItem(ret, boost::python::incref(boost::python::object(kv->first).ptr()), boost::python::incref(boost::python::object(kv->second).ptr()));
        return ret;
    }
};

template<typename K, typename V>
struct pythran_to_python< core::dict<K,V> > {
    pythran_to_python() {
        pythran_to_python<K>();
        pythran_to_python<V>();
        register_once< core::dict<K,V>, custom_core_dict_to_dict<K,V> >();
    }
};

template<typename K, typename V>
struct custom_pair_to_tuple {
    static PyObject* convert(std::pair<K,V> const & t) {
        return boost::python::incref(boost::python::make_tuple( t.first, t.second ).ptr());
    }
};

template<typename K, typename V>
struct pythran_to_python< std::pair<K,V> > {
    pythran_to_python() {
        pythran_to_python<K>();
        pythran_to_python<V>();
        register_once<std::pair<K,V>, custom_pair_to_tuple<K,V>>();
    }
};

template<typename... Types>
struct custom_tuple_to_tuple {
    template<int ...S>
        static PyObject* do_convert( std::tuple<Types...> const & t, seq<S...>) {
            return boost::python::incref(boost::python::make_tuple( std::get<S>(t)...).ptr());
        }
    static PyObject* convert(std::tuple<Types...> const & t) {
        return do_convert(t, typename gens< sizeof...(Types) >::type());
    }
};

template<typename... Types>
struct pythran_to_python< std::tuple<Types...> > {
    pythran_to_python() {
        pythonic::fwd(pythran_to_python<Types>()...);
        register_once<std::tuple<Types...>, custom_tuple_to_tuple<Types...>>();
    }
};

template<typename T, size_t N>
struct custom_ltuple_to_tuple {
    static PyObject* convert(core::array<T,N> const & t) {
        size_t n = t.size();
        PyObject* obj = PyTuple_New(n);
        for(size_t i=0; i<n; ++i)
            PyTuple_SET_ITEM(obj, i, boost::python::incref(boost::python::object(t[i]).ptr()));
        return obj;
    }
};

template<typename T, size_t N>
struct pythran_to_python< core::array<T,N> > {
    pythran_to_python() {
        pythran_to_python<T>();
        register_once<core::array<T,N>, custom_ltuple_to_tuple<T,N>>();
    }
};

struct custom_xrange_to_list {
    static PyObject* convert(__builtin__::xrange const &xr) {
        boost::python::list ret;
        for(const long& e:xr) ret.append(e);
        return boost::python::incref(ret.ptr());
    }
};

template<>
struct pythran_to_python< __builtin__::xrange > {
    pythran_to_python() { register_once<__builtin__::xrange, custom_xrange_to_list >(); }
};

struct custom_empty_list_to_list {
    static PyObject* convert(core::empty_list const &) {
        boost::python::list ret;
        return boost::python::incref(ret.ptr());
    }
};
template<>
struct pythran_to_python< core::empty_list > {
    pythran_to_python() { register_once< core::empty_list, custom_empty_list_to_list >(); }
};

struct custom_empty_dict_to_dict {
    static PyObject* convert(core::empty_dict const &) {
        boost::python::dict ret;
        return boost::python::incref(ret.ptr());
    }
};
template<>
struct pythran_to_python< core::empty_dict > {
    pythran_to_python() { register_once< core::empty_dict, custom_empty_dict_to_dict >(); }
};
struct custom_empty_set_to_set {
    static PyObject* convert(core::empty_set const &) {
        PyObject* obj = PySet_New(nullptr);
        return obj;
    }
};
template<>
struct pythran_to_python< core::empty_set > {
    pythran_to_python() { register_once< core::empty_set, custom_empty_set_to_set >(); }
};

template <typename T>
struct custom_boost_simd_logical {
    static PyObject* convert( boost::simd::logical<T> const& n) {
        return boost::python::incref(boost::python::object((T)n).ptr());
    }
};
template<typename T>
struct pythran_to_python< boost::simd::logical<T> > {
    pythran_to_python() { register_once< boost::simd::logical<T>, custom_boost_simd_logical<T> >(); }
};

template <typename T>
struct custom_none_to_any {
    static PyObject* convert( none<T> const& n) {
        if(n.is_none) return boost::python::incref(boost::python::object().ptr());
        else return boost::python::incref(boost::python::object(static_cast<T const&>(n)).ptr());
    }
};

template<typename T>
struct pythran_to_python< none<T> > {
    pythran_to_python() {
        pythran_to_python<T>();
        register_once<none<T>, custom_none_to_any<T>>();
    }
};


template<class T, size_t N>
struct custom_array_to_ndarray {
    static PyObject* convert( core::ndarray<T,N> n) {
        n.mem.forget();
        PyObject* result = PyArray_SimpleNewFromData(N, n.shape.data(), c_type_to_numpy_type<T>::value, n.buffer);
        if (!result)
            return nullptr;
        return result;
    }
};

template<class T, size_t N>
struct pythran_to_python< core::ndarray<T,N> > {
    pythran_to_python() {
        register_once< core::ndarray<T,N> , custom_array_to_ndarray<T,N> >();
    }
};

template<class T>
struct custom_sliced_array_to_ndarray {
    static PyObject* convert( core::sliced_ndarray<T> n) {
        return custom_array_to_ndarray<typename T::dtype, T::value>().convert(n);
    }
};

template<class T>
struct pythran_to_python< core::sliced_ndarray<T> > {
    pythran_to_python() {
        register_once< core::sliced_ndarray<T> , custom_sliced_array_to_ndarray<T> >();
    }
};
/* } */

#define REGISTER_EXCEPTION_TRANSLATOR(name) \
	void translate_##name(core::name const& e) { PyErr_SetString(PyExc_##name, __builtin__::str(e.args).c_str()); }
REGISTER_EXCEPTION_TRANSLATOR(BaseException);
REGISTER_EXCEPTION_TRANSLATOR(SystemExit);
REGISTER_EXCEPTION_TRANSLATOR(KeyboardInterrupt);
REGISTER_EXCEPTION_TRANSLATOR(GeneratorExit);
REGISTER_EXCEPTION_TRANSLATOR(Exception);
REGISTER_EXCEPTION_TRANSLATOR(StopIteration);
REGISTER_EXCEPTION_TRANSLATOR(StandardError);
REGISTER_EXCEPTION_TRANSLATOR(Warning);
REGISTER_EXCEPTION_TRANSLATOR(BytesWarning);
REGISTER_EXCEPTION_TRANSLATOR(UnicodeWarning);
REGISTER_EXCEPTION_TRANSLATOR(ImportWarning);
REGISTER_EXCEPTION_TRANSLATOR(FutureWarning);
REGISTER_EXCEPTION_TRANSLATOR(UserWarning);
REGISTER_EXCEPTION_TRANSLATOR(SyntaxWarning);
REGISTER_EXCEPTION_TRANSLATOR(RuntimeWarning);
REGISTER_EXCEPTION_TRANSLATOR(PendingDeprecationWarning);
REGISTER_EXCEPTION_TRANSLATOR(DeprecationWarning);
REGISTER_EXCEPTION_TRANSLATOR(BufferError);
REGISTER_EXCEPTION_TRANSLATOR(ArithmeticError);
REGISTER_EXCEPTION_TRANSLATOR(AssertionError);
REGISTER_EXCEPTION_TRANSLATOR(AttributeError);
REGISTER_EXCEPTION_TRANSLATOR(EOFError);
REGISTER_EXCEPTION_TRANSLATOR(ImportError);
REGISTER_EXCEPTION_TRANSLATOR(LookupError);
REGISTER_EXCEPTION_TRANSLATOR(MemoryError);
REGISTER_EXCEPTION_TRANSLATOR(NameError);
REGISTER_EXCEPTION_TRANSLATOR(ReferenceError);
REGISTER_EXCEPTION_TRANSLATOR(RuntimeError);
REGISTER_EXCEPTION_TRANSLATOR(SyntaxError);
REGISTER_EXCEPTION_TRANSLATOR(SystemError);
REGISTER_EXCEPTION_TRANSLATOR(TypeError);
REGISTER_EXCEPTION_TRANSLATOR(ValueError);
REGISTER_EXCEPTION_TRANSLATOR(FloatingPointError);
REGISTER_EXCEPTION_TRANSLATOR(OverflowError);
REGISTER_EXCEPTION_TRANSLATOR(ZeroDivisionError);
REGISTER_EXCEPTION_TRANSLATOR(IndexError);
REGISTER_EXCEPTION_TRANSLATOR(KeyError);
REGISTER_EXCEPTION_TRANSLATOR(UnboundLocalError);
REGISTER_EXCEPTION_TRANSLATOR(NotImplementedError);
REGISTER_EXCEPTION_TRANSLATOR(IndentationError);
REGISTER_EXCEPTION_TRANSLATOR(TabError);
REGISTER_EXCEPTION_TRANSLATOR(UnicodeError);
REGISTER_EXCEPTION_TRANSLATOR(IOError);
REGISTER_EXCEPTION_TRANSLATOR(EnvironmentError);
REGISTER_EXCEPTION_TRANSLATOR(OSError);

#ifdef __VMS
REGISTER_EXCEPTION_TRANSLATOR(VMSError);
#endif

#ifdef MS_WINDOWS
REGISTER_EXCEPTION_TRANSLATOR(WindowsError);
#endif

#endif

#ifdef USE_GMP
#include "pythran_gmp.h"
#endif


#endif
