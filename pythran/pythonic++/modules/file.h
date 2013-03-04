#ifndef PYTHONIC_MODULE_FILE_H
#define PYTHONIC_MODULE_FILE_H

namespace pythonic {
    namespace __file__ { /* to avoid conflict with the set intrinsic */
		void close(core::file &f){f.close();}
		void close(core::file &&f){f.close();}
        PROXY(pythonic::__file__, close);

		void flush(core::file &f){f.flush();}
		void flush(core::file &&f){f.flush();}
        PROXY(pythonic::__file__, flush);

		int fileno(core::file const& f){return f.fileno();}
        PROXY(pythonic::__file__, fileno);

		bool isatty(core::file const& f){return f.isatty();}
        PROXY(pythonic::__file__, isatty);

		core::string read(core::file &f, int size = -1){return f.read(size);}
		core::string read(core::file &&f, int size = -1){return f.read(size);}
        PROXY(pythonic::__file__, read);

		core::string readline(core::file &f, int size = -1){return size < 0 ? f.readline() : f.readline(size);}
		core::string readline(core::file &&f, int size = -1){return size < 0 ? f.readline() : f.readline(size);}
        PROXY(pythonic::__file__, readline);

		template<class F>
		core::list<core::string> readlines(F&& f){return f.readlines();}
		template<class F>
		core::list<core::string> readlines(F&& f, int sizehint){return f.readlines(sizehint);}
        PROXY(pythonic::__file__, readlines);

		core::file::iterator xreadlines(core::file &f){return f.xreadlines();}
		core::file::iterator xreadlines(core::file &&f){return f.xreadlines();}
        PROXY(pythonic::__file__, xreadlines);

		void seek(core::file &f, int offset){f.seek(offset);}
		void seek(core::file &&f, int offset){f.seek(offset);}
		void seek(core::file &f, int offset, int whence){f.seek(offset, whence);}
		void seek(core::file &&f, int offset, int whence){f.seek(offset, whence);}
        PROXY(pythonic::__file__, seek);

		int tell(core::file const& f){return f.tell();}
        PROXY(pythonic::__file__, tell);

		void truncate(core::file & f){f.truncate();}
		void truncate(core::file && f){f.truncate();}
		void truncate(core::file & f, int size){f.truncate(size);}
		void truncate(core::file && f, int size){f.truncate(size);}
        PROXY(pythonic::__file__, truncate);

		void write(core::file & f, core::string const& str){f.write(str);}
		void write(core::file && f, core::string const& str){f.write(str);}
        PROXY(pythonic::__file__, write);

		template<class F, class T>
			void writelines(F&& f, T const& sequence){
				f.writelines(sequence);
			}
        PROXY(pythonic::__file__, writelines);

	}
}

#endif
