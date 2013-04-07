#ifndef PYTHONIC_MODULE_FLOAT_H
#define PYTHONIC_MODULE_FLOAT_H
namespace pythonic {

    namespace __float__ {

        bool is_integer(double d) {
            double intpart;
            return std::modf(d, &intpart) == d;
        }
        PROXY(pythonic::__float__, is_integer);
    }
}
#endif

