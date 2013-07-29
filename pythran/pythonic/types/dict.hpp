#ifndef PYTHONIC_TYPES_DICT_HPP
#define PYTHONIC_TYPES_DICT_HPP

#include "pythonic/types/assignable.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/types/empty_iterator.hpp"
#include "pythonic/types/content_of.hpp"

#include "pythonic/utils/shared_ref.hpp"
#include "pythonic/utils/iterator.hpp"
#include "pythonic/utils/reserve.hpp"

#include "pythonic/__builtin__/None.hpp"

#include <map>
#include <memory>
#include <utility>
#include <limits>
#include <algorithm>
#include <iterator>
#include <boost/unordered_map.hpp>


namespace  pythonic {

    namespace types {

        static const size_t DEFAULT_DICT_CAPACITY = 64;

        struct empty_dict;

        template<class I>
            struct key_iterator_adaptator : I {
                typedef typename I::value_type::first_type  value_type;
                typedef typename I::value_type::first_type* pointer;
                typedef typename I::value_type::first_type& reference;
                key_iterator_adaptator() : I() {}
                key_iterator_adaptator(I const &i) : I(i) {}
                value_type operator*() { return (*this)->first; }
            };

        template<class I>
            struct value_iterator_adaptator : I {
                typedef typename I::value_type::second_type  value_type;
                typedef typename I::value_type::second_type* pointer;
                typedef typename I::value_type::second_type& reference;
                value_iterator_adaptator() : I() {}
                value_iterator_adaptator(I const &i) : I(i) {}
                value_type operator*() { return (*this)->second; }
            };

        template<class I>
            struct dict_iterator {
                typedef I iterator;
                I _begin;
                I _end;
                dict_iterator(I b, I e) : _begin(b), _end(e) {}
                iterator begin() { return _begin; }
                iterator end() { return _end; }
            };

        template<class D>
            struct dict_items {
                typedef typename D::item_const_iterator iterator;
                D data;
                dict_items() {}
                dict_items(D const & d) : data(d) {}
                iterator begin() const { return data.item_begin(); }
                iterator end() const { return data.item_end(); }
            };
        template<class D>
            struct dict_keys {
                typedef typename D::key_const_iterator iterator;
                D data;
                dict_keys(){};
                dict_keys(D const & d) : data(d) {}
                iterator begin() const { return data.key_begin(); }
                iterator end() const { return data.key_end(); }
            };
        template<class D>
            struct dict_values {
                typedef typename D::value_const_iterator iterator;
                D data;
                dict_values(){};
                dict_values(D const & d) : data(d) {}
                iterator begin() const { return data.value_begin(); }
                iterator end() const { return data.value_end(); }
            };

        template<class K, class V>
            class dict {

                // data holder
                typedef  typename std::remove_cv< typename std::remove_reference<K>::type>::type  _key_type;
                typedef  typename std::remove_cv< typename std::remove_reference<V>::type>::type  _value_type;
                typedef boost::unordered_map< _key_type, _value_type > container_type;
                utils::shared_ref<container_type> data; 


                public:

                // types
                typedef typename container_type::reference reference;
                typedef typename container_type::const_reference const_reference;
                typedef utils::comparable_iterator<key_iterator_adaptator<typename container_type::iterator> > iterator;
                typedef utils::comparable_iterator<key_iterator_adaptator<typename container_type::const_iterator> > const_iterator;
                typedef utils::comparable_iterator<typename container_type::iterator> item_iterator;
                typedef utils::comparable_iterator<typename container_type::const_iterator> item_const_iterator;
                typedef utils::comparable_iterator<key_iterator_adaptator<typename container_type::iterator> > key_iterator;
                typedef utils::comparable_iterator<key_iterator_adaptator<typename container_type::const_iterator> > key_const_iterator;
                typedef utils::comparable_iterator<value_iterator_adaptator<typename container_type::iterator> > value_iterator;
                typedef utils::comparable_iterator<value_iterator_adaptator<typename container_type::const_iterator> > value_const_iterator;
                typedef typename container_type::size_type size_type;
                typedef typename container_type::difference_type difference_type;
                typedef typename container_type::value_type value_type;
                typedef typename container_type::allocator_type allocator_type;
                typedef typename container_type::pointer pointer;
                typedef typename container_type::const_pointer const_pointer;

                // constructors
                dict() : data(utils::no_memory()) {}
                dict(empty_dict const &) : data(DEFAULT_DICT_CAPACITY) {}
                dict(std::initializer_list<value_type> l) : data(l.begin(), l.end()) {}
                dict(dict<K,V> const & other) : data(other.data) {}
                template<class Kp, class Vp>
                    dict(dict<Kp,Vp> const & other) : data(other.item_begin(), other.item_end()) {}
                template<class B, class E>
                    dict(B begin, E end) : data(begin, end) {}

                // iterators
                iterator begin() { return iterator(data->begin()); }
                const_iterator begin() const { return key_iterator_adaptator<typename container_type::const_iterator>(data->begin()); }
                iterator end() { return iterator(data->end()); }
                const_iterator end() const { return  key_iterator_adaptator<typename container_type::const_iterator>(data->end()); }
                item_iterator item_begin() { return item_iterator(data->begin()); }
                item_const_iterator item_begin() const { return item_const_iterator(data->begin()); }
                item_iterator item_end() { return item_iterator(data->end()); }
                item_const_iterator item_end() const { return item_const_iterator(data->end()); }
                key_iterator key_begin() { return key_iterator_adaptator<typename container_type::iterator>(data->begin()); }
                key_const_iterator key_begin() const { return key_iterator_adaptator<typename container_type::const_iterator>(data->begin()); }
                key_iterator key_end() { return key_iterator_adaptator<typename container_type::iterator>(data->end()); }
                key_const_iterator key_end() const { return key_iterator_adaptator<typename container_type::const_iterator>(data->end()); }
                value_iterator value_begin() { return value_iterator_adaptator<typename container_type::iterator>(data->begin()); }
                value_const_iterator value_begin() const { return value_iterator_adaptator<typename container_type::const_iterator> (data->begin()); }
                value_iterator value_end() { return value_iterator_adaptator<typename container_type::iterator>(data->end()); }
                value_const_iterator value_end() const { return value_iterator_adaptator<typename container_type::const_iterator>(data->end()); }

                // dict interface
                operator bool() { return not data->empty(); }
                V& operator[](K const & key) { return (*data)[key]; }
                V const & operator[](K const & key) const { return (*data)[key]; }

                item_const_iterator find(K const & key) const { return item_const_iterator(data->find(key)); }

                void clear() { return data->clear(); }

                dict<K,V> copy() const{
                    return dict<K,V>(this->item_begin(), this->item_end());
                }



                template <class W>
                    decltype(std::declval<V>()+std::declval<W>()) get(K const& key, W d) const {
                        auto ivalue = data->find(key);
                        if(ivalue != data->end()) return ivalue->second;
                        else return d;
                    }

                none<V> get(K const& key) const {
                    auto ivalue = data->find(key);
                    if(ivalue != data->end()) return ivalue->second;
                    else return __builtin__::None;
                }
                template <class W>
                    V& setdefault(K const& key, W d) {
                        auto ivalue = data->find(key);
                        if(ivalue != data->end()) return ivalue->second;
                        else {
                            return (*data)[key]=d;
                        }
                    }
                none<V>& setdefault(K const& key) {
                    auto ivalue = data->find(key);
                    if(ivalue != data->end()) return ivalue->second;
                    else {
                        return (*data)[key]=__builtin__::None;
                    }
                }
                template<class K0, class W0>
                    void update(dict<K0,W0> const & d) {
                        for(auto kv : *d.data)
                            (*data)[kv.first]=kv.second;
                    }
                template<class Iterable>
                    void update(Iterable const & d)  {
                        for(auto kv : d)
                            (*data)[std::get<0>(kv)]=std::get<1>(kv);
                    }

                template <class W>
                    decltype(std::declval<V>()+std::declval<W>()) pop(K const& key, W d) {
                        auto ivalue = data->find(key);
                        if(ivalue != data->end()) {
                            auto tmp = ivalue->second;
                            data->erase(ivalue);
                            return tmp;
                        }
                        else return d;
                    }
                V pop(K const& key) {
                    auto ivalue = data->find(key);
                    if(ivalue != data->end()) {
                        auto tmp = ivalue->second;
                        data->erase(ivalue);
                        return tmp;
                    }
                    else throw std::range_error("KeyError");
                }
                std::tuple<K,V> popitem() {
                    auto b = data->begin();
                    if(b == data->end())
                        throw std::range_error("KeyError");
                    else {
                        auto r = *b;
                        data->erase(b);
                        return std::make_tuple(r.first, r.second);
                    }
                }

                long size() const { return data->size(); }

                dict_iterator<item_iterator> iteritems() { return dict_iterator<item_iterator>(item_begin(), item_end()); }
                dict_iterator<item_const_iterator> iteritems() const { return dict_iterator<item_const_iterator>(item_begin(), item_end()); }

                dict_iterator<key_iterator> iterkeys() { return dict_iterator<key_iterator>(key_begin(), key_end()); }
                dict_iterator<key_const_iterator> iterkeys() const { return dict_iterator<key_const_iterator>(key_begin(), key_end()); }

                dict_iterator<value_iterator> itervalues() { return dict_iterator<value_iterator>(value_begin(), value_end()); }
                dict_iterator<value_const_iterator> itervalues() const { return dict_iterator<value_const_iterator>(value_begin(), value_end()); }

                dict_items<dict<K,V>> viewitems() const { return dict_items<dict<K,V>>(*this); }
                dict_keys<dict<K,V>> viewkeys() const { return dict_keys<dict<K,V>>(*this); }
                dict_values<dict<K,V>> viewvalues() const { return dict_values<dict<K,V>>(*this); }

                // type inference stuff
                template<class K_, class V_> 
                    dict<decltype(std::declval<K>()+std::declval<K_>()),decltype(std::declval<V>()+std::declval<V_>())> operator+(dict<K_,V_> const & ); 

                // id interface
                intptr_t id() const {
                    return reinterpret_cast<intptr_t>(&(*data));
                }
                template<class T>
                    bool contains(T const& key) const { return data->find(key) != data->end();}
            };

        struct empty_dict {

            typedef empty_iterator iterator;
            typedef empty_iterator const_iterator;

            template<class K, class V> 
                dict<K,V> operator+(dict<K,V> const & s) { return s; }
            empty_dict operator+(empty_dict const &) { return empty_dict(); }
            operator bool() const { return false; }
            iterator begin() const { return empty_iterator(); }
            iterator end() const { return empty_iterator(); }
            template<class V>
                bool contains(V const&) const { return false;}
        };
        template <class K, class V>
            dict<K, V> operator+(dict<K,V> const& d, empty_dict) {
                return d;
            }
        template<class K, class V>
            struct content_of< dict<K,V> > {
                typedef V type;
            };
    }

    template<class K,class V>
        struct assignable<types::dict<K,V> >{
            typedef types::dict<typename assignable<K>::type,typename assignable<V>::type > type;
        };

    std::ostream& operator<<(std::ostream& os, types::empty_dict const & ) {
        return os << "{}";
    }
    template<class K, class V>
        std::ostream& operator<<(std::ostream& os, std::pair<K,V> const & p) {
            os << p.first << ": ";
            return os << p.second ;
        }
    template<class K, class V>
        std::ostream& operator<<(std::ostream& os, types::dict<K,V> const & v) {
            os << '{';
            auto iter = v.item_begin();
            if(iter != v.item_end()) {
                auto niter = iter ; ++niter;
                while(niter != v.item_end()) {
                    os << *iter << ", ";
                    ++niter, ++iter;
                }
                os << *iter ;
            }
            return os << '}';
        }
}
/* overload std::get */
namespace std {
    template <size_t I, class K, class V>
        auto get( pythonic::types::dict<K,V>& d) -> decltype(d[I]) { return d[I]; }
    template <size_t I, class K, class V>
        auto get( pythonic::types::dict<K,V> const & d) -> decltype(d[I]) { return d[I]; }

    template <size_t I, class K, class V>
        struct tuple_element<I, pythonic::types::dict<K,V> > {
            typedef typename pythonic::types::dict<K,V>::value_type type;
        };
}

/* type inference stuff  {*/
#include "pythonic/types/combined.hpp"
#include "pythonic/types/list.hpp"

template <class A>
struct __combined<container<A> , pythonic::types::empty_dict > {
    typedef dict_container<A> type;
};
template <class A>
struct __combined<pythonic::types::empty_dict , container<A> > {
    typedef dict_container<A> type;
};
template <class A, class B, class C>
struct __combined<container<A> , pythonic::types::dict<C,B> > {
    typedef pythonic::types::dict<C, typename __combined<A,B>::type > type;
};

template <class A, class B, class C>
struct __combined<pythonic::types::dict<C,B> , container<A> > {
    typedef pythonic::types::dict<C, typename __combined<A,B>::type > type;
};
template <class T>
struct __combined<pythonic::types::empty_dict, pythonic::types::list<T>> {
    typedef pythonic::types::dict<typename std::tuple_element<0,T>::type, typename std::tuple_element<1,T>::type> type;
};
template <class T>
struct __combined<pythonic::types::list<T>, pythonic::types::empty_dict> {
    typedef pythonic::types::dict<typename std::tuple_element<0,T>::type, typename std::tuple_element<1,T>::type> type;
};
template <class K0, class V0, class T>
struct __combined<pythonic::types::dict<K0,V0> , pythonic::types::list<T> > {
    typedef pythonic::types::dict<typename __combined<K0,typename std::tuple_element<0,T>::type>::type, typename __combined<V0, typename std::tuple_element<1,T>::type>::type > type;
};

template <class K0, class V0, class T>
struct __combined<pythonic::types::list<T>, pythonic::types::dict<K0,V0>> {
    typedef pythonic::types::dict<typename __combined<K0,typename std::tuple_element<0,T>::type>::type, typename __combined<V0, typename std::tuple_element<1,T>::type>::type > type;
};
template<class K>
struct __combined<indexable<K>, pythonic::types::empty_dict> {
    typedef indexable_dict<K> type;
};

template<class K>
struct __combined<pythonic::types::empty_dict, indexable_dict<K>> {
    typedef indexable_dict<K> type;
};

template<class K>
struct __combined<indexable_dict<K>, pythonic::types::empty_dict> {
    typedef indexable_dict<K> type;
};

template<class K0, class K1, class V1>
struct __combined<pythonic::types::dict<K1,V1>, indexable_dict<K0>> {
    typedef pythonic::types::dict<typename __combined<K0,K1>::type, V1> type;
};

template<class K0, class K1, class V1>
struct __combined<indexable_dict<K0>, pythonic::types::dict<K1,V1>> {
    typedef pythonic::types::dict<typename __combined<K0,K1>::type, V1> type;
};

template<class K>
struct __combined<pythonic::types::empty_dict, indexable<K>> {
    typedef indexable_dict<K> type;
};

template<class K0, class V, class K1>
struct __combined<pythonic::types::dict<K0,V>, indexable<K1>> {
    typedef pythonic::types::dict<typename __combined<K0,K1>::type, V> type;
};

template<class K0, class V, class K1>
struct __combined<indexable<K1>, pythonic::types::dict<K0,V>> {
    typedef pythonic::types::dict<typename __combined<K0,K1>::type, V> type;
};
template< class K, class V>
struct __combined<pythonic::types::empty_dict, indexable_container<K,V>> {
    typedef pythonic::types::dict<K,V> type;
};

template< class K0, class V0, class K1, class V1>
struct __combined<pythonic::types::dict<K0,V0>, indexable_container<K1,V1>> {
    typedef pythonic::types::dict<typename __combined<K0,K1>::type, typename __combined<V0,V1>::type> type;
};

template< class K0, class V0, class K1, class V1>
struct __combined<indexable_container<K1,V1>, pythonic::types::dict<K0,V0>> {
    typedef pythonic::types::dict<typename __combined<K0,K1>::type, typename __combined<V0,V1>::type> type;
};

template< class K, class V>
struct __combined<indexable_container<K,V>, pythonic::types::empty_dict> {
    typedef pythonic::types::dict<K,V> type;
};


template <class K, class V>
struct __combined<indexable<K>, dict_container<V>> {
    typedef pythonic::types::dict<K,V> type;
};

template <class V, class K>
struct __combined<dict_container<V>, indexable<K>> {
    typedef pythonic::types::dict<K,V> type;
};

template <class V, class K, class W>
struct __combined<dict_container<V>, indexable_container<K,W>> {
    typedef pythonic::types::dict<K,typename __combined<V,W>::type> type;
};

template <class V, class K, class W>
struct __combined<indexable_container<K,W>, dict_container<V>> {
    typedef pythonic::types::dict<K,typename __combined<V,W>::type> type;
};

template <class K, class V, class W>
struct __combined<pythonic::types::dict<K,V>, dict_container<W>> {
    typedef pythonic::types::dict<K,typename __combined<V,W>::type> type;
};

template <class V, class K, class W>
struct __combined<dict_container<W>, pythonic::types::dict<K,V>> {
    typedef pythonic::types::dict<K,typename __combined<V,W>::type> type;
};


template <class K, class V>
struct __combined<indexable_dict<K>, container<V>> {
    typedef pythonic::types::dict<K,V> type;
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
    typedef pythonic::types::dict<K,V> type;
};

/* } */
#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/register_once.hpp"
#include <boost/python/dict.hpp>
#include <boost/python/object.hpp>

namespace pythonic {

    template<typename K, typename V>
        struct python_to_pythran< types::dict<K,V> >{
            python_to_pythran(){
                python_to_pythran<K>();
                python_to_pythran<V>();
                static bool registered =false;
                if(not registered) {
                    registered=true;
                    boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id<types::dict<K,V> >());
                }
            }
            static void* convertible(PyObject* obj_ptr){
                // the second condition is important, for some reason otherwise there were attempted conversions of Body to list which failed afterwards.
                if(!PyDict_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr,"__len__")) return 0;
                return obj_ptr;
            }
            static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
                void* storage=((boost::python::converter::rvalue_from_python_storage<types::dict<K,V> >*)(data))->storage.bytes;
                new (storage) types::dict<K,V>(types::empty_dict());
                types::dict<K,V>& v=*(types::dict<K,V>*)(storage);

                PyObject *key, *value;
                Py_ssize_t pos = 0;
                while(PyDict_Next(obj_ptr, &pos, &key, &value)) {
                    v[boost::python::extract<K>(key)]=boost::python::extract<V>(value);
                }
                data->convertible=storage;
            }
        };
    template<typename K, typename V>
        struct custom_pythran_dict_to_dict{
            static PyObject* convert(const types::dict<K,V>& v){
                PyObject* ret = PyDict_New();
                for(auto kv=v.item_begin(); kv != v.item_end(); ++kv)
                    PyDict_SetItem(ret, boost::python::incref(boost::python::object(kv->first).ptr()), boost::python::incref(boost::python::object(kv->second).ptr()));
                return ret;
            }
        };

    template<typename K, typename V>
        struct pythran_to_python< types::dict<K,V> > {
            pythran_to_python() {
                pythran_to_python<K>();
                pythran_to_python<V>();
                register_once< types::dict<K,V>, custom_pythran_dict_to_dict<K,V> >();
            }
        };
    struct custom_empty_dict_to_dict {
        static PyObject* convert(types::empty_dict const &) {
            boost::python::dict ret;
            return boost::python::incref(ret.ptr());
        }
    };
    template<>
        struct pythran_to_python< types::empty_dict > {
            pythran_to_python() { register_once< types::empty_dict, custom_empty_dict_to_dict >(); }
        };

}

#endif


#endif
