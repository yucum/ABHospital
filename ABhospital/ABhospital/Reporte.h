#ifndef REPORTE_H
#define REPORTE_H

#include <string>
#include <vector>
#include "Cita.h"

using namespace std;

class Reporte {
private:
    string fechaInicio;
    string fechaFin;

public:
    Reporte(string inicio, string fin);

    void generarListadoPacientesAtendidos(const vector<Cita>& citas);
    void listarCitasPendientes(const vector<Cita>& citas);
};

#endif