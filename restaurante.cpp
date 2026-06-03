#include "restaurante.h"
#include "agenda.h"

Restaurante::Restaurante() : _siguiente_id(1), _tiempo_actual(0) {}

id_reserva Restaurante::nueva_reserva(const string& cliente, timestamp fecha_hora, int comensales) {
    Reserva r;
    r.id = _siguiente_id++;
    r.cliente = cliente;
    r.fecha_hora = fecha_hora;
    r.comensales = comensales;

    _agenda.registrar_reserva(r);

    return r.id;
}

const list<Reserva>& Restaurante::reservas() const {
    return _agenda.reservas();
}

Agenda& Restaurante::agenda() {
    return _agenda;
}

int Restaurante::reservas_de_hoy() const {
    return _agenda.reservas_del_dia(_tiempo_actual);
}

timestamp Restaurante::tiempo_actual() const {
    return _tiempo_actual;
}

void Restaurante::avanzar_un_dia() {
    _tiempo_actual += SEGUNDOS_POR_DIA;
}

Restaurante::~Restaurante() {}
