cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(SistemaIoTSensores VERSION 1.0 LANGUAGES CXX)

# Estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Directorio de includes
include_directories(${PROJECT_SOURCE_DIR}/include)

# Archivos fuente
set(SOURCES
    src/main.cpp
    src/SensorBase.cpp
    src/SensorTemperatura.cpp
    src/SensorPresion.cpp
    src/ListaGeneral.cpp
    src/SerialReader.cpp
)

# Archivos de encabezado
set(HEADERS
    include/SensorBase.h
    include/SensorTemperatura.h
    include/SensorPresion.h
    include/ListaSensor.h
    include/ListaGeneral.h
    include/SerialReader.h
)

# Ejecutable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Instalación
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Configuración para Doxygen (opcional)
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Generando documentación con Doxygen"
        VERBATIM
    )
endif()