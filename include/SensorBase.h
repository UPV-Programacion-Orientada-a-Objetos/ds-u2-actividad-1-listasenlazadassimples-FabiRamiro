/**
 * @file SensorBase.h
 * @brief Clase base abstracta para todos los sensores del sistema IoT
 * @author FabiRamiro
 * @date 2025-10-31
 */

#ifndef SENSORBASE_H
#define SENSORBASE_H

#include <iostream>

/**
 * @class SensorBase
 * @brief Clase abstracta que define la interfaz común para todos los sensores
 *
 * Esta clase establece el contrato que deben cumplir todas las clases derivadas
 * de sensores. Utiliza métodos virtuales puros para forzar la implementación
 * en las subclases.
 */
class SensorBase
{
protected:
    char nombre[50]; ///< Identificador único del sensor

public:
    /**
     * @brief Constructor por defecto
     */
    SensorBase();

    /**
     * @brief Constructor con parámetro de nombre
     * @param nombreSensor Cadena de caracteres con el identificador del sensor
     */
    SensorBase(const char *nombreSensor);

    /**
     * @brief Destructor virtual
     *
     * Es crucial que sea virtual para garantizar la correcta liberación
     * de memoria en las clases derivadas al usar polimorfismo
     */
    virtual ~SensorBase();

    /**
     * @brief Método virtual puro para procesar lecturas del sensor
     *
     * Cada tipo de sensor implementará su propia lógica de procesamiento
     * (ej: calcular promedio, eliminar outliers, etc.)
     */
    virtual void procesarLectura() = 0;

    /**
     * @brief Método virtual puro para imprimir información del sensor
     *
     * Muestra en consola los datos relevantes del sensor y su estado
     */
    virtual void imprimirInfo() const = 0;

    /**
     * @brief Obtiene el nombre del sensor
     * @return Puntero constante al nombre del sensor
     */
    const char *getNombre() const;

    /**
     * @brief Establece el nombre del sensor
     * @param nombreSensor Nuevo nombre para el sensor
     */
    void setNombre(const char *nombreSensor);
};

#endif // SENSORBASE_H