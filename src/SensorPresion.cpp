/**
 * @file SensorPresion.cpp
 * @brief Implementación del sensor de presión
 * @author FabiRamiro
 * @date 2025-10-31
 */

#include "SensorPresion.h"

SensorPresion::SensorPresion(const char *nombreSensor)
    : SensorBase(nombreSensor)
{
    std::cout << "[Log] SensorPresion '" << nombre << "' creado." << std::endl;
}

SensorPresion::~SensorPresion()
{
    std::cout << "[Destructor SensorPresion] Liberando lista interna de '"
              << nombre << "'..." << std::endl;
}

void SensorPresion::registrarLectura(int presion)
{
    historial.insertar(presion);
    std::cout << "[" << nombre << "] Lectura registrada: "
              << presion << " PSI" << std::endl;
}

void SensorPresion::procesarLectura()
{
    std::cout << "\n-> Procesando Sensor " << nombre << " (Presion)..." << std::endl;

    if (historial.estaVacia())
    {
        std::cout << "  [Advertencia] No hay lecturas para procesar." << std::endl;
        return;
    }

    // Calcular promedio de todas las lecturas
    float promedio = historial.calcularPromedio();
    std::cout << "  [Sensor Presion] Promedio calculado sobre "
              << historial.getContador() << " lectura(s): "
              << promedio << " PSI" << std::endl;
}

void SensorPresion::imprimirInfo() const
{
    std::cout << "\n=== Sensor de Presion ===" << std::endl;
    std::cout << "ID: " << nombre << std::endl;
    std::cout << "Tipo: Presion (int)" << std::endl;
    std::cout << "Lecturas almacenadas: " << historial.getContador() << std::endl;
    historial.imprimir();
}