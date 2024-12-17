#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>
#include <vector>
using namespace std;

class Paciente {
private:
    string nombre;
    int id;
    string fechaIngreso;
    vector<string> historialClinico;

public:

    Paciente(string nombre, int id, string fechaIngreso);

    string getNombre() const;
    int getId() const;
    string getFechaIngreso() const;
    vector<string> getHistorialClinico() const;

    void setNombre(string nuevoNombre);
    void setId(int nuevoId);
    void setFechaIngreso(string nuevaFecha);

    void altaPaciente() const;
    void bajaPaciente() const;
    void registrarHistorial(string entrada);
};

#endif