#include "Medico.h"
#include <iostream>

Medico::Medico(string nom, int id, string esp, bool disp) : nombre(nom), id(id), especialidad(esp), disponibilidad(disp) {}

void Medico::altaMedico() {
    cout << "M�dico dado de alta con �xito: " << nombre << "\n";
}

void Medico::bajaMedico() {
    cout << "M�dico dado de baja con �xito: " << nombre << "\n";
}

void Medico::asignarEspecialidad(string nuevaEspecialidad) {
    especialidad = nuevaEspecialidad;
    cout << "Nueva especialidad asignada: " << especialidad << "\n";
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

bool Medico::isDisponible() const {
    return disponibilidad;
}
