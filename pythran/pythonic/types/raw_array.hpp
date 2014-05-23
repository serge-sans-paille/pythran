#ifndef PYTHONIC_TYPES_RAW_ARRAY_HPP
#define PYTHONIC_TYPES_RAW_ARRAY_HPP

namespace pythonic {

    namespace types {
        /* Wrapper class to store an array pointer
         *
         * for internal use only, meant to be stored in a shared_ptr
         */
        template<class T>
            class raw_array {
                raw_array(raw_array<T> const& ) = delete;

                public:
                typedef T* pointer_type;

                T* data;
                raw_array() : data(nullptr) {}
                raw_array(size_t n) : data((T*)malloc(sizeof(T) * n)) {}
                raw_array(T* d) : data(d) {}
                raw_array(raw_array<T>&& d) : data(d.data) { d.data = nullptr; }

                ~raw_array() {
                    if(data)
                        free(data);
                }
            };

    }
}

#endif
