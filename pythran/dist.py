'''
This modules contains a distutils extension mechanism for Pythran
    * PythranExtension: is used as distutils's Extension
'''

import pythran.config as cfg

from collections import defaultdict
import os.path
import os

from distutils.command.build_ext import build_ext as LegacyBuildExt

from numpy.distutils.extension import Extension


class PythranBuildExt(LegacyBuildExt, object):
    """Subclass of `distutils.command.build_ext.build_ext` which is required to
    build `PythranExtension` with the configured C++ compiler. It may also be
    subclassed if you want to combine with another build_ext class (NumPy,
    Cython implementations).

    """
    def build_extension(self, ext):
        prev = {
                # linux-like
                'preprocessor': None,
                'compiler_cxx': None,
                'compiler_so': None,
                'compiler': None,
                'linker_exe': None,
                'linker_so': None,
                # Windows-like
                'cc': None,
                'linker': None,
                'lib': None,
                'rc': None,
                'mc': None,
        }
        if hasattr(ext, 'cxx'):
            # Backup compiler settings
            for key in list(prev.keys()):
                if hasattr(self.compiler, key):
                    prev[key] = getattr(self.compiler, key)[0]
                    getattr(self.compiler, key)[0] = ext.cxx
                else:
                    del prev[key]

            # In general, distutils uses -Wstrict-prototypes, but this option
            # is not valid for C++ code, only for C.  Remove it if it's there
            # to avoid a spurious warning on every compilation.
            try:
                self.compiler.compiler_so.remove('-Wstrict-prototypes')
            except (AttributeError, ValueError):
                pass

            # Remove -arch i386 if 'x86_64' is specified, otherwise incorrect
            # code is generated, at least on OSX
            if hasattr(self.compiler, 'compiler_so'):
                archs = defaultdict(list)
                for i, flag in enumerate(self.compiler.compiler_so[1:]):
                    if self.compiler.compiler_so[i] == '-arch':
                        archs[flag].append(i + 1)
                if 'x86_64' in archs and 'i386' in archs:
                    for i in archs['i386']:
                        self.compiler.compiler_so[i] = 'x86_64'

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
    '''

    def __init__(self, name, sources, *args, **kwargs):
        cfg_ext = cfg.make_extension(python=True, **kwargs)
        self.cxx = cfg_ext.pop('cxx')
        self._sources = sources
        Extension.__init__(self, name, sources, *args, **cfg_ext)
        self.__dict__.pop("sources", None)

    @property
    def sources(self):
        import pythran.toolchain as tc
        cxx_sources = []
        for source in self._sources:
            base, ext = os.path.splitext(source)
            if ext != '.py':
                cxx_sources.append(source)
                continue
            output_file = base + '.cpp'  # target name

            if os.path.exists(source) and (not os.path.exists(output_file)
               or os.stat(output_file) < os.stat(source)):
                # get the last name in the path
                if '.' in self.name:
                    module_name = os.path.splitext(self.name)[-1][1:]
                else:
                    module_name = self.name
                tc.compile_pythranfile(source, output_file,
                                       module_name, cpponly=True)
            cxx_sources.append(output_file)
        return cxx_sources

    @sources.setter
    def sources(self, sources):
        self._sources = sources
