#ifndef PYTHONIC_TYPES_FILE_HPP
#define PYTHONIC_TYPES_FILE_HPP

#include "pythonic/types/assignable.hpp"
#include "pythonic/utils/shared_ref.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/none.hpp"
#include "pythonic/types/exceptions.hpp"

#include <fstream>
#include <iterator>
#include <cstring>
#include <string>
#include <cstdio>
#include <unistd.h>

namespace pythonic {

    namespace types {
        class file;


        struct file_iterator : std::iterator< std::forward_iterator_tag, types::str, ptrdiff_t, types::str*, types::str /* no ref */ >
        {
            private:
                file & f;
                types::str curr;
                int position;

            public:
                typedef types::str value_type;
                struct npos {
                };
                file_iterator(file & ref);
                file_iterator(file & ref, npos);
                bool operator==(file_iterator const& f2) const;
                bool operator!=(file_iterator const& f2) const;
                bool operator<(file_iterator const& f2) const;
                file_iterator& operator++();
                types::str const& operator*() const;
        };

        struct _file{
            FILE* f;
            char* _buffer; // Buffer used by file.readline()
            size_t _buffer_size;
            _file() : f(nullptr), _buffer(nullptr), _buffer_size(0){}
            _file(types::str const& filename, types::str const& strmode = "r") : f(fopen(filename.c_str(), strmode.c_str())), _buffer(nullptr), _buffer_size(0){}
            FILE* operator*() const {return f;}
            ~_file() {if(f) fclose(f); if (_buffer) free(_buffer);}
        };

        class file {

            typedef _file container_type;
            utils::shared_ref<container_type> data; 
            private:
            bool is_open;
            types::str mode, name, newlines;

            public:
            // Types
            typedef file_iterator iterator;
            typedef types::str value_type;

            // Constructors
            file() : data(utils::no_memory()) {}
            file(types::str const& filename, types::str const& strmode = "r") : data(utils::no_memory()), mode(strmode), name(filename), newlines('\n'){
                open(filename, strmode);
            }

            // Iterators
            iterator begin() { return iterator(*this); }
            iterator end() { return iterator(*this, iterator::npos()); }

            // Modifiers
            void open(types::str const& filename, types::str const& strmode) {
                const char *smode = strmode.c_str();
                // Python enforces that the mode, after stripping 'U', begins with 'r', 'w' or 'a'.
                if(*smode=='U') {++smode;}// Not implemented yet

                data = utils::shared_ref<container_type>(filename, smode);
                if(not **data)
                    throw types::IOError("Couldn't open file " + filename);
                is_open = true;
            }

            void close() {
                fclose(**data);
                data->f = nullptr;
                is_open = false;
            }

            bool closed() const { 
                return not is_open;
            }

            types::str const& getmode() const{
                return mode;
            }

            types::str const& getname() const{
                return name;
            }

            types::str const& getnewlines() const{
                // Python seems to always return none... Doing the same in getattr<3>
                return newlines;
            }

            bool eof() {
                return ::feof(**data);
            }

            void flush() {
                if(not is_open) throw ValueError("I/O operation on closed file");
                fflush(**data);
            }

            int fileno() const {
                if(not is_open) throw ValueError("I/O operation on closed file");
                return ::fileno(**data);
            }

            bool isatty() const {
                if(not is_open) throw ValueError("I/O operation on closed file");
                return ::isatty(this->fileno());
            }

            types::str next() {
                if(not is_open) throw ValueError("I/O operation on closed file");
                if (feof(**data) && mode.find_first_of("ra") == std::string::npos) {
                    // If we are at eof on reading mode throw exception
                    throw StopIteration("file.next() : EOF reached.");
                }
                return readline();
            }

            types::str read(int size = -1) {
                if(not is_open) throw ValueError("I/O operation on closed file");
                if (mode.find_first_of("r+") == std::string::npos)
                    throw IOError("File not open for reading");
                if (size == 0 or (feof(**data) && mode.find_first_of("ra") == std::string::npos) ) return types::str();
                int curr_pos = tell();
                seek(0, SEEK_END);
                size = size < 0 ? tell() - curr_pos : size;
                seek(curr_pos);
                char *content = new char[size+1];
                // This part needs a new implementation of types::str(char*) to avoid unnecessary copy.
                types::str res(content, fread(content, sizeof(char), size, **data));
                delete[] content;
                return res;
            }

            types::str readline(ssize_t size=std::numeric_limits<ssize_t>::max()) {
                if(not is_open) throw ValueError("I/O operation on closed file");
                if (mode.find_first_of("r+") == std::string::npos)
                    throw IOError("File not open for reading");
                if(size == 0) return types::str();
                // if(size < 0) return readline(); // Already checked in module/file.h
                // Getline will always realloc content to store full string.
                // => Emulating expected behaviour
                ssize_t real_size = getline(&data->_buffer, &data->_buffer_size, **data);
                if (real_size > size){
                    fseek(**data, -(long)(real_size - size), SEEK_CUR);
                }
                // This part needs a new implementation of types::str(char*, size_t) to avoid unnecessary copy.
                if(real_size>0) return types::str(data->_buffer, std::min(real_size, size));
                else return types::str();
            }

            types::list<types::str> readlines(int sizehint = -1) {
                // Official python doc specifies that sizehint is used as a max of chars
                // But it has not been implemented in the standard python interpreter...
                types::str str;
                types::list<types::str> lst(0);
                while((str=readline())){
                    lst.push_back(str);
                }
                return lst;
            }

            void seek(int offset, int whence = SEEK_SET) {
                if(not is_open) throw ValueError("I/O operation on closed file");
                if(whence != SEEK_SET && whence != SEEK_CUR && whence != SEEK_END)
                    throw IOError("file.seek() :  Invalid argument.");
                fseek(**data, offset, whence);
            }

            int tell() const {
                if(not is_open) throw ValueError("I/O operation on closed file");
                return ftell(**data);
            }

            void truncate(int size = -1){
                if(not is_open) throw ValueError("I/O operation on closed file");
                if (mode.find_first_of("wa+") == std::string::npos) 
                    throw IOError("file.write() :  File not opened for writing.");
                if (size <0) size = this->tell();
                int error = ftruncate(fileno(), size);
                if(error==-1)
                    throw RuntimeError(strerror(errno));
            }

            void write(types::str const& str){
                if(not is_open) throw ValueError("I/O operation on closed file");
                if (mode.find_first_of("wa+") == std::string::npos) 
                    throw IOError("file.write() :  File not opened for writing.");
                fwrite(str.c_str(), sizeof(char), str.size(), **data);
            }

            template<class T>
                void writelines(T const& seq){
                    auto end = seq.end();
                    for(auto it = seq.begin(); it != end; ++it)
                        write(*it);
                }
        };

        // file_iterator implementation
        file_iterator::file_iterator(file & ref) : f(ref), curr(ref.readline()), position(ref.tell()) {};
        file_iterator::file_iterator(file & ref, npos) : f(ref), curr(), position(-1) {};
        bool file_iterator::operator==(file_iterator const& f2) const{
            return position == f2.position;
        }
        bool file_iterator::operator!=(file_iterator const& f2) const{
            return position != f2.position;
        }
        bool file_iterator::operator<(file_iterator const& f2) const{
            // Not really elegant...
            // Equivalent to 'return *this != f2;'
            return  position != f2.position;
        }
        file_iterator& file_iterator::operator++(){
            // Check if ftell == -1 when fgetpos(FILE *stream, fpos_t eof) == 0
            if(f.eof()) return *this; 
            curr = f.readline();
            position = f.eof() ? -1 : f.tell();
            return *this;
        }
        types::str const &file_iterator::operator*() const{
            return curr;
        }
        // End of file_iterator implementation

    }

}

/* pythran attribute system { */
namespace pythonic {
    namespace types {
        namespace __file {

            template<int I>
                struct getattr;
            template<>
                struct getattr<0> {
                    bool operator()(file const& f) {return f.closed();}
                };

            template<>
                struct getattr<1> {
                    str const& operator()(file const& f) {return f.getmode();}
                };

            template<>
                struct getattr<2> {
                    str const& operator()(file const& f) {return f.getname();}
                };

            template<>
                struct getattr<3> {
                    // Python seems to always return none... Doing the same.
                    none_type operator()(file const& f) {return __builtin__::None;}
                };
        }
    }
}
template<int I>
auto getattr(pythonic::types::file const& f) -> decltype(pythonic::types::__file::getattr<I>()(f)) {
    return pythonic::types::__file::getattr<I>()(f);
}

/* } */

#endif

