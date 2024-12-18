#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
#include "Paciente.h"
#include "Medico.h"
#include "Cita.h"
#include "Reporte.h"

using namespace std;

void menuPrincipal();
void gestionarPacientes(vector<Paciente>& pacientes);
void gestionarMedicos(vector<Medico>& medicos);
void gestionarCitas(vector<Cita>& citas, vector<Paciente>& pacientes, vector<Medico>& medicos);
void generarReportes(vector<Cita>& citas);
bool validarFecha(const string& fecha);
void guardarDatosCSV(const vector<Paciente>& pacientes, const vector<Medico>& medicos, const vector<Cita>& citas);
void mostrarTodosPacientes(const vector<Paciente>& pacientes);
void mostrarTodosMedicos(const vector<Medico>& medicos);

int main() {
    vector<Paciente> pacientes;
    vector<Medico> medicos;
    vector<Cita> citas;

    pacientes.push_back(Paciente("Manolito Churrero", 172, "23/11/2024"));
    pacientes.push_back(Paciente("Ivan Butanero", 203, "15/11/2024"));

    pacientes[0].registrarHistorial("Diagnóstico: Gripe, Tratamiento: Antibióticos por 7 días");
    pacientes[1].registrarHistorial("Diagnóstico: Dolor de espalda crónico, Tratamiento: Fisioterapia semanal");

    medicos.push_back(Medico("Daniel Ferre", 431, "Cardiología", true));
    medicos.push_back(Medico("Yucum Bala", 622, "Pediatría", false));

    citas.push_back(Cita("25/11/2024", "Alta", pacientes[0], medicos[0]));
    citas.push_back(Cita("28/11/2024", "Media", pacientes[1], medicos[1]));

    int opcion;

    do {
        menuPrincipal();
        cin >> opcion;
        switch (opcion) {
        case 1:
            gestionarPacientes(pacientes);
            break;
        case 2:
            gestionarMedicos(medicos);
            break;
        case 3:
            gestionarCitas(citas, pacientes, medicos);
            break;
        case 4:
            generarReportes(citas);
            break;
        case 0:
            cout << "Saliendo del programa.\n";
            break;
        default:
            cout << "Opción no válida.\n";
        }
    } while (opcion != 0);

    guardarDatosCSV(pacientes, medicos, citas);

    return 0;
}

void menuPrincipal() {
    cout << "\n=== Menú Principal ===\n";
    cout << "1. Gestionar Pacientes\n";
    cout << "2. Gestionar Médicos\n";
    cout << "3. Gestionar Citas\n";
    cout << "4. Generar Reportes\n";
    cout << "0. Salir\n";
    cout << "Ingrese una opción: ";
}

bool validarFecha(const string& fecha) {
    regex formatoFecha("^\\d{2}/\\d{2}/\\d{4}$");
    if (regex_match(fecha, formatoFecha)) {
        return true;
    }
    cout << "La fecha introducida no es correcta. Debe ser DD/MM/AAAA.\n";
    return false;
}

void guardarDatosCSV(const vector<Paciente>& pacientes, const vector<Medico>& medicos, const vector<Cita>& citas) {

    ofstream archivoPaciente("paciente_datos.csv");
    if (archivoPaciente.is_open()) {
        archivoPaciente << "ID,Nombre,Fecha de Ingreso,Historial Clínico\n";
        for (const auto& paciente : pacientes) {
            archivoPaciente << paciente.getId() << ","
                << paciente.getNombre() << ","
                << paciente.getFechaIngreso() << ",";
            const auto& historial = paciente.getHistorial();
            for (size_t i = 0; i < historial.size(); ++i) {
                archivoPaciente << historial[i];
                if (i != historial.size() - 1) {
                    archivoPaciente << "|";
                }
            }
            archivoPaciente << "\n";
        }
        archivoPaciente.close();
        cout << "Datos de pacientes guardados.\n";
    }
    else {
        cout << "No se pudo abrir el archivo de pacientes.\n";
    }

    ofstream archivoMedico("medico_datos.csv");
    if (archivoMedico.is_open()) {
        archivoMedico << "ID,Nombre,Especialidad,Disponibilidad\n";
        for (const auto& medico : medicos) {
            archivoMedico << medico.getId() << ","
                << medico.getNombre() << ","
                << medico.getEspecialidad() << ","
                << (medico.getDisponibilidad() ? "Disponible" : "No disponible") << "\n";
        }
        archivoMedico.close();
        cout << "Datos de médicos guardados.\n";
    }
    else {
        cout << "No se pudo abrir el archivo de médicos.\n";
    }

    ofstream archivoCita("cita_datos.csv");
    if (archivoCita.is_open()) {
        archivoCita << "Fecha,Urgencia,Paciente_ID,Medico_ID\n";
        for (const auto& cita : citas) {
            archivoCita << cita.getFecha() << ","
                << cita.getUrgencia() << ","
                << cita.getPaciente().getId() << ","
                << cita.getMedico().getId() << "\n";
        }
        archivoCita.close();
        cout << "Datos de citas guardados.\n";
    }
    else {
        cout << "No se pudo abrir el archivo de citas.\n";
    }
}

void mostrarTodosPacientes(const vector<Paciente>& pacientes) {
    if (pacientes.empty()) {
        cout << "No hay pacientes registrados.\n";
    }
    else {
        cout << "Listado de pacientes:\n";
        for (const auto& paciente : pacientes) {
            cout << "Nombre: " << paciente.getNombre() << ", ID: " << paciente.getId() << ", Fecha de Ingreso: " << paciente.getFechaIngreso() << "\n";
        }
    }
}
void gestionarPacientes(vector<Paciente>& pacientes) {
    cout << "\nGestion de Pacientes\n";
    cout << "1. Registrar nuevo paciente\n";
    cout << "2. Buscar paciente por ID\n";
    cout << "3. Editar paciente por ID\n";
    cout << "4. Eliminar paciente por ID\n";
    cout << "5. Listar todos los pacientes\n";
    cout << "6. Gestionar historial clinico de un paciente\n";
    cout << "Ingrese una opcion: ";

    int opcion;
    cin >> opcion;

    if (opcion == 1) { 
        string nombre, fechaIngreso;
        int id;

        cin.ignore(); 
        cout << "Ingrese el nombre del paciente: ";
        getline(cin, nombre);
        cout << "Ingrese el ID del paciente: ";
        cin >> id;
        cin.ignore(); 
        cout << "Ingrese la fecha de ingreso (dd/mm/aaaa): ";
        getline(cin, fechaIngreso);

        Paciente nuevoPaciente(nombre, id, fechaIngreso);
        pacientes.push_back(nuevoPaciente);
        cout << "Paciente registrado exitosamente.\n";
    }
    else if (opcion == 2) { 
        cout << "Ingrese el ID del paciente a buscar: ";
        int id;
        cin >> id;
        bool encontrado = false;

        for (const auto& paciente : pacientes) {
            if (paciente.getId() == id) {
                encontrado = true;
                cout << "Paciente encontrado:\n";
                cout << "Nombre: " << paciente.getNombre() << "\n";
                cout << "ID: " << paciente.getId() << "\n";
                cout << "Fecha de Ingreso: " << paciente.getFechaIngreso() << "\n";
                break;
            }
        }

        if (!encontrado) {
            cout << "No se encontró un paciente con el ID " << id << ".\n";
        }
    }

    else if (opcion == 3) { 
        cout << "Ingrese el ID del paciente a editar: ";
        int id;
        cin >> id;
        bool encontrado = false;

        for (auto& paciente : pacientes) {
            if (paciente.getId() == id) {
                encontrado = true;
                string nombre, fechaIngreso;

                cin.ignore();
                cout << "Ingrese el nuevo nombre del paciente: ";
                getline(cin, nombre);
                cout << "Ingrese la nueva fecha de ingreso (dd/mm/aaaa): ";
                getline(cin, fechaIngreso);

                paciente.setNombre(nombre); 
                paciente.setFechaIngreso(fechaIngreso);

                cout << "Datos del paciente actualizados.\n";
                break;
            }
        }

        if (!encontrado) {
            cout << "No se encontró un paciente con el ID " << id << ".\n";
        }
    }
    else if (opcion == 4) { 
        cout << "Ingrese el ID del paciente a eliminar: ";
        int id;
        cin >> id;
        auto it = pacientes.begin();
        bool encontrado = false;

        while (it != pacientes.end()) {
            if (it->getId() == id) {
                encontrado = true;
                pacientes.erase(it);
                cout << "Paciente eliminado exitosamente.\n";
                break;
            }
            ++it;
        }

        if (!encontrado) {
            cout << "No se encontró un paciente con el ID " << id << ".\n";
        }
    }
    else if (opcion == 5) {
        mostrarTodosPacientes(pacientes);
    }
    else if (opcion == 6) { 
        cout << "Ingrese el ID del paciente para gestionar su historial clínico: ";
        int id;
        cin >> id;
        bool encontrado = false;

        for (auto& paciente : pacientes) {
            if (paciente.getId() == id) {
                encontrado = true;
                int historialOpcion;
                do {
                    cout << "\nGestionar Historial Clínico\n";
                    cout << "1. Ver historial clínico\n";
                    cout << "2. Actualizar historial\n";
                    cout << "3. Volver al menú de pacientes\n";
                    cout << "Ingrese una opcion: ";
                    cin >> historialOpcion;

                    if (historialOpcion == 1) { 
                        const vector<string>& historial = paciente.getHistorial();
                        if (historial.empty()) {
                            cout << "El paciente no tiene historial clínico registrado.\n";
                        }
                        else {
                            cout << "Historial clínico:\n";
                            for (const auto& entrada : historial) {
                                cout << entrada << "\n";
                            }
                        }
                    }

                    else if (historialOpcion == 2) { 

                        cin.ignore(); 
                        string diagnostico, tratamiento;
                        cout << "Ingrese el diagnóstico: ";
                        getline(cin, diagnostico);
                        cout << "Ingrese el tratamiento: ";
                        getline(cin, tratamiento);

                        string entrada = "Diagnóstico: " + diagnostico + ", Tratamiento: " + tratamiento;
                        paciente.registrarHistorial(entrada);
                        cout << "Entrada registrada en el historial clínico.\n";
                    }

                } while (historialOpcion != 3);

                break;
            }
        }

        if (!encontrado) {
            cout << "No se encontró un paciente con el ID " << id << ".\n";
        }
    }
    else {
        cout << "Opción inválida. Intente nuevamente.\n";
    }
}

void mostrarTodosMedicos(const vector<Medico>& medicos) {
    cout << "=== Lista de Médicos ===\n";
    for (const auto& medico : medicos) {
        cout << "ID: " << medico.getId() << ", Nombre: " << medico.getNombre()
            << ", Especialidad: " << medico.getEspecialidad()
            << ", Disponibilidad: " << (medico.getDisponibilidad() ? "Disponible" : "No disponible") << "\n";
    }
}

void gestionarMedicos(vector<Medico>& medicos) {
    cout << "Gestion de Medicos\n";
    cout << "1.Dar de alta\n";
    cout << "2.Dar de baja\n";
    cout << "3.Asignar especialidad\n";
    cout << "4.Mostrar todos los medicos\n";
    cout << "Ingrese una opcion:";
    int opcion;
    cin >> opcion;

    if (opcion == 1) {
        string nombre, especialidad;
        int id;
        bool disponibilidad;
        cout << "Nombre:";
        cin.ignore();
        getline(cin, nombre);
        cout << "ID:";
        cin >> id;
        cout << "Especialidad:";
        cin.ignore();
        getline(cin, especialidad);
        cout << "Disponibilidad (1 para disponible, 0 para no disponible):";
        cin >> disponibilidad;
        medicos.push_back(Medico(nombre, id, especialidad, disponibilidad));
        cout << "Medico dado de alta correctamente.\n";
    }

    else if (opcion == 2) {
        cout << "Ingrese el ID del medico a dar de baja:";
        int id;
        cin >> id;

        for (auto it = medicos.begin(); it != medicos.end(); ++it) {

            if (it->getId() == id) {
                cout << "Medico " << it->getNombre() << " dado de baja.\n";
                medicos.erase(it);
                break;
            }
        }
    }

    else if (opcion == 3) {
        cout << "Ingrese el ID del medico para asignar nueva especialidad:";
        int id;
        cin >> id;
        for (auto& medico : medicos) {
            if (medico.getId() == id) {
                cout << "Ingrese la nueva especialidad:";
                string especialidad;
                cin.ignore();
                getline(cin, especialidad);
                medico.asignarEspecialidad(especialidad);
                break;
            }
        }
    }
    else if (opcion == 4) {
        mostrarTodosMedicos(medicos);
    }
}

void gestionarCitas(vector<Cita>& citas, vector<Paciente>& pacientes, vector<Medico>& medicos) {
    cout << "Gestion de Citas\n";
    cout << "1. Asignar nueva cita\n";
    cout << "2. Cancelar cita\n";
    cout << "Ingrese una opcion: ";
    int opcion;
    cin >> opcion;
    if (opcion == 1) {
        string fecha, urgencia;
        int idPaciente, idMedico;
        do {
            cout << "Fecha (DD/MM/AAAA):";
            cin >> fecha;
        } while (!validarFecha(fecha));
        cout << "Urgencia:";
        cin >> urgencia;
        cout << "ID del Paciente:";
        cin >> idPaciente;
        cout << "ID del Medico:";
        cin >> idMedico;

        Paciente* paciente = nullptr;
        for (auto& p : pacientes) {
            if (p.getId() == idPaciente) {
                paciente = &p;
                break;
            }
        }
        if (!paciente) {
            cout << "No se ha encontrado un paciente con el ID " << idPaciente << ".\n";
            return;
        }
        Medico* medico = nullptr;
        for (auto& m : medicos) {
            if (m.getId() == idMedico) {
                medico = &m;
                break;
            }
        }
        if (!medico) {
            cout << "No se ha encontrado un medico con el ID " << idMedico << ".\n";
            return;
        }

        citas.push_back(Cita(fecha, urgencia, *paciente, *medico));
        cout << "Cita asignada correctamente.\n";

    }
    else if (opcion == 2) {
        cout << "Ingrese la fecha de la cita a cancelar (DD/MM/AA):";
        string fecha;
        do {
            cin >> fecha;
        } while (!validarFecha(fecha));

        for (auto it = citas.begin(); it != citas.end(); ++it) {
            if (it->getFecha() == fecha) {
                cout << "Cita del " << it->getFecha() << " cancelada.\n";
                citas.erase(it);
                break;
            }
        }
    }
}

void generarReportes(vector<Cita>& citas) {
    cout << "Generando reportes de citas\n";
    for (const auto& cita : citas) {
        cout << "Fecha:" << cita.getFecha()
            << ",Paciente:" << cita.getPaciente().getNombre()
            << ",Medico:" << cita.getMedico().getNombre()
            << ",Urgencia:" << cita.getUrgencia() << "\n";
    }
}