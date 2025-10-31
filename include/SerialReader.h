/**
 * @file SerialReader.h
 * @brief Simulador de lectura desde puerto serial (Arduino/ESP32)
 * @author FabiRamiro
 * @date 2025-10-31
 */

#ifndef SERIALREADER_H
#define SERIALREADER_H

/**
 * @class SerialReader
 * @brief Clase para simular la lectura de datos desde el puerto serial
 *
 * En un entorno real, esta clase manejaría la comunicación con el ESP32
 * a través del puerto serial. Para propósitos de demostración, simula
 * las lecturas de manera aleatoria.
 */
class SerialReader
{
private:
    bool conectado; ///< Estado de conexión con el dispositivo

public:
    /**
     * @brief Constructor por defecto
     */
    SerialReader();

    /**
     * @brief Destructor
     */
    ~SerialReader();

    /**
     * @brief Simula la conexión al puerto serial
     * @param puerto Nombre del puerto (ej: "COM3", "/dev/ttyUSB0")
     * @return true si la conexión fue exitosa
     */
    bool conectar(const char *puerto);

    /**
     * @brief Cierra la conexión serial
     */
    void desconectar();

    /**
     * @brief Lee una línea de datos desde el serial
     * @param buffer Buffer donde se almacenará la línea leída
     * @param tamano Tamaño máximo del buffer
     * @return true si se leyó correctamente
     */
    bool leerLinea(char *buffer, int tamano);

    /**
     * @brief Verifica si hay datos disponibles para leer
     * @return true si hay datos disponibles
     */
    bool hayDatos() const;
};

#endif // SERIALREADER_H