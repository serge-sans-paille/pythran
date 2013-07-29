#ifndef PYTHONIC_TYPES_LIST_HPP
#define PYTHONIC_TYPES_LIST_HPP

#include "pythonic/types/assignable.hpp"
#include "pythonic/types/empty_iterator.hpp"
#include "pythonic/utils/shared_ref.hpp"
#include "pythonic/utils/reserve.hpp"
#include "pythonic/types/slice.hpp"

#include <cassert>
#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <limits>
#include <algorithm>
#include <iterator>


namespace pythonic {

    namespace types {

        static const size_t DEFAULT_LIST_CAPACITY = 16;

        /* forward declaration */
        struct empty_list;
        template<class T> class list;
        template<class T> class list_view;

        /* for type disambiguification */
        struct single_value {};

        /* list view */
        template<class T>
            class list_view {

                // data holder
                typedef  typename std::remove_cv< typename std::remove_reference<T>::type>::type  _type;
                typedef std::vector< _type > container_type;
                utils::shared_ref<container_type> data; 

                template<class U>
                    friend class list;

                normalized_slice slicing;

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

                // constructor
                list_view(): data(utils::no_memory()) {}
                list_view(list_view<T> const & s): data(s.data), slicing(s.slicing) {}
                list_view(list<T> & other, slice const & s) : data(other.data), slicing(s.normalize(other.size())) {}

                // assignment
                list_view& operator=(list<T> const & );
                list_view& operator=(list_view<T> const & );
                list<T> operator+(list<T> const & );
                list<T> operator+(list_view<T> const & );

                // iterators
                iterator begin() { assert(slicing.step==1) ; return data->begin()+slicing.lower; }
                const_iterator begin() const { assert(slicing.step==1) ; return data->begin()+slicing.lower; }
                iterator end() { assert(slicing.step==1) ; return data->begin()+slicing.upper; }
                const_iterator end() const { assert(slicing.step==1) ; return data->begin()+slicing.upper; }

                // size
                size_type size() const { return slicing.size(); }

                // accessor
                T const & operator[](long i) const { return (*data)[slicing.lower + i*slicing.step];}
                T & operator[](long i) { return (*data)[slicing.lower + i*slicing.step];}

                // comparison
                template <class K>
                    bool operator==(list<K> const & other) const {
                        if(size()!=other.size()) return false;
                        return std::equal(begin(),end(),other.begin());
                    }
                bool operator==(empty_list const& other) const {
                    return size() == 0;
                }
            };

        /* list */
        template<class T>
            class list {

                // data holder
                typedef  typename std::remove_cv< typename std::remove_reference<T>::type>::type  _type;
                typedef std::vector< _type > container_type;
                utils::shared_ref<container_type> data; 

                template<class U>
                    friend class list_view;

                template<class U>
                    friend class list;

                public:

                // types
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


                // constructors
                list() : data(utils::no_memory()) {}
                template<class InputIterator>
                    list(InputIterator start, InputIterator stop) : data() {
                        data->reserve(DEFAULT_LIST_CAPACITY);
                        std::copy(start, stop, std::back_inserter(*data));
                    }
                list(empty_list const&) :data(0) {}
                list(size_type sz) :data(sz) {}
                list(T const& value, single_value) : data(1) { (*data)[0] = value; }
                list(std::initializer_list<T> l) : data(std::move(l)) {}
                list(list<T> && other) : data(std::move(other.data)) {}
                list(list<T> const & other) : data(other.data) {}
                template<class F>
                    list(list<F> const & other) : data(other.size()) {
                        std::copy(other.begin(), other.end(), begin());
                    }
#if 0
                template<class... Types>
                    list(std::tuple<Types...> const& t) : data(sizeof...(Types)) {
                        tuple_dump(t, *this, int_<sizeof...(Types)-1>());
                    }
#endif
                list(list_view<T> const & other) : data( other.begin(), other.end()) {}

                list<T>& operator=(list<T> && other) {
                    data=std::move(other.data);
                    return *this;
                }
                list<T>& operator=(list<T> const & other) {
                    data=other.data;
                    return *this;
                }
                list<T>& operator=(empty_list const & ) {
                    data=utils::shared_ref<container_type>();
                    return *this;
                }

                list<T>& operator=(list_view<T> const & other) {
                    if(other.data == data ) {
                        auto it = std::copy(other.begin(), other.end(), data->begin());
                        data->resize(it - data->begin());
                    }
                    else {
                        data=utils::shared_ref<T>(other.begin(),other.end());
                    }
                    return *this;
                }
                list<T>& operator+=(list_view<T> const & other) {
                    data->resize(data->size() + other.size());
                    std::copy(other.begin(), other.end(), data->begin());
                    return *this;
                }
                list<T> operator+(list_view<T> const & other) const {
                    list<T> new_list(begin(), end());
                    new_list.reserve(data->size() + other.size());
                    std::copy(other.begin(), other.end(), std::back_inserter(new_list));
                    return new_list;
                }

                // io

                /* list */

                friend std::ostream& operator<<(std::ostream& os, list<T> const & v) {
                    os << '[';
                    auto iter = v.begin();
                    if(iter != v.end()) {
                        while(iter+1 != v.end())
                            os << *iter++ << ", ";
                        os << *iter;
                    }
                    return os << ']';
                }

                // comparison
                template <class K>
                    bool operator==(list<K> const & other) const {
                        if(size()!=other.size()) return false;
                        return std::equal(begin(),end(),other.begin());
                    }
                bool operator==(empty_list const&) const {
                    return size() == 0;
                }
                template <class K>
                    bool operator!=(list<K> const & other) const {
                        return !operator==(other);
                    }
                bool operator!=(empty_list const&) const {
                    return size() != 0;
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

                // comparison
                int operator<(list<T> const& other) const {
                    auto other_iter = other.begin();
                    auto self_iter = begin();
                    for(; other_iter != other.end() and self_iter != end(); ++other_iter, ++self_iter) {
                        if( *other_iter < *self_iter ) return 1;
                        if( *other_iter > *self_iter ) return -1;
                    }
                    if(other_iter !=other.end() and self_iter == end()) return 1;
                    if(other_iter ==other.end() and self_iter != end()) return -1;
                    return 0;
                }

                // element access
                reference operator[]( long n ) {
                    return (*data)[(n>=0)?n : (data->size() + n)];
                }
                const_reference operator[]( long n ) const {
                    return (*data)[(n>=0)?n : (data->size() + n)];
                }
                const_reference at( long n ) const {
                    return (*data)[n];
                }

                list<T> operator[]( slice const &s ) const {
                    normalized_slice norm = s.normalize(size());
                    list<T> out(norm.size());
                    for(long i = 0; i < out.size() ; i++)
                        out[i] = (*data)[norm.lower + i * norm.step];
                    return out;
                }

                list_view<T> operator()( slice const &s) const {
                    return list_view<T>(*const_cast<list<T>*>(this), s); // SG: ugly !
                }

                // modifiers
                void push_back( T const & x) { data->push_back(x); }
                void insert(size_t i, T const & x) {
                    if(i==size()) data->push_back(x);
                    else data->insert(data->begin()+i, x);
                }

                void reserve(size_t n) { data->reserve(n); }
                void resize(size_t n) { data->resize(n); }
                iterator erase(size_t n) { return data->erase(data->begin()+n); }

                T pop(long x = -1) {
                    x = x%size();
                    if (x<0) x+=size();
                    T res = (*this)[x];
                    erase(x);
                    return res;
                }

                //TODO: have to raise a valueError
                void remove(T const& x) {
                    erase(index(x));
                }



                //Misc
                //TODO: have to raise a valueError
                long index(T const& x) const { return std::find(begin(),end(),x)-begin(); }	


                // list interface
                explicit
                    operator bool() const { return not data->empty(); }

                template <class F>
                    list<decltype(std::declval<T>()+std::declval<typename list<F>::value_type>())> operator+(list<F> const & s) const {
                        list<decltype(std::declval<T>()+std::declval<typename list<F>::value_type>())> clone(data->size()+s.data->size());
                        std::copy(s.begin(), s.end(), std::copy(begin(), end(), clone.begin()));
                        return clone;
                    }

                template <class F>
                    list<decltype(std::declval<T>()+std::declval<typename list_view<F>::value_type>())> operator+(list_view<F> const & s) const {
                        list<decltype(std::declval<T>()+std::declval<typename list_view<F>::value_type>())> clone(data->size()+len(s));
                        std::copy(s.begin(), s.end(), std::copy(begin(), end(), clone.begin()));
                        return clone;
                    }

                list<T> operator+(empty_list const &) const {
                    return list<T>(begin(), end());
                }
                template<class F>
                    list<T> operator*(F const& t) const {
                        size_t n = t;
                        list<T> r(data->size()*n);
                        auto start = r.begin();
                        for(size_t i=0;i<n;i++, start+=data->size()) 
                            std::copy(this->begin(), this->end(),start);
                        return r;
                    }

                template <class F>
                    list<T>& operator+=(list<F> const & s) {
                        reserve(size()+s.size());
                        std::copy(s.begin(), s.end(), std::back_inserter(*this));
                        return *this;
                    }
                long size() const { return data->size(); }

                template<class V>
                    bool contains(V const & v) const {
                        return std::find(data->begin(), data->end(), v) != data->end();
                    }
                intptr_t id() const {
                    return reinterpret_cast<intptr_t>(&(*data));
                }



            };


        /* list_view implementation */
        template<class T>
            inline list_view<T>& list_view<T>::operator=(list_view<T> const & s) {
                slicing=s.slicing;
                if(data != s.data) {
                    data=s.data;
                }
                return *this;
            }

        template<class T>
            list_view<T>& list_view<T>::operator=(list<T> const & seq) {
                if( slicing.step == 1) {
                    data->erase(begin(), end());
                    data->insert(begin(), seq.begin(), seq.end());
                }
                else {
                    assert("not implemented yet");
                }
                return *this;
            }
        template<class T>
            list<T> list_view<T>::operator+(list<T> const & s) {
                list<T> out(size() + s.size());
                std::copy(s.begin(), s.end(), std::copy(begin(), end(), out.begin()));
                return out;
            }
        template<class T>
            list<T> list_view<T>::operator+(list_view<T> const & s) {
                list<T> out(size() + s.size());
                std::copy(s.begin(), s.end(), std::copy(begin(), end(), out.begin()));
                return out;
            }
        template<class N, class T>
            list<T> operator*(N n, list<T> const& l) {
                return l*n;
            }

        /* empty list implementation */
        struct empty_list {
            typedef empty_iterator iterator;
            typedef empty_iterator const_iterator;
            template<class T>
                list<T> operator+(list<T> const & s) const { return s; }
            template<class T>
                list_view<T> operator+(list_view<T> const & s) const { return s; }
            empty_list operator+(empty_list const &) const { return empty_list(); }
            operator bool() const { return false; }
            template<class T>
                operator list<T>() const { return list<T>(0); }
        };


        std::ostream& operator<<(std::ostream& os, empty_list const & ) {
            return os << "[]";
        }

    }


    namespace utils {

        template <class T, class From>
            void reserve(types::list<T> & l, From const &f, typename From::const_iterator p=typename From::const_iterator())
            {
                l.reserve(len(f));
            }

    }

    template<class T>
        struct assignable<types::list<T> >{
            typedef types::list<typename assignable<T>::type > type;
        };

}

/* overload std::get */
namespace std {
    template <size_t I, class T>
        typename pythonic::types::list<T>::reference get( pythonic::types::list<T>& t) { return t[I]; }
    template <size_t I, class T>
        typename pythonic::types::list<T>::const_reference get( pythonic::types::list<T> const & t) { return t[I]; }

    template <size_t I, class T>
        struct tuple_element<I, pythonic::types::list<T> > {
            typedef typename pythonic::types::list<T>::value_type type;
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

/*
   template <class A>
   struct __combined<container<A> , none_type > {
   typedef typename __combined<pythonic::types::list<A>, none_type>::type type;
   };

   template <class A>
   struct __combined<none_type , container<A> > {
   typedef typename __combined<pythonic::types::list<A>, none_type>::type type;
   };
   */

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
#include <boost/python/numeric.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/object.hpp>

namespace pythonic {

    template<typename T>
        struct custom_pythran_list_to_list{
            static PyObject* convert(const types::list<T>& v){
                Py_ssize_t n = v.size();
                PyObject* ret = PyList_New(n);
                for(Py_ssize_t i=0;i<n;i++)
                    PyList_SET_ITEM(ret, i, boost::python::incref(boost::python::object(v[i]).ptr()));
                return ret;
            }
        };

    template<typename T>
        struct pythran_to_python< types::list<T> > {
            pythran_to_python() {
                pythran_to_python<T>();
                register_once< types::list<T>, custom_pythran_list_to_list<T> >();
            }
        };

    template<typename T>
        struct python_to_pythran< types::list<T> >{
            python_to_pythran(){
                python_to_pythran<T>();
                static bool registered =false;
                if(not registered) {
                    registered=true;
                    boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id<types::list<T> >());
                }
            }
            static void* convertible(PyObject* obj_ptr){
                // the second condition is important, for some reason otherwise there were attempted conversions of Body to list which failed afterwards.
                if( !PySequence_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr,"__len__")) return 0;
                return obj_ptr;
            }
            static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
                void* storage=((boost::python::converter::rvalue_from_python_storage<types::list<T> >*)(data))->storage.bytes;
                boost::python::extract<boost::python::numeric::array> extractor(obj_ptr);
                types::list<T>& v=*(types::list<T>*)(storage);
                if(extractor.check()) {
                    Py_ssize_t l=PySequence_Size(obj_ptr);
                    new (storage) types::list<T>(l);
                    boost::python::numeric::array data = extractor;
                    for(Py_ssize_t i=0; i<l; i++)
                        v[i]=boost::python::extract<T>(data[i]);
                }
                else {
                    Py_ssize_t l=PySequence_Fast_GET_SIZE(obj_ptr);
                    new (storage) types::list<T>(l);
                    PyObject** core = PySequence_Fast_ITEMS(obj_ptr);
                    for(Py_ssize_t i=0; i<l; i++)
                        v[i]=boost::python::extract<T>(*core++);
                }
                data->convertible=storage;
            }
        };
    struct custom_empty_list_to_list {
        static PyObject* convert(types::empty_list const &) {
            boost::python::list ret;
            return boost::python::incref(ret.ptr());
        }
    };
    template<>
        struct pythran_to_python< types::empty_list > {
            pythran_to_python() { register_once< types::empty_list, custom_empty_list_to_list >(); }
        };
}

#endif

#endif
