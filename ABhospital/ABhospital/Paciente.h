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
    vector<string> historial; //Se almacena el historial clinico

public:
    Paciente(string nombre, int id, string fechaIngreso);
    
    string getNombre() const;
    int getId() const;
    string getFechaIngreso() const;
    const vector<string>& getHistorial() const;
    
    void setNombre(const string& nuevoNombre);
    void setFechaIngreso(const string& nuevaFecha);

    void registrarHistorial(const string& entrada);
    void mostrarHistorial() const;
};

#endif
