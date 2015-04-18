#ifndef PYTHONIC_INCLUDE_TYPES_LIST_HPP
#define PYTHONIC_INCLUDE_TYPES_LIST_HPP

#include "pythonic/types/array_like.hpp"
#include "pythonic/types/assignable.hpp"
#include "pythonic/types/empty_iterator.hpp"
#include "pythonic/utils/shared_ref.hpp"
#include "pythonic/utils/reserve.hpp"
#include "pythonic/utils/nested_container.hpp"
#include "pythonic/types/slice.hpp"

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>

#ifdef USE_BOOST_SIMD
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#endif

namespace pythonic {

    namespace types {

        static const size_t DEFAULT_LIST_CAPACITY = 16;

        /* forward declaration */
        struct empty_list;
        template<class T> class list;
        template<class T, class S> class sliced_list;
        template<class T, size_t N> struct ndarray;
        template<class T> struct is_list { static const bool value = false; };
        template<class T> struct is_list<list<T>> { static const bool value = true; };
        template<class T, class S> struct is_list<sliced_list<T,S>> { static const bool value = true; };

        /* for type disambiguification */
        struct single_value {};

        /* list view */
        template<class T, class S=slice>
            class sliced_list {

                // data holder
                typedef  typename std::remove_cv< typename std::remove_reference<T>::type>::type  _type;
                typedef std::vector< _type > container_type;
                utils::shared_ref<container_type> data;

                template<class U>
                    friend class list;

                typename S::normalized_type slicing;

                public:
                //  types
                typedef typename container_type::reference reference;
                typedef typename container_type::const_reference const_reference;
                typedef typename container_type::iterator iterator;
                typedef typename container_type::const_iterator const_iterator;
                typedef typename container_type::size_type size_type;
                typedef typename container_type::difference_type difference_type;
                typedef typename container_type::value_type value_type;
                typedef typename container_type::allocator_type allocator_type;
                typedef typename container_type::pointer pointer;
                typedef typename container_type::const_pointer const_pointer;
                typedef typename container_type::reverse_iterator reverse_iterator;
                typedef typename container_type::const_reverse_iterator const_reverse_iterator;

                // minimal ndarray interface
                typedef typename utils::nested_container_value_type<sliced_list>::type dtype;
                static const size_t value = utils::nested_container_depth<sliced_list>::value;
                static const bool is_vectorizable = false; // overly cautious \simeq lazy

                // constructor
                sliced_list();
                sliced_list(sliced_list<T,S> const & s);
                sliced_list(list<T> & other, S const & s);

                // assignment
                sliced_list& operator=(list<T> const & );
                sliced_list& operator=(sliced_list<T,S> const & );
                list<T> operator+(list<T> const & );
                list<T> operator+(sliced_list<T,S> const & );

                // iterators
                iterator begin();
                const_iterator begin() const;
                iterator end();
                const_iterator end() const;

                // size
                size_t size() const;

                // accessor
                T const & operator[](long i) const;
                T & operator[](long i);

                // comparison
                template <class K>
                    bool operator==(list<K> const & other) const;
                bool operator==(empty_list const& other) const;
            };

        /* list */
        template<class T>
            class list : public ArrayLike<typename utils::nested_container_value_type<list<T>>::type,
                                          utils::nested_container_depth<list<T>>::value, true, false, T,
                                          typename std::vector<typename std::remove_cv<typename std::remove_reference<T>::type>::type>::reference> {

                using parent = ArrayLike<typename utils::nested_container_value_type<list<T>>::type, // Inner type
                                         utils::nested_container_depth<list<T>>::value, // depth
                                         true, // vectorizable
                                         false, // strided
                                         T, // value_type
                                         typename std::vector<typename std::remove_cv<typename std::remove_reference<T>::type>::type>::reference // reference to contente type
                                        >;


                // data holder
                typedef  typename std::remove_cv< typename std::remove_reference<T>::type>::type  _type;
                typedef std::vector< _type > container_type;
                utils::shared_ref<container_type> data; 

                template<class U, class S>
                    friend class sliced_list;

                template<class U>
                    friend class list;

                public:

                // types
                typedef typename container_type::const_reference const_reference;
                typedef typename container_type::iterator iterator;
                typedef typename container_type::const_iterator const_iterator;
                typedef typename container_type::size_type size_type;
                typedef typename container_type::difference_type difference_type;
                typedef typename container_type::allocator_type allocator_type;
                typedef typename container_type::pointer pointer;
                typedef typename container_type::const_pointer const_pointer;
                typedef typename container_type::reverse_iterator reverse_iterator;
                typedef typename container_type::const_reverse_iterator const_reverse_iterator;

                // constructors
                list();
                template<class InputIterator>
                    list(InputIterator start, InputIterator stop);
                list(empty_list const&);
                list(size_type sz);
                list(T const& value, single_value);
                list(std::initializer_list<T> l);
                list(list<T> && other);
                list(list<T> const & other);
                template<class F>
                    list(list<F> const & other);
                template<class S>
                    list(sliced_list<T,S> const & other);
                list<T>& operator=(list<T> && other);
                template<class F>
                    list<T>& operator=(list<F> const& other);
                list<T>& operator=(list<T> const & other);
                list<T>& operator=(empty_list const & );
                template<class S>
                    list<T>& operator=(sliced_list<T,S> const & other);

                list& operator=(ndarray<T,1> const & ); // implemented in ndarray.hpp

                template<class S>
                    list<T>& operator+=(sliced_list<T,S> const & other);
                template<class S>
                    list<T> operator+(sliced_list<T,S> const & other) const;

                template<class E>
                    void init_shape(E const& e, utils::int_<1>);
                template<class E, size_t L>
                    void init_shape(E const& e, utils::int_<L>);

                // io
                template<class S>
                    friend std::ostream& operator<<(std::ostream& os, list<S> const & v);

                // comparison
                template <class K>
                    bool operator==(list<K> const & other) const;
                bool operator==(empty_list const&) const;
                template <class K>
                    bool operator!=(list<K> const & other) const;
                bool operator!=(empty_list const&) const;

                // iterators
                iterator begin();
                const_iterator begin() const;
                iterator end();
                const_iterator end() const;
                reverse_iterator rbegin();
                const_reverse_iterator rbegin() const;
                reverse_iterator rend();
                const_reverse_iterator rend() const;

                // comparison
                int operator<(list<T> const& other) const;

                // element access
#ifdef USE_BOOST_SIMD
                auto load(long i) const -> decltype(boost::simd::load<boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>>((*this->data),i));
                template<class V>
                    void store(V &&v, long i);
#endif
                typename parent::reference fast(long n);
                typename parent::reference operator[]( long n );

                const_reference fast(long n) const;
                const_reference operator[]( long n ) const;

                list<T> operator[]( slice const &s ) const;
                list<T> operator[]( contiguous_slice const &s ) const;

                sliced_list<T,slice> operator()( slice const &s) const;
                sliced_list<T,contiguous_slice> operator()( contiguous_slice const &s) const;

                // modifiers
                void push_back( T const & x);
                void insert(size_t i, T const & x);

                void reserve(size_t n);
                void resize(size_t n);
                iterator erase(size_t n);

                T pop(long x = -1);

                //TODO: have to raise a valueError
                void remove(T const& x);

                //Misc
                //TODO: have to raise a valueError
                long index(T const& x) const;

                // list interface
                explicit operator bool() const;

                template <class F>
                    list<decltype(std::declval<T>()+std::declval<typename list<F>::value_type>())> operator+(list<F> const & s) const;

                template <class F, class S>
                    list<decltype(std::declval<T>()+std::declval<typename sliced_list<F,S>::value_type>())> operator+(sliced_list<F,S> const & s) const;

                list<T> operator+(empty_list const &) const;
                list<T> operator*(long t) const;

                template <class F>
                    list<T>& operator+=(list<F> const & s);
                size_t size() const;
                template<class E>
                    long _flat_size(E const& e, utils::int_<1>) const;
                template<class E, size_t L>
                    long _flat_size(E const& e, utils::int_<L>) const;
                size_t flat_size() const;

                template<class V>
                    bool contains(V const & v) const;
                intptr_t id() const;

                long count(T const& x) const;
            };

        /* empty list implementation */
        struct empty_list {
            typedef void value_type;
            typedef empty_iterator iterator;
            typedef empty_iterator const_iterator;
            template<class T>
                list<T> operator+(list<T> const & s) const;
            template<class T, class S>
                sliced_list<T,S> operator+(sliced_list<T,S> const & s) const;
            empty_list operator+(empty_list const &) const;
            operator bool() const;
            template<class T>
                operator list<T>() const;
        };


        std::ostream& operator<<(std::ostream& os, empty_list const & );

    }


    namespace utils {
        template <class T, class From>
            void reserve(types::list<T> & l, From const &f, typename From::const_iterator *p=nullptr);
    }

    template<class T>
        struct assignable<types::list<T> >{
            typedef types::list<typename assignable<T>::type > type;
        };

}

/* overload std::get */
namespace std {
    template <size_t I, class T>
        typename pythonic::types::list<T>::reference get( pythonic::types::list<T>& t);
    template <size_t I, class T>
        typename pythonic::types::list<T>::const_reference get( pythonic::types::list<T> const & t);
    template <size_t I, class T>
        typename pythonic::types::sliced_list<T>::reference get( pythonic::types::sliced_list<T>& t);
    template <size_t I, class T>
        typename pythonic::types::sliced_list<T>::const_reference get( pythonic::types::sliced_list<T> const & t);

    template <size_t I, class T>
        struct tuple_element<I, pythonic::types::list<T> > {
            typedef typename pythonic::types::list<T>::value_type type;
        };
    template <size_t I, class T>
        struct tuple_element<I, pythonic::types::sliced_list<T> > {
            typedef typename pythonic::types::sliced_list<T>::value_type type;
        };
}

/* type inference stuff  {*/
#include "pythonic/types/combined.hpp"

template <class A>
struct __combined<container<A>, pythonic::types::empty_list> {
    typedef pythonic::types::list<A> type;
};

template <class A>
struct __combined<pythonic::types::empty_list , container<A> > {
    typedef pythonic::types::list<A> type;
};

template <class A, class B>
struct __combined<container<A> , pythonic::types::list<B> > {
    typedef pythonic::types::list<typename __combined<A,B>::type> type;
};

template <class A, class B>
struct __combined<pythonic::types::list<B> , container<A> > {
    typedef pythonic::types::list<typename __combined<A,B>::type> type;
};

template <class K, class V>
struct __combined<indexable<K>, pythonic::types::list<V>> {
    typedef pythonic::types::list<V> type;
};

template <class V, class K>
struct __combined<pythonic::types::list<V>, indexable<K>> {
    typedef pythonic::types::list<V> type;
};

template <class K, class V0, class V1>
struct __combined<indexable_container<K,V0>, pythonic::types::list<V1>> {
    typedef pythonic::types::list<typename __combined<V0,V1>::type> type;
};

template <class K, class V0, class V1>
struct __combined<pythonic::types::list<V1>, indexable_container<K,V0>> {
    typedef pythonic::types::list<typename __combined<V0,V1>::type> type;
};

template <class K, class V>
struct __combined<indexable_container<K,V>, pythonic::types::empty_list> {
    typedef pythonic::types::list<V> type;
};

template <class K, class V>
struct __combined<pythonic::types::empty_list, indexable_container<K,V>> {
    typedef pythonic::types::list<V> type;
};

template<class T0, class T1>
struct __combined<pythonic::types::list<T0>, pythonic::types::list<T1>> {
    typedef pythonic::types::list<typename __combined<T0,T1>::type> type;
};

/* } */

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/register_once.hpp"
#include "pythonic/python/extract.hpp"
#include <boost/python/object.hpp>

namespace pythonic {

    template<typename T>
        struct custom_pythran_list_to_list{
            static PyObject* convert(const types::list<T>& v);
        };

  /*
   This specialization is a workaround for a boost::python bug triggered when
   using std::vector<bool> and libc++.
   Indeed v[i] returns a wrapper class to keep a reference to the bit in the 
   bitset. The issue is that operator& is overloaded and prevent taking the
   address of the wrapper class.
   This is a copy paste of the generic case, plus a cast to (bool) to get rid
   of the wrapper.
   The cast can't be added to the generic version because casting may trigger
   an extra copy that is not what we want for heavy objects
   */
    template<>
        struct custom_pythran_list_to_list<bool> {
            static PyObject* convert(const types::list<bool>& v);
        };

    template<typename T>
        struct pythran_to_python< types::list<T> > {
            pythran_to_python();
        };

    template<typename T>
        struct python_to_pythran< types::list<T> >{
            python_to_pythran();
            static void* convertible(PyObject* obj_ptr);
            template <class T1>
                static typename std::enable_if<!types::has_shape<T1>::value, void>::type
                set_shape(types::list<T1>&, typename types::list<T1>::reference);

            template <class T1>
                static typename std::enable_if< types::has_shape<T1>::value, void>::type
                set_shape(types::list<T1>& l, typename types::list<T1>::reference e);

            static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data);
        };
    struct custom_empty_list_to_list {
        static PyObject* convert(types::empty_list const &);
    };
    template<>
        struct pythran_to_python< types::empty_list > {
            pythran_to_python();
        };
}

#endif

#endif
