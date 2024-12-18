#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>
#include <vector>

class Paciente {
private:
    std::string nombre;
    int id;
    std::string fechaIngreso;
    std::vector<std::string> historial;

public:
   
    Paciente(std::string nombre, int id, std::string fechaIngreso);

    std::string getNombre() const;
    int getId() const;
    std::string getFechaIngreso() const;
    const std::vector<std::string>& getHistorial() const;

    void setNombre(const std::string& nuevoNombre);
    void setFechaIngreso(const std::string& nuevaFecha);

    void registrarHistorial(const std::string& entrada);
    void mostrarHistorial() const;
};

#endif
