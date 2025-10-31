/**
 * @file ListaGeneral.h
 * @brief Lista enlazada NO genérica para gestión polimórfica de sensores
 * @author FabiRamiro
 * @date 2025-10-31
 */

#ifndef LISTAGENERAL_H
#define LISTAGENERAL_H

#include "SensorBase.h"

/**
 * @brief Nodo para la lista de gestión polimórfica
 *
 * Almacena punteros a SensorBase para aprovechar el polimorfismo
 */
struct NodoSensor
{
    SensorBase *sensor;    ///< Puntero polimórfico al sensor
    NodoSensor *siguiente; ///< Puntero al siguiente nodo

    /**
     * @brief Constructor del nodo
     * @param s Puntero al sensor
     */
    NodoSensor(SensorBase *s) : sensor(s), siguiente(nullptr) {}
};

/**
 * @class ListaGeneral
 * @brief Lista enlazada simple para gestionar múltiples tipos de sensores
 *
 * Utiliza polimorfismo para almacenar diferentes tipos de sensores
 * (SensorTemperatura, SensorPresion) en una única estructura
 */
class ListaGeneral
{
private:
    NodoSensor *cabeza; ///< Primer nodo de la lista
    int contador;       ///< Número de sensores en la lista

public:
    /**
     * @brief Constructor por defecto
     */
    ListaGeneral();

    /**
     * @brief Destructor - Libera todos los sensores y nodos
     */
    ~ListaGeneral();

    /**
     * @brief Inserta un nuevo sensor en la lista
     * @param sensor Puntero al sensor a insertar
     */
    void insertarSensor(SensorBase *sensor);

    /**
     * @brief Busca un sensor por su nombre
     * @param nombre Identificador del sensor
     * @return Puntero al sensor encontrado, nullptr si no existe
     */
    SensorBase *buscarSensor(const char *nombre) const;

    /**
     * @brief Procesa todos los sensores de la lista polimórficamente
     *
     * Llama al método procesarLectura() de cada sensor
     */
    void procesarTodosSensores();

    /**
     * @brief Imprime información de todos los sensores
     */
    void imprimirTodosSensores() const;

    /**
     * @brief Obtiene el número de sensores registrados
     * @return Cantidad de sensores
     */
    int getContador() const;
};

#endif // LISTAGENERAL_H