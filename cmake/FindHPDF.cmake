# Find libharu (HPDF) library
#
# This module defines
# HPDF_INCLUDE_DIRS - where to find hpdf.h
# HPDF_LIBRARIES - the libraries needed to use HPDF
# HPDF_FOUND - system has HPDF

find_path(HPDF_INCLUDE_DIR
    NAMES hpdf.h
    PATHS
        /usr/include
        /usr/local/include
        /opt/homebrew/include
    PATH_SUFFIXES libharu haru
)

find_library(HPDF_LIBRARY
    NAMES hpdf libhpdf
    PATHS
        /usr/lib
        /usr/local/lib
        /opt/homebrew/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(HPDF DEFAULT_MSG HPDF_LIBRARY HPDF_INCLUDE_DIR)

if(HPDF_FOUND)
    set(HPDF_LIBRARIES ${HPDF_LIBRARY})
    set(HPDF_INCLUDE_DIRS ${HPDF_INCLUDE_DIR})
endif() 