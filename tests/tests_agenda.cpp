#include <string>
#include <cassert>
#include <gtest/gtest.h>

#include "../lib.h"
#include "../restaurante.h"
#include "../agenda.h"
#include "tests_lib.h"

using namespace std;

class test_agenda : public ::testing::Test {
protected:
    Restaurante restaurante;
    Agenda& agenda = restaurante.agenda();
};

TEST_F(test_agenda, reservas_devuelve_todas_en_orden_cronologico) {
    // Creamos varias reservas en orden cronológico
    restaurante.nueva_reserva("Juan", 1000, 4);
    restaurante.nueva_reserva("Maria", 2000, 2);
    restaurante.nueva_reserva("Pedro", 3000, 6);
    restaurante.nueva_reserva("Ana", 4000, 3);

    const list<Reserva>& todas = agenda.reservas();

    // Verificamos que tengamos 4 reservas
    EXPECT_EQ(todas.size(), 4);

    // Verificamos que estén en el orden correcto (cronológico)
    auto it = todas.begin();
    EXPECT_EQ(it->cliente, "Juan");
    EXPECT_EQ(it->fecha_hora, 1000);
    ++it;
    EXPECT_EQ(it->cliente, "Maria");
    EXPECT_EQ(it->fecha_hora, 2000);
    ++it;
    EXPECT_EQ(it->cliente, "Pedro");
    EXPECT_EQ(it->fecha_hora, 3000);
    ++it;
    EXPECT_EQ(it->cliente, "Ana");
    EXPECT_EQ(it->fecha_hora, 4000);
}

TEST_F(test_agenda, permite_consultar_cantidad_de_reservas) {
    EXPECT_EQ(agenda.cantidad_reservas(), 0);

    restaurante.nueva_reserva("Juan", 1000, 4);
    EXPECT_EQ(agenda.cantidad_reservas(), 1);

    restaurante.nueva_reserva("Maria", 2000, 2);
    EXPECT_EQ(agenda.cantidad_reservas(), 2);

    restaurante.nueva_reserva("Pedro", 3000, 6);
    EXPECT_EQ(agenda.cantidad_reservas(), 3);
}

TEST_F(test_agenda, permite_listar_ultimas_reservas) {
    restaurante.nueva_reserva("Juan", 1000, 4);
    restaurante.nueva_reserva("Maria", 2000, 2);
    restaurante.nueva_reserva("Pedro", 3000, 6);

    vector<Reserva> ultimas2 = agenda.ultimas_reservas(2);

    EXPECT_EQ(ultimas2.size(), 2);
    EXPECT_EQ(ultimas2[0].cliente, "Pedro");
    EXPECT_EQ(ultimas2[1].cliente, "Maria");

    vector<Reserva> ultimas3 = agenda.ultimas_reservas(3);
    EXPECT_EQ(ultimas3.size(), 3);
    EXPECT_EQ(ultimas3[0].cliente, "Pedro");
    EXPECT_EQ(ultimas3[1].cliente, "Maria");
    EXPECT_EQ(ultimas3[2].cliente, "Juan");
}

TEST_F(test_agenda, ultimas_reservas_devuelve_todas_si_se_pide_mas_del_total) {
    restaurante.nueva_reserva("Juan", 1000, 4);
    EXPECT_EQ(agenda.ultimas_reservas(10).size(), 1);
}

TEST_F(test_agenda, ultimas_reservas_devuelve_vacio_si_no_hay_reservas) {
    EXPECT_EQ(agenda.ultimas_reservas(5).size(), 0);
}

TEST_F(test_agenda, permite_consultar_reservas_del_dia) {
    // Día 0: 2 reservas
    restaurante.nueva_reserva("Juan", 1000, 4);
    restaurante.nueva_reserva("Maria", 2000, 2);

    // Día 1: 3 reservas
    restaurante.nueva_reserva("Pedro", SEGUNDOS_POR_DIA + 100, 6);
    restaurante.nueva_reserva("Ana", SEGUNDOS_POR_DIA + 200, 3);
    restaurante.nueva_reserva("Luis", SEGUNDOS_POR_DIA + 300, 2);

    // Día 2: 1 reserva
    restaurante.nueva_reserva("Carlos", 2 * SEGUNDOS_POR_DIA + 100, 4);

    EXPECT_EQ(agenda.reservas_del_dia(500), 2);                      // Día 0
    EXPECT_EQ(agenda.reservas_del_dia(SEGUNDOS_POR_DIA + 150), 3);   // Día 1
    EXPECT_EQ(agenda.reservas_del_dia(2 * SEGUNDOS_POR_DIA + 50), 1); // Día 2
    EXPECT_EQ(agenda.reservas_del_dia(3 * SEGUNDOS_POR_DIA + 100), 0); // Día 3 (sin reservas)
}

TEST_F(test_agenda, reservas_del_dia_funciona_con_reservas_en_medianoche) {
    // Reserva exactamente a medianoche (inicio del día 1)
    restaurante.nueva_reserva("Juan", SEGUNDOS_POR_DIA, 4);

    EXPECT_EQ(agenda.reservas_del_dia(0), 0);
    EXPECT_EQ(agenda.reservas_del_dia(SEGUNDOS_POR_DIA), 1);
}

TEST_F(test_agenda, permite_consultar_clientes_frecuentes) {
    // Juan: 3 reservas
    restaurante.nueva_reserva("Juan", 1000, 4);
    restaurante.nueva_reserva("Juan", 2000, 2);
    restaurante.nueva_reserva("Juan", 3000, 6);

    // Maria: 2 reservas
    restaurante.nueva_reserva("Maria", 4000, 3);
    restaurante.nueva_reserva("Maria", 5000, 2);

    // Pedro: 1 reserva
    restaurante.nueva_reserva("Pedro", 6000, 4);

    chequear_clientes(agenda.clientes_frecuentes(1), {"Juan"});
    chequear_clientes(agenda.clientes_frecuentes(2), {"Juan", "Maria"});
    chequear_clientes(agenda.clientes_frecuentes(3), {"Juan", "Maria", "Pedro"});
    chequear_clientes(agenda.clientes_frecuentes(4), {"Juan", "Maria", "Pedro"});
}

TEST_F(test_agenda, clientes_frecuentes_devuelve_vacio_si_no_hay_reservas) {
    EXPECT_EQ(agenda.clientes_frecuentes(5).size(), 0);
}

TEST_F(test_agenda, clientes_frecuentes_con_un_solo_cliente) {
    restaurante.nueva_reserva("Juan", 1000, 4);
    restaurante.nueva_reserva("Juan", 2000, 2);

    chequear_clientes(agenda.clientes_frecuentes(1), {"Juan"});
    chequear_clientes(agenda.clientes_frecuentes(5), {"Juan"});
}

TEST_F(test_agenda, caso_completo_con_varias_operaciones) {
    // Creamos varias reservas
    restaurante.nueva_reserva("Juan", 1000, 4);
    restaurante.nueva_reserva("Maria", SEGUNDOS_POR_DIA + 100, 2);
    restaurante.nueva_reserva("Juan", SEGUNDOS_POR_DIA + 200, 3);
    restaurante.nueva_reserva("Pedro", 2 * SEGUNDOS_POR_DIA + 100, 6);
    restaurante.nueva_reserva("Juan", 2 * SEGUNDOS_POR_DIA + 200, 2);

    // Verificamos todas las consultas
    EXPECT_EQ(agenda.cantidad_reservas(), 5);

    vector<Reserva> ultimas = agenda.ultimas_reservas(4);
    EXPECT_EQ(ultimas.size(), 4);
    EXPECT_EQ(ultimas[0].cliente, "Juan");
    EXPECT_EQ(ultimas[1].cliente, "Pedro");
    EXPECT_EQ(ultimas[2].cliente, "Juan");
    EXPECT_EQ(ultimas[3].cliente, "Maria");

    EXPECT_EQ(agenda.reservas_del_dia(500), 1);
    EXPECT_EQ(agenda.reservas_del_dia(SEGUNDOS_POR_DIA + 150), 2);
    EXPECT_EQ(agenda.reservas_del_dia(2 * SEGUNDOS_POR_DIA + 150), 2);

    chequear_clientes(agenda.clientes_frecuentes(2), {"Juan", "Maria"});
}
