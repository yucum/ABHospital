#include "Paciente.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

Paciente::Paciente(string nombre, int id, string fechaIngreso)
    : nombre(nombre), id(id), fechaIngreso(fechaIngreso) {
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

const vector<string>& Paciente::getHistorial() const {
    return historial;
}

void Paciente::setNombre(const string& nuevoNombre) {
    nombre = nuevoNombre;
}

void Paciente::setFechaIngreso(const string& nuevaFecha) {
    fechaIngreso = nuevaFecha;
}

void Paciente::registrarHistorial(const string& entrada) {
    historial.push_back(entrada);
}

void Paciente::mostrarHistorial() const {
    if (historial.empty()) {
        cout << "El paciente no tiene historial clínico registrado.\n";
    }
    else {
        cout << "Historial clínico de " << nombre << ":\n";
        for (const auto& entrada : historial) {
            cout << "- " << entrada << "\n";
        }
    }
}
