/**
 * @file ListaGeneral.cpp
 * @brief Implementación de la lista de gestión polimórfica
 * @author FabiRamiro
 * @date 2025-10-31
 */

#include "ListaGeneral.h"
#include <cstring>

ListaGeneral::ListaGeneral() : cabeza(nullptr), contador(0)
{
    std::cout << "[Log] ListaGeneral de sensores creada." << std::endl;
}

ListaGeneral::~ListaGeneral()
{
    std::cout << "\n--- Liberacion de Memoria en Cascada ---" << std::endl;

    NodoSensor *actual = cabeza;
    while (actual != nullptr)
    {
        NodoSensor *siguiente = actual->siguiente;

        std::cout << "[Destructor General] Liberando Nodo: "
                  << actual->sensor->getNombre() << std::endl;

        delete actual->sensor; // Llama al destructor virtual apropiado
        delete actual;

        actual = siguiente;
    }

    std::cout << "Sistema cerrado. Memoria limpia." << std::endl;
}

void ListaGeneral::insertarSensor(SensorBase *sensor)
{
    NodoSensor *nuevoNodo = new NodoSensor(sensor);

    if (cabeza == nullptr)
    {
        cabeza = nuevoNodo;
    }
    else
    {
        NodoSensor *actual = cabeza;
        while (actual->siguiente != nullptr)
        {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }

    contador++;
    std::cout << "[Log] Sensor '" << sensor->getNombre()
              << "' insertado en la lista de gestion." << std::endl;
}

SensorBase *ListaGeneral::buscarSensor(const char *nombre) const
{
    NodoSensor *actual = cabeza;

    while (actual != nullptr)
    {
        if (std::strcmp(actual->sensor->getNombre(), nombre) == 0)
        {
            return actual->sensor;
        }
        actual = actual->siguiente;
    }

    return nullptr; // No encontrado
}

void ListaGeneral::procesarTodosSensores()
{
    std::cout << "\n--- Ejecutando Polimorfismo ---" << std::endl;

    NodoSensor *actual = cabeza;

    while (actual != nullptr)
    {
        actual->sensor->procesarLectura(); // Llamada polimórfica
        actual = actual->siguiente;
    }
}

void ListaGeneral::imprimirTodosSensores() const
{
    std::cout << "\n--- Lista de Sensores Registrados ---" << std::endl;
    std::cout << "Total de sensores: " << contador << std::endl;

    NodoSensor *actual = cabeza;
    int index = 1;

    while (actual != nullptr)
    {
        std::cout << "\n[" << index << "] ";
        actual->sensor->imprimirInfo();
        actual = actual->siguiente;
        index++;
    }
}

int ListaGeneral::getContador() const
{
    return contador;
}