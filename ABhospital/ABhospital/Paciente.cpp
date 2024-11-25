#include "Paciente.h"
#include <iostream>

Paciente::Paciente(string nom, int id, string fecha) : nombre(nom), id(id), fechaIngreso(fecha), historialClinico("") {}

void Paciente::altaPaciente() {
    cout << "Paciente dado de alta con éxito: " << nombre << "\n";
}

void Paciente::bajaPaciente() {
    cout << "Paciente dado de baja con éxito: " << nombre << "\n";
}

void Paciente::modificarDatos() {
    cout << "Modificando datos del paciente " << nombre << "\n";
}

void Paciente::buscarPaciente() const {
    cout << "Buscando paciente: " << nombre << " con ID: " << id << "\n";
}

void Paciente::registrarHistorial() {
    cout << "Registrando historial clínico para el paciente " << nombre << "\n";
    historialClinico = "Historial registrado para demostración.";
}

string Paciente::getNombre() const {
    return nombre;
}

int Paciente::getId() const {
    return id;
}

string Paciente::getFechaIngreso() const {
    return fechaIngreso;
}

string Paciente::getHistorialClinico() const {
    return historialClinico;
}
