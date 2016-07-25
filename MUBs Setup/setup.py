#!/usr/bin/env python
# -*- coding: UTF-8 -*-

from distutils.core import setup, Extension
import numpy as np

ext_modules = [ Extension('mubs', sources = ['mubsmodule.cpp'], extra_compile_args=['-ffast-math']) ]

setup(
        name = 'mubs',
        author='Jack K. Fitzsimons',
        version = '1.0',
        include_dirs = [np.get_include()], #Add Include path of numpy
        ext_modules = ext_modules
      )