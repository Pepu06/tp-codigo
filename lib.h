#ifndef LIB_H_
#define LIB_H_

#include <string>

using namespace std;

typedef unsigned int id_reserva;
typedef unsigned int timestamp;

struct Reserva {
    id_reserva id;
    string cliente;
    timestamp fecha_hora;
    int comensales;
};

// Funciones auxiliares para trabajar con timestamps

// Devuelve el timestamp correspondiente a la medianoche anterior a t.
timestamp principio_del_dia(timestamp t);

// Devuelve el timestamp correspondiente a la medianoche siguiente a t.
timestamp fin_del_dia(timestamp t);

// Constante: cantidad de segundos en un día
const unsigned int SEGUNDOS_POR_DIA = 86400;

#endif // LIB_H_
