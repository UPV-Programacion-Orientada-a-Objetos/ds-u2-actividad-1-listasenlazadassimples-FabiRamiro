/**
 * @file main.cpp
 * @brief Programa principal del sistema IoT de gestion de sensores
 * @author FabiRamiro
 * @date 2025-10-31
 */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <limits>
#include "SensorTemperatura.h"
#include "SensorPresion.h"
#include "ListaGeneral.h"
#include "SerialReader.h"

#ifdef _WIN32
#include <windows.h>
#endif

/**
 * @brief Detecta y muestra los puertos COM disponibles en Windows
 */
void detectarPuertosCOM()
{
    std::cout << "\n=== Puertos COM Disponibles ===" << std::endl;

    bool encontrado = false;

    for (int i = 1; i <= 20; i++)
    {
        char puerto[10];
        sprintf(puerto, "COM%d", i);

        char nombrePuerto[20];
        snprintf(nombrePuerto, sizeof(nombrePuerto), "\\\\.\\%s", puerto);

        HANDLE hSerial = CreateFileA(nombrePuerto,
                                     GENERIC_READ | GENERIC_WRITE,
                                     0, NULL, OPEN_EXISTING,
                                     FILE_ATTRIBUTE_NORMAL, NULL);

        if (hSerial != INVALID_HANDLE_VALUE)
        {
            std::cout << "  [OK] " << puerto << " (disponible)" << std::endl;
            CloseHandle(hSerial);
            encontrado = true;
        }
        else
        {
            DWORD error = GetLastError();
            if (error == ERROR_ACCESS_DENIED)
            {
                std::cout << "  [EN USO] " << puerto << " (en uso por otra aplicacion)" << std::endl;
                encontrado = true;
            }
        }
    }

    if (!encontrado)
    {
        std::cout << "  No se detectaron puertos COM" << std::endl;
    }

    std::cout << "================================" << std::endl;
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

/**
 * @brief Imprime el menu principal del sistema
 */
void imprimirMenu()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "  Sistema IoT de Monitoreo Polimorfico" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. Crear Sensor de Temperatura" << std::endl;
    std::cout << "2. Crear Sensor de Presion" << std::endl;
    std::cout << "3. Registrar Lectura Manual" << std::endl;
    std::cout << "4. Conectar y Leer desde ESP32" << std::endl;
    std::cout << "5. Procesar Todos los Sensores" << std::endl;
    std::cout << "6. Mostrar Informacion de Sensores" << std::endl;
    std::cout << "7. Detectar Puertos COM Disponibles" << std::endl;
    std::cout << "8. Salir (Liberar Memoria)" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Opcion: ";
}

/**
 * @brief Parsea una linea de datos del formato serial
 * @param linea Linea a parsear (formato: "TIPO:ID:VALOR")
 * @param tipo Buffer para almacenar el tipo de sensor
 * @param id Buffer para almacenar el ID del sensor
 * @param valor Buffer para almacenar el valor como cadena
 */
void parsearLinea(const char *linea, char *tipo, char *id, char *valor)
{
    char lineaCopia[256];
    std::strncpy(lineaCopia, linea, 255);
    lineaCopia[255] = '\0';

    char *token = std::strtok(lineaCopia, ":");
    if (token != nullptr)
    {
        std::strcpy(tipo, token);
    }

    token = std::strtok(nullptr, ":");
    if (token != nullptr)
    {
        std::strcpy(id, token);
    }

    token = std::strtok(nullptr, ":");
    if (token != nullptr)
    {
        std::strcpy(valor, token);
    }
}

/**
 * @brief Funcion principal del programa
 * @return Codigo de salida del programa
 */
int main()
{
    ListaGeneral sistemaGestion;
    SerialReader serialReader;
    int opcion;
    bool continuar = true;

    std::cout << "\n*** SISTEMA IOT DE GESTION POLIMORFICA DE SENSORES ***" << std::endl;
    std::cout << "Autor: FabiRamiro" << std::endl;
    std::cout << "Fecha: 2025-10-31" << std::endl;

    while (continuar)
    {
        imprimirMenu();
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion)
        {
        case 1:
        {
            char nombreSensor[50];
            std::cout << "\nIngrese el ID del sensor de temperatura: ";
            std::cin.getline(nombreSensor, 50);

            SensorTemperatura *nuevoTempSensor = new SensorTemperatura(nombreSensor);
            sistemaGestion.insertarSensor(nuevoTempSensor);

            std::cout << "Sensor de temperatura creado e insertado." << std::endl;
            break;
        }

        case 2:
        {
            char nombreSensor[50];
            std::cout << "\nIngrese el ID del sensor de presion: ";
            std::cin.getline(nombreSensor, 50);

            SensorPresion *nuevoPresSensor = new SensorPresion(nombreSensor);
            sistemaGestion.insertarSensor(nuevoPresSensor);

            std::cout << "Sensor de presion creado e insertado." << std::endl;
            break;
        }

        case 3:
        {
            char idSensor[50];
            std::cout << "\nIngrese el ID del sensor: ";
            std::cin.getline(idSensor, 50);

            SensorBase *sensor = sistemaGestion.buscarSensor(idSensor);

            if (sensor == nullptr)
            {
                std::cout << "Error: Sensor no encontrado." << std::endl;
                break;
            }

            SensorTemperatura *tempSensor = dynamic_cast<SensorTemperatura *>(sensor);
            SensorPresion *presSensor = dynamic_cast<SensorPresion *>(sensor);

            if (tempSensor != nullptr)
            {
                float temperatura;
                std::cout << "Ingrese la temperatura (grados C): ";
                std::cin >> temperatura;
                tempSensor->registrarLectura(temperatura);
            }
            else if (presSensor != nullptr)
            {
                int presion;
                std::cout << "Ingrese la presion (PSI): ";
                std::cin >> presion;
                presSensor->registrarLectura(presion);
            }

            break;
        }

        case 4:
        {
            char puerto[20];
            std::cout << "\nIngrese el puerto COM (ej: COM3): ";
            std::cin.getline(puerto, 20);

            if (!serialReader.conectar(puerto))
            {
                std::cout << "Error al conectar con el puerto serial." << std::endl;
                break;
            }

            std::cout << "\nCuantas lecturas desea capturar? (0 = continuo): ";
            int numLecturas;
            std::cin >> numLecturas;
            std::cin.ignore();

            std::cout << "\n--- Capturando datos del ESP32 ---\n"
                      << std::endl;

            int lecturasCaptadas = 0;
            while (numLecturas == 0 || lecturasCaptadas < numLecturas)
            {
                char buffer[256];
                if (serialReader.leerLinea(buffer, 256))
                {
                    std::cout << "[ESP32] Recibido: " << buffer << std::endl;

                    char tipo[10], id[50], valor[50];
                    parsearLinea(buffer, tipo, id, valor);

                    SensorBase *sensor = sistemaGestion.buscarSensor(id);

                    if (sensor == nullptr)
                    {
                        if (std::strcmp(tipo, "TEMP") == 0)
                        {
                            sensor = new SensorTemperatura(id);
                            sistemaGestion.insertarSensor(sensor);
                        }
                        else if (std::strcmp(tipo, "PRES") == 0)
                        {
                            sensor = new SensorPresion(id);
                            sistemaGestion.insertarSensor(sensor);
                        }
                    }

                    if (sensor != nullptr)
                    {
                        SensorTemperatura *tempSensor = dynamic_cast<SensorTemperatura *>(sensor);
                        SensorPresion *presSensor = dynamic_cast<SensorPresion *>(sensor);

                        if (tempSensor != nullptr)
                        {
                            float temp = std::atof(valor);
                            tempSensor->registrarLectura(temp);
                        }
                        else if (presSensor != nullptr)
                        {
                            int pres = std::atoi(valor);
                            presSensor->registrarLectura(pres);
                        }
                    }

                    lecturasCaptadas++;
                }
            }

            serialReader.desconectar();
            std::cout << "\nCaptura completada. " << lecturasCaptadas << " lecturas registradas." << std::endl;
            break;
        }

        case 5:
        {
            sistemaGestion.procesarTodosSensores();
            break;
        }

        case 6:
        {
            sistemaGestion.imprimirTodosSensores();
            break;
        }

        case 7:
        {
            detectarPuertosCOM();
            break;
        }

        case 8:
        {
            std::cout << "\nCerrando sistema..." << std::endl;
            continuar = false;
            break;
        }

        default:
            std::cout << "Opcion no valida." << std::endl;
            break;
        }
    }

    return 0;
}