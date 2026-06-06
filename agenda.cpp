#include "agenda.h"
#include <algorithm>

Agenda::Agenda() {
    _cantidad_reservas = 0;
}

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

    _cantidad_reservas++;
}

int Agenda::cantidad_reservas() const
{
    // devuelvo la cantidad de reservas guardado en el private
    return _cantidad_reservas;
}

vector<Reserva> Agenda::ultimas_reservas(int k) const
{
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
    // creo un vector para guardar los clientes frecuentes
    vector<string> resultado;
    
    // creo un iterador para ir avanzando entre los _clientes_ordenados dentro del while
    list<pair<string,int>>::const_iterator cliente = _clientes_ordenados.begin();

    int contador = 0;

    // chequeo si _clientes_ordenados esta vacio y devuelvo un vector vacio en ese caso
    if (_clientes_ordenados.empty()){
        return resultado;
    }

    // mientras que el contador sea menor a k (cuando son iguales corta), agrego los nombres de los clientes al vector de resultado, si el contador aun no llego a k pero no hay mas clientes en _clientes_ordenados, devuelvo lo que hay hasta ese momento
    while (contador < k)
    {
        resultado.push_back(cliente->first);
        contador++;
        cliente++;

        if (cliente == _clientes_ordenados.end()){
            return resultado;
        }
    }

    return resultado;
}
