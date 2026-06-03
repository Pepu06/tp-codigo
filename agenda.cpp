#include "agenda.h"
#include <algorithm>

Agenda::Agenda() {}

const list<Reserva> &Agenda::reservas() const
{
    return _reservas;
}

void Agenda::registrar_reserva(Reserva r)
{
    _reservas.push_back(r);

    // le sumo 1 a la cantidad de reservas del dia de hoy
    _reservas_por_dia[principio_del_dia(r.fecha_hora)] += 1;

    // le sumo 1 a la cantidad de reservas del cliente que hizo la reserva
    _reservas_por_cliente[r.cliente] += 1;

    // defino un booleano para ver si el cliente esta en la lista o no
    bool cliente_encontrado = false;

    // recorro toda la lista y si encuentro al cliente, le sumo la cantidad de reservas que tiene, y ordeno la lista swapeandolo con su anterior si es que tiene mas reservas ahora
    for (list<pair<string, int>>::iterator cliente = _clientes_ordenados.begin(); cliente != _clientes_ordenados.end(); cliente++)
    {
        if (cliente->first == r.cliente)
        {
            cliente_encontrado = true;
            cliente->second += 1;

            while (_clientes_ordenados.begin() != cliente && prev(cliente)->second < cliente->second)
            {
                swap(*prev(cliente), *cliente);
                cliente = prev(cliente);
            }
        }
    }

    // si luego de recorrer la lista no encontre al cliente, lo agrego al final
    if (!cliente_encontrado)
    {
        _clientes_ordenados.push_back({r.cliente, 1});
    }
}

int Agenda::cantidad_reservas() const
{
    // Implementación trivial O(n): recorre toda la lista
    return _reservas.size();
}

vector<Reserva> Agenda::ultimas_reservas(int k) const
{
    // Implementación trivial O(n): recorre toda la lista
    // vector<Reserva> resultado;
    // const list<Reserva> &todas = _reservas;

    // // Tomamos las últimas k (o todas si hay menos de k)
    // int total = todas.size();
    // int inicio = max(0, total - k);
    // int i = 0;

    // for (const Reserva &r : todas)
    // {
    //     if (i >= inicio)
    //     {
    //         resultado.push_back(r);
    //     }
    //     i++;
    // }

    // // Las invertimos para que queden de más reciente a más antigua
    // reverse(resultado.begin(), resultado.end());

    // inicio un contador para luego verificar cuando llego a k
    int contador = 0;
    vector<Reserva> res;

    // me fijo si no existen reservas
    if (_reservas.empty())
    {
        return res;
    }

    // voy reserva por reserva, empezando desde el final, hasta que mi contador sea igual a k, cuando llega ese momento devuelvo res
    list<Reserva>::const_iterator reserva = _reservas.end();
    reserva--;

    while (contador < k)
    {
        res.push_back(*reserva);
        contador++;

        // si llego al principio de la lista, corto el ciclo
        if (reserva == _reservas.begin())
        {
            break;
        }
        reserva--;
    }

    return res;
}

int Agenda::reservas_del_dia(timestamp t) const
{
    // Implementación trivial O(n): recorre toda la lista
    // timestamp inicio_dia = principio_del_dia(t);
    // timestamp fin_dia = fin_del_dia(t);

    // int cantidad = 0;
    // for (const Reserva &r : _reservas)
    // {
    //     if (r.fecha_hora >= inicio_dia && r.fecha_hora < fin_dia)
    //     {
    //         cantidad++;
    //     }
    // }

    // aprovecho el hecho de que ya tenemos un map con las reservas por dia, y simplemente devuelvo el valor asociado al dia de la fecha
    if (_reservas_por_dia.count(principio_del_dia(t)) == 0)
    {
        return 0;
    }
    else
    {
        return _reservas_por_dia.at(principio_del_dia(t));
    }
}

vector<string> Agenda::clientes_frecuentes(int k) const
{
    // Implementación trivial O(n*c): recorre todas las reservas y ordena
    // Primero contamos las reservas por cliente
    vector<pair<string, int>> conteo;

    for (const Reserva &r : _reservas)
    {
        bool encontrado = false;
        for (auto &p : conteo)
        {
            if (p.first == r.cliente)
            {
                p.second++;
                encontrado = true;
                break;
            }
        }
        if (!encontrado)
        {
            conteo.push_back({r.cliente, 1});
        }
    }

    // Ordenamos por cantidad de reservas (descendente)
    sort(conteo.begin(), conteo.end(), [](const pair<string, int> &a, const pair<string, int> &b)
         { return a.second > b.second; });

    // Tomamos los primeros k
    vector<string> resultado;
    for (int i = 0; i < k && i < (int)conteo.size(); i++)
    {
        resultado.push_back(conteo[i].first);
    }

    return resultado;
}
