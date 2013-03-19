#ifndef PYTHONIC_FILE_H
#define PYTHONIC_FILE_H

#include <fstream>
#include <iterator>
#include <string>
#include <cstdio>
#include <unistd.h>

namespace  pythonic {

    namespace core {
		    class file;

		    struct npos{npos(){}};

		    struct file_iterator : std::iterator< std::forward_iterator_tag, core::string > {
					private:
				core::file & f;
				core::string curr;
				int position;

					public:
				typedef core::string value_type;
		        file_iterator(core::file & ref);
        		file_iterator(core::file & ref, core::npos);
        		bool operator==(file_iterator const& f2) const;
		        bool operator!=(file_iterator const& f2) const;
		        bool operator<(file_iterator const& f2) const;
				file_iterator& operator++();
				core::string operator*() const;
			};

			struct _file{
					FILE* f;
					_file() : f(nullptr) {}
					_file(core::string const& filename, core::string const& strmode = "r") : f(fopen(filename.c_str(), strmode.c_str())){}
					FILE* operator*() const {return f;}
					~_file() {if(f) fclose(f);}
			};

			class file {

                typedef _file container_type;
                impl::shared_ref<container_type> data; 
					private:
				bool is_open;
				core::string mode, name, newlines;

					public:
				// Types
				typedef core::file_iterator iterator;

				// Constructors
				file() : data(impl::no_memory()) {}
				file(core::string const& filename, core::string const& strmode = "r") : mode(strmode), name(filename), newlines('\n'){
					open(filename, strmode);
				}

				// Iterators
				iterator begin() { return iterator(*this); }
				iterator end() { return iterator(*this, core::npos()); }

				// Modifiers
				void open(core::string const& filename, core::string const& strmode) {
					const char *smode = strmode.c_str();
					// Python enforces that the mode, after stripping 'U', begins with 'r', 'w' or 'a'.
					if(*smode=='U') {++smode;}// Not implemented yet

					data = impl::shared_ref<container_type>(filename, smode);
					if(not **data)
						throw core::IOError("Couldn't open file " + filename);
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

				core::string const& getmode() const{
					return mode;
				}

				core::string const& getname() const{
					return name;
				}

				core::string const& getnewlines() const{
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

				core::string next() {
					if(not is_open) throw ValueError("I/O operation on closed file");
					if (feof(**data) && mode.find_first_of("ra") == std::string::npos) {
					// If we are at eof on reading mode throw exception
						throw StopIteration("file.next() : EOF reached.");
					}
					return readline();
				}

				core::string read(int size = -1) {
					if(not is_open) throw ValueError("I/O operation on closed file");
					if (mode.find_first_of("r+") == std::string::npos)
						throw IOError("File not open for reading");
					if (size == 0 or (feof(**data) && mode.find_first_of("ra") == std::string::npos) ) return core::string();
					int curr_pos = tell();
					seek(0, SEEK_END);
					size = size < 0 ? tell() - curr_pos : size;
					seek(curr_pos);
					char *content = new char[size+1];
					// Putting a '\0' after relevant info even if size is > number of bits in file.
					content[fread(content, sizeof(char), size, **data)] = '\0';
					// This part needs a new implementation of core::string(char*) to avoid unnecessary copy.
					core::string res(content);
					delete[] content;
					return res;
				}

				core::string readline(size_t size=std::numeric_limits<size_t>::max()) {
					if(not is_open) throw ValueError("I/O operation on closed file");
					if (mode.find_first_of("r+") == std::string::npos)
						throw IOError("File not open for reading");
					if(size == 0) return core::string();
					// if(size < 0) return readline(); // Already checked in module/file.h
					// Getline will always realloc content to store full string.
					// => Emulating expected behaviour
                    static __thread char * buffer = nullptr;
					static size_t n=0;
					ssize_t real_size = getline(&buffer, &n, **data);
					if (real_size > size){
						fseek(**data, -(long)(real_size - size), SEEK_CUR);
						buffer[size] = '\0';
					}
					// This part needs a new implementation of core::string(char*, size_t) to avoid unnecessary copy.
                    if(real_size>0) return core::string(buffer, real_size);
                    else return core::string();
				}

				core::list<core::string> readlines(int sizehint = -1) {
					// Official python doc specifies that sizehint is used as a max of chars
					// But it has not been implemented in the standard python interpreter...
					core::string str;
					core::list<core::string> lst = core::empty_list(); 
					while((str=readline())){
						lst.push_back(str);
					}
					return lst;
				}

				iterator xreadlines() {
					// Deprecated
					if(not is_open) throw ValueError("I/O operation on closed file");
					return begin();
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
					ftruncate(fileno(), size);
				}

				void write(core::string const& str){
					if(not is_open) throw ValueError("I/O operation on closed file");
					if (mode.find_first_of("wa+") == std::string::npos) 
						throw IOError("file.write() :  File not opened for writing.");
					fwrite(str.c_str(), sizeof(char), str.length(), **data);
				}

				template<class T>
					void writelines(T const& seq){
						auto end = seq.end();
						for(auto it = seq.begin(); it != end; ++it)
							write(*it);
					}
			};

			// file_iterator implementation
				file_iterator::file_iterator(core::file & ref) : f(ref), curr(ref.readline()), position(ref.tell()) {};
        		file_iterator::file_iterator(core::file & ref, core::npos) : f(ref), position(-1), curr() {};
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
				core::string file_iterator::operator*() const{
        		    return core::string(curr);
		        }
			// End of file_iterator implementation

	}

}
#endif
