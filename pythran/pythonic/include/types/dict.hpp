#ifndef PYTHONIC_INCLUDE_TYPES_DICT_HPP
#define PYTHONIC_INCLUDE_TYPES_DICT_HPP

#include "pythonic/types/assignable.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/types/empty_iterator.hpp"
#include "pythonic/types/content_of.hpp"

#include "pythonic/utils/shared_ref.hpp"
#include "pythonic/utils/iterator.hpp"
#include "pythonic/utils/reserve.hpp"

#include "pythonic/__builtin__/None.hpp"

#include <memory>
#include <utility>
#include <limits>
#include <algorithm>
#include <iterator>
#include <boost/unordered_map.hpp>


namespace pythonic {

    namespace types {

        static const size_t DEFAULT_DICT_CAPACITY = 64;

        struct empty_dict;

        template<class I>
            struct key_iterator_adaptator : public I
            {
                using value_type = typename I::value_type::first_type;
                using pointer = typename I::value_type::first_type*;
                using reference = typename I::value_type::first_type&;
                key_iterator_adaptator();
                key_iterator_adaptator(I const &i);
                value_type operator*();
            };

        template<class I>
            struct value_iterator_adaptator : public I
            {
                using value_type = typename I::value_type::second_type;
                using pointer = typename I::value_type::second_type*;
                using reference = typename I::value_type::second_type&;
                value_iterator_adaptator();
                value_iterator_adaptator(I const &i);
                value_type operator*();
            };

        template<class I>
            struct dict_iterator {
                typedef I iterator;
                I _begin;
                I _end;
                dict_iterator(I b, I e);
                iterator begin();
                iterator end();
            };

        template<class D>
            struct dict_items
            {
                using iterator = typename D::item_const_iterator;
                D data;
                dict_items();
                dict_items(D const & d);
                iterator begin() const;
                iterator end() const;
            };

        template<class D>
            struct dict_keys
            {
                using iterator = typename D::key_const_iterator;
                D data;
                dict_keys();
                dict_keys(D const & d);
                iterator begin() const;
                iterator end() const;
            };

        template<class D>
            struct dict_values {
                using iterator = typename D::value_const_iterator;
                D data;
                dict_values();
                dict_values(D const & d);
                iterator begin() const;
                iterator end() const;
            };

        template<class K, class V>
            class dict
            {

                // data holder
                using _key_type = typename std::remove_cv< typename std::remove_reference<K>::type>::type;
                using _value_type = typename std::remove_cv< typename std::remove_reference<V>::type>::type;
                using container_type = boost::unordered_map< _key_type, _value_type >;

                utils::shared_ref<container_type> data;

                public:

                // types
                using reference = typename container_type::reference;
                using const_reference = typename container_type::const_reference;
                using iterator = utils::comparable_iterator<key_iterator_adaptator<typename container_type::iterator> >;
                using const_iterator = utils::comparable_iterator<key_iterator_adaptator<typename container_type::const_iterator> >;
                using item_iterator = utils::comparable_iterator<typename container_type::iterator>;
                using item_const_iterator = utils::comparable_iterator<typename container_type::const_iterator>;
                using key_iterator = utils::comparable_iterator<key_iterator_adaptator<typename container_type::iterator> >;
                using key_const_iterator = utils::comparable_iterator<key_iterator_adaptator<typename container_type::const_iterator> >;
                using value_iterator = utils::comparable_iterator<value_iterator_adaptator<typename container_type::iterator> >;
                using value_const_iterator = utils::comparable_iterator<value_iterator_adaptator<typename container_type::const_iterator> >;
                using size_type = typename container_type::size_type;
                using difference_type = typename container_type::difference_type;
                using value_type = typename container_type::value_type;
                using allocator_type = typename container_type::allocator_type;
                using pointer = typename container_type::pointer;
                using const_pointer = typename container_type::const_pointer;

                // constructors
                dict();
                dict(empty_dict const &);
                dict(std::initializer_list<value_type> l);
                dict(dict<K,V> const & other);
                template<class Kp, class Vp>
                    dict(dict<Kp,Vp> const & other);
                template<class B, class E>
                    dict(B begin, E end);

                // iterators
                iterator begin();
                const_iterator begin() const;
                iterator end();
                const_iterator end() const;
                item_iterator item_begin();
                item_const_iterator item_begin() const;
                item_iterator item_end();
                item_const_iterator item_end() const;
                key_iterator key_begin();
                key_const_iterator key_begin() const;
                key_iterator key_end();
                key_const_iterator key_end() const;
                value_iterator value_begin();
                value_const_iterator value_begin() const;
                value_iterator value_end();
                value_const_iterator value_end() const;

                // dict interface
                operator bool();
                V& operator[](K const & key);
                V const & operator[](K const & key) const;

                V& fast(K const & key);
                V const & fast(K const & key) const;

                item_const_iterator find(K const & key) const;

                void clear();

                dict<K,V> copy() const;

                template <class W>
                    typename __combined<V, W>::type get(K const& key, W d) const;

                none<V> get(K const& key) const;

                template <class W>
                    V& setdefault(K const& key, W d);

                none<V>& setdefault(K const& key);

                template<class K0, class W0>
                    void update(dict<K0,W0> const & d);

                template<class Iterable>
                    void update(Iterable const & d);

                template <class W>
                    typename __combined<V,W>::type pop(K const& key, W d);

                V pop(K const& key);

                std::tuple<K,V> popitem();

                long size() const;

                dict_iterator<item_iterator> iteritems();
                dict_iterator<item_const_iterator> iteritems() const;

                dict_iterator<key_iterator> iterkeys();
                dict_iterator<key_const_iterator> iterkeys() const;

                dict_iterator<value_iterator> itervalues();
                dict_iterator<value_const_iterator> itervalues() const;

                dict_items<dict<K,V>> viewitems() const;
                dict_keys<dict<K,V>> viewkeys() const;
                dict_values<dict<K,V>> viewvalues() const;

                // type inference stuff
                template<class K_, class V_> 
                    dict<typename __combined<K, K_>::type, typename __combined<V, V_>::type>
                    operator+(dict<K_,V_> const & ); 

                // id interface
                intptr_t id() const;

                template<class T>
                    bool contains(T const& key) const;
            };

        struct empty_dict {

            using value_type = void;
            using iterator = empty_iterator;
            using const_iterator = empty_iterator;

            template<class K, class V> 
                dict<K,V> operator+(dict<K,V> const & s);

            empty_dict operator+(empty_dict const &);
            operator bool() const;
            iterator begin() const;
            iterator end() const;
            template<class V>
                bool contains(V const&) const;
        };

        template <class K, class V>
            dict<K, V> operator+(dict<K,V> const& d, empty_dict);

        template<class K, class V>
            struct content_of< dict<K,V> > {
                using type = V;
            };
    }

    template<class K,class V>
        struct assignable<types::dict<K,V> >
        {
            using type = types::dict<typename assignable<K>::type,typename assignable<V>::type >;
        };

    std::ostream& operator<<(std::ostream& os, types::empty_dict const & );

    template<class K, class V>
        std::ostream& operator<<(std::ostream& os, std::pair<K,V> const & p);

    template<class K, class V>
        std::ostream& operator<<(std::ostream& os, types::dict<K,V> const & v);
}

/* overload std::get */
namespace std {
    template <size_t I, class K, class V>
        auto get( pythonic::types::dict<K,V>& d)
        -> decltype(d[I]);

    template <size_t I, class K, class V>
        auto get( pythonic::types::dict<K,V> const & d)
        -> decltype(d[I]);

    template <size_t I, class K, class V>
        struct tuple_element<I, pythonic::types::dict<K,V> >
        {
            using type = V;
        };
}

/* type inference stuff  {*/
#include "pythonic/types/combined.hpp"
#include "pythonic/types/list.hpp"

template <class A>
struct __combined<container<A> , pythonic::types::empty_dict >
{
    using type = dict_container<A>;
};

template <class A>
struct __combined<pythonic::types::empty_dict , container<A> >
{
    using type = dict_container<A>;
};

template <class A, class B, class C>
struct __combined<container<A> , pythonic::types::dict<C,B> >
{
    using type = pythonic::types::dict<C, typename __combined<A,B>::type >;
};

template <class A, class B, class C>
struct __combined<pythonic::types::dict<C,B> , container<A> >
{
    using type = pythonic::types::dict<C, typename __combined<A,B>::type >;
};

template <class T>
struct __combined<pythonic::types::empty_dict, pythonic::types::list<T>>
{
    using type = pythonic::types::dict<typename std::tuple_element<0,T>::type, typename std::tuple_element<1,T>::type>;
};

template <class T>
struct __combined<pythonic::types::list<T>, pythonic::types::empty_dict>
{
    using type = pythonic::types::dict<typename std::tuple_element<0,T>::type, typename std::tuple_element<1,T>::type>;
};

template <class K0, class V0, class T>
struct __combined<pythonic::types::dict<K0,V0> , pythonic::types::list<T> >
{
    using type = pythonic::types::dict<typename __combined<K0,typename std::tuple_element<0,T>::type>::type, typename __combined<V0, typename std::tuple_element<1,T>::type>::type >;
};

template <class K0, class V0, class T>
struct __combined<pythonic::types::list<T>, pythonic::types::dict<K0,V0>>
{
    using type = pythonic::types::dict<typename __combined<K0,typename std::tuple_element<0,T>::type>::type, typename __combined<V0, typename std::tuple_element<1,T>::type>::type >;
};

template<class K>
struct __combined<indexable<K>, pythonic::types::empty_dict>
{
    using type = indexable_dict<K>;
};

template<class K>
struct __combined<pythonic::types::empty_dict, indexable_dict<K>>
{
    using type = indexable_dict<K>;
};

template<class K>
struct __combined<indexable_dict<K>, pythonic::types::empty_dict>
{
    using type = indexable_dict<K>;
};

template<class K0, class K1, class V1>
struct __combined<pythonic::types::dict<K1,V1>, indexable_dict<K0>>
{
    using type = pythonic::types::dict<typename __combined<K0,K1>::type, V1>;
};

template<class K0, class K1, class V1>
struct __combined<indexable_dict<K0>, pythonic::types::dict<K1,V1>>
{
    using type = pythonic::types::dict<typename __combined<K0,K1>::type, V1>;
};

template<class K>
struct __combined<pythonic::types::empty_dict, indexable<K>>
{
    using type = indexable_dict<K>;
};

template<class K0, class V, class K1>
struct __combined<pythonic::types::dict<K0,V>, indexable<K1>>
{
    using type = pythonic::types::dict<typename __combined<K0,K1>::type, V>;
};

template<class K0, class V, class K1>
struct __combined<indexable<K1>, pythonic::types::dict<K0,V>>
{
    using type = pythonic::types::dict<typename __combined<K0,K1>::type, V>;
};

template< class K, class V>
struct __combined<pythonic::types::empty_dict, indexable_container<K,V>>
{
    using type = pythonic::types::dict<K,V>;
};

template< class K0, class V0, class K1, class V1>
struct __combined<pythonic::types::dict<K0,V0>, indexable_container<K1,V1>>
{
    using type = pythonic::types::dict<typename __combined<K0,K1>::type, typename __combined<V0,V1>::type>;
};

template< class K0, class V0, class K1, class V1>
struct __combined<indexable_container<K1,V1>, pythonic::types::dict<K0,V0>> {
    using type = pythonic::types::dict<typename __combined<K0,K1>::type, typename __combined<V0,V1>::type>;
};

template< class K, class V>
struct __combined<indexable_container<K,V>, pythonic::types::empty_dict>
{
    using type = pythonic::types::dict<K,V>;
};


template <class K, class V>
struct __combined<indexable<K>, dict_container<V>>
{
    using type = pythonic::types::dict<K,V>;
};

template <class V, class K>
struct __combined<dict_container<V>, indexable<K>>
{
    using type = pythonic::types::dict<K,V>;
};

template <class V, class K, class W>
struct __combined<dict_container<V>, indexable_container<K,W>>
{
    using type = pythonic::types::dict<K,typename __combined<V,W>::type>;
};

template <class V, class K, class W>
struct __combined<indexable_container<K,W>, dict_container<V>>
{
    using type = pythonic::types::dict<K,typename __combined<V,W>::type>;
};

template <class K, class V, class W>
struct __combined<pythonic::types::dict<K,V>, dict_container<W>>
{
    using type = pythonic::types::dict<K,typename __combined<V,W>::type>;
};

template <class V, class K, class W>
struct __combined<dict_container<W>, pythonic::types::dict<K,V>>
{
    using type = pythonic::types::dict<K,typename __combined<V,W>::type>;
};


template <class K, class V>
struct __combined<indexable_dict<K>, container<V>>
{
    using type = pythonic::types::dict<K,V>;
};

template <class K0, class K1>
struct __combined<indexable_dict<K0>, indexable<K1>>
{
    using type = indexable_dict<typename __combined<K0,K1>::type>;
};

template <class K0, class K1>
struct __combined<indexable<K0>, indexable_dict<K1>>
{
    using type = indexable_dict<typename __combined<K0,K1>::type>;
};

template <class V, class K>
struct __combined<container<V>, indexable_dict<K>>
{
    using type = pythonic::types::dict<K,V>;
};

/* } */
#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/register_once.hpp"
#include "pythonic/python/extract.hpp"
#include <boost/python/dict.hpp>
#include <boost/python/object.hpp>

namespace pythonic {

    template<typename K, typename V>
        struct python_to_pythran< types::dict<K,V> >
        {
            python_to_pythran();
            static void* convertible(PyObject* obj_ptr);
            static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data);
        };

    template<typename K, typename V>
        struct custom_pythran_dict_to_dict
        {
            static PyObject* convert(const types::dict<K,V>& v);
        };

    template<typename K, typename V>
        struct pythran_to_python< types::dict<K,V> >
        {
            pythran_to_python();
        };

    struct custom_empty_dict_to_dict
    {
        static PyObject* convert(types::empty_dict const &);
    };

    template<>
        struct pythran_to_python< types::empty_dict >
        {
            pythran_to_python();
        };

}

#endif

#endif
