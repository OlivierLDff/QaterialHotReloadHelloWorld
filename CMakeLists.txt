# Copyright 2019-2020 Olivier Le Doeuff
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
# modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
# is furnished to do so, subject to the following conditions:
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
# OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

cmake_minimum_required(VERSION 3.17.0 FATAL_ERROR)

# ───── PROJECT VERSION ─────

include(cmake/Version.cmake)

# ───── PROJECT ─────

project("HelloWorld" VERSION ${HELLOWORLD_VERSION} LANGUAGES CXX)

# ───── DEPENDENCIES ─────

include(cmake/FetchDependencies.cmake)

# ───── LIB ─────

set(HELLOWORLD_LIB_SRCS
  lib/HelloWorld/HelloWorld.hpp
  lib/HelloWorld/HelloWorld.cpp
)

add_library(HelloWorldCore STATIC
  ${HELLOWORLD_LIB_SRCS}
)

add_library(HelloWorld::Core ALIAS HelloWorldCore)

target_include_directories(HelloWorldCore PUBLIC lib)

target_compile_features(HelloWorldCore PUBLIC cxx_std_17)

set_target_properties(HelloWorldCore PROPERTIES AUTOMOC TRUE)

target_link_libraries(HelloWorldCore PUBLIC
  QOlm
  Qt::Core
  Qt::Qml
)

# ───── UI ─────

qt_generate_qmldir(HELLOWORLD_UI_QMLDIRS
  SOURCE_DIR qml/HelloWorld
  MODULE "HelloWorld"
  RECURSE
)

qt_generate_qrc(HELLOWORLD_UI_QRC
  SOURCE_DIR qml
  DEST_DIR ${CMAKE_CURRENT_BINARY_DIR}
  NAME HelloWorld.qrc
  GLOB_EXPRESSION "*.qml" "qmldir"
  ALWAYS_OVERWRITE
  RECURSE
)

add_library(HelloWorldUi STATIC ${HELLOWORLD_UI_QRC})
add_library(HelloWorld::Ui ALIAS HelloWorldUi)
target_link_libraries(HelloWorldUi PUBLIC
  Qt::Core
  Qt::Qml
  Qt::Quick
  Qt::QuickControls2
  Qt::Svg
  Qt::Xml
)

set_target_properties(HelloWorldUi PROPERTIES AUTORCC TRUE)

# ───── APP ─────

set(HELLOWORLD_APP_SRCS
  app/HelloWorld/Main.cpp
)

add_executable(HelloWorld ${HELLOWORLD_APP_SRCS})

target_link_libraries(HelloWorld PUBLIC
  HelloWorld::Core
  HelloWorld::Ui
)

# ───── HOTRELOAD ─────

set(HELLOWORLD_HOTRELOAD_SRCS
  app/HotReload/Main.cpp
)

add_executable(HelloWorldHotReload ${HELLOWORLD_HOTRELOAD_SRCS})

target_link_libraries(HelloWorldHotReload PUBLIC
  HelloWorld::Core
  Qaterial::HotReload
)
