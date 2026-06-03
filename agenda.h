#ifndef AGENDA_H
#define AGENDA_H

#include <string>
#include <vector>
#include <list>
#include "lib.h"

using namespace std;

class Agenda {
  public:
    /**
     * Constructor.
     */
    Agenda();

    /**
     * Lista de todas las reservas registradas.
     *
     * Complejidad: O(1), usando una referencia no modificable.
     */
    const list<Reserva>& reservas() const;

    /**
     * Método utilizado para registrar una nueva reserva en la agenda.
     *
     * Complejidad esperada: O(log(D) + C), donde:
     *   - D es la máxima cantidad de días distintos con reservas
     *   - C es la máxima cantidad de clientes distintos
     */
    void registrar_reserva(Reserva r);

    /**
     * Devuelve la cantidad total de reservas activas.
     *
     * Complejidad esperada: O(1)
     */
    int cantidad_reservas() const;

    /**
     * Devuelve las últimas `k` reservas registradas.
     * Si hay menos de k reservas, devuelve todas las existentes.
     *
     * Complejidad esperada: O(k)
     */
    vector<Reserva> ultimas_reservas(int k) const;

    /**
     * Devuelve la cantidad de reservas que hay para el día de `t`.
     *
     * Por ejemplo, si t es el 10 de enero a las 15hs, devolveremos
     * la cantidad de reservas que hay para el 10 de enero.
     *
     * Complejidad esperada: O(log(D)), donde D es la máxima cantidad
     * de días distintos con reservas
     */
    int reservas_del_dia(timestamp t) const;

    /**
     * Devuelve los nombres de los `k` clientes que más reservas realizaron.
     * Si hay menos de k clientes distintos, devuelve todos los existentes.
     *
     * Complejidad esperada: O(k)
     */
    vector<string> clientes_frecuentes(int k) const;

  private:
    // =====================================================================
    // INVARIANTE DE REPRESENTACIÓN:
    //
    // TODO: Escribir acá el invariante de representación en castellano!
    //
    // Recordar que también hay que presentarlo escrito en lenguaje formal.
    //
    // =====================================================================

    // =====================================================================
    // TODO: A partir de aquí, modificar la estructura según sea necesario y
    // escribir en un comentario invariante de representación en castellano.
    // =====================================================================

    /** Listado de todas las reservas realizadas */
    list<Reserva> _reservas;
};

#endif
