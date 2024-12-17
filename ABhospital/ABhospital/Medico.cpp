#include "Medico.h"
#include <iostream>

using namespace std;

Medico::Medico(string nombre, int id, string especialidad, bool disponibilidad)
    : nombre(nombre), id(id), especialidad(especialidad), disponibilidad(disponibilidad) {
}

string Medico::getNombre() const {
    return nombre;
}

int Medico::getId() const {
    return id;
}

string Medico::getEspecialidad() const {
    return especialidad;
}

bool Medico::getDisponibilidad() const {
    return disponibilidad;
}

void Medico::altaMedico() const {
    cout << "Medico " << nombre << " (ID:" << id << ") dado de alta.\n";
}

void Medico::bajaMedico() const {
    cout << "Medico " << nombre << " (ID:" << id << ") dado de baja.\n";
}

void Medico::asignarEspecialidad(string nuevaEspecialidad) {
    especialidad = nuevaEspecialidad;
    cout << "Especialidad de " << nombre << " (ID:" << id << ") asignada a: " << especialidad << ".\n";
}

void Medico::cambiarDisponibilidad(bool nuevaDisponibilidad) {
    disponibilidad = nuevaDisponibilidad;
    cout << "Disponibilidad de " << nombre << " (ID:" << id << ") actualizada a: "
        << (disponibilidad ? "Disponible" : "No disponible") << ".\n";
}