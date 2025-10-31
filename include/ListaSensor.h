/**
 * @file ListaSensor.h
 * @brief Implementación de lista enlazada simple genérica para almacenar lecturas
 * @author FabiRamiro
 * @date 2025-10-31
 */

#ifndef LISTASENSOR_H
#define LISTASENSOR_H

#include <iostream>

/**
 * @brief Estructura de nodo genérico para la lista enlazada
 * @tparam T Tipo de dato que almacenará el nodo (int, float, double, etc.)
 */
template <typename T>
struct Nodo
{
    T dato;             ///< Valor almacenado en el nodo
    Nodo<T> *siguiente; ///< Puntero al siguiente nodo de la lista

    /**
     * @brief Constructor del nodo
     * @param valor Valor inicial del nodo
     */
    Nodo(T valor) : dato(valor), siguiente(nullptr) {}
};

/**
 * @class ListaSensor
 * @brief Lista enlazada simple genérica para gestionar lecturas de sensores
 * @tparam T Tipo de dato de las lecturas (int para presión, float para temperatura)
 *
 * Implementa la Regla de los Tres para gestión correcta de memoria dinámica:
 * - Destructor
 * - Constructor de copia
 * - Operador de asignación
 */
template <typename T>
class ListaSensor
{
private:
    Nodo<T> *cabeza; ///< Puntero al primer nodo de la lista
    int contador;    ///< Número de elementos en la lista

public:
    /**
     * @brief Constructor por defecto
     * Inicializa una lista vacía
     */
    ListaSensor() : cabeza(nullptr), contador(0)
    {
        std::cout << "[Log] ListaSensor<T> creada." << std::endl;
    }

    /**
     * @brief Destructor - Libera toda la memoria de los nodos
     *
     * Recorre la lista completa liberando cada nodo para evitar fugas de memoria
     */
    ~ListaSensor()
    {
        std::cout << "[Log] Destruyendo ListaSensor<T>..." << std::endl;
        limpiar();
    }

    /**
     * @brief Constructor de copia (Regla de los Tres)
     * @param otra Lista a copiar
     *
     * Realiza una copia profunda de todos los nodos
     */
    ListaSensor(const ListaSensor<T> &otra) : cabeza(nullptr), contador(0)
    {
        copiar(otra);
    }

    /**
     * @brief Operador de asignación (Regla de los Tres)
     * @param otra Lista a asignar
     * @return Referencia a esta lista
     */
    ListaSensor<T> &operator=(const ListaSensor<T> &otra)
    {
        if (this != &otra)
        {
            limpiar();
            copiar(otra);
        }
        return *this;
    }

    /**
     * @brief Inserta un nuevo elemento al final de la lista
     * @param valor Valor a insertar
     */
    void insertar(T valor)
    {
        Nodo<T> *nuevoNodo = new Nodo<T>(valor);

        if (cabeza == nullptr)
        {
            cabeza = nuevoNodo;
        }
        else
        {
            Nodo<T> *actual = cabeza;
            while (actual->siguiente != nullptr)
            {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }

        contador++;
        std::cout << "[Log] Nodo<T> insertado. Valor: " << valor << std::endl;
    }

    /**
     * @brief Calcula el promedio de todos los elementos de la lista
     * @return Promedio de tipo T
     */
    T calcularPromedio() const
    {
        if (contador == 0)
        {
            std::cout << "[Advertencia] Lista vacía. Promedio = 0." << std::endl;
            return static_cast<T>(0);
        }

        T suma = static_cast<T>(0);
        Nodo<T> *actual = cabeza;

        while (actual != nullptr)
        {
            suma += actual->dato;
            actual = actual->siguiente;
        }

        return suma / static_cast<T>(contador);
    }

    /**
     * @brief Encuentra y elimina el valor más bajo de la lista
     * @return Valor eliminado (0 si la lista está vacía)
     */
    T eliminarMinimo()
    {
        if (cabeza == nullptr)
        {
            std::cout << "[Advertencia] Lista vacía. No se puede eliminar mínimo." << std::endl;
            return static_cast<T>(0);
        }

        // Buscar el nodo con valor mínimo
        Nodo<T> *actual = cabeza;
        Nodo<T> *minNodo = cabeza;
        Nodo<T> *prevMin = nullptr;
        Nodo<T> *prevActual = nullptr;

        while (actual != nullptr)
        {
            if (actual->dato < minNodo->dato)
            {
                minNodo = actual;
                prevMin = prevActual;
            }
            prevActual = actual;
            actual = actual->siguiente;
        }

        T valorMinimo = minNodo->dato;

        // Eliminar el nodo mínimo
        if (prevMin == nullptr)
        {
            // El mínimo es la cabeza
            cabeza = minNodo->siguiente;
        }
        else
        {
            prevMin->siguiente = minNodo->siguiente;
        }

        delete minNodo;
        contador--;

        std::cout << "[Log] Nodo<T> con valor mínimo (" << valorMinimo << ") eliminado." << std::endl;

        return valorMinimo;
    }

    /**
     * @brief Imprime todos los elementos de la lista
     */
    void imprimir() const
    {
        if (cabeza == nullptr)
        {
            std::cout << "  [Lista vacía]" << std::endl;
            return;
        }

        Nodo<T> *actual = cabeza;
        std::cout << "  Lecturas: ";
        while (actual != nullptr)
        {
            std::cout << actual->dato;
            if (actual->siguiente != nullptr)
            {
                std::cout << " -> ";
            }
            actual = actual->siguiente;
        }
        std::cout << std::endl;
    }

    /**
     * @brief Obtiene el número de elementos en la lista
     * @return Cantidad de nodos
     */
    int getContador() const
    {
        return contador;
    }

    /**
     * @brief Verifica si la lista está vacía
     * @return true si no hay elementos, false en caso contrario
     */
    bool estaVacia() const
    {
        return cabeza == nullptr;
    }

private:
    /**
     * @brief Libera toda la memoria de la lista
     */
    void limpiar()
    {
        Nodo<T> *actual = cabeza;
        while (actual != nullptr)
        {
            Nodo<T> *siguiente = actual->siguiente;
            std::cout << "  [Log] Nodo<T> liberado: " << actual->dato << std::endl;
            delete actual;
            actual = siguiente;
        }
        cabeza = nullptr;
        contador = 0;
    }

    /**
     * @brief Copia profunda de otra lista
     * @param otra Lista a copiar
     */
    void copiar(const ListaSensor<T> &otra)
    {
        if (otra.cabeza == nullptr)
        {
            return;
        }

        Nodo<T> *actualOtra = otra.cabeza;
        while (actualOtra != nullptr)
        {
            insertar(actualOtra->dato);
            actualOtra = actualOtra->siguiente;
        }
    }
};

#endif // LISTASENSOR_H