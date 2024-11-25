#ifndef CITA_H
#define CITA_H

#include <string>
#include "Paciente.h"
#include "Medico.h"

using namespace std;

class Cita {
private:
    string fecha;
    string urgencia;
    Paciente paciente;
    Medico medico;

public:
    Cita(string fecha, string urg, Paciente pac, Medico med);

    void asignarCita();
    void cancelarCita();
    string getFecha() const;
    string getUrgencia() const;
    Paciente getPaciente() const;
    Medico getMedico() const;
};

#endif
