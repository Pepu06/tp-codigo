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
    _reservas.push_back(r); // O(1)

    // le sumo 1 a la cantidad de reservas del dia de hoy
    _reservas_por_dia[principio_del_dia(r.fecha_hora)] += 1; // O(log(D))

    // le sumo 1 a la cantidad de reservas del cliente que hizo la reserva
    _reservas_por_cliente[r.cliente] += 1; // O(log(C))

    // defino un booleano para ver si el cliente esta en la lista o no
    bool cliente_encontrado = false; // O(1)

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

    // Complejidad del ciclo for :
    // El ciclo recorre a lo sumo C clientes. Se divide en:
    // 1. Iteraciones fallidas (if falso): (C - 1) iteraciones * O(1) = O(C)
    // 2. Iteración exitosa (if verdadero): O(1) del if + (peor caso del while: C - 1 swaps * O(1)) = O(C)
    // Complejidad total del bloque = O(C) + O(C) = max{O(C), O(C)} = O(C)

    // si luego de recorrer la lista no encontre al cliente, lo agrego al final
    if (!cliente_encontrado)
    {
        _clientes_ordenados.push_back({r.cliente, 1}); // O(1)
    }

    _cantidad_reservas++;  // 0(1)


    // Complejidad total de registrar_reserva: O(1) + O(log(D)) + O(log(C)) + O(1)+ O(C) + O(1) + O(1)
    // Max de los  O(1) = max{O(1),O(1),O(1),O(1)} = O(1) + O(log(D)) + O(log(C)) + O(C)
    // Max {O(1) , O(log(D))} = O(log(D)) + O(log(C)) + O(C)
    // Max {O(log(C)), O(C)} = O(C)
    // Complejidad total: Max{log(D)+ O(C)} = O(log(D) + C) en el peor caso.
    
}

int Agenda::cantidad_reservas() const
{
    // devuelvo la cantidad de reservas guardado en el private
    return _cantidad_reservas; // O(1)

    // complejidad total: O(1) 
}

vector<Reserva> Agenda::ultimas_reservas(int k) const
{
    // inicio un contador para luego verificar cuando llego a k
    int contador = 0; // O(1)
    vector<Reserva> res; // O(1)

    // me fijo si no existen reservas
    if (_reservas.empty()) 
    {
        return res; // O(1)
    }

    // voy reserva por reserva, empezando desde el final, hasta que mi contador sea igual a k, cuando llega ese momento devuelvo res
    auto reserva = _reservas.end(); // O(1)
    reserva--;

    while (contador < k)
    {
        res.push_back(*reserva); // O(1)
        contador++;

        // si llego al principio de la lista, corto el ciclo
        if (reserva == _reservas.begin()) // O(1)
        {
            break;
        }
        reserva--;
    }

    // Complejidad del while:
    // Costo de cada iteración = O(1) + O(1) + O(1) + O(1) 
    // Max de los O(1) = max{O(1),O(1),O(1),O(1)} = O(1)
    // Complejidad total del bloque = (k iteraciones) * O(1) = O(k) (En el peor caso)
    

    return res; // O(1)

    // Complejidad total de ultimas_reservas: O(1) + O(1) + O(1) + O(k) + O(1)
    // Max de los O(1) = max{O(1),O(1),O(1),O(1)} + O(K) = O(k) + O(1)
    // Complejidad total: max{O(1), O(k)} = O(k) 
}

int Agenda::reservas_del_dia(timestamp t) const
{
    // aprovecho el hecho de que ya tenemos un map con las reservas por dia, y simplemente devuelvo el valor asociado al dia de la fecha
    if (_reservas_por_dia.count(principio_del_dia(t)) == 0) // O(log(D)) 
    {
        return 0; // O(1)
    }
    else
    {
        return _reservas_por_dia.at(principio_del_dia(t)); // O(log(D)) 
    }

    // Son log(D) en el peor caso porque el map tiene logarítmica de complejidad para buscar una clave.
    // Complejidad total de reservas_del_dia: O(log(D)) + O(1) + O(log(D))
    // Max {O(log(D)) , O(1)} = O(log(D)) + O(log(D)) = max{O(log(D)), O(log(D))} = O(log(D))
    // complejidad total: O(log(D))
}

vector<string> Agenda::clientes_frecuentes(int k) const
{
    // creo un vector para guardar los clientes frecuentes
    vector<string> resultado;
    
    // creo un iterador para ir avanzando entre los _clientes_ordenados dentro del while
    auto cliente = _clientes_ordenados.begin(); // O(1)

    int contador = 0;

    // chequeo si _clientes_ordenados esta vacio y devuelvo un vector vacio en ese caso
    if (_clientes_ordenados.empty()){ // O(1)
        return resultado;
    }

    // mientras que el contador sea menor a k (cuando son iguales corta), agrego los nombres de los clientes al vector de resultado, si el contador aun no llego a k pero no hay mas clientes en _clientes_ordenados, devuelvo lo que hay hasta ese momento
    while (contador < k)
    {
        resultado.push_back(cliente->first); // O(1)
        contador++;
        cliente++;

        if (cliente == _clientes_ordenados.end()){ // O(1)
            return resultado;
        }
    }

    // Complejidad del while:
    // Costo de cada iteración = O(1) + O(1) + O(1) + O(1) 
    // Max{O(1),O(1),O(1),O(1)} = O(1)
    // Complejidad total del bloque = O(k) * O(1) = O(k) (En el peor caso)


    return resultado; // O(1)

    // Complejidad total de clientes_frecuentes: O(1) + O(1) + O(1) + O(k) + O(1)
    //  Max{O(1),O(1),O(1),O(1)} = O(1) = O(1) + O(k)
    // Complejidad total: max{O(1), O(k)} = O(k)

}
