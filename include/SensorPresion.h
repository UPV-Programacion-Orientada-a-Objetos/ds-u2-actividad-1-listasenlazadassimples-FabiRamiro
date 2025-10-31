/**
 * @file SensorPresion.h
 * @brief Sensor de presión con lecturas enteras
 * @author FabiRamiro
 * @date 2025-10-31
 */

#ifndef SENSORPRESION_H
#define SENSORPRESION_H

#include "SensorBase.h"
#include "ListaSensor.h"

/**
 * @class SensorPresion
 * @brief Sensor especializado para medir presión en PSI
 *
 * Almacena lecturas de tipo int y procesa los datos calculando
 * el promedio de todas las lecturas registradas
 */
class SensorPresion : public SensorBase
{
private:
    ListaSensor<int> historial; ///< Lista enlazada de lecturas de presión

public:
    /**
     * @brief Constructor con nombre del sensor
     * @param nombreSensor Identificador único del sensor
     */
    SensorPresion(const char *nombreSensor);

    /**
     * @brief Destructor - Libera la lista de lecturas
     */
    ~SensorPresion();

    /**
     * @brief Registra una nueva lectura de presión
     * @param presion Valor en PSI (entero)
     */
    void registrarLectura(int presion);

    /**
     * @brief Procesa las lecturas: calcula el promedio
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

#endif // SENSORPRESION_H