#ifndef PYTHONIC_TYPES_SET_HPP
#define PYTHONIC_TYPES_SET_HPP

#include "pythonic/include/types/set.hpp"

#include "pythonic/types/assignable.hpp"
#include "pythonic/types/empty_iterator.hpp"
#include "pythonic/types/list.hpp"

#include "pythonic/utils/shared_ref.hpp"
#include "pythonic/utils/iterator.hpp"

#include "pythonic/__builtin__/in.hpp"

#include <set>
#include <memory>
#include <utility>
#include <limits>
#include <algorithm>
#include <iterator>

namespace pythonic {

    namespace types {

        /// set implementation
        // constructors
        template<class T>
            set<T>::set() :
                data(utils::no_memory())
            {}

        template<class T>
        template<class InputIterator>
            set<T>::set(InputIterator start, InputIterator stop) :
                data()
            {
                std::copy(start, stop, std::back_inserter(*this));
            }

        template<class T>
            set<T>::set(empty_set const &) :
                data()
            {}

        template<class T>
            set<T>::set(std::initializer_list<value_type> l) :
                data(std::move(l))
            {}

        template<class T>
            set<T>::set(set<T> const & other) :
                data(other.data)
            {}

        template<class T>
        template<class F>
            set<T>::set(set<F> const & other) :
                data()
            {
                std::copy(other.begin(), other.end(), std::inserter(*data, data->begin()));
            }

        // iterators
        template<class T>
            typename set<T>::iterator set<T>::begin()
            {
                return data->begin();
            }

        template<class T>
            typename set<T>::const_iterator set<T>::begin() const
            {
                return data->begin();
            }

        template<class T>
            typename set<T>::iterator set<T>::end()
            {
                return data->end();
            }

        template<class T>
            typename set<T>::const_iterator set<T>::end() const
            {
                return data->end();
            }

        template<class T>
            typename set<T>::reverse_iterator set<T>::rbegin()
            {
                return data->rbegin();
            }

        template<class T>
            typename set<T>::const_reverse_iterator set<T>::rbegin() const
            {
                return data->rbegin();
            }

        template<class T>
            typename set<T>::reverse_iterator set<T>::rend()
            {
                return data->rend();
            }

        template<class T>
            typename set<T>::const_reverse_iterator set<T>::rend() const
            {
                return data->rend();
            }

        // modifiers
        template<class T>
            T set<T>::pop()
            {
                if(size()<=0)
                    throw std::out_of_range("Trying to pop() an empty set.");

                T tmp = *begin();
                data->erase(begin());
                return tmp;
            }

        template<class T>
            void set<T>::add( const T& x)
            {
                data->insert(x);
            }

        template<class T>
            void set<T>::push_back( const T& x) 
            {
                data->insert(x);
            }

        template<class T>
            void set<T>::clear()
            {
                data->clear();
            }

        template<class T>
        template<class U>
            void set<T>::discard(U const& elem)
            {
                //Remove element elem from the set if it is present.
                data->erase(elem);
            }

        template<class T>
        template<class U>
            void set<T>::remove(U const& elem)
            {
                //Remove element elem from the set. Raises KeyError if elem is not contained in the set.
                if(not data->erase(elem))
                    throw std::runtime_error("set.delete() : couldn't delete element not in the set.");
            }

        // set interface
        template<class T>
            set<T>::operator bool() const
            {
                return not data->empty();
            }

        template<class T>
            long set<T>::size() const
            {
                return data->size();
            }

        // Misc

        template<class T>
            set<T> set<T>::copy() const
            {
                return set<T>(begin(), end());
            }

        template<class T>
        template<class U>
            bool set<T>::isdisjoint(U const & other) const
            {
                //Return true if the this has no elements in common with other.
                for(iterator it=begin(); it!=end(); ++it)
                {
                    if(in(other, *it))
                        return false;
                }
                return true;
            }

        template<class T>
        template<class U>
            bool set<T>::issubset(U const& other) const
            {
                //Test whether every element in the set is in other.
                for(iterator it=begin(); it!=end(); ++it)
                {
                    if(not in(other, *it))
                        return false;
                }
                return true;
            }

        template<class T>
        template<class U>
            bool set<T>::issuperset(U const& other) const
            {
                // Test whether every element in other is in the set.
                return other.issubset(*this);
            }

        template<class T>
            set<T> set<T>::union_() const
            {
                return set<T>(begin(), end());
            }

        template<class T>
        template<typename U, typename... Types>
            typename __combined<set<T>, U, Types...>::type
            set<T>::union_(U && other, Types &&... others) const
            {
                typename __combined<set<T>, U, Types...>::type tmp = union_(std::forward<Types...>(others)...);
                tmp.data->insert(other.begin(), other.end());
                return tmp;
            }

        template<class T>
        template<typename... Types>
            void set<T>::update(Types &&... others)
            {
                *this = union_(std::forward<Types>(others)...);
            }

        template<class T>
            set<T> set<T>::intersection() const
            {
                return set<T>(begin(), end());
            }

        template<class T>
        template<typename U, typename... Types>
            typename __combined<set<T>, U, Types...>::type
            set<T>::intersection(U const& other, Types const&... others) const
            {
                //Return a new set with elements common to the set and all others.
                typename __combined<set<T>, U, Types...>::type tmp = intersection(others...);
                for(auto it=tmp.begin(); it!=tmp.end();++it)
                {
                    if(not in(other, *it))
                        tmp.discard(*it); //faster than remove() but not direct interaction with data
                }
                return tmp;
            }

        template<class T>
        template<typename... Types>
            void set<T>::intersection_update(Types const&... others)
            {
                *this = intersection(others...);
            }

        template<class T>
            set<T> set<T>::difference() const
            {
                return set<T>(begin(), end());
            }

        template<class T>
        template<typename U, typename... Types>
            set<T>
            set<T>::difference(U const& other, Types const&... others) const
            {
                //Return a new set with elements in the set that are not in the others.
                set<T> tmp = difference(others...);
                /*
                   for(iterator it=tmp.begin(); it!=tmp.end();++it){
                   if(other.get_data().find(*it)!=other.end())
                   tmp.discard(*it);
                   }
                   *///This algo will do several times the same find(), because std::set::erase() calls find. Lame!
                for(typename U::const_iterator it=other.begin(); it!=other.end();++it)
                {
                    tmp.discard(*it);
                }
                return tmp;
            }

        template<class T>
        template <class V>
            bool set<T>::contains(V const& v) const
            {
                return data->find(v) != data->end();
            }

        template<class T>
        template<typename... Types>
            void set<T>::difference_update(Types const&... others)
            {
                *this=difference(others...);
            }

        template<class T>
        template<typename U>
            set<typename __combined<T, U>::type>
            set<T>::symmetric_difference(set<U> const& other) const
            {
                //Return a new set with elements in either the set or other but not both.
                //return ((*this-other) | (other-*this));

                //We must use fcts and not operators because fcts have to handle any iterable objects and operators only sets (cf python ref)
                return (this->difference(other)).union_(other.difference(*this));
            }

        template<class T>
        template<typename U>
            typename __combined<U, set<T>>::type
            set<T>::symmetric_difference(U const& other) const
            {
                //Return a new set with elements in either the set or other but not both.
                set<typename U::iterator::value_type> tmp(other.begin(), other.end());

                //We must use fcts and not operators because fcts have to handle any iterable objects and operators only sets (cf python ref)
                return (this->difference(other)).union_(tmp.difference(*this));
            }

        template<class T>
        template<typename U>
            void set<T>::symmetric_difference_update(U const& other)
            {
                *this=symmetric_difference(other);
            }

        // Operators
        template<class T>
        template<class U>
            bool set<T>::operator==(set<U> const& other) const
            {
                return *data == *other.data;
            }

        template<class T>
        template<class U>
            bool set<T>::operator<=(set<U> const& other) const
            {
                // Every element in *this is in other
                return issubset(other);
            }

        template<class T>
        template<class U>
            bool set<T>::operator<(set<U> const& other) const
            {
                // Every element in this is in other and this != other
                return (*this <= other) && (this->size() != other.size());
            }

        template<class T>
        template<class U>
            bool set<T>::operator>=(set<U> const& other) const
            {
                // Every element in other is in set
                return other <= *this;
            }

        template<class T>
        template<class U>
            bool set<T>::operator>(set<U> const& other) const
            {
                // Every element in other is in set and this != other
                return other < *this;
            }

        template<class T>
        template<class U>
            set<typename __combined<T, U>::type>
            set<T>::operator|(set<U> const& other) const 
            {
                return union_(other);
            }

        template<class T>
        template<class U>
            void set<T>::operator|=(set<U> const& other)
            {
                return update(other);
            }

        template<class T>
        template<class U>
            set<typename __combined<U, T>::type>
            set<T>::operator&(set<U> const& other) const
            {
                return intersection(other);
            }

        template<class T>
        template<class U>
            void set<T>::operator&=(set<U> const& other)
            {
                return intersection_update(other);
            }

        template<class T>
        template<class U>
            set<T> set<T>::operator-(set<U> const& other) const
            {
                return difference(other);
            }

        template<class T>
        template<class U>
            void set<T>::operator-=(set<U> const& other)
            {
                return difference_update(other);
            }

        template<class T>
        template<class U>
            set<typename __combined<U, T>::type>
            set<T>::operator^(set<U> const& other) const
            {
                return symmetric_difference(other);
            }

        template<class T>
        template<class U>
            void set<T>::operator^=(set<U> const& other)
            {
                return symmetric_difference_update(other);
            }

        template<class T>
            intptr_t set<T>::id() const
            {
                return reinterpret_cast<intptr_t>(&(*data));
            }

        template<class T>
            std::ostream& operator<<(std::ostream& os, set<T> const & v)
            {
                os << "set([";
                const char *commaSeparator = "";
                for(const auto &e : v) {
                    os << commaSeparator << e;
                    commaSeparator = ", ";
                }
                return os << "])";
            }


        /// empty_set implementation

        empty_set empty_set::operator|(empty_set const &)
        {
            return empty_set();
        }

        template<class T>
            set<T> empty_set::operator|(set<T> const & s)
            {
                return s;
            }

        template<class U>
            empty_set empty_set::operator&(U const & s)
            {
                return empty_set();
            }

        template<class U>
            empty_set empty_set::operator-(U const & s)
            {
                return empty_set();
            }

        empty_set empty_set::operator^(empty_set const &)
        {
            return empty_set();
        }

        template<class T>
            set<T> empty_set::operator^(set<T> const & s)
            {
                return s;
            }

        template<class... Types>
            void empty_set::update(Types&&...)
            {}

        empty_set::operator bool()
        {
            return false;
        }

        empty_set::iterator empty_set::begin() const
        {
            return empty_iterator();
        }

        empty_set::iterator empty_set::end() const
        {
            return empty_iterator();
        }

        template<class V>
            bool empty_set::contains(V const&) const
            {
                return false;
            }

    }

}

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/register_once.hpp"
#include "pythonic/python/extract.hpp"
#include <boost/python/object.hpp>

namespace pythonic {

    template<typename T>
        python_to_pythran< types::set<T> >::python_to_pythran()
        {
            python_to_pythran<T>();
            static bool registered =false;
            if(not registered)
            {
                registered=true;
                boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id<types::set<T> >());
            }
        }

    template<typename T>
        void* python_to_pythran< types::set<T> >::convertible(PyObject* obj_ptr)
        {
            // the second condition is important, for some reason otherwise there were attempted conversions of Body to list which failed afterwards.
            if(!PySet_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr,"__len__"))
                return 0;
            return obj_ptr;
        }

    template<typename T>
        void python_to_pythran< types::set<T> >::construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data)
        {
            void* storage=((boost::python::converter::rvalue_from_python_storage<types::set<T> >*)(data))->storage.bytes;
            new (storage) types::set<T>(types::empty_set());
            types::set<T>& v=*(types::set<T>*)(storage);
            // may be useful to reserve more space ?
            PyObject *iterator = PyObject_GetIter(obj_ptr);

            /* first round use boost extractor that performs a lot of checks
             * next we use our cutom one that goes faster
             */
            if(PyObject *item = PyIter_Next(iterator))
            {
                v.add(boost::python::extract<T>(item));
                Py_DECREF(item);
                while((item = PyIter_Next(iterator)))
                {
                    v.add(extract<T>(item));
                    Py_DECREF(item);
                }
            }
            Py_DECREF(iterator);
            data->convertible=storage;
        }

    template<typename T>
        PyObject* custom_pythran_set_to_set<T>::convert(const types::set<T>& v)
        {
            PyObject* obj = PySet_New(nullptr);
            for(const T& e:v)
                PySet_Add(obj, boost::python::incref(boost::python::object(e).ptr()));
            return obj;
        }

    template<typename T>
        pythran_to_python< types::set<T> >::pythran_to_python()
        {
            pythran_to_python<T>();
            register_once< types::set<T>, custom_pythran_set_to_set<T> >();
        }

    PyObject* custom_empty_set_to_set::convert(types::empty_set const &)
    {
        PyObject* obj = PySet_New(nullptr);
        return obj;
    }

    pythran_to_python< types::empty_set >::pythran_to_python()
    {
        register_once< types::empty_set, custom_empty_set_to_set >();
    }

}

#endif

#endif
