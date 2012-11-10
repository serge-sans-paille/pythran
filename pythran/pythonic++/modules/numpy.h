#ifndef PYTHONIC_MODULE_NUMPY_H
#define PYTHONIC_MODULE_NUMPY_H
#include <nt2/table.hpp>
#include <nt2/include/functions/polyfit.hpp>

namespace pythonic {
    namespace numpy {

        template< class Iterable0, class Iterable1, class T>
            core::list<double>
            polyfit(Iterable0 iter0, Iterable1 iter1, T rank) {
				nt2::table<double> x(nt2::of_size(1,len(iter0)), iter0.begin(), iter0.end());
				nt2::table<double> y(nt2::of_size(1,len(iter1)), iter1.begin(), iter1.end());
				nt2::table<double> z = nt2::polyfit(x, y, rank);
				double const * raw = z.raw();
				return core::list<double>(raw, raw+rank+1);
            }

        PROXY(pythonic::numpy, polyfit);
    }
}

#endif
