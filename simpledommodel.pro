#=============================================================================
#This is a Program to demonstrate a trivial treeview sorting with combobox on.
#header
#Copyright (C) 2015  Pradyumna Pramod Saraph
#Contact: prady.pps@gmail.com
#
#This program is free software: you can redistribute it and/or modify
#it under the terms of the Lesser GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.

#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#Lesser GNU General Public License for more details.
#
#You should have received a copy of the Lesser GNU General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>.
#=============================================================================
HEADERS     = \
              mainwindow.h \
    ccustomtreeview.h \
    cheaderview.h \
    cdomItem.h \
    cdommodel.h \
    ccommondefines.h \
    ctreefilterproxymodel.h
SOURCES     = \
              main.cpp \
              mainwindow.cpp \
    ccustomtreeview.cpp \
    cheaderview.cpp \
    cdomItem.cpp \
    cdommodel.cpp \
    ctreefilterproxymodel.cpp
CONFIG  += qt
QT      += xml

# install
target.path = $$[QT_INSTALL_EXAMPLES]/itemviews/simpledommodel
sources.files = $$SOURCES $$HEADERS $$RESOURCES *.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/itemviews/simpledommodel
INSTALLS += target sources

symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
maemo5: include($$QT_SOURCE_TREE/examples/maemo5pkgrules.pri)

