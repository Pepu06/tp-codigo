#ifndef TESTS_LIB_H_
#define TESTS_LIB_H_

#include <cassert>
#include <gtest/gtest.h>
#include "../lib.h"

void inline chequear_reserva(const Reserva& r, id_reserva id, const string& cliente, timestamp fecha_hora, int comensales) {
    EXPECT_EQ(r.id, id);
    EXPECT_EQ(r.cliente, cliente);
    EXPECT_EQ(r.fecha_hora, fecha_hora);
    EXPECT_EQ(r.comensales, comensales);
}

void inline chequear_clientes(const vector<string>& v1, const vector<string>& v2) {
    EXPECT_EQ(v1, v2);
}

#endif // TESTS_LIB_H_
