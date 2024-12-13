﻿#include <iostream>
#include <vector>
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

int main() {
    vector<Paciente> pacientes;
    vector<Medico> medicos;
    vector<Cita> citas;

    pacientes.push_back(Paciente("Manolito Churrero", 172, "23/11/2024"));
    pacientes.push_back(Paciente("Ivan Butanero", 203, "15/11/2024"));

    medicos.push_back(Medico("Daniel Ferre", 431, "Cardiologia", true));
    medicos.push_back(Medico("Yucum Bala", 622, "Pediatria", false));

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
            cout << "Opcion no valida.\n";
        }
    } while(opcion != 0);

    return 0;
}

void menuPrincipal() {
    cout << "\n=== Menu ===\n";
    cout << "1. Gestionar Pacientes\n";
    cout << "2. Gestionar Medicos\n";
    cout << "3. Gestionar Citas\n";
    cout << "4. Generar Reportes\n";
    cout << "0. Salir\n";
    cout << "Ingrese una opcion: ";
}

void gestionarPacientes(vector<Paciente>& pacientes) {
    cout << "Gestion de Pacientes\n";
    cout << "1. Dar de alta\n";
    cout << "2. Dar de baja\n";
    cout << "3. Registrar historial\n";
    cout << "4. Mostrar listado de pacientes\n";
    cout << "Ingrese una opcion: ";
    int opcion;
    cin >> opcion;

    if(opcion == 1) {
        string nombre, fecha;
        int id;
        cout << "Nombre: ";
        cin.ignore();
        getline(cin, nombre);
        cout << "ID: ";
        cin >> id;
        cout << "Fecha de ingreso (DD/MM/AAAA): ";
        cin >> fecha;
        pacientes.push_back(Paciente(nombre, id, fecha));
        pacientes.back().altaPaciente();
    }

    else if(opcion == 2) {
        cout << "Ingrese el ID del paciente a dar de baja: ";
        int id;
        cin >> id;
        for (auto it = pacientes.begin(); it != pacientes.end(); ++it) {
            if (it->getId() == id) {
                it->bajaPaciente();
                pacientes.erase(it);
                break;
            }
        }
    }

    else if(opcion == 3) {
        cout << "Ingrese el ID del paciente para registrar historial: ";
        int id;
        cin >> id;
        for (auto& paciente : pacientes) {
            if (paciente.getId() == id) {
                paciente.registrarHistorial();
                break;
            }
        }
    }
    else if(opcion == 4) {
        cout << "Listado de pacientes:\n";
        for (const auto& paciente : pacientes) {
            cout << "- Nombre: " << paciente.getNombre() << ", ID: " << paciente.getId() << "\n";
        }
    }
}

void gestionarMedicos(vector<Medico>& medicos) {
    cout << "Gestion de Medicos\n";
    cout << "1. Dar de alta\n";
    cout << "2. Dar de baja\n";
    cout << "3. Asignar especialidad\n";
    cout << "4. Mostrar listado de medicos\n";
    cout << "Ingrese una opcion: ";
    int opcion;
    cin >> opcion;

    if(opcion == 1) {
        string nombre, especialidad;
        int id;
        bool disponibilidad;
        cout << "Nombre: ";
        cin.ignore();
        getline(cin, nombre);
        cout << "ID: ";
        cin >> id;
        cout << "Especialidad: ";
        cin.ignore();
        getline(cin, especialidad);
        cout << "Disponibilidad (1 para disponible, 0 para no disponible): ";
        cin >> disponibilidad;
        medicos.push_back(Medico(nombre, id, especialidad, disponibilidad));
        medicos.back().altaMedico();
    }
    else if(opcion == 2) {
        cout << "Ingrese el ID del medico a dar de baja: ";
        int id;
        cin >> id;
        for (auto it = medicos.begin(); it != medicos.end(); ++it) {
            if (it->getId() == id) {
                it->bajaMedico();
                medicos.erase(it);
                break;
            }
        }
    }
    else if(opcion == 3) {
        cout << "Ingrese el ID del medico para asignar nueva especialidad: ";
        int id;
        cin >> id;

        for (auto& medico : medicos) {
            if (medico.getId() == id) {
                cout << "Ingrese la nueva especialidad: ";
                string especialidad;
                cin.ignore();
                getline(cin, especialidad);
                medico.asignarEspecialidad(especialidad);
                break;
            }
        }
    }

    else if(opcion == 4) {
        cout << "Listado de medicos:\n";
        for (const auto& medico : medicos) {
            cout << "- Nombre: " << medico.getNombre() << ", ID: " << medico.getId()
                << ", Especialidad: " << medico.getEspecialidad()
                << ", Disponibilidad: " << (medico.getDisponibilidad() ? "Disponible" : "No disponible") << "\n";
        }
    }
}

void gestionarCitas(vector<Cita>& citas, vector<Paciente>& pacientes, vector<Medico>& medicos) {
    cout << "Gestion de Citas\n";
    cout << "1. Asignar nueva cita\n";
    cout << "2. Cancelar cita\n";
    cout << "Ingrese una opcion: ";
    int opcion;
    cin >> opcion;

    if(opcion == 1) {
        string fecha, urgencia;
        int idPaciente, idMedico;
        cout << "Fecha (DD/MM/AAAA): ";
        cin >> fecha;
        cout << "Urgencia: ";
        cin >> urgencia;
        cout << "ID del Paciente: ";
        cin >> idPaciente;
        cout << "ID del Medico: ";
        cin >> idMedico;

        Paciente* paciente = nullptr;

        for(auto& p : pacientes) {
            if (p.getId() == idPaciente) {
                paciente = &p;
                break;
            }
        }

        if(!paciente) {
            cout << "No se ha encontrado un paciente con el ID " << idPaciente << ".\n";
            return;
        }

        Medico* medico = nullptr;
        for(auto& m : medicos) {
            if (m.getId() == idMedico) {
                medico = &m;
                break;
            }
        }
        if(!medico) {
            cout << "No se ha encontrado un medico con el ID " << idMedico << ".\n";
            return;
        }

        citas.push_back(Cita(fecha, urgencia, *paciente, *medico));
        citas.back().asignarCita();
    }
    else if(opcion == 2) {
        cout << "Ingrese el indice de la cita a cancelar: ";
        int index;
        cin >> index;
        if (index >= 0 && index < citas.size()) {
            citas[index].cancelarCita();
            citas.erase(citas.begin() + index);
        }
        else {
            cout << "Indice invalido.\n";
        }
    }
}

void generarReportes(vector<Cita>& citas) {
    cout << "Reportes\n";
    cout << "1. Listar pacientes atendidos\n";
    cout << "2. Listar citas pendientes\n";
    cout << "Ingrese una opcion: ";
    int opcion;
    cin >> opcion;

    if(opcion == 1) {
        cout << "Ingrese la fecha de inicio (DD/MM/AAAA): ";
        string inicio, fin;
        cin >> inicio;
        cout << "Ingrese la fecha de fin (DD/MM/AAAA): ";
        cin >> fin;
        Reporte reporte(inicio, fin);
        reporte.generarListadoPacientesAtendidos(citas);
    }
    else if(opcion == 2) {
        Reporte reporte("", "");
        reporte.listarCitasPendientes(citas);
    }
}
