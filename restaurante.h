#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#include <list>
#include <cstdlib>

#include "lib.h"
#include "agenda.h"

using namespace std;

class Restaurante {
  public:
    /** Constructor */
    Restaurante();

    /**
     * Registra una nueva reserva en el restaurante.
     *
     * @param cliente Nombre del cliente
     * @param fecha_hora Timestamp de la reserva
     * @param comensales Cantidad de comensales
     * @return ID asignado a la reserva
     *
     * Complejidad: O(1) + complejidad de registrar_reserva de Agenda
     */
    id_reserva nueva_reserva(const string& cliente, timestamp fecha_hora, int comensales);

    /**
     * Lista de todas las reservas registradas.
     *
     * Complejidad: O(1), usando una referencia no modificable.
     */
    const list<Reserva>& reservas() const;

    /**
     * Devuelve una referencia a la agenda del restaurante.
     */
    Agenda& agenda();

    /**
     * Devuelve la cantidad de reservas para el día actual (simulado).
     *
     * Complejidad: O(log(D)), donde D es la máxima cantidad de días
     * distintos con reservas.
     */
    int reservas_de_hoy() const;

    /**
     * Retorna el timestamp actual (simulado).
     * Usado internamente para asignar timestamps a nuevas reservas.
     */
    timestamp tiempo_actual() const;

    /**
     * Avanza el tiempo simulado un día.
     */
    void avanzar_un_dia();

    /**
     * Destructor.
     */
    ~Restaurante();

  private:
    /** Agenda del restaurante */
    Agenda _agenda;

    /** Siguiente ID a utilizar para reservas */
    id_reserva _siguiente_id;

    /** Tiempo actual simulado */
    timestamp _tiempo_actual;
};

#endif
