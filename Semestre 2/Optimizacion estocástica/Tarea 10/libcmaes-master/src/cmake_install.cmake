# Install script for directory: /home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/ericksav22/.local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcmaes.so.0.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcmaes.so.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcmaes.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/home/ericksav22/.local/lib")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/libcmaes.so.0.0.0"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/libcmaes.so.0"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/libcmaes.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcmaes.so.0.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcmaes.so.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcmaes.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH ":::::::::::::::::::::::::::"
           NEW_RPATH "/home/ericksav22/.local/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libcmaes" TYPE FILE FILES
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/cmaes.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/opti_err.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/eo_matrix.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/cmastrategy.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/esoptimizer.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/esostrategy.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/cmasolutions.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/parameters.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/cmaparameters.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/cmastopcriteria.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/ipopcmastrategy.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/bipopcmastrategy.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/covarianceupdate.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/acovarianceupdate.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/vdcmaupdate.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/pwq_bound_strategy.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/eigenmvn.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/candidate.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/genopheno.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/noboundstrategy.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/scaling.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/llogging.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/errstats.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/pli.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/contour.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/surrcmaes.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/surrogatestrategy.h"
    "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/cmaes_export.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libcmaes" TYPE DIRECTORY FILES "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/src/surrogates")
endif()

