cmake_minimum_required(VERSION 3.12)

project(ABhospital VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

set(SOURCES
    ABhospital.cpp
    Paciente.cpp
    Medico.cpp
    Cita.cpp
    Reporte.cpp
)

set(HEADERS
    Paciente.h
    Medico.h
    Cita.h
    Reporte.h
)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(ABhospital ${SOURCES} ${HEADERS})

message(STATUS "Configuración de CMake completada para ABhospital")
