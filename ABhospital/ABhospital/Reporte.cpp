#include "Reporte.h"
#include <iostream>

using namespace std;


Reporte::Reporte(string inicio, string fin) : fechaInicio(inicio), fechaFin(fin) {}

void Reporte::generarListadoPacientesAtendidos(const vector<Cita>& citas) {
    cout << "Pacientes atendidos entre " << fechaInicio << " y " << fechaFin << ":\n";
    for (const auto& cita : citas) {
        cout << "- " << cita.getPaciente().getNombre()
            << " atendido por " << cita.getMedico().getNombre() << "\n";
    }
}

void Reporte::listarCitasPendientes(const vector<Cita>& citas) {
    cout << "Citas pendientes:\n";
    for (const auto& cita : citas) {

        cout << "- Paciente: " << cita.getPaciente().getNombre()
            << ", Medico: " << cita.getMedico().getNombre() << "\n";
    }
}