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
    Medico(string nom, int id, string esp, bool disp);

    void altaMedico();
    void bajaMedico();
    void asignarEspecialidad(string nuevaEspecialidad);
    string getNombre() const;
    int getId() const;
    string getEspecialidad() const;
    bool isDisponible() const;
};

#endif
