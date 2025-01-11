#include <iostream>
#include <locale>
#include <vector>
#include <regex>
#include <fstream>
#define NOMINMAX
#include <limits>
#include "Paciente.h"
#include "Medico.h"
#include "Cita.h"
#include "Reporte.h"

using namespace std;

void menuPrincipal();
void gestionarPacientes(vector<Paciente>& pacientes);
void gestionarMedicos(vector<Medico>& medicos);
void gestionarCitas(vector<Cita>& citas, vector<Paciente>& pacientes, vector<Medico>& medicos);
void gestionarReportes(const vector<Cita>& citas, const vector<Paciente>& pacientes);
bool validarFecha(const string& fecha);
void guardarDatosCSV(const vector<Paciente>& pacientes, const vector<Medico>& medicos, const vector<Cita>& citas);
void mostrarTodosPacientes(const vector<Paciente>& pacientes);
void mostrarTodosMedicos(const vector<Medico>& medicos);



int main() {
    //UTF-8
    locale::global(locale(""));
    wcin.imbue(locale());
    wcout.imbue(std::locale());
    ios::sync_with_stdio(false);

    vector<Paciente> pacientes;
    vector<Medico> medicos;
    vector<Cita> citas;

    pacientes.push_back(Paciente("Manolito Churrero", 172, "23/11/2024"));
    pacientes.push_back(Paciente("Ivan Butanero", 203, "15/11/2024"));

    pacientes[0].registrarHistorial("Diagnóstico: Gripe, Tratamiento: Antibióticos por 7 días");
    pacientes[1].registrarHistorial("Diagnóstico: Dolor de espalda crónico, Tratamiento: Fisioterapia semanal");

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
            gestionarReportes(citas, pacientes);
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
    cout << "4. Gestionar Reportes\n";
    cout << "0. Salir\n";
    cout << "Ingrese una opción: ";
}

bool validarFecha(const string& fecha) {
    regex formatoFecha("^\\d{2}/\\d{2}/\\d{4}$");  
    if (regex_match(fecha, formatoFecha)) {
        int dia = stoi(fecha.substr(0, 2));
        int mes = stoi(fecha.substr(3, 2));
        

        if (dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12) {
            return true;
        }
    }
    cout << "La fecha introducida no es correcta. Debe ser en formato DD(01-31)/MM(01-12)/AAAA.\n";
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

    ofstream archivoBackup("backup_datos.csv");
    if (archivoBackup.is_open()) {

        archivoBackup << "Pacientes\n";
        archivoBackup << "ID,Nombre,Fecha de Ingreso,Historial Clínico\n";
        for (const auto& paciente : pacientes) {
            archivoBackup << paciente.getId() << ","
                << paciente.getNombre() << ","
                << paciente.getFechaIngreso() << ",";
            const auto& historial = paciente.getHistorial();
            for (size_t i = 0; i < historial.size(); ++i) {
                archivoBackup << historial[i];
                if (i != historial.size() - 1) {
                    archivoBackup << "|";
                }
            }
            archivoBackup << "\n";
        }

        archivoBackup << "\nMédicos\n";
        archivoBackup << "ID,Nombre,Especialidad,Disponibilidad\n";
        for (const auto& medico : medicos) {
            archivoBackup << medico.getId() << ","
                << medico.getNombre() << ","
                << medico.getEspecialidad() << ","
                << (medico.getDisponibilidad() ? "Disponible" : "No disponible") << "\n";
        }

        archivoBackup << "\nCitas\n";
        archivoBackup << "Fecha,Urgencia,Paciente_ID,Medico_ID\n";
        for (const auto& cita : citas) {
            archivoBackup << cita.getFecha() << ","
                << cita.getUrgencia() << ","
                << cita.getPaciente().getId() << ","
                << cita.getMedico().getId() << "\n";
        }

        archivoBackup.close();
        cout << "Datos de respaldo guardados en backup_datos.csv.\n";
    }
    else {
        cout << "No se pudo abrir el archivo de backup.\n";
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
    cout << "6. Gestionar historial clínico\n";
    cout << "Ingrese una opcion: ";

    int opcion;
    cin >> opcion;

    if (opcion == 1) {
        string nombre, fechaIngreso;
        int id;

        cin.ignore();
        cout << "Ingrese el nombre del paciente: ";
        getline(cin, nombre);

        bool idUnico;
        do {
            idUnico = true;
            cout << "Ingrese el ID del paciente: ";
            while (!(cin >> id)) {
                cout << "Entrada inválida. Por favor, ingrese solo números.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ingrese el ID del paciente: ";
            }
            for (const auto& paciente : pacientes) {
                if (paciente.getId() == id) {
                    cout << "El ID ya existe. Ingrese un ID único.\n";
                    idUnico = false;
                    break;
                }
            }
        } while (!idUnico);

        cin.ignore();
        do {
            cout << "Ingrese la fecha de ingreso (DD/MM/AAAA): ";
            getline(cin, fechaIngreso);
        } while (!validarFecha(fechaIngreso));

        Paciente nuevoPaciente(nombre, id, fechaIngreso);
        pacientes.push_back(nuevoPaciente);
        cout << "Paciente registrado exitosamente.\n";
    }
    else if (opcion == 2) {
        cout << "Ingrese el ID del paciente a buscar: ";
        int id;
        while (!(cin >> id)) {
            cout << "Entrada incorrecta. Por favor, ingrese solo números.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese el ID del paciente a buscar: ";
        }
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
        while (!(cin >> id)) {
            cout << "Entrada incorrecta. Por favor, ingrese solo números.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese el ID del paciente a editar: ";
        }
        bool encontrado = false;

        for (auto& paciente : pacientes) {
            if (paciente.getId() == id) {
                encontrado = true;
                string nombre, fechaIngreso;

                cin.ignore();
                cout << "Ingrese el nuevo nombre del paciente: ";
                getline(cin, nombre);

                do {
                    cout << "Ingrese la nueva fecha de ingreso (DD/MM/AAAA): ";
                    getline(cin, fechaIngreso);
                } while (!validarFecha(fechaIngreso));

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
        while (!(cin >> id)) {
            cout << "Entrada incorrecta. Por favor, ingrese solo números.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese el ID del paciente a eliminar: ";
        }
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
        cout << "Opción no válida. Intente nuevamente.\n";
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

        cin.ignore();
        cout << "Ingrese el nombre del médico: ";
        getline(cin, nombre);

        bool idUnico;
        do {
            idUnico = true;
            cout << "Ingrese el ID del médico: ";
            while (!(cin >> id)) {
                cout << "Entrada incorrecta. Por favor, ingrese solo números.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ingrese el ID del médico: ";
            }
            for (const auto& medico : medicos) {
                if (medico.getId() == id) {
                    cout << "El ID ya existe. Ingrese un ID único.\n";
                    idUnico = false;
                    break;
                }
            }
        } while (!idUnico);

        cin.ignore();
        cout << "Ingrese la especialidad: ";
        getline(cin, especialidad);

        cout << "Ingrese la disponibilidad (1 para disponible, 0 para no disponible): ";
        while (!(cin >> disponibilidad)) {
            cout << "Entrada inválida. Por favor, ingrese 1 o 0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        medicos.push_back(Medico(nombre, id, especialidad, disponibilidad));
        cout << "Médico registrado exitosamente.\n";
    }
    else if (opcion == 2) {
        cout << "Ingrese el ID del medico a dar de baja: ";
        int id;
        while (!(cin >> id)) {
            cout << "Entrada incorrecta. Por favor, ingrese solo números.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese el ID del medico a dar de baja: ";
        }

        bool encontrado = false;
        for (auto it = medicos.begin(); it != medicos.end(); ++it) {
            if (it->getId() == id) {
                cout << "Medico " << it->getNombre() << " dado de baja.\n";
                medicos.erase(it);
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            cout << "No se encontró un médico con el ID proporcionado.\n";
        }
    }
    else if (opcion == 3) {
        cout << "Ingrese el ID del medico para asignar nueva especialidad: ";
        int id;
        while (!(cin >> id)) {
            cout << "Entrada incorrecta. Por favor, ingrese solo números.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese el ID del medico para asignar nueva especialidad: ";
        }

        bool encontrado = false;
        for (auto& medico : medicos) {
            if (medico.getId() == id) {
                cout << "Ingrese la nueva especialidad: ";
                cin.ignore();
                string especialidad;
                getline(cin, especialidad);
                medico.asignarEspecialidad(especialidad);
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            cout << "No se encontró un médico con el ID proporcionado.\n";
        }
    }
    else if (opcion == 4) {
        mostrarTodosMedicos(medicos);
    }
    else {
        cout << "Opción no válida. Intente nuevamente.\n";
    }
}

void gestionarCitas(vector<Cita>& citas, vector<Paciente>& pacientes, vector<Medico>& medicos) {
    cout << "\nGestion de Citas\n";
    cout << "1. Registrar nueva cita\n";
    cout << "2. Cancelar cita existente\n";
    cout << "3. Mostrar todas las citas\n";
    cout << "4. Modificar cita existente\n";
    cout << "Ingrese una opcion: ";
    int opcion;
    cin >> opcion;

    if (opcion == 1) {
        string fecha, urgencia;
        int idPaciente, idMedico;

        do {
            cout << "Ingrese la fecha de la cita (DD/MM/AAAA): ";
            if (cin.peek() == '\n') cin.ignore();  // Limpia solo si hay un salto de línea pendiente
            getline(cin, fecha);
        } while (!validarFecha(fecha));

        cout << "Ingrese la urgencia (Alta, Media, Baja): ";
        getline(cin, urgencia);

        cout << "Ingrese el ID del paciente: ";
        while (!(cin >> idPaciente)) {
            cout << "Entrada incorrecta. Por favor, ingrese solo números.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese el ID del paciente: ";
        }

        cout << "Ingrese el ID del medico: ";
        while (!(cin >> idMedico)) {
            cout << "Entrada incorrecta. Por favor, ingrese solo números.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese el ID del medico: ";
        }

        Paciente* pacienteSeleccionado = nullptr;
        Medico* medicoSeleccionado = nullptr;

        for (auto& paciente : pacientes) {
            if (paciente.getId() == idPaciente) {
                pacienteSeleccionado = &paciente;
                break;
            }
        }

        for (auto& medico : medicos) {
            if (medico.getId() == idMedico) {
                medicoSeleccionado = &medico;
                break;
            }
        }

        if (pacienteSeleccionado && medicoSeleccionado) {
            citas.push_back(Cita(fecha, urgencia, *pacienteSeleccionado, *medicoSeleccionado));
            cout << "Cita registrada exitosamente.\n";
        }
        else {
            cout << "No se encontró el paciente o el médico con los IDs proporcionados.\n";
        }
    }
    else if (opcion == 2) {
        string fecha;
        do {
            cout << "Ingrese la fecha de la cita a cancelar (DD/MM/AAAA): ";
            if (cin.peek() == '\n') cin.ignore();
            getline(cin, fecha);
        } while (!validarFecha(fecha));

        auto it = citas.begin();
        bool encontrada = false;

        while (it != citas.end()) {
            if (it->getFecha() == fecha) {
                encontrada = true;
                citas.erase(it);
                cout << "Cita cancelada exitosamente.\n";
                break;
            }
            ++it;
        }

        if (!encontrada) {
            cout << "No se encontró una cita con la fecha proporcionada.\n";
        }
    }
    else if (opcion == 3) {

        if (citas.empty()) {
            cout << "No hay citas registradas.\n";
        }
        else {
            cout << "Listado de citas:\n";
            for (const auto& cita : citas) {
                cout << "Fecha: " << cita.getFecha()
                    << ", Urgencia: " << cita.getUrgencia()
                    << ", Paciente: " << cita.getPaciente().getNombre()
                    << ", Médico: " << cita.getMedico().getNombre() << "\n";
            }
        }
    }
    else if (opcion == 4) {
        string fecha;
        do {
            cout << "Ingrese la fecha de la cita a modificar (DD/MM/AAAA): ";
            if (cin.peek() == '\n') cin.ignore();
            getline(cin, fecha);
        } while (!validarFecha(fecha));

        bool encontrada = false;

        for (auto& cita : citas) {
            cout << "Cita encontrada:\n";
            cout << "Fecha: " << cita.getFecha()
                << ", Urgencia: " << cita.getUrgencia()
                << ", Paciente: " << cita.getPaciente().getNombre()
                << ", Médico: " << cita.getMedico().getNombre() << "\n";

            if (cita.getFecha() == fecha) {
                encontrada = true;
                cout << "Seleccione qué desea modificar:\n";
                cout << "1. Fecha\n";
                cout << "2. Urgencia\n";
                cout << "3. Paciente\n";
                cout << "4. Médico\n";
                cout << "Ingrese una opción: ";
                int opcionMod;
                cin >> opcionMod;

                if (opcionMod == 1) {
                    string nuevaFecha;
                    do {
                        cout << "Ingrese la nueva fecha (DD/MM/AAAA): ";
                        if (cin.peek() == '\n') cin.ignore();
                        getline(cin, nuevaFecha);
                    } while (!validarFecha(nuevaFecha));
                    cita.setFecha(nuevaFecha);
                    cout << "Fecha actualizada exitosamente.\n";
                }
                else if (opcionMod == 2) {
                    string nuevaUrgencia;
                    cout << "Ingrese la nueva urgencia (Alta, Media, Baja): ";
                    cin.ignore();
                    getline(cin, nuevaUrgencia);
                    cita.setUrgencia(nuevaUrgencia);
                    cout << "Urgencia actualizada exitosamente.\n";
                }
                else if (opcionMod == 3) {
                    int nuevoIdPaciente;
                    cout << "Ingrese el nuevo ID del paciente: ";
                    while (!(cin >> nuevoIdPaciente)) {
                        cout << "Entrada incorrecta. Por favor, ingrese solo números.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Ingrese el nuevo ID del paciente: ";
                    }

                    Paciente* nuevoPaciente = nullptr;
                    for (auto& paciente : pacientes) {
                        if (paciente.getId() == nuevoIdPaciente) {
                            nuevoPaciente = &paciente;
                            break;
                        }
                    }

                    if (nuevoPaciente) {
                        cita.setPaciente(*nuevoPaciente);
                        cout << "Paciente actualizado exitosamente.\n";
                    }
                    else {
                        cout << "No se encontró un paciente con el ID proporcionado.\n";
                    }
                }
                else if (opcionMod == 4) {
                    int nuevoIdMedico;
                    cout << "Ingrese el nuevo ID del médico: ";
                    while (!(cin >> nuevoIdMedico)) {
                        cout << "Entrada incorrecta. Por favor, ingrese solo números.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Ingrese el nuevo ID del médico: ";
                    }

                    Medico* nuevoMedico = nullptr;
                    for (auto& medico : medicos) {
                        if (medico.getId() == nuevoIdMedico) {
                            nuevoMedico = &medico;
                            break;
                        }
                    }

                    if (nuevoMedico) {
                        cita.setMedico(*nuevoMedico);
                        cout << "Médico actualizado exitosamente.\n";
                    }
                    else {
                        cout << "No se encontró un médico con el ID proporcionado.\n";
                    }
                }
                else {
                    cout << "Opción no válida.\n";
                }
                break;
            }
        }

        if (!encontrada) {
            cout << "No se encontró una cita con la fecha proporcionada.\n";
        }
    }
}


static bool compararFechas(const string& fecha1, const string& fecha2) {
    int dia1 = stoi(fecha1.substr(0, 2));
    int mes1 = stoi(fecha1.substr(3, 2));

    int dia2 = stoi(fecha2.substr(0, 2));
    int mes2 = stoi(fecha2.substr(3, 2));
    return dia1 <= dia2;
}

static void pacientesAtendidosEnRango(const vector<Cita>& citas, const string& fechaInicio, const string& fechaFin) {
    cout << "Pacientes atendidos entre " << fechaInicio << " y " << fechaFin << ":\n";
    for (const auto& cita : citas) {
        if (compararFechas(fechaInicio, cita.getFecha()) && compararFechas(cita.getFecha(), fechaFin)) {
            cout << "- " << cita.getPaciente().getNombre() << "\n";
        }
    }
}

static void citasPendientesPorMedico(const vector<Cita>& citas, const string& filtro, bool porEspecialidad = false) {
    cout << "Citas pendientes ";
    if (porEspecialidad) {
        cout << "por especialidad " << filtro << ":\n";
    }
    else {
        cout << "del médico " << filtro << ":\n";
    }

    for (const auto& cita : citas) {
        if ((porEspecialidad && cita.getMedico().getEspecialidad() == filtro) ||
            (!porEspecialidad && cita.getMedico().getNombre() == filtro)) {
            cout << "- Paciente: " << cita.getPaciente().getNombre() << ", Fecha: " << cita.getFecha() << "\n";
        }
    }
}

void gestionarReportes(const vector<Cita>& citas, const vector<Paciente>& pacientes) {
    int opcion;
    do {
        cout << "\n--- Reportes ---\n";
        cout << "1. Listado de pacientes atendidos en un rango de fechas\n";
        cout << "2. Citas pendientes por médico (ID)\n";
        cout << "3. Citas pendientes por especialidad\n";
        cout << "4. Volver\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string fechaInicio, fechaFin;
            do {
                cout << "Ingrese la fecha de inicio (DD/MM/AAAA): ";
                if (cin.peek() == '\n') cin.ignore();
                getline(cin, fechaInicio);
            } while (!validarFecha(fechaInicio));

            do {
                cout << "Ingrese la fecha de fin (DD/MM/AAAA): ";
                getline(cin, fechaFin);
            } while (!validarFecha(fechaFin));

            pacientesAtendidosEnRango(citas, fechaInicio, fechaFin);
            break;
        }
        case 2: {
            int idMedico;
            bool medicoEncontrado = false;
            do {
                cout << "Ingrese el ID del médico: ";
                while (!(cin >> idMedico)) {
                    cout << "Entrada incorrecta. Por favor, ingrese solo números.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Ingrese el ID del médico: ";
                }

                for (const auto& cita : citas) {
                    if (cita.getMedico().getId() == idMedico) {
                        medicoEncontrado = true;
                        break;
                    }
                }

                if (!medicoEncontrado) {
                    cout << "No se encontró un médico con ese ID.\n";
                }
            } while (!medicoEncontrado);

            cout << "Citas pendientes para el médico con ID " << idMedico << ":\n";
            for (const auto& cita : citas) {
                if (cita.getMedico().getId() == idMedico) {
                    cout << "Paciente: " << cita.getPaciente().getNombre() << ", Fecha: " << cita.getFecha() << "\n";
                }
            }
            break;
        }
        case 3: {
            string especialidad;
            cout << "Ingrese la especialidad: ";
            cin.ignore();
            getline(cin, especialidad);
            citasPendientesPorMedico(citas, especialidad, true);
            break;
        }
        case 4:
            cout << "Volviendo al menú principal...\n";
            break;
        default:
            cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 4);
}