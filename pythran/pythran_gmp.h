#include <gmpxx.h>

#undef pythran_long
#undef pythran_long_def
#define pythran_long(a) mpz_class(#a)
#define pythran_long_def mpz_class

template<class T, class U>
    struct assignable<__gmp_expr<T,U> >{
        typedef mpz_class type;
    };

template<>
struct python_to_pythran<mpz_class>{
	python_to_pythran(){
        static bool registered =false;
        if(not registered) {
            registered=true;
            boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id<mpz_class>());
        }
    }
	static void* convertible(PyObject* obj_ptr){
		if(!PyLong_Check(obj_ptr)) return 0;
		return obj_ptr;
	}
	static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
		 void* storage=((boost::python::converter::rvalue_from_python_storage<mpz_class>*)(data))->storage.bytes;

        new (storage) mpz_class(PyString_AsString(PyObject_Str(obj_ptr)));

	    data->convertible=storage;
    }
};

struct mpz_class_to_long{
    static PyObject* convert(const mpz_class& v){
        return PyNumber_Long(PyString_FromString(v.get_str().c_str()));
    }
};

template<>
struct pythran_to_python< mpz_class > {
    pythran_to_python() {
        register_once< mpz_class, mpz_class_to_long >();
    }
};

