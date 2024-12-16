#include "Paciente.h"
#include <iostream>

using namespace std;

Paciente::Paciente(string nombre, int id, string fechaIngreso)
    : nombre(nombre), id(id), fechaIngreso(fechaIngreso) {

    historialClinico.push_back("Ingreso inicial: " + fechaIngreso);
    historialClinico.push_back("Consulta médica: Sin hallazgos actualmente");
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

vector<string> Paciente::getHistorialClinico() const {
    return historialClinico;
}

void Paciente::setNombre(string nuevoNombre) {
    nombre = nuevoNombre;
}

void Paciente::setId(int nuevoId) {
    id = nuevoId;
}

void Paciente::setFechaIngreso(string nuevaFecha) {
    fechaIngreso = nuevaFecha;
}

void Paciente::altaPaciente() const {
    cout << "Paciente " << nombre << " (ID: " << id << ") dado de alta.\n";
}

void Paciente::bajaPaciente() const {
    cout << "Paciente " << nombre << " (ID: " << id << ") dado de baja.\n";
}

void Paciente::registrarHistorial(string entrada) {
    historialClinico.push_back(entrada);
}
