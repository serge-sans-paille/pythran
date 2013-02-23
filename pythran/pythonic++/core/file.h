#ifndef PYTHONIC_FILE_H
#define PYTHONIC_FILE_H

#include <fstream>
#include <iterator>
#include <string>

// TODO: Modifier les implicits : open(), iter, ...
// 		 Corriger problemes de references dans modules/file.h pr read, readline....

namespace  pythonic {

    namespace core {
			class file;

			struct npos{npos(){}};

		    class file_iterator : std::iterator< std::forward_iterator_tag, core::string > {
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
        		file_iterator& operator++(int i);
				core::string operator*() const;
			};

			class file {

                typedef std::fstream container_type;
                impl::shared_ref<container_type> data; 

					public:
				// Enum
				//enum {SEEK_SET, SEEK_CUR, SEEK_END};

				// Types
				typedef core::file_iterator iterator;

				// Constructors
				file() : data(impl::no_memory()) {}
				file(core::string const& filename, core::string const& strmode = "r") {
					open(filename, strmode);
				}

				// Iterators
				iterator begin() { return iterator(*this); }
				iterator end() { return iterator(*this, core::npos()); }

				// Modifiers
				void open(core::string const& filename, core::string const& strmode) {
					std::ios_base::openmode mode; // Init? 
					const char *smode = strmode.c_str();
					// Python enforces that the mode, after stripping 'U', begins with 'r', 'w' or 'a'.
					if(*smode=='U') {++smode;}// Not implemented yet
						
					while(*smode) {
						switch(*smode) {
							case 'r':
								mode |= std::ios_base::in;
								break;
							case 'w':
								mode |= std::ios_base::out | std::ios_base::trunc;
								break;
							case 'a':
								mode |= std::ios_base::app | std::ios_base::in | std::ios_base::out;
								break;
							case 'b':
								mode |= std::ios_base::binary;
								break;
							case '+':
								mode |= std::ios_base::ate;
								break;
							default:
								break;
						}
						++smode;
					}
					data = impl::shared_ref<container_type>(filename, mode);
					if(not data->is_open())
						throw core::IOError("Couldn't open file " + filename);
					data->exceptions( std::ios_base::badbit );
				}

				void close() {
					data->close();
				}

				void flush() {
					data->flush();
				}

				int fileno() const {
					throw NotImplementedError("file.fileno() : std::fstream doesn't provide fileno.");
				}

				bool isatty() const {
					throw NotImplementedError("file.isatty() : Not implemented yet.");
				}

				core::string next() {
					// If we are at eof on reading mode throw exception
					if (data->eof() && (data->flags() & std::ios_base::in)) {
						throw StopIteration("file.next() : EOF reached.");
					}
					return readline();
				}

				core::string read(int size = -1) {
					if(size == 0 | data->eof() | data->peek() == EOF) return core::string();
					int curr_pos = tell();
					seek(0, SEEK_END);
					size = size < 0 ? tell() - curr_pos : size;
					seek(curr_pos);
					char *content = new char[size];
					data->read(content, size);
					// Syncing pointers
					seek(data->tellg());
					return core::string(std::move(content));
			}

				core::string readline() {
					if(data->eof() | data->peek() == EOF){seek(data->tellg()); return core::string();}
					core::string str;
					std::getline(*data, str);
					// Unix only since Windows doesn't use the same separator.
					//
					// std::getline() discards separator, python doesn't so putting it back
					if(!data->eof()) str.push_back('\n');
					// Syncing pointers
					seek(data->tellg());
					return str;
				}

				core::string readline(int size) {
					if(size == 0 | data->eof() | data->peek() == EOF) {seek(data->tellg()); return core::string();}
					if(size < 0) return readline();
					char *content = new char[size + 2];
					data->getline(content, size + 1);
					// We encountered a '\n' and discarded it.
					if(!data->fail()){
						size = data->gcount();
						content[size - 1] = '\n';	
						content[size] = '\0';	
					}
					data->clear();
					// Syncing pointers
					seek(data->tellg());
					return core::string(std::move(content));
				}

				core::list<core::string> readlines(int sizehint = -1) {
					// Official python doc specifies that sizehint is used as a max of chars
					// But it has not been implemented in the standard python interpreter...
					core::string str;
					core::list<core::string> lst = core::empty_list(); 
					while(str=readline()){
						lst.push_back(str);
					}
					return lst;
				}

				iterator xreadlines() {
					// Deprecated
					return begin();
				}

				void seek(int offset) {
					// We have two pointers to handle, but only one in python.
					// We are handling them both together.
					data->seekg(offset);
					data->seekp(offset);
				}

				void seek(int offset, int whence) {
					std::ios_base::seekdir seek;
					switch(whence){
						case SEEK_SET:
							seek = std::ios_base::beg;
							break;
						case SEEK_CUR:
							seek = std::ios_base::cur;
							break;
						case SEEK_END:
							seek = std::ios_base::end;
							break;
						default:	
							throw IOError("file.seek() :  Invalid argument.");
							return;
					}
					data->seekg(offset, seek);
					data->seekp(offset, seek);
				}

				int tell() const {
					assert(data->tellg() == data->tellp());
					return data->tellg();
				}

				void truncate(){
					throw NotImplementedError("file.truncate() : Not implemented yet.");
				}

				void truncate(int size){
					throw NotImplementedError("file.truncate(int) : Not implemented yet.");
				}

				void write(core::string const& str){
					data->write(str.c_str(), str.length());
					// Syncing pointers
					data->seekg(data->tellp());
				}

				template<class T>
					void writelines(T const& seq){
						auto end = seq.end();
						for(auto it = seq.begin(); it != end; ++it){
							write(*it);
						}
						// Syncing pointers
						data->seekg(data->tellp());
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
					if(position == -1) return *this; 
		            curr = f.readline();
					position = f.tell();
					return *this;
        		}
        		file_iterator& file_iterator::operator++(int i){
					while(--i >= 0){
						++*this;
					}
					return *this;
				}
				core::string file_iterator::operator*() const{
        		    return core::string(curr);
		        }
			// End of file_iterator implementation

	}

}
#endif
