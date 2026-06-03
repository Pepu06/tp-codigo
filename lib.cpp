#include "lib.h"

timestamp principio_del_dia(timestamp t) {
    return (t / SEGUNDOS_POR_DIA) * SEGUNDOS_POR_DIA;
}

timestamp fin_del_dia(timestamp t) {
    return principio_del_dia(t) + SEGUNDOS_POR_DIA;
}
