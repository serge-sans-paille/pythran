#ifndef PYTHONIC_DICT_H
#define PYTHONIC_DICT_H
#include <map>
#include <memory>
#include <utility>
#include <limits>
#include <algorithm>
#include <iterator>
//#include <unordered_map>
#include <boost/unordered_map.hpp>
#include "shared_ref.h"

namespace  pythonic {


    /* the container type */
    namespace core {

        static const size_t DEFAULT_DICT_SIZE = 64;

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
                impl::shared_ref<container_type> data; 


                public:

                // types
                typedef typename container_type::reference reference;
                typedef typename container_type::const_reference const_reference;
                typedef comparable_iterator<key_iterator_adaptator<typename container_type::iterator> > iterator;
                typedef comparable_iterator<key_iterator_adaptator<typename container_type::const_iterator> > const_iterator;
                typedef comparable_iterator<typename container_type::iterator> item_iterator;
                typedef comparable_iterator<typename container_type::const_iterator> item_const_iterator;
                typedef comparable_iterator<key_iterator_adaptator<typename container_type::iterator> > key_iterator;
                typedef comparable_iterator<key_iterator_adaptator<typename container_type::const_iterator> > key_const_iterator;
                typedef comparable_iterator<value_iterator_adaptator<typename container_type::iterator> > value_iterator;
                typedef comparable_iterator<value_iterator_adaptator<typename container_type::const_iterator> > value_const_iterator;
                typedef typename container_type::size_type size_type;
                typedef typename container_type::difference_type difference_type;
                typedef typename container_type::value_type value_type;
                typedef typename container_type::allocator_type allocator_type;
                typedef typename container_type::pointer pointer;
                typedef typename container_type::const_pointer const_pointer;

                // constructors
                dict() : data(impl::no_memory()) {}
                dict(empty_dict const &) : data(DEFAULT_DICT_SIZE) {}
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
                    return core::dict<K,V>(this->item_begin(), this->item_end());
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
                    void update(core::dict<K0,W0> const & d) {
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

                dict_items<core::dict<K,V>> viewitems() const { return dict_items<core::dict<K,V>>(*this); }
                dict_keys<core::dict<K,V>> viewkeys() const { return dict_keys<core::dict<K,V>>(*this); }
                dict_values<core::dict<K,V>> viewvalues() const { return dict_values<core::dict<K,V>>(*this); }

                // type inference stuff
                template<class K_, class V_> 
                    dict<decltype(std::declval<K>()+std::declval<K_>()),decltype(std::declval<V>()+std::declval<V_>())> operator+(dict<K_,V_> const & ); 
            };

        struct empty_dict {

            template<class K, class V> 
                dict<K,V> operator+(dict<K,V> const & s) { return s; }
            empty_dict operator+(empty_dict const &) { return empty_dict(); }
            operator bool() const { return false; }
        };
        template <class K, class V>
            core::dict<K, V> operator+(core::dict<K,V> const& d, core::empty_dict) {
                return d;
            }
    }
}

/* overload std::get */
namespace std {
    template <size_t I, class K, class V>
        auto get( pythonic::core::dict<K,V>& d) -> decltype(d[I]) { return d[I]; }
    template <size_t I, class K, class V>
        auto get( pythonic::core::dict<K,V> const & d) -> decltype(d[I]) { return d[I]; }

    template <size_t I, class K, class V>
        struct tuple_element<I, pythonic::core::dict<K,V> > {
            typedef typename pythonic::core::dict<K,V>::value_type type;
        };
}
#endif
