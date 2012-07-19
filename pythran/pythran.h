#ifndef PYTHRAN_H
#define PYTHRAN_H
#include <boost/python.hpp>

#include <pythonic++.h>
using namespace pythonic;

/* for type inference only,  a bit dangerous ? */
template <class A, class B>
variant<A,B> operator+(A , B );

/* for type inference too */
template<class T>
class container {
    public:
        typedef typename std::remove_cv< typename std::remove_reference<T>::type>::type value_type;
    private:
        container();
};

template <class A, class B>
B operator+(container<A>&& , B );
template <class A, class B>
B operator+(B , container<A>&& );

template <class A, class B>
core::list<decltype(std::declval<A>()+std::declval<B>())> operator+(container<A> , core::list<B> );
template <class A, class B>
core::list<decltype(std::declval<A>()+std::declval<B>())> operator+(core::list<B> , container<A> );

template <class A>
decltype(std::declval<core::list<A>>() + none_type()) operator+(container<A> , none_type );
template <class A>
decltype(std::declval<core::list<A>>() + none_type()) operator+(none_type , container<A> );

none_type operator+(none_type , none_type );

template <class A, class B>
container<decltype(std::declval<A>()+std::declval<B>())> operator+(container<A> , container<B> );

/* some overloads */
namespace std {
    /* for core::list */
    template <size_t I, class T>
        auto get( core::list<T>& t) -> decltype(t[I]) { return t[I]; }

    template <size_t I, class T>
        struct tuple_element<I, core::list<T> > {
            typedef typename core::list<T>::value_type type;
        };

    /* for containers */
    template <size_t I, class T>
        struct tuple_element<I, container<T> > {
            typedef typename container<T>::value_type type;
        };

    /* for complex numbers */
    template <size_t I, class T>
        struct tuple_element<I, complex<T> > {
            typedef T type;
        };
#define GET_COMPLEX(T)\
    template <size_t I>\
        T& get( std::complex<T>& );\
    template <>\
        T& get<0>( std::complex<T>& t) { return reinterpret_cast<T*>(&t)[0]; }\
    template <>\
        T& get<1>( std::complex<T>& t) { return reinterpret_cast<T*>(&t)[1]; }\

    GET_COMPLEX(double)

}
namespace pythonic {
    namespace proxy {
        struct bind0 {
            template<typename Operator, typename... Types>
                auto operator()(Operator const& op, Types &&... types) -> function<decltype(std::bind(op, types...))> {
                    return function<decltype(std::bind(op, types...))>(std::bind(op, types...)); 
                }
        };
        struct bind1 {
            template<typename Operator, typename... Types>
                auto operator()(Operator const& op, Types &&... types) -> function<decltype(std::bind(op, types..., std::placeholders::_1))> {
                    return function<decltype(std::bind(op, types..., std::placeholders::_1))>(std::bind(op, types..., std::placeholders::_1)); 
                }
        };
        struct bind2 {
            template<typename Operator, typename... Types>
                auto operator()(Operator const& op, Types &&... types) -> function<decltype(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2))> {
                    return function<decltype(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2))>(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2));
                }
        };
        struct bind3 {
            template<typename Operator, typename... Types>
                auto operator()(Operator const& op, Types &&... types) -> function<decltype(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))> {
                    return function<decltype(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))>(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)); 
                }
        };
    }
}

template<class T>
struct content_of {
    typedef typename T::value_type type;
};

/* boost::python converters */
#include <boost/python/numeric.hpp>

template<int ...> struct seq {};

template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};

template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };

template<typename... Types>
void fwd(Types const&... types) {
}

template <typename T>
struct python_to_pythran {};

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
		 Py_ssize_t l=PySet_GET_SIZE(obj_ptr);
		 new (storage) core::set<T>();
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

template<typename... Types>
struct python_to_pythran< std::tuple<Types...> >{
	python_to_pythran(){
        static bool registered=false;
        fwd(python_to_pythran<Types>()...);
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

template<typename T>
struct custom_core_list_to_list{
    static PyObject* convert(const core::list<T>& v){
        Py_ssize_t n = len(v);
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

template<typename... Types>
struct custom_tuple_to_list {
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
        fwd(pythran_to_python<Types>()...);
        register_once<std::tuple<Types...>, custom_tuple_to_list<Types...>>();
    }
};

struct custom_xrange_to_list {
    static PyObject* convert(xrange const &xr) {
        boost::python::list ret;
        for(const long& e:xr) ret.append(e);
        return boost::python::incref(ret.ptr());
    }
};

template<>
struct pythran_to_python< xrange > {
    pythran_to_python() { register_once<xrange, custom_xrange_to_list >(); }
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

#endif
