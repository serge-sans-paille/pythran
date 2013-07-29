#ifndef PYTHONIC_PYTHON_REGISTER_ONCE_HPP
#define PYTHONIC_PYTHON_REGISTER_ONCE_HPP

#include <boost/python/to_python_converter.hpp>

namespace pythonic {

    template<typename T>
        struct pythran_to_python {
        };

    template<typename T>
        struct python_to_pythran {
        };

    template<class Type, class Converter>
        static void register_once() {
            boost::python::type_info info = boost::python::type_id<Type >();
            const boost::python::converter::registration* reg = boost::python::converter::registry::query(info);
            if(not reg or not (*reg).m_to_python) {
                boost::python::to_python_converter< Type, Converter >();
            }
        }

}

#endif
