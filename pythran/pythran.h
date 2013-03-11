#ifndef PYTHRAN_H
#define PYTHRAN_H

#define pythran_long(v) v ## LL
#define pythran_long_def long long

#include <pythonic++.h>
#include <type_traits>
using namespace pythonic;

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
    typedef T type;
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

template<class T>
struct content_of {
    typedef typename T::value_type type;
};

template<class T>
struct content_of< std::tuple<T> > {
    typedef T type;
};
template<class T, size_t N>
struct content_of< core::ltuple<T,N> > {
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
core::list<A> operator+(container<A>, core::empty_list);
template <class A>
core::list<A> operator+(core::empty_list , container<A> );

template <class A, class B>
core::list<typename __combined<A,B>::type> operator+(container<A> , core::list<B> );
template <class A, class B>
core::list<typename __combined<A,B>::type> operator+(core::list<B> , container<A> );

template <class A, class B>
core::set<typename __combined<A,B>::type> operator+(container<A> , core::set<B> );
template <class A, class B>
core::set<typename __combined<A,B>::type> operator+(core::set<B> , container<A> );

template <class A, class B>
core::set<typename __combined<A,B>::type> operator+(core::list<A> , core::set<B> );
template <class A, class B>
core::set<typename __combined<A,B>::type> operator+(core::set<B> , core::list<A> );

template <class A>
core::set<A> operator+(core::list<A> , core::empty_set );
template <class A>
core::set<A> operator+(core::empty_set , core::list<A> );

template <class A, class B, class C>
core::dict<C, typename __combined<A,B>::type > operator+(container<A> , core::dict<C,B> );
template <class A, class B, class C>
core::dict<C, typename __combined<A,B>::type > operator+(core::dict<C,B> , container<A> );

template <class A, class B>
dict_container<typename __combined<A,B>::type > operator+(container<A> , dict_container<B> );
template <class A, class B, class C>
dict_container<typename __combined<A,B>::type > operator+(dict_container<B> , container<A> );

template <class A>
dict_container<A> operator+(dict_container<A> , dict_container<A> );
template <class A>
dict_container<A> operator+(container<A> , core::empty_dict );
template <class A>
dict_container<A> operator+(core::empty_dict , container<A> );

template <class K, class V>
core::dict<K, V> operator+(core::empty_dict , core::list<std::tuple<K,V>> );
template <class K, class V>
core::dict<K, V> operator+(core::list<std::tuple<K,V>>, core::empty_dict);
template <class K0, class V0, class K1, class V1>
core::dict<typename __combined<K0,K1>::type, typename __combined<V0, V1>::type > operator+(core::dict<K0,V0> , core::list<std::tuple<K1,V1>> );
template <class K0, class V0, class K1, class V1>
core::dict<typename __combined<K0,K1>::type, typename __combined<V0, V1>::type > operator+(core::list<std::tuple<K1,V1>>, core::dict<K0,V0>);

/* in case tuples were converted to list { */
template <class T, size_t N>
core::dict<T, T> operator+(core::empty_dict , core::list<core::ltuple<T,N>> );
template <class T, size_t N>
core::dict<T, T> operator+(core::list<core::ltuple<T,N>>,core::empty_dict  );
template <class K0, class V0, class T, size_t N>
core::dict<typename __combined<K0,T>::type, typename __combined<V0, T>::type > operator+(core::dict<K0,V0> , core::list<core::ltuple<T,N>> );
template <class K0, class V0, class T, size_t N>
core::dict<typename __combined<K0,T>::type, typename __combined<V0, T>::type > operator+(core::list<core::ltuple<T,N>>, core::dict<K0,V0>);
/* } */

template <class A>
typename __combined<core::list<A>, none_type>::type operator+(container<A> , none_type );
template <class A>
typename __combined<core::list<A>, none_type>::type operator+(none_type , container<A> );

template <class A, class B>
container<typename __combined<A,B>::type> operator+(container<A> , container<B> );

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
indexable_dict<K> operator+(indexable_dict<K>, indexable_dict<K>);
template<class K0, class K1>
indexable<typename __combined<K0,K1>::type> operator+(indexable<K0>, indexable<K1>);
template<class K>
indexable<K> operator+(indexable<K>, core::empty_list);
template<class K>
indexable<K> operator+(core::empty_list, indexable<K>);
template<class K>
indexable<K> operator+(indexable<K>, core::empty_set);
template<class K>
indexable<K> operator+(core::empty_set, indexable<K>);
template<class K>
indexable_dict<K> operator+(indexable<K>, core::empty_dict);
template<class K>
indexable_dict<K> operator+(core::empty_dict, indexable_dict<K>);
template<class K>
indexable_dict<K> operator+(indexable_dict<K>, core::empty_dict);
template<class K0, class K1, class V1>
core::dict<typename __combined<K0,K1>::type, V1> operator+(core::dict<K1,V1>, indexable_dict<K0>);
template<class K0, class K1, class V1>
core::dict<typename __combined<K0,K1>::type, V1> operator+(indexable_dict<K0>, core::dict<K1,V1>);
template<class K>
indexable_dict<K> operator+(core::empty_dict, indexable<K>);
template<class K0, class V, class K1>
core::dict<typename __combined<K0,K1>::type, V> operator+(core::dict<K0,V>, indexable<K1>);
template<class K0, class V, class K1>
core::dict<typename __combined<K0,K1>::type, V> operator+(indexable<K1>, core::dict<K0,V>);
template<class K, class... Types>
std::tuple<Types...> operator+(indexable<K>, std::tuple<Types...>);
template<class K, class... Types>
std::tuple<Types...> operator+(std::tuple<Types...>, indexable<K>);
template<class K, class T, size_t N>
core::ltuple<T,N> operator+(indexable<K>, core::ltuple<T,N>);
template<class K, class T, size_t N>
core::ltuple<T,N> operator+(core::ltuple<T,N>, indexable<K>);
template<class K>
std::complex<double> operator+(indexable<K>, std::complex<double>);
template<class K>
std::complex<double> operator+(std::complex<double>, indexable<K>);

template<class K, class V>
class indexable_container {
    public:
        typedef typename std::remove_cv< typename std::remove_reference<K>::type>::type key_type;
        typedef typename std::remove_cv< typename std::remove_reference<V>::type>::type value_type;
    private:
        indexable_container();
};
template<class K0, class V0, class K1, class V1>
indexable_container<typename __combined<K0,K1>::type, typename __combined<V0,V1>::type> operator+(indexable_container<K0,V0>, indexable_container<K1,V1>);

template <class K, class V>
indexable_container<K,V> operator+(indexable<K>, container<V>);
template <class V, class K>
indexable_container<K,V> operator+(container<V>, indexable<K>);

template <class K, class V, class W>
indexable_container<K, typename __combined<V,W>::type> operator+(indexable_container<K,V>, container<W>);
template <class V, class K, class W>
indexable_container<K, typename __combined<V,W>::type> operator+(container<W>, indexable_container<K,V>);

template <class K, class V>
core::list<V> operator+(indexable<K>, core::list<V>);
template <class V, class K>
core::list<V> operator+(core::list<V>, indexable<K>);

template <class K, class V>
core::set<V> operator+(indexable<K>, core::set<V>);
template <class K, class V>
core::set<V> operator+(core::set<V>, indexable<K>);

template <class K1, class V1, class K2>
indexable_container<typename __combined<K1,K2>::type,V1> operator+(indexable_container<K1,V1>, indexable<K2>);
template <class K1, class V1, class K2>
indexable_container<typename __combined<K1,K2>::type,V1> operator+(indexable<K2>, indexable_container<K1,V1>);

template <class K, class V0, class V1>
core::list<typename __combined<V0,V1>::type> operator+(indexable_container<K,V0>, core::list<V1>);
template <class K, class V0, class V1>
core::list<typename __combined<V0,V1>::type> operator+(core::list<V1>, indexable_container<K,V0>);

template <class K, class V>
core::list<V> operator+(indexable_container<K,V>, core::empty_list);
template <class K, class V>
core::list<V> operator+(core::empty_list, indexable_container<K,V>);

template<unsigned long N, class type, class K, class V>
core::ndarray<type,N> operator+(core::ndarray<type,N>, indexable_container<K,V>);
template<unsigned long N, class type, class K, class V>
core::ndarray<type,N> operator+(indexable_container<K,V>, core::ndarray<type,N>);

template<unsigned long N, class T, class K>
core::ndarray<T,N> operator+(core::ndarray<T,N>, indexable<K>);
template<class K, class T, unsigned long N>
core::ndarray<T,N> operator+(indexable<K>, core::ndarray<T,N>);

template <class K, class V1, class V2>
core::set<decltype(std::declval<V1>()+std::declval<V2>())> operator+(indexable_container<K,V1>, core::set<V2>);
template <class K, class V1, class V2>
core::set<decltype(std::declval<V1>()+std::declval<V2>())> operator+(core::set<V2>, indexable_container<K,V1>);

template< class K, class V>
core::dict<K,V> operator+(core::empty_dict, indexable_container<K,V>);
template< class K0, class V0, class K1, class V1>
core::dict<typename __combined<K0,K1>::type, typename __combined<V0,V1>::type> operator+(core::dict<K0,V0>, indexable_container<K1,V1>);
template< class K, class V>
core::dict<K,V> operator+(indexable_container<K,V>, core::empty_dict);

template <class K, class V>
core::dict<K,V> operator+(indexable<K>, dict_container<V>);
template <class V, class K>
core::dict<K,V> operator+(dict_container<V>, indexable<K>);
template <class V, class K, class W>
core::dict<K,typename __combined<V,W>::type> operator+(dict_container<V>, indexable_container<K,W>);

template <class K, class V, class W>
core::dict<K,typename __combined<V,W>::type> operator+(core::dict<K,V>, dict_container<W>);
template <class V, class K, class W>
core::dict<K,typename __combined<V,W>::type> operator+(dict_container<W>, core::dict<K,V>);

template <class K, class V>
core::dict<K,V> operator+(indexable_dict<K>, container<V>);
template <class K0, class K1>
indexable_dict<typename __combined<K0,K1>::type> operator+(indexable_dict<K0>, indexable<K1>);
template <class K0, class K1>
indexable_dict<typename __combined<K0,K1>::type> operator+(indexable<K0>, indexable_dict<K1>);
template <class V, class K>
core::dict<K,V> operator+(container<V>, indexable_dict<K>);

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
template<class T0, class T1, size_t N0, size_t N1>
struct __combined<core::ltuple<T0,N0>, core::ltuple<T1,N1>> {
    typedef core::ltuple<typename __combined<T0,T1>::type, N0> type;
};
template<class... T0, class... T1>
struct __combined<std::tuple<T0...>, std::tuple<T1...>> {
    typedef std::tuple<typename __combined<T0,T1>::type ...> type;  // no further combination
};
template<class T, size_t N, class... Types>
struct __combined<core::ltuple<T,N>, std::tuple<Types...>> {
    typedef std::tuple<Types...> type;
};
template<class T, size_t N, class... Types>
struct __combined<std::tuple<Types...>, core::ltuple<T,N>> {
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

struct dummy {};

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

/* specialization for callable types */
template <class T0, class T1>
typename std::enable_if< is_callable<T0>::value and is_callable<T1>::value, variant<T0,T1> >::type operator+(T0 , T1 );

template <class T>
typename std::enable_if< is_callable<T>::value, T>::type operator+(T , T);


/* some overloads */
namespace std {

    /* for remove_cv */
    template <class K, class V>
        struct remove_cv< std::pair<const K, V> > {
            typedef std::pair<K, V> type;
        };
    /* for core::list */
    template <size_t I, class T>
        typename core::list<T>::reference get( core::list<T>& t) { return t[I]; }
    template <size_t I, class T>
        typename core::list<T>::const_reference get( core::list<T> const & t) { return t[I]; }

    template <size_t I, class T>
        struct tuple_element<I, core::list<T> > {
            typedef typename core::list<T>::value_type type;
        };

    /* for core::ndarray */
    template <size_t I, class T, unsigned long N>
        typename core::ndarray_helper<T,N>::result_type get( core::ndarray<T,N>& a) { return a[I]; }
    template <size_t I, class T, unsigned long N>
        typename core::ndarray_helper<T,N>::const_result_type get( core::ndarray<T,N> const& a) { return a[I]; }
    template <size_t I, class T>
        struct tuple_element<I, core::ndarray<T,1> > {
            typedef T type;
        };
    template <size_t I, class T, unsigned long N>
        struct tuple_element<I, core::ndarray<T,N> > {
            typedef core::ndarray<T,N-1> type;
        };

    /* for core::dict */
    template <size_t I, class K, class V>
        auto get( core::dict<K,V>& d) -> decltype(d[I]) { return d[I]; }
    template <size_t I, class K, class V>
        auto get( core::dict<K,V> const & d) -> decltype(d[I]) { return d[I]; }

    template <size_t I, class K, class V>
        struct tuple_element<I, core::dict<K,V> > {
            typedef typename core::dict<K,V>::value_type type;
        };
    /* for core::string */
    template <size_t I>
        typename core::string get( core::string const &t) { return core::string(t[I]); }

    template <size_t I>
        struct tuple_element<I, core::string > {
            typedef typename core::string type;
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
    none_type getattr<3>(core::file const& f) {return None;}

/* for ndarrays */
template <class T, unsigned long N>
    struct attribute_element<0, pythonic::core::ndarray<T,N> > {
        typedef core::list<long> type;
    };

template <class T, unsigned long N>
    struct attribute_element<1, pythonic::core::ndarray<T,N> > {
        typedef long type;
    };

template <class T, unsigned long N>
    struct attribute_element<2, pythonic::core::ndarray<T,N> > {
        typedef core::list<long> type;
    };

template <class T, unsigned long N>
    struct attribute_element<3, pythonic::core::ndarray<T,N> > {
        typedef long type;
    };

template <class T, unsigned long N>
    struct attribute_element<4, pythonic::core::ndarray<T,N> > {
        typedef long type;
    };

template <class T, unsigned long N>
    struct attribute_element<5, pythonic::core::ndarray<T,N> > {
        typedef long type;
    };

template <class T, unsigned long N>
    struct attribute_element<6, pythonic::core::ndarray<T,N> > {
        typedef pythonic::core::ndarray_flat_const<T,N> type;
    };

template <unsigned int I, class T, unsigned long N>
    struct ndarray_attr;

template <class T, unsigned long N>
    struct ndarray_attr<0,T,N>
    {
        typename attribute_element<0,pythonic::core::ndarray<T,N>>::type const operator()(core::ndarray<T,N> const& a)
        {
            return core::list<long>(a.shape->begin(), a.shape->end());
        }
    };

template <class T, unsigned long N>
    struct ndarray_attr<1,T,N>
    {
        typename attribute_element<1,pythonic::core::ndarray<T,N>>::type const operator()(core::ndarray<T,N> const& a)
        {
            return N;
        }
    };

template <class T, unsigned long N>
    struct ndarray_attr<2,T,N>
    {
        typename attribute_element<2,pythonic::core::ndarray<T,N>>::type const operator()(core::ndarray<T,N> const& a)
        {
            core::list<long> strides(N);
            strides[N-1] = sizeof(T);
            std::transform(strides.rbegin(), strides.rend() -1, a.shape->rbegin(), strides.rbegin()+1, std::multiplies<long>());
            return strides;
        }
    };

template <class T, unsigned long N>
    struct ndarray_attr<3,T,N>
    {
        typename attribute_element<3,pythonic::core::ndarray<T,N>>::type const operator()(core::ndarray<T,N> const& a)
        {
            return std::accumulate(a.shape->begin(), a.shape->end(), 1, std::multiplies<int>());
        }
    };

template <class T, unsigned long N>
    struct ndarray_attr<4,T,N>
    {
        typename attribute_element<4,pythonic::core::ndarray<T,N>>::type const operator()(core::ndarray<T,N> const& a)
        {
            return sizeof(T);
        }
    };

template <class T, unsigned long N>
    struct ndarray_attr<5,T,N>
    {
        typename attribute_element<5,pythonic::core::ndarray<T,N>>::type const operator()(core::ndarray<T,N> const& a)
        {
            return std::accumulate(a.shape->begin(), a.shape->end(), sizeof(T), std::multiplies<int>());
        }
    };

template <class T, unsigned long N>
    struct ndarray_attr<6,T,N>
    {
        typename attribute_element<6,pythonic::core::ndarray<T,N>>::type const operator()(core::ndarray<T,N> const& a)
        {
            return pythonic::core::ndarray_flat_const<T,N>(a);
        }
    };

template <unsigned int I, class T, unsigned long N>
    typename attribute_element<I,pythonic::core::ndarray<T,N>>::type const getattr(core::ndarray<T,N> const& a)
    {
        return ndarray_attr<I,T,N>()(a);
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
        none<typename core::BaseError::Type<1>::type> getattr<1>( const core::name& t ){ if(t.args.size()>3 || t.args.size()<2) return (None); else return t.args[0];}\
    template <>\
        none<typename core::BaseError::Type<2>::type> getattr<2>( const core::name& t ){ if(t.args.size()>3 || t.args.size()<2) return None; else return t.args[1];}\
    template <>\
        none<typename core::BaseError::Type<3>::type> getattr<3>( const core::name& t ){ if(t.args.size()==3) return t.args[2]; else return None; }\

ENVIRONMENTERROR_EXCEPTION(EnvironmentError)
ENVIRONMENTERROR_EXCEPTION(IOError)
ENVIRONMENTERROR_EXCEPTION(OSError)

/* } */

/* wrapper used by generated code to simulate closures { */
namespace pythonic {
    namespace __builtin__ {
        namespace proxy {
            struct bind0 {
                template<typename Operator, typename... Types>
                    auto operator()(Operator const& op, Types &&... types)
                    -> function<decltype(std::bind(op, types...))> {
                        return function<decltype(std::bind(op, types...))>(std::bind(op, types...)); 
                    }
            };
            struct bind1 {
                template<typename Operator, typename... Types>
                    auto operator()(Operator const& op, Types &&... types)
                    -> function<decltype(std::bind(op, types..., std::placeholders::_1))> {
                        return function<decltype(std::bind(op, types..., std::placeholders::_1))>(std::bind(op, types..., std::placeholders::_1)); 
                    }
            };
            struct bind2 {
                template<typename Operator, typename... Types>
                    auto operator()(Operator const& op, Types &&... types)
                    -> function<decltype(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2))> {
                        return function<decltype(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2))>(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2));
                    }
            };
            struct bind3 {
                template<typename Operator, typename... Types>
                    auto operator()(Operator const& op, Types &&... types)
                    -> function<decltype(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))> {
                        return function<decltype(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))>(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)); 
                    }
            };
            struct bind4 {
                template<typename Operator, typename... Types>
                    auto operator()(Operator const& op, Types &&... types)
                    -> function<decltype(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4))> {
                        return function<decltype(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4))>(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,  std::placeholders::_4)); 
                    }
            };
            struct bind5 {
                template<typename Operator, typename... Types>
                    auto operator()(Operator const& op, Types &&... types)
                    -> function<decltype(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5))> {
                        return function<decltype(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5))>(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,  std::placeholders::_4, std::placeholders::_5)); 
                    }
            };
        }
    }
}
/* } */

#ifdef ENABLE_PYTHON_MODULE
/* python <-> c++ conversion stuff { */

#include <boost/python.hpp>
#include <boost/python/module.hpp>

/* boost::python converters */
#include <boost/python/numeric.hpp>
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
        new (storage) core::string(s);
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

template<typename type, unsigned long N>
struct python_to_pythran< core::ndarray<type, N> >{
    python_to_pythran(){
        static bool registered=false;
        pythonic::fwd(python_to_pythran<type>());
        if(not registered) {
            registered=true;
            boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id< core::ndarray<type, N> >());
        }
    }
    static void* convertible(PyObject* obj_ptr){
        if(!PyArray_Check(obj_ptr) ) return 0;
        return obj_ptr;
    }

    static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
        void* storage=((boost::python::converter::rvalue_from_python_storage<core::ndarray<type,N>>*)(data))->storage.bytes;
        new (storage) core::ndarray< type, N>((type*)PyArray_BYTES(obj_ptr), PyArray_DIMS(obj_ptr), PyArray_SIZE(obj_ptr));
        data->convertible=storage;
    }
};

template<typename T>
struct pythran_to_python {
};

template<class Type, class Converter>
static void register_once() {
    static bool registered=false;
    if(not registered) {
        registered=true;
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
        return PyString_FromString(v.c_str());
    }
};

template<>
struct pythran_to_python< core::string > {
    pythran_to_python() {
        register_once< core::string, custom_core_string_to_str >();
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
    static PyObject* convert(core::ltuple<T,N> const & t) {
        size_t n = t.size();
        PyObject* obj = PyTuple_New(n);
        for(size_t i=0; i<n; ++i)
            PyTuple_SET_ITEM(obj, i, boost::python::incref(boost::python::object(t[i]).ptr()));
        return obj;
    }
};

template<typename T, size_t N>
struct pythran_to_python< core::ltuple<T,N> > {
    pythran_to_python() {
        pythran_to_python<T>();
        register_once<core::ltuple<T,N>, custom_ltuple_to_tuple<T,N>>();
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
struct custom_none_to_any {
    static PyObject* convert( none<T> const& n) {
        if(n.is_none) return boost::python::incref(boost::python::object().ptr());
        else return boost::python::incref(boost::python::object(n.data).ptr());
    }
};

template<typename T>
struct pythran_to_python< none<T> > {
    pythran_to_python() {
        pythran_to_python<T>();
        register_once<none<T>, custom_none_to_any<T>>();
    }
};

template<class T>
struct c_type_to_numpy_type {};

template<>
struct c_type_to_numpy_type<double> {
    static const int value = NPY_DOUBLE;
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
struct c_type_to_numpy_type<bool> {
    static const int value = NPY_BOOL;
};

template<class T, unsigned long N>
struct custom_array_to_ndarray {
    static PyObject* convert( core::ndarray<T,N> n) {
        PyObject* result = PyArray_SimpleNewFromData(N, n.shape->data(), c_type_to_numpy_type<T>::value, n.data.forget()->data + *n.offset_data);

        if (!result)
            return nullptr;
        return boost::python::incref(result);
    }
};

template<class T, unsigned long N>
struct pythran_to_python< core::ndarray<T,N> > {
    pythran_to_python() {
        register_once< core::ndarray<T,N> , custom_array_to_ndarray<T,N> >();
    }
};
/* } */
#endif

#endif
