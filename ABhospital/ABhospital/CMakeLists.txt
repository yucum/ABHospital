cmake_minimum_required(VERSION 3.12)
project(ABhospital)

# Version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Archivos fuente
add_executable(ABhospital
    "ABhospital.cpp"
    "Paciente.cpp"
    "Medico.cpp"
    "Cita.cpp"
    "Reporte.cpp"
)