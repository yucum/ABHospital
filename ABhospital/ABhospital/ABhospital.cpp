#include <iostream>
#include <vector>
#include <regex>
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

int main() {
    vector<Paciente> pacientes;
    vector<Medico> medicos;
    vector<Cita> citas;

    pacientes.push_back(Paciente("Manolito Churrero", 172, "23/11/24"));
    pacientes.push_back(Paciente("Ivan Butanero", 203, "15/11/24"));

    medicos.push_back(Medico("Daniel Ferre", 431, "Cardiologia", true));
    medicos.push_back(Medico("Yucum Bala", 622, "Pediatria", false));

    citas.push_back(Cita("25/11/24", "Alta", pacientes[0], medicos[0]));
    citas.push_back(Cita("28/11/24", "Media", pacientes[1], medicos[1]));

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
    } while (opcion != 0);

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

bool validarFecha(const string& fecha) {
    regex formatoFecha("^\\d{2}/\\d{2}/\\d{4}$");
    if (regex_match(fecha, formatoFecha)) {
        return true;
    }
    cout << "La fecha introducida no es correcta. Debe ser DD/MM/AAAA.\n";
    return false;
}

void gestionarPacientes(vector<Paciente>& pacientes) {
    cout << "Gestion de Pacientes\n";
    cout << "1.Dar de alta\n";
    cout << "2.Dar de baja\n";
    cout << "3.Modificar datos personales\n";
    cout << "4.Buscar paciente\n";
    cout << "5.Mostrar historial clinico\n";
    cout << "Ingrese una opcion: ";
    int opcion;
    cin >> opcion;


    if (opcion == 1) {
        string nombre, fecha;
        int id;
        cout << "Nombre: ";
        cin.ignore();
        getline(cin, nombre);
        cout << "ID: ";
        cin >> id;
        do {
            cout << "Fecha de ingreso (DD/MM/AA): ";
            cin >> fecha;
        } while (!validarFecha(fecha));

        pacientes.push_back(Paciente(nombre, id, fecha));
        cout << "Paciente dado de alta correctamente.\n";

    }
    else if (opcion == 2) {
        cout << "Ingrese el ID del paciente a dar de baja: ";
        int id;
        cin >> id;
        for (auto it = pacientes.begin(); it != pacientes.end(); ++it) {
            if (it->getId() == id) {
                cout << "Paciente " << it->getNombre() << " dado de baja.\n";
                pacientes.erase(it);
                break;
            }
        }
    }

    else if (opcion == 3) {
        cout << "Ingrese el ID del paciente a modificar: ";
        int id;
        cin >> id;

        for(auto& paciente : pacientes) {
            if (paciente.getId() == id) {
                cout << "Modificar:\n1.Nombre\n2.ID\n3.Fecha de ingreso\nIngrese una opcion: ";
                int subopcion;
                cin >> subopcion;

                if (subopcion == 1) {
                    cout << "Nuevo nombre: ";
                    string nuevoNombre;
                    cin.ignore();
                    getline(cin, nuevoNombre);
                    paciente.setNombre(nuevoNombre);
                }

                else if (subopcion == 2) {
                    cout << "Nuevo ID: ";
                    int nuevoId;
                    cin >> nuevoId;
                    paciente.setId(nuevoId);
                }

                else if (subopcion == 3) {
                    string nuevaFecha;
                    do {
                        cout << "Nueva fecha de ingreso (DD/MM/AA):";
                        cin >> nuevaFecha;
                    } while (!validarFecha(nuevaFecha));
                    paciente.setFechaIngreso(nuevaFecha);
                }
                break;
            }
        }
    }

    else if(opcion == 4) {
        cout << "Buscar por:\n1.Nombre\n2.ID\n3.Fecha de ingreso\nIngrese una opcion: ";
        int subopcion;
        cin >> subopcion;
        if (subopcion == 1) {
            cout << "Ingrese el nombre:";
            string nombre;
            cin.ignore();
            getline(cin, nombre);
            for (const auto& paciente : pacientes) {
                if (paciente.getNombre() == nombre) {
                    cout << "-Nombre: " << paciente.getNombre() << ",ID: " << paciente.getId()
                        << ",Fecha de ingreso: " << paciente.getFechaIngreso() << "\n";
                }
            }
        }

        else if(subopcion == 2) {
            cout << "Ingrese el ID:";
            int id;
            cin >> id;
            for (const auto& paciente : pacientes) {
                if (paciente.getId() == id) {
                    cout << "- Nombre:" << paciente.getNombre() << ", ID:" << paciente.getId()
                        << ", Fecha de ingreso:" << paciente.getFechaIngreso() << "\n";
                }
            }
        }
        else if(subopcion == 3) {
            string fecha;
            do {
                cout << "Ingrese la fecha de ingreso (DD/MM/AA):";
                cin >> fecha;
            } while (!validarFecha(fecha));


            for (const auto& paciente : pacientes) {
                if (paciente.getFechaIngreso() == fecha) {
                    cout << "- Nombre:" << paciente.getNombre() << ",ID:" << paciente.getId()
                        << ", Fecha de ingreso:" << paciente.getFechaIngreso() << "\n";
                }
            }
        }
    }

    else if(opcion == 5) {
        cout << "Ingrese el ID del paciente para ver su historial clinico:";
        int id;
        cin >> id;
        for (const auto& paciente : pacientes) {
            if (paciente.getId() == id) {
                cout << "Historial clinico de " << paciente.getNombre() << ":\n";
                for (const auto& entrada : paciente.getHistorialClinico()) {
                    cout << "- " << entrada << "\n";
                }
                break;
            }
        }
    }
}

void gestionarMedicos(vector<Medico>& medicos) {
    cout << "Gestion de Medicos\n";
    cout << "1.Dar de alta\n";
    cout << "2.Dar de baja\n";
    cout << "3.Asignar especialidad\n";
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
    cout <<"Generando reportes de citas\n";
    for (const auto& cita : citas) {
        cout << "Fecha:" << cita.getFecha()
            << ",Paciente:" << cita.getPaciente().getNombre()
            << ",Medico:" << cita.getMedico().getNombre()
            << ",Urgencia:" << cita.getUrgencia() << "\n";
    }
}
