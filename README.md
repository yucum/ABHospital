# ABHospital - Sistema de Gestión Hospitalaria

 **ABHospital** es un sistema de gestión hospitalaria desarrollado en C++ para manejar de manera eficiente pacientes, médicos, citas y reportes.

---

## 🏥 Funcionalidades

- **Gestión de Pacientes**
  - Registro, edición, eliminación y visualización de pacientes.
  - Manejo del historial clínico individual.
- **Gestión de Médicos**
  - Alta, baja y modificación de datos de médicos.
  - Asignación de especialidades.
- **Gestión de Citas**
  - Creación, cancelación y modificación de citas.
  - Asociación entre pacientes y médicos.
- **Generación de Reportes**
  - Reportes de citas pendientes.
  - Listado de pacientes atendidos en un rango de fechas.
- **Persistencia de Datos**
  - Guardado y carga de información desde archivos CSV.

---

## 🔧 Requisitos del Sistema

- **Sistema Operativo**: Linux o Windows.
- **Compilador**: `g++` compatible con C++20.
- **Herramientas Opcionales**: CMake para la gestión de construcción.

---

## 🚀 Instalación y Ejecución

1. Clona el repositorio:
   ```bash
   git clone https://github.com/tuusuario/ABHospital.git
   cd ABHospital
2. Construye el proyecto usando CMake:
```bash
mkdir build
cd build
cmake ..
make
```
3. Ejecuta el programa:
```bash
./ABhospital
```

📚 Estructura del Proyecto
- ABhospital.cpp: Archivo principal que coordina la interacción entre todas las clases.
- Paciente.cpp / Paciente.h: Clase que gestiona la información y el historial clínico de los pacientes.
- Medico.cpp / Medico.h: Clase que gestiona a los médicos y sus especialidades.
- Cita.cpp / Cita.h: Clase para la creación y administración de citas.
- Reporte.cpp / Reporte.h: Clase para la generación de reportes.
- CMakeLists.txt: Archivo para la construcción del proyecto con CMake.
