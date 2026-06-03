#include <string>
#include <cassert>
#include <gtest/gtest.h>

#include "../lib.h"
#include "../restaurante.h"
#include "tests_lib.h"

using namespace std;

TEST(test_restaurante, permite_crear_reservas) {
    Restaurante restaurante;

    id_reserva id1 = restaurante.nueva_reserva("Juan", 1000, 4);
    id_reserva id2 = restaurante.nueva_reserva("Maria", 2000, 2);
    id_reserva id3 = restaurante.nueva_reserva("Pedro", 3000, 6);

    // Chequeo que todos tengan ids distintos. Los valores específicos no importan.
    EXPECT_NE(id1, id2);
    EXPECT_NE(id1, id3);
    EXPECT_NE(id2, id3);

    EXPECT_EQ(restaurante.reservas().size(), 3);
}

TEST(test_restaurante, permite_listar_reservas) {
    Restaurante restaurante;

    restaurante.nueva_reserva("Juan", 1000, 4);
    restaurante.nueva_reserva("Maria", 2000, 2);

    const list<Reserva>& reservas = restaurante.reservas();
    EXPECT_EQ(reservas.size(), 2);

    auto it = reservas.begin();
    EXPECT_EQ(it->cliente, "Juan");
    EXPECT_EQ(it->fecha_hora, 1000);
    EXPECT_EQ(it->comensales, 4);

    ++it;
    EXPECT_EQ(it->cliente, "Maria");
    EXPECT_EQ(it->fecha_hora, 2000);
    EXPECT_EQ(it->comensales, 2);
}

TEST(test_restaurante, provee_acceso_a_agenda) {
    Restaurante restaurante;

    restaurante.nueva_reserva("Juan", 1000, 4);

    // La agenda está integrada en el restaurante
    EXPECT_EQ(restaurante.agenda().cantidad_reservas(), 1);
}

TEST(test_restaurante, reservas_de_hoy_sin_reservas) {
    Restaurante restaurante;

    EXPECT_EQ(restaurante.reservas_de_hoy(), 0);
}

TEST(test_restaurante, reservas_de_hoy_con_reservas) {
    Restaurante restaurante;

    // El tiempo inicial es 0 (día 0)
    // Creamos reservas para el día 0
    restaurante.nueva_reserva("Juan", 100, 4);
    restaurante.nueva_reserva("Maria", 200, 2);

    EXPECT_EQ(restaurante.reservas_de_hoy(), 2);
}

TEST(test_restaurante, reservas_de_hoy_avanzando_dias) {
    Restaurante restaurante;

    // Tiempo inicial: día 0
    restaurante.nueva_reserva("Juan", 100, 4);       // día 0
    restaurante.nueva_reserva("Maria", 200, 2);      // día 0

    EXPECT_EQ(restaurante.reservas_de_hoy(), 2);

    // Avanzamos al día 1
    restaurante.avanzar_un_dia();
    EXPECT_EQ(restaurante.reservas_de_hoy(), 0);

    // Creamos una reserva para el día 1
    restaurante.nueva_reserva("Pedro", SEGUNDOS_POR_DIA + 100, 3);
    EXPECT_EQ(restaurante.reservas_de_hoy(), 1);

    // Avanzamos al día 2
    restaurante.avanzar_un_dia();
    EXPECT_EQ(restaurante.reservas_de_hoy(), 0);
}
