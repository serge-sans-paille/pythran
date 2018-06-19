'''
This modules contains a distutils extension mechanism for Pythran
    * PythranExtension: is used as distutils's Extension
'''

import pythran.config as cfg

import os.path
import os

from distutils.command.build_ext import build_ext as LegacyBuildExt

from numpy.distutils.extension import Extension


class PythranBuildExt(LegacyBuildExt):
    """Subclass of `distutils.command.build_ext.build_ext` which is required to
    build `PythranExtension` with the configured C++ compiler. It may also be
    subclassed if you want to combine with another build_ext class (NumPy,
    Cython implementations).

    """
    def build_extension(self, ext):
        prev = {'preprocessor': None,
                'compiler_cxx': None,
                'compiler_so': None,
                'compiler': None,
                'linker_exe': None,
                'linker_so': None}

        if hasattr(ext, 'cxx'):
            # Backup compiler settings
            for key in prev.keys():
                prev[key] = getattr(self.compiler, key)[0]
                getattr(self.compiler, key)[0] = ext.cxx

            try:
                return super(PythranBuildExt, self).build_extension(ext)
            finally:
                # Revert compiler settings
                for key in prev.keys():
                    getattr(self.compiler, key)[0] = prev[key]
        else:
            return super(PythranBuildExt, self).build_extension(ext)


class PythranExtension(Extension):
    '''
    Description of a Pythran extension

    Similar to distutils.core.Extension except that the sources are .py files
    They must be processable by pythran, of course.

    The compilation process ends up in a native Python module.

    Unlike distutils.core.Extension it also accepts a cxx keyword argument to
    force the compiler executable.
    '''
    def __init__(self, name, sources, *args, **kwargs):
        # the goal is to rely on original Extension
        # to do so we convert the .py to .cpp with pythran
        # and register the .cpp in place of the .py
        # That's stage 0, and it's enough if you get the source
        # from github and `python setup.py install it`
        #
        # *But* if you want to distribute the source through
        # `python setup.py sdist` then the .py no longer exists
        # and only the .cpp is distributed. That's stage 1

        import pythran.toolchain as tc

        cxx_sources = []
        for source in sources:
            base, ext = os.path.splitext(source)
            if ext == ".cpp":
                output_file = source
                stage = 1
            else:
                output_file = base + '.cpp'  # target name
                # stage 0 when we have the .py
                if os.path.exists(source):
                    stage = 0
                # stage 1 otherwise. `.cpp' should already be there
                # as generated upon stage 0
                else:
                    assert os.path.exists(output_file)
                    stage = 1
                    source = output_file

            # stage-dependant processing
            if stage == 0:
                # get the last name in the path
                if '.' in name:
                    module_name = os.path.splitext(name)[-1][1:]
                else:
                    module_name = name
                tc.compile_pythranfile(source, output_file,
                                       module_name, cpponly=True)
            cxx_sources.append(output_file)

        cfg_ext = cfg.make_extension(**kwargs)
        self.cxx = cfg_ext.pop('cxx')
        Extension.__init__(self, name, cxx_sources, *args, **cfg_ext)
