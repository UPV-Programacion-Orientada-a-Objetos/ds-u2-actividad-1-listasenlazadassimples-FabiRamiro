/**
 * @file SensorTemperatura.cpp
 * @brief Implementación del sensor de temperatura
 * @author FabiRamiro
 * @date 2025-10-31
 */

#include "SensorTemperatura.h"

SensorTemperatura::SensorTemperatura(const char *nombreSensor)
    : SensorBase(nombreSensor)
{
    std::cout << "[Log] SensorTemperatura '" << nombre << "' creado." << std::endl;
}

SensorTemperatura::~SensorTemperatura()
{
    std::cout << "[Destructor SensorTemperatura] Liberando lista interna de '"
              << nombre << "'..." << std::endl;
}

void SensorTemperatura::registrarLectura(float temperatura)
{
    historial.insertar(temperatura);
    std::cout << "[" << nombre << "] Lectura registrada: "
              << temperatura << " °C" << std::endl;
}

void SensorTemperatura::procesarLectura()
{
    std::cout << "\n-> Procesando Sensor " << nombre << " (Temperatura)..." << std::endl;

    if (historial.estaVacia())
    {
        std::cout << "  [Advertencia] No hay lecturas para procesar." << std::endl;
        return;
    }

    // Eliminar el valor más bajo
    float minimo = historial.eliminarMinimo();
    std::cout << "  [Sensor Temp] Lectura mas baja (" << minimo
              << " °C) eliminada." << std::endl;

    // Calcular promedio de los valores restantes
    if (!historial.estaVacia())
    {
        float promedio = historial.calcularPromedio();
        std::cout << "  [Sensor Temp] Promedio calculado sobre "
                  << historial.getContador() << " lectura(s): "
                  << promedio << " °C" << std::endl;
    }
    else
    {
        std::cout << "  [Sensor Temp] No quedan lecturas despues de eliminar el minimo."
                  << std::endl;
    }
}

void SensorTemperatura::imprimirInfo() const
{
    std::cout << "\n=== Sensor de Temperatura ===" << std::endl;
    std::cout << "ID: " << nombre << std::endl;
    std::cout << "Tipo: Temperatura (float)" << std::endl;
    std::cout << "Lecturas almacenadas: " << historial.getContador() << std::endl;
    historial.imprimir();
}