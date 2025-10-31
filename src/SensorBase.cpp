/**
 * @file SensorBase.cpp
 * @brief Implementación de la clase base abstracta SensorBase
 * @author FabiRamiro
 * @date 2025-10-31
 */

#include "SensorBase.h"
#include <cstring>

SensorBase::SensorBase()
{
    nombre[0] = '\0';
}

SensorBase::SensorBase(const char *nombreSensor)
{
    setNombre(nombreSensor);
}

SensorBase::~SensorBase()
{
    std::cout << "[Destructor SensorBase] Sensor " << nombre << " liberado." << std::endl;
}

const char *SensorBase::getNombre() const
{
    return nombre;
}

void SensorBase::setNombre(const char *nombreSensor)
{
    if (nombreSensor != nullptr)
    {
        std::strncpy(nombre, nombreSensor, 49);
        nombre[49] = '\0'; // Asegurar terminación
    }
}