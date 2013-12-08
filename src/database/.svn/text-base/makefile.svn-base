#
# Copyright (c) 2005-2009 Instigate CJSC, Armenia
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free
# Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#

# The source files under the project.
cpp_files := \
	dynamic.cpp \

# The header files under the project, which are supposed to be used by other
# projects.
public_headers := \

# Building QT project.
# TODO: Add detailed comments.
qt_headers :=

moc_flags :=

qt_ui_files :=

uic_flags :=

# The compiler flags can be updated/overwritten for the project.
# 
# Example:
# compiler_flags += -s -Wno-long-long -fno-strict-aliasing
# compiler_flags := $(filter-out -Wshadow -Wconversion, $(compiler_flags))
# 
# Note: It is not recommended to overwrite the value (don't use := operator).
# 
compiler_flags +=

# The linker flags can be updated/overwritten for the project
#
# Example:
# linker_flags += -i 
#
# Note: It is not recommended to overwrite the value (don't use := operator).
#
linker_flags += -lstdc++

# The libraries which should be linked to the current project. The link type is
# specified as a global parameter, except the libraries, which are built as a
# either shared or static library. For those libraries the appropriate linking
# type is selected, e.g. if current project is being linked to lib_project,
# which is static library, then current project will be always linked to
# lib_project statically, despite global link type is shared or static.
# 
# Example:
# libs := project1 tcl gtkmm-2.4 
# 
# Note: Specifying the library version is not supported.
#
libs := 

# Library version
#
# Note: If the library version is not specified, then the program_version is
# taken for this library.
#
lib_version :=

# For each project either executable file or a library can be generated.
#
# To generate the executable file the exe.mk should be included, which is
# located in mkf directory.
#
# Two types of libraries can be generated for each project:
#       dynamic (shared objects) and static (archives).
#
# To generate the shared object the dynamic.mk should be included here.
# To generate the archive the static.mk file should be included here.
# To generate either (shared object or archive) depending on the global link
# type the lib.mk should be included.
#
# Note that the generated library will be located in local $lib_dir directory
# (by default $(project_root)/lib/).
#

include $(mkf_path)/dynamic.mk
