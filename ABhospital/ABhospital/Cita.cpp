#include "Cita.h"
#include <iostream>

using namespace std;

Cita::Cita(string fecha, string urg, Paciente pac, Medico med)
    : fecha(fecha), urgencia(urg), paciente(pac), medico(med) {
}

void Cita::asignarCita() {
    cout << "Cita asignada el " << fecha << " con urgencia " << urgencia << "\n";
}

void Cita::cancelarCita() {
    cout << "Cita cancelada para el paciente " << paciente.getNombre() << "\n";
}

string Cita::getFecha() const {
    return fecha;
}

string Cita::getUrgencia() const {
    return urgencia;
}

Paciente Cita::getPaciente() const {
    return paciente;
}

Medico Cita::getMedico() const {
    return medico;
}

void Cita::setFecha(const string& nuevaFecha) {
    fecha = nuevaFecha;
}

void Cita::setUrgencia(const string& nuevaUrgencia) {
    urgencia = nuevaUrgencia;
}

void Cita::setPaciente(const Paciente& nuevoPaciente) {
    paciente = nuevoPaciente;
}

void Cita::setMedico(const Medico& nuevoMedico) {
    medico = nuevoMedico;
}