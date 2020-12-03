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

include(FetchContent)

set(QATERIALHOTRELOAD_REPOSITORY "https://github.com/OlivierLDff/QaterialHotReload.git" CACHE STRING "QaterialHotReload repository url")
set(QATERIALHOTRELOAD_TAG "master" CACHE STRING "QaterialHotReload git tag")

FetchContent_Declare(
  QaterialHotReload
  GIT_REPOSITORY ${QATERIALHOTRELOAD_REPOSITORY}
  GIT_TAG        ${QATERIALHOTRELOAD_TAG}
)

set(QATERIALHOTRELOAD_FOLDER_PREFIX "Dependencies/Qaterial" CACHE STRING "Prefix folder for all QaterialHotReload generated targets in generated project (only decorative)")
set(QATERIALHOTRELOAD_ENABLE_HOTRELOAD_APP OFF CACHE BOOL "")
FetchContent_MakeAvailable(QaterialHotReload)
