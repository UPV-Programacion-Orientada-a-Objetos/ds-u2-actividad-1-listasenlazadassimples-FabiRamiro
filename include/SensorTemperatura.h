/**
 * @file SensorTemperatura.h
 * @brief Sensor de temperatura con lecturas de punto flotante
 * @author FabiRamiro
 * @date 2025-10-31
 */

#ifndef SENSORTEMPERATURA_H
#define SENSORTEMPERATURA_H

#include "SensorBase.h"
#include "ListaSensor.h"

/**
 * @class SensorTemperatura
 * @brief Sensor especializado para medir temperatura en grados Celsius
 *
 * Almacena lecturas de tipo float y procesa los datos eliminando
 * el valor más bajo y calculando el promedio de los restantes
 */
class SensorTemperatura : public SensorBase
{
private:
    ListaSensor<float> historial; ///< Lista enlazada de lecturas de temperatura

public:
    /**
     * @brief Constructor con nombre del sensor
     * @param nombreSensor Identificador único del sensor
     */
    SensorTemperatura(const char *nombreSensor);

    /**
     * @brief Destructor - Libera la lista de lecturas
     */
    ~SensorTemperatura();

    /**
     * @brief Registra una nueva lectura de temperatura
     * @param temperatura Valor en grados Celsius
     */
    void registrarLectura(float temperatura);

    /**
     * @brief Procesa las lecturas: elimina el mínimo y calcula promedio
     *
     * Implementación del método virtual puro de SensorBase
     */
    void procesarLectura() override;

    /**
     * @brief Imprime información del sensor y sus lecturas
     *
     * Implementación del método virtual puro de SensorBase
     */
    void imprimirInfo() const override;
};

#endif // SENSORTEMPERATURA_H