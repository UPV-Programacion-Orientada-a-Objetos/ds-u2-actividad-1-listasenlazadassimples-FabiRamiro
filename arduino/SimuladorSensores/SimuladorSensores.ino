/**
 * @file SimuladorSensores.ino
 * @brief Simulador de sensores IoT para ESP32
 * @author FabiRamiro
 * @date 2025-10-31
 *
 * Este sketch simula el envío de datos de múltiples sensores
 * (temperatura y presión) a través del puerto serial en formato:
 * TIPO:ID:VALOR
 *
 * Ejemplos:
 * - TEMP:T-001:23.5
 * - PRES:P-105:85
 */

// Intervalo de envío de datos (milisegundos)
const unsigned long INTERVALO_ENVIO = 2000;

// Variables para control de tiempo
unsigned long tiempoAnterior = 0;

// Contadores para IDs de sensores
int contadorTemp = 1;
int contadorPres = 1;

/**
 * @brief Configuración inicial del ESP32
 */
void setup()
{
    // Inicializar comunicación serial a 115200 baudios
    Serial.begin(115200);

    // Inicializar generador de números aleatorios
    randomSeed(analogRead(0));

    // Mensaje de inicio
    delay(2000);
    Serial.println("ESP32 - Simulador de Sensores IoT Iniciado");
    Serial.println("Formato: TIPO:ID:VALOR");
    Serial.println("========================================");
}

/**
 * @brief Genera y envía datos simulados de un sensor de temperatura
 */
void enviarDatosTemperatura()
{
    // Generar ID del sensor
    char id[20];
    sprintf(id, "T-%03d", contadorTemp);

    // Generar temperatura aleatoria entre 15.0 y 45.0 °C
    float temperatura = 15.0 + random(0, 300) / 10.0;

    // Enviar datos en formato TIPO:ID:VALOR
    Serial.print("TEMP:");
    Serial.print(id);
    Serial.print(":");
    Serial.println(temperatura, 1);

    // Incrementar contador (ciclar entre 1-10)
    contadorTemp = (contadorTemp % 10) + 1;
}

/**
 * @brief Genera y envía datos simulados de un sensor de presión
 */
void enviarDatosPresion()
{
    // Generar ID del sensor
    char id[20];
    sprintf(id, "P-%03d", contadorPres);

    // Generar presión aleatoria entre 50 y 150 PSI
    int presion = random(50, 151);

    // Enviar datos en formato TIPO:ID:VALOR
    Serial.print("PRES:");
    Serial.print(id);
    Serial.print(":");
    Serial.println(presion);

    // Incrementar contador (ciclar entre 1-10)
    contadorPres = (contadorPres % 10) + 1;
}

/**
 * @brief Loop principal del programa
 */
void loop()
{
    unsigned long tiempoActual = millis();

    // Verificar si ha pasado el intervalo de envío
    if (tiempoActual - tiempoAnterior >= INTERVALO_ENVIO)
    {
        tiempoAnterior = tiempoActual;

        // Alternar entre enviar datos de temperatura y presión
        if (random(0, 2) == 0)
        {
            enviarDatosTemperatura();
        }
        else
        {
            enviarDatosPresion();
        }
    }

    // Pequeña pausa para no saturar el procesador
    delay(10);
}