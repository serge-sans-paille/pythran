#ifndef PYTHONIC_TYPES_SET_HPP
#define PYTHONIC_TYPES_SET_HPP

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

        struct empty_set;

        template<class T>
            class set {

                // data holder
                typedef  typename std::remove_cv< typename std::remove_reference<T>::type>::type  _type;
                typedef std::set< _type > container_type;
                utils::shared_ref<container_type> data; 

                public:

                template<class U> friend class set;

                // types
                typedef typename container_type::reference reference;
                typedef typename container_type::const_reference const_reference;
                typedef utils::comparable_iterator<typename container_type::iterator> iterator;
                typedef utils::comparable_iterator<typename container_type::const_iterator> const_iterator;
                typedef typename container_type::size_type size_type;
                typedef typename container_type::difference_type difference_type;
                typedef typename container_type::value_type value_type;
                typedef typename container_type::allocator_type allocator_type;
                typedef typename container_type::pointer pointer;
                typedef typename container_type::const_pointer const_pointer;
                typedef typename container_type::reverse_iterator reverse_iterator;
                typedef typename container_type::const_reverse_iterator const_reverse_iterator;

                // constructors
                set() : data(utils::no_memory()) {}
                template<class InputIterator>
                    set(InputIterator start, InputIterator stop) :  data() {
                        std::copy(start, stop, std::back_inserter(*this));
                    }
                set(empty_set const &) : data() {}
                set(std::initializer_list<value_type> l) : data(std::move(l)) {}
                set(set<T> const & other) : data(other.data) {}
                template<class F>
                    set(set<F> const & other) :  data(){
                        std::copy(other.begin(), other.end(), std::inserter(*data, data->begin()));
                    }

                // iterators
                iterator begin() { return data->begin(); }
                const_iterator begin() const { return data->begin(); }
                iterator end() { return data->end(); }
                const_iterator end() const { return data->end(); }
                reverse_iterator rbegin() { return data->rbegin(); }
                const_reverse_iterator rbegin() const { return data->rbegin(); }
                reverse_iterator rend() { return data->rend(); }
                const_reverse_iterator rend() const { return data->rend(); }


                // modifiers
                T pop() {
                    if(size()<=0)
                        throw std::out_of_range("Trying to pop() an empty set.");

                    T tmp=*begin();
                    data->erase(begin());
                    return tmp;
                }
                void add( const T& x) { data->insert(x); }
                void push_back( const T& x) { data->insert(x); }
                void clear() { data->clear(); };

                template<class U>
                    void discard(U const& elem){
                        //Remove element elem from the set if it is present.
                        data->erase(elem);
                    }

                template<class U>
                    void remove(U const& elem){
                        //Remove element elem from the set. Raises KeyError if elem is not contained in the set.
                        if(not data->erase(elem))
                            throw std::runtime_error("set.delete() : couldn't delete element not in the set.");
                    }

                // set interface
                operator bool() { return not data->empty(); }

                long size() const { return data->size(); }
                set<T> operator+(empty_set const &) { return copy(); }

                // Misc

                set<T> copy() const{
                    return set<T>(begin(), end());
                }


                template<class U>
                    bool isdisjoint(set<U> const & other) const {
                        //Return true if the this has no elements in common with other.
                        for(iterator it=begin(); it!=end(); ++it){
                            if(other.data->find(*it)!=other.end())
                                return false;
                        }
                        return true;
                    }

                template<class U>
                    bool issubset(set<U> const& other) const{
                        //Test whether every element in the set is in other.
                        for(iterator it=begin(); it!=end(); ++it){
                            if(not in(other, *it))
                                return false;
                        }
                        return true;
                    }

                template<class U>
                    bool issuperset(set<U> const& other) const{
                        //    Test whether every element in other is in the set.
                        return other.issubset(*this);
                    }

                set<T> union_() const{
                    return set<T>(begin(), end());
                }

                template<typename U, typename... Types> 
                    set<T> union_(U && other, Types &&... others) const{
                        set<T> tmp = union_(std::forward<Types...>(others)...);
                        tmp.data->insert(other.begin(), other.end());
                        return tmp;
                    }
                template<class U>
                    set<T> operator+(set<U> const &other) { return union_(other); }

                template<typename... Types> 
                    void update(Types &&... others) {
                        *this=union_(std::forward<Types>(others)...);
                    }

                set<T> intersection() const{
                    return set<T>(begin(), end());
                }

                template<typename U, typename... Types> 
                    set<T> intersection(U const& other, Types const&... others) const{
                        //Return a new set with elements common to the set and all others.
                        set<T> tmp = intersection(others...);
                        for(iterator it=tmp.begin(); it!=tmp.end();++it){
                            if(not in(other, *it))
                                tmp.discard(*it); //faster than remove() but not direct interaction with data
                        }
                        return tmp;
                    }


                template<typename... Types> 
                    void intersection_update(Types const&... others) {
                        *this=intersection(others...);
                    }

                set<T> difference() const{
                    return set<T>(begin(), end());
                }

                template<typename U, typename... Types> 
                    set<T> difference(U const& other, Types const&... others) const{
                        //Return a new set with elements in the set that are not in the others.
                        set<T> tmp = difference(others...);
                        /*
                           for(iterator it=tmp.begin(); it!=tmp.end();++it){
                           if(other.get_data().find(*it)!=other.end())
                           tmp.discard(*it);
                           }
                           *///This algo will do several times the same find(), because std::set::erase() calls find. Lame!
                        for(typename U::const_iterator it=other.begin(); it!=other.end();++it){
                            tmp.discard(*it);
                        }
                        return tmp;
                    }

                template <class V>
                    bool contains(V const& v) const {
                        return data->find(v) != data->end();
                    }

                template<typename... Types> 
                    void difference_update(Types const&... others) {
                        *this=difference(others...);
                    }

                template<typename U> 
                    set<T> symmetric_difference(set<U> const& other) const{
                        //Return a new set with elements in either the set or other but not both.
                        //return ((*this-other) | (other-*this));

                        //We must use fcts and not operators because fcts have to handle any itarable objects and operators only sets (cf pyhton ref)
                        return (this->difference(other)).union_(other.difference(*this));
                    }

                template<typename U> 
                    set<T> symmetric_difference(U const& other) const{
                        //Return a new set with elements in either the set or other but not both.
                        set<typename U::iterator::value_type> tmp(other.begin(), other.end());

                        //We must use fcts and not operators because fcts have to handle any itarable objects and operators only sets (cf pyhton ref)
                        return (this->difference(other)).union_(tmp.difference(*this));
                    }

                template<typename U> 
                    void symmetric_difference_update(U const& other) {
                        *this=symmetric_difference(other);
                    }

                // Operators
                template<class U>
                    bool operator==(set<U> const& other) const {
                        return *data == *other.data;
                    }

                template<class U>
                    bool operator<=(set<U> const& other) const {
                        // Every element in *this is in other
                        return issubset(other);
                    }

                template<class U>
                    bool operator<(set<U> const& other) const {
                        // Every element in this is in other and this != other
                        return (*this <= other) && (this->size() != other.size());
                    }

                template<class U>
                    bool operator>=(set<U> const& other) const {
                        // Every element in other is in set
                        return other <= *this;
                    }

                template<class U>
                    bool operator>(set<U> const& other) const {
                        // Every element in other is in set and this != other
                        return other < *this;
                    }

                template<class U>
                    set<T> operator|(set<U> const& other) const {
                        return union_(other);
                    }

                template<class U>
                    void operator|=(set<U> const& other) {
                        return update(other);
                    }

                template<class U>
                    set<T> operator&(set<U> const& other) const {
                        return intersection(other);
                    }

                template<class U>
                    void operator&=(set<U> const& other) {
                        return intersection_update(other);
                    }

                template<class U>
                    set<T> operator-(set<U> const& other) const {
                        return difference(other);
                    }

                template<class U>
                    void operator-=(set<U> const& other) {
                        return difference_update(other);
                    }

                template<class U>
                    set<T> operator^(set<U> const& other) const {
                        return symmetric_difference(other);
                    }

                template<class U>
                    void operator^=(set<U> const& other) {
                        return symmetric_difference_update(other);
                    }

                intptr_t id() const {
                    return reinterpret_cast<intptr_t>(&(*data));
                }
            };


        struct empty_set {

            typedef empty_iterator iterator;
            typedef empty_iterator const_iterator;

            template<class T> 
                set<T> operator+(set<T> const & s) { return s; }
            empty_set operator+(empty_set const &) { return empty_set(); }
            empty_set operator|(empty_set const &) { return empty_set(); }
            template<class T> 
                set<T> operator|(set<T> const & s) { return s; }
            empty_set operator&(empty_set const &) { return empty_set(); }
            template<class T> 
                empty_set operator&(set<T> const & s) { return empty_set(); }
            empty_set operator-(empty_set const &) { return empty_set(); }
            template<class T> 
                set<T> operator-(set<T> const & s) { return s; }
            empty_set operator^(empty_set const &) { return empty_set(); }
            template<class T> 
                set<T> operator^(set<T> const & s) { return s; }

            operator bool() { return false; }
            iterator begin() const { return empty_iterator(); }
            iterator end() const { return empty_iterator(); }
            template<class V>
                bool contains(V const&) const { return false;}
        };

    }

    template<class T>
        struct assignable<types::set<T> >{
            typedef types::set<typename assignable<T>::type > type;
        };

}
/* type inference stuff  {*/
#include "pythonic/types/combined.hpp"
template <class A, class B>
struct __combined<container<A> , pythonic::types::set<B> > {
    typedef pythonic::types::set<typename __combined<A,B>::type> type;
};
template <class A, class B>
struct __combined<pythonic::types::set<B> , container<A> > {
    typedef pythonic::types::set<typename __combined<A,B>::type> type;
};

template <class A, class B>
struct __combined<pythonic::types::list<A> , pythonic::types::set<B> > {
    typedef pythonic::types::set<typename __combined<A,B>::type> type;
};

template <class A, class B>
struct __combined<pythonic::types::set<B> , pythonic::types::list<A> > {
    typedef pythonic::types::set<typename __combined<A,B>::type> type;
};
template <class A>
struct __combined<pythonic::types::list<A> , pythonic::types::empty_set > {
    typedef pythonic::types::set<A> type;
};

template <class A>
struct __combined<pythonic::types::empty_set , pythonic::types::list<A> > {
    typedef pythonic::types::set<A> type;
};
template<class K>
struct __combined<indexable<K>, pythonic::types::empty_set> {
    typedef indexable<K> type;
};

template<class K>
struct __combined<pythonic::types::empty_set, indexable<K>> {
    typedef indexable<K> type;
};
template <class K, class V>
struct __combined<indexable<K>, pythonic::types::set<V>> {
    typedef pythonic::types::set<V> type;
};

template <class K, class V>
struct __combined<pythonic::types::set<V>, indexable<K>> {
    typedef pythonic::types::set<V> type;
};
template <class K, class V1, class V2>
struct __combined<indexable_container<K,V1>, pythonic::types::set<V2>> {
    typedef pythonic::types::set<decltype(std::declval<V1>()+std::declval<V2>())> type;
};

template <class K, class V1, class V2>
struct __combined<pythonic::types::set<V2>, indexable_container<K,V1>> {
    typedef pythonic::types::set<decltype(std::declval<V1>()+std::declval<V2>())> type;
};
template<class T0, class T1>
struct __combined<pythonic::types::set<T0>, pythonic::types::set<T1>> {
    typedef pythonic::types::set<typename __combined<T0,T1>::type> type;
};

/* } */

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/register_once.hpp"
#include <boost/python/extract.hpp>
#include <boost/python/object.hpp>

namespace pythonic {

    template<typename T>
        struct python_to_pythran< types::set<T> >{
            python_to_pythran(){
                python_to_pythran<T>();
                static bool registered =false;
                if(not registered) {
                    registered=true;
                    boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id<types::set<T> >());
                }
            }
            static void* convertible(PyObject* obj_ptr){
                // the second condition is important, for some reason otherwise there were attempted conversions of Body to list which failed afterwards.
                if(!PySet_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr,"__len__")) return 0;
                return obj_ptr;
            }
            static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
                void* storage=((boost::python::converter::rvalue_from_python_storage<types::set<T> >*)(data))->storage.bytes;
                new (storage) types::set<T>(types::empty_set());
                types::set<T>& v=*(types::set<T>*)(storage);
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
    template<typename T>
        struct custom_pythran_set_to_set{
            static PyObject* convert(const types::set<T>& v){
                PyObject* obj = PySet_New(nullptr);
                for(const T& e:v)
                    PySet_Add(obj, boost::python::incref(boost::python::object(e).ptr()));
                return obj;
            }
        };

    template<typename T>
        struct pythran_to_python< types::set<T> > {
            pythran_to_python() {
                pythran_to_python<T>();
                register_once< types::set<T>, custom_pythran_set_to_set<T> >();
            }
        };
    struct custom_empty_set_to_set {
        static PyObject* convert(types::empty_set const &) {
            PyObject* obj = PySet_New(nullptr);
            return obj;
        }
    };
    template<>
        struct pythran_to_python< types::empty_set > {
            pythran_to_python() { register_once< types::empty_set, custom_empty_set_to_set >(); }
        };

}

#endif

#endif
