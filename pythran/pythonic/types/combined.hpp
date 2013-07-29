#ifndef PYTHONIC_TYPES_COMBINED_HPP
#define PYTHONIC_TYPES_COMBINED_HPP

#include "pythonic/types/traits.hpp"
#include "pythonic/types/variant.hpp"

/* special handling for functors { */
template <class T0, class T1>
typename std::enable_if< pythonic::types::is_callable<T0>::value and pythonic::types::is_callable<T1>::value, pythonic::types::variant<T0,T1> >::type operator+(T0 , T1 );

template <class T>
typename std::enable_if< pythonic::types::is_callable<T>::value, T>::type operator+(T , T);

/* } */

/* type inference stuff
*/

template<class T0, class T1, class... Types>
struct __combined {
    typedef typename __combined< T0, typename __combined<T1, Types...>::type >::type type;
};

template<class T0, class T1>
struct __combined<T0,T1> {
    typedef decltype(std::declval<T0>()+std::declval<T1>()) type;
};

template<class T>
class container {
    public:
        typedef typename std::remove_cv< typename std::remove_reference<T>::type>::type value_type;
    private:
        container();
};

template<class K, class V>
class indexable_container {
    public:
        typedef typename std::remove_cv< typename std::remove_reference<K>::type>::type key_type;
        typedef typename std::remove_cv< typename std::remove_reference<V>::type>::type value_type;
    private:
        indexable_container();
};

template<class T>
class dict_container {
    public:
        typedef typename std::remove_cv< typename std::remove_reference<T>::type>::type value_type;
    private:
        dict_container();
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

template<class K0, class V0, class K1, class V1>
struct __combined<indexable_container<K0,V0>, indexable_container<K1,V1>> {
    typedef indexable_container<typename __combined<K0,K1>::type, typename __combined<V0,V1>::type> type;
};

template <class K, class V>
struct __combined<indexable<K>, indexable<V>> {
    typedef indexable<typename __combined<K,V>::type> type;
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

template <class K1, class V1, class K2>
struct __combined<indexable_container<K1,V1>, indexable<K2>> {
    typedef indexable_container<typename __combined<K1,K2>::type,V1> type;
};

template <class K1, class V1, class K2>
struct __combined<indexable<K2>, indexable_container<K1,V1>> {
    typedef indexable_container<typename __combined<K1,K2>::type,V1> type;
};

template <class A, class B>
struct __combined<container<A> , container<B> > {
    typedef container<typename __combined<A,B>::type> type;
};


#endif
