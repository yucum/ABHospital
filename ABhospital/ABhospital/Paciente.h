#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>

using namespace std;

class Paciente {
private:
    string nombre;
    int id;
    string fechaIngreso;
    string historialClinico;

public:
    Paciente(string nom, int id, string fecha);

    void altaPaciente();
    void bajaPaciente();
    void modificarDatos();
    void buscarPaciente() const;
    void registrarHistorial();
    string getNombre() const;
    int getId() const;
    string getFechaIngreso() const;
    string getHistorialClinico() const;
};

#endif
