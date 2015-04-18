#ifndef PYTHONIC_TYPES_DICT_HPP
#define PYTHONIC_TYPES_DICT_HPP

#include "pythonic/include/types/dict.hpp"

#include "pythonic/types/tuple.hpp"
#include "pythonic/types/empty_iterator.hpp"

#include "pythonic/utils/iterator.hpp"

#include "pythonic/__builtin__/None.hpp"

#include <memory>
#include <utility>
#include <limits>
#include <algorithm>
#include <iterator>
#include <boost/unordered_map.hpp>


namespace  pythonic {

    namespace types {

        /// key_iterator_adaptator implementation
        template<class I>
            key_iterator_adaptator<I>::key_iterator_adaptator() :
                I()
            {}

        template<class I>
            key_iterator_adaptator<I>::key_iterator_adaptator(I const &i):
                I(i)
            {}

        template<class I>
            typename key_iterator_adaptator<I>::value_type
            key_iterator_adaptator<I>::operator*()
            {
                return (*this)->first;
            }

        /// value_iterator_adaptator implementation
        template<class I>
            value_iterator_adaptator<I>::value_iterator_adaptator() :
                I()
            {}

        template<class I>
            value_iterator_adaptator<I>::value_iterator_adaptator(I const &i):
                I(i)
            {}

        template<class I>
            typename value_iterator_adaptator<I>::value_type
            value_iterator_adaptator<I>::operator*()
            {
                return (*this)->second;
            }

        template<class I>
            dict_iterator<I>::dict_iterator(I b, I e):
                _begin(b),
                _end(e)
            {}

        template<class I>
            typename dict_iterator<I>::iterator dict_iterator<I>::begin()
            {
                return _begin;
            }

        template<class I>
            typename dict_iterator<I>::iterator dict_iterator<I>::end()
            {
                return _end;
            }

        template<class D>
            dict_items<D>::dict_items()
            {}

        template<class D>
            dict_items<D>::dict_items(D const & d) :
                data(d)
            {}

        template<class D>
            typename dict_items<D>::iterator dict_items<D>::begin() const
            {
                return data.item_begin();
            }

        template<class D>
            typename dict_items<D>::iterator dict_items<D>::end() const
            {
                return data.item_end();
            }

        template<class D>
            dict_keys<D>::dict_keys()
            {}

        template<class D>
            dict_keys<D>::dict_keys(D const & d) :
                data(d)
            {}

        template<class D>
            typename dict_keys<D>::iterator dict_keys<D>::begin() const
            {
                return data.key_begin();
            }

        template<class D>
            typename dict_keys<D>::iterator dict_keys<D>::end() const
            {
                return data.key_end();
            }

        template<class D>
            dict_values<D>::dict_values()
            {}

        template<class D>
            dict_values<D>::dict_values(D const & d) :
                data(d)
            {}

        template<class D>
            typename dict_values<D>::iterator dict_values<D>::begin() const
            {
                return data.value_begin();
            }

        template<class D>
            typename dict_values<D>::iterator dict_values<D>::end() const
            {
                return data.value_end();
            }

        template<class K, class V>
            dict<K, V>::dict() :
                data(utils::no_memory())
            {}

        template<class K, class V>
            dict<K, V>::dict(empty_dict const &) :
                data(DEFAULT_DICT_CAPACITY)
            {}

        template<class K, class V>
            dict<K, V>::dict(std::initializer_list<value_type> l) :
                data(l.begin(), l.end())
            {}

        template<class K, class V>
            dict<K, V>::dict(dict<K,V> const & other) :
                data(other.data)
            {}

        template<class K, class V>
        template<class Kp, class Vp>
            dict<K, V>::dict(dict<Kp,Vp> const & other) :
                data(other.item_begin(), other.item_end())
            {}

        template<class K, class V>
        template<class B, class E>
            dict<K, V>::dict(B begin, E end) :
                data(begin, end)
            {}

                // iterators
        template<class K, class V>
            typename dict<K, V>::iterator dict<K, V>::begin()
            {
                return typename dict<K, V>::iterator(data->begin());
            }

        template<class K, class V>
            typename dict<K, V>::const_iterator dict<K, V>::begin() const
            {
                return key_iterator_adaptator<typename dict<K, V>::container_type::const_iterator>(data->begin());
            }

        template<class K, class V>
            typename dict<K, V>::iterator dict<K, V>::end()
            {
                return typename dict<K, V>::iterator(data->end());
            }

        template<class K, class V>
            typename dict<K, V>::const_iterator dict<K, V>::end() const
            {
                return key_iterator_adaptator<typename dict<K, V>::container_type::const_iterator>(data->end());
            }

        template<class K, class V>
            typename dict<K, V>::item_iterator dict<K, V>::item_begin()
            {
                return typename dict<K, V>::item_iterator(data->begin());
            }

        template<class K, class V>
            typename dict<K, V>::item_const_iterator dict<K, V>::item_begin() const
            {
                return typename dict<K, V>::item_const_iterator(data->begin());
            }

        template<class K, class V>
            typename dict<K, V>::item_iterator dict<K, V>::item_end()
            {
                return typename dict<K, V>::item_iterator(data->end());
            }

        template<class K, class V>
            typename dict<K, V>::item_const_iterator dict<K, V>::item_end() const
            {
                return typename dict<K, V>::item_const_iterator(data->end());
            }

        template<class K, class V>
            typename dict<K, V>::key_iterator dict<K, V>::key_begin()
            {
                return key_iterator_adaptator<typename dict<K, V>::container_type::iterator>(data->begin());
            }

        template<class K, class V>
            typename dict<K, V>::key_const_iterator dict<K, V>::key_begin() const
            {
                return key_iterator_adaptator<typename dict<K, V>::container_type::const_iterator>(data->begin());
            }

        template<class K, class V>
            typename dict<K, V>::key_iterator dict<K, V>::key_end()
            {
                return key_iterator_adaptator<typename dict<K, V>::container_type::iterator>(data->end());
            }

        template<class K, class V>
            typename dict<K, V>::key_const_iterator dict<K, V>::key_end() const
            {
                return key_iterator_adaptator<typename dict<K, V>::container_type::const_iterator>(data->end());
            }

        template<class K, class V>
            typename dict<K, V>::value_iterator dict<K, V>::value_begin()
            {
                return value_iterator_adaptator<typename dict<K, V>::container_type::iterator>(data->begin());
            }

        template<class K, class V>
            typename dict<K, V>::value_const_iterator dict<K, V>::value_begin() const
            {
                return value_iterator_adaptator<typename dict<K, V>::container_type::const_iterator> (data->begin());
            }

        template<class K, class V>
            typename dict<K, V>::value_iterator dict<K, V>::value_end()
            {
                return value_iterator_adaptator<typename dict<K, V>::container_type::iterator>(data->end());
            }

        template<class K, class V>
            typename dict<K, V>::value_const_iterator dict<K, V>::value_end() const
            {
                return value_iterator_adaptator<typename dict<K, V>::container_type::const_iterator>(data->end());
            }

        // dict interface
        template<class K, class V>
            dict<K, V>::operator bool()
            {
                return not data->empty();
            }

        template<class K, class V>
            V& dict<K, V>::operator[](K const & key)
            {
                return fast(key);
            }

        template<class K, class V>
            V const & dict<K, V>::operator[](K const & key) const
            {
                return fast(key);
            }

        template<class K, class V>
            V& dict<K, V>::fast(K const & key)
            {
                return (*data)[key];
            }

        template<class K, class V>
            V const & dict<K, V>::fast(K const & key) const
            {
                return (*data)[key];
            }

        template<class K, class V>
            typename dict<K, V>::item_const_iterator
            dict<K, V>::find(K const & key) const
            {
                return typename dict<K, V>::item_const_iterator(data->find(key));
            }

        template<class K, class V>
            void dict<K, V>::clear()
            {
                return data->clear();
            }

        template<class K, class V>
            dict<K,V> dict<K, V>::copy() const
            {
                return dict<K,V>(this->item_begin(), this->item_end());
            }

        template<class K, class V>
        template <class W>
            typename __combined<V, W>::type
            dict<K, V>::get(K const& key, W d) const
            {
                auto ivalue = data->find(key);
                if(ivalue != data->end())
                    return ivalue->second;
                else
                    return d;
            }

        template<class K, class V>
            none<V> dict<K, V>::get(K const& key) const
            {
                auto ivalue = data->find(key);
                if(ivalue != data->end())
                    return ivalue->second;
                else
                    return __builtin__::None;
            }

        template<class K, class V>
        template <class W>
            V& dict<K, V>::setdefault(K const& key, W d)
            {
                auto ivalue = data->find(key);
                if(ivalue != data->end())
                    return ivalue->second;
                else
                    return (*data)[key]=d;
            }

        template<class K, class V>
            none<V>& dict<K, V>::setdefault(K const& key)
            {
                auto ivalue = data->find(key);
                if(ivalue != data->end())
                    return ivalue->second;
                else
                    return (*data)[key] = __builtin__::None;
            }

        template<class K, class V>
        template<class K0, class W0>
            void dict<K, V>::update(dict<K0,W0> const & d)
            {
                for(auto kv : *d.data)
                    (*data)[kv.first] = kv.second;
            }

        template<class K, class V>
        template<class Iterable>
            void dict<K, V>::update(Iterable const & d)
            {
                for(auto kv : d)
                    (*data)[std::get<0>(kv)] = std::get<1>(kv);
            }

        template<class K, class V>
        template <class W>
            typename __combined<V,W>::type dict<K, V>::pop(K const& key, W d)
            {
                auto ivalue = data->find(key);
                if(ivalue != data->end())
                {
                    auto tmp = ivalue->second;
                    data->erase(ivalue);
                    return tmp;
                } else
                    return d;
            }

        template<class K, class V>
            V dict<K, V>::pop(K const& key)
            {
                auto ivalue = data->find(key);
                if(ivalue != data->end())
                {
                    auto tmp = ivalue->second;
                    data->erase(ivalue);
                    return tmp;
                } else
                    throw std::range_error("KeyError");
            }

        template<class K, class V>
            std::tuple<K,V> dict<K, V>::popitem()
            {
                auto b = data->begin();
                if(b == data->end())
                    throw std::range_error("KeyError");
                else {
                    auto r = *b;
                    data->erase(b);
                    return std::make_tuple(r.first, r.second);
                }
            }

        template<class K, class V>
            long dict<K, V>::size() const
            {
                return data->size();
            }

        template<class K, class V>
            dict_iterator<typename dict<K, V>::item_iterator>
            dict<K, V>::iteritems()
            {
                return dict_iterator<typename dict<K, V>::item_iterator>(item_begin(), item_end());
            }

        template<class K, class V>
            dict_iterator<typename dict<K, V>::item_const_iterator>
            dict<K, V>::iteritems() const
            {
                return dict_iterator<typename dict<K, V>::item_const_iterator>(item_begin(), item_end());
            }

        template<class K, class V>
            dict_iterator<typename dict<K, V>::key_iterator>
            dict<K, V>::iterkeys()
            {
                return dict_iterator<typename dict<K, V>::key_iterator>(key_begin(), key_end());
            }

        template<class K, class V>
            dict_iterator<typename dict<K, V>::key_const_iterator>
            dict<K, V>::iterkeys() const
            {
                return dict_iterator<typename dict<K, V>::key_const_iterator>(key_begin(), key_end());
            }

        template<class K, class V>
            dict_iterator<typename dict<K, V>::value_iterator>
            dict<K, V>::itervalues()
            {
                return dict_iterator<typename dict<K, V>::value_iterator>(value_begin(), value_end());
            }

        template<class K, class V>
            dict_iterator<typename dict<K, V>::value_const_iterator>
            dict<K, V>::itervalues() const
            {
                return dict_iterator<typename dict<K, V>::value_const_iterator>(value_begin(), value_end());
            }

        template<class K, class V>
            dict_items<dict<K,V>> dict<K, V>::viewitems() const
            {
                return dict_items<dict<K,V>>(*this);
            }

        template<class K, class V>
            dict_keys<dict<K,V>> dict<K, V>::viewkeys() const
            {
                return dict_keys<dict<K,V>>(*this);
            }

        template<class K, class V>
            dict_values<dict<K,V>> dict<K, V>::viewvalues() const
            {
                return dict_values<dict<K,V>>(*this);
            }

        // id interface
        template<class K, class V>
            intptr_t dict<K, V>::id() const
            {
                return reinterpret_cast<intptr_t>(&(*data));
            }

        template<class K, class V>
        template<class T>
            bool dict<K, V>::contains(T const& key) const
            {
                return data->find(key) != data->end();
            }

        template<class K, class V> 
            dict<K,V> empty_dict::operator+(dict<K,V> const & s)
            {
                return s;
            }

        empty_dict empty_dict::operator+(empty_dict const &)
        {
            return empty_dict();
        }

        empty_dict::operator bool() const
        {
            return false;
        }

        typename empty_dict::iterator empty_dict::begin() const
        {
            return empty_iterator();
        }

        typename empty_dict::iterator empty_dict::end() const
        {
            return empty_iterator();
        }

        template<class V>
            bool empty_dict::contains(V const&) const
            {
                return false;
            }

        template <class K, class V>
            dict<K, V> operator+(dict<K,V> const& d, empty_dict)
            {
                return d;
            }

    }

    std::ostream& operator<<(std::ostream& os, types::empty_dict const & )
    {
        return os << "{}";
    }

    template<class K, class V>
        std::ostream& operator<<(std::ostream& os, std::pair<K,V> const & p)
        {
            os << p.first << ": ";
            return os << p.second ;
        }

    template<class K, class V>
        std::ostream& operator<<(std::ostream& os, types::dict<K,V> const & v)
        {
            os << '{';
            auto iter = v.item_begin();
            if(iter != v.item_end())
            {
                auto niter = iter;
                ++niter;
                while(niter != v.item_end())
                {
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
        auto get(pythonic::types::dict<K,V>& d) -> decltype(d[I])
        {
            return d[I];
        }

    template <size_t I, class K, class V>
        auto get(pythonic::types::dict<K,V> const & d) -> decltype(d[I])
        {
            return d[I];
        }
}

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/register_once.hpp"
#include "pythonic/python/extract.hpp"
#include <boost/python/dict.hpp>
#include <boost/python/object.hpp>

namespace pythonic {

    template<typename K, typename V>
        python_to_pythran< types::dict<K,V> >::python_to_pythran()
        {
            python_to_pythran<K>();
            python_to_pythran<V>();
            static bool registered = false;
            if(not registered) {
                registered = true;
                boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id<types::dict<K,V> >());
            }
        }

    template<typename K, typename V>
        void* python_to_pythran< types::dict<K,V> >::convertible(PyObject* obj_ptr)
        {
            // the second condition is important, for some reason otherwise there were attempted conversions of Body to list which failed afterwards.
            if(!PyDict_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr,"__len__"))
                return 0;
            return obj_ptr;
        }

    template<typename K, typename V>
        void python_to_pythran< types::dict<K,V> >::construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data)
        {
            void* storage=((boost::python::converter::rvalue_from_python_storage<types::dict<K,V> >*)(data))->storage.bytes;
            new (storage) types::dict<K,V>(types::empty_dict());
            types::dict<K,V>& v=*(types::dict<K,V>*)(storage);

            PyObject *key, *value;
            Py_ssize_t pos = 0;
            /* first round use boost version that performs a lot of check
             * then we rely on faster but less secure version
             */
            if(PyDict_Next(obj_ptr, &pos, &key, &value))
            {
                v[boost::python::extract<K>(key)] = boost::python::extract<V>(value);
                while(PyDict_Next(obj_ptr, &pos, &key, &value))
                    v[extract<K>(key)] = extract<V>(value);
            }
            data->convertible=storage;
        }

    template<typename K, typename V>
        PyObject* custom_pythran_dict_to_dict<K, V>::convert(const types::dict<K,V>& v)
        {
            PyObject* ret = PyDict_New();
            for(auto kv=v.item_begin(); kv != v.item_end(); ++kv)
                PyDict_SetItem(ret, boost::python::incref(boost::python::object(kv->first).ptr()), boost::python::incref(boost::python::object(kv->second).ptr()));
            return ret;
        }

    template<typename K, typename V>
        pythran_to_python< types::dict<K,V> >::pythran_to_python()
        {
            pythran_to_python<K>();
            pythran_to_python<V>();
            register_once< types::dict<K,V>, custom_pythran_dict_to_dict<K,V> >();
        }

    PyObject* custom_empty_dict_to_dict::convert(types::empty_dict const &)
    {
        return PyDict_New();
    }

    pythran_to_python< types::empty_dict >::pythran_to_python()
    {
        register_once< types::empty_dict, custom_empty_dict_to_dict >();
    }

}

#endif

#endif
