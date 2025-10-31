/**
 * @file SerialReader.cpp
 * @brief Implementación del simulador de lectura serial
 * @author FabiRamiro
 * @date 2025-10-31
 */

#include "SerialReader.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

SerialReader::SerialReader() : conectado(false)
{
    // Inicializar generador de números aleatorios
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

SerialReader::~SerialReader()
{
    if (conectado)
    {
        desconectar();
    }
}

bool SerialReader::conectar(const char *puerto)
{
    std::cout << "[SerialReader] Intentando conectar a " << puerto << "..." << std::endl;

    // Simulación de conexión
    conectado = true;

    std::cout << "[SerialReader] Conectado exitosamente." << std::endl;
    return true;
}

void SerialReader::desconectar()
{
    if (conectado)
    {
        std::cout << "[SerialReader] Desconectando..." << std::endl;
        conectado = false;
    }
}

bool SerialReader::leerLinea(char *buffer, int tamano)
{
    if (!conectado || buffer == nullptr || tamano <= 0)
    {
        return false;
    }

    // Simulación de lectura de datos del ESP32
    // Formato esperado: "TIPO:ID:VALOR"
    // Ejemplo: "TEMP:T-001:23.5" o "PRES:P-105:85"

    int tipoSensor = std::rand() % 2; // 0 = Temperatura, 1 = Presión

    if (tipoSensor == 0)
    {
        // Sensor de temperatura
        float temperatura = 15.0f + (std::rand() % 300) / 10.0f; // 15.0 a 45.0
        std::snprintf(buffer, tamano, "TEMP:T-%03d:%.1f",
                      std::rand() % 100, temperatura);
    }
    else
    {
        // Sensor de presión
        int presion = 50 + (std::rand() % 100); // 50 a 150 PSI
        std::snprintf(buffer, tamano, "PRES:P-%03d:%d",
                      std::rand() % 100, presion);
    }

    return true;
}

bool SerialReader::hayDatos() const
{
    // En una implementación real, verificaría si hay bytes disponibles
    // Para simulación, siempre retorna true si está conectado
    return conectado;
}