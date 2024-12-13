#ifndef MEDICO_H
#define MEDICO_H

#include <string>
using namespace std;

class Medico {
private:
    string nombre;
    int id;
    string especialidad;
    bool disponibilidad;

public:
    // Constructor
    Medico(string nombre, int id, string especialidad, bool disponibilidad);

    // Getters
    string getNombre() const;
    int getId() const;
    string getEspecialidad() const;
    bool getDisponibilidad() const;

    void altaMedico() const;
    void bajaMedico() const;
    void asignarEspecialidad(string nuevaEspecialidad);
    void cambiarDisponibilidad(bool nuevaDisponibilidad);
};

#endif
