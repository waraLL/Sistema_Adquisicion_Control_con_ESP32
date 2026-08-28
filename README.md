# Sistema de Adquisición y Control de Temperatura con ESP32

Proyecto de Ingeniería Electrónica que integra **adquisición de datos, control de temperatura mediante histéresis y análisis de datos con Python**. El sistema fue desarrollado inicialmente en el simulador **Wokwi** utilizando un ESP32, un sensor DHT22 y una pantalla OLED SSD1306, con el objetivo de construir un flujo completo de adquisición de datos para su posterior procesamiento y visualización.

> **Estado del proyecto:** 🚧 🛠️ 💻 En desarrollo (Etapa de simulación y adquisición de datos completada) 🚧 🛠️ 💻 

---

## Descripción del proyecto

Este proyecto implementa un sistema capaz de:

* Adquirir mediciones de temperatura y humedad mediante un sensor DHT22
* Controlar un ventilador de acuerdo con un **setpoint** utilizando una lógica de **histéresis**
* Mostrar información en tiempo real en una pantalla OLED SSD1306
* Registrar las mediciones en formato CSV a través del puerto serial para generar un conjunto de datos listo para análisis en Python

El proyecto está pensado como un ejemplo de integración entre **Electrónica, Sistemas Embebidos y Ciencia de Datos**.

---

## Objetivos

* Implementar un sistema de adquisición de datos utilizando ESP32
* Aplicar un algoritmo de control ON/OFF con histéresis para evitar conmutaciones constantes del ventilador
* Registrar datos estructurados para su procesamiento en Python
* Desarrollar un flujo de trabajo reproducible desde la adquisición hasta la visualización de datos.

---

## Tecnologías y herramientas

| Área                     | Herramientas                  |
| ------------------------ | ----------------------------- |
| Microcontrolador         | ESP32 DevKit V1               |
| Sensor                   | DHT22 (Temperatura y Humedad) |
| Visualización local      | OLED SSD1306 (I2C)            |
| Simulación               | Wokwi                         |
| Programación embebida    | Arduino IDE / C++             |
| Procesamiento de datos   | Python (Pandas, NumPy)        |
| Visualización de datos   | Plotly, Matplotlib            |
| Dashboard (próximamente) | Streamlit                     |

---

## Componentes utilizados

| Componente         | Función                                |
| ------------------ | -------------------------------------- |
| ESP32 DevKit V1    | Unidad de procesamiento y control      |
| Sensor DHT22       | Medición de temperatura y humedad      |
| OLED SSD1306       | Visualización de variables del sistema |
| LED Verde          | Indica funcionamiento normal           |
| LED Rojo           | Simula el estado del ventilador        |
| Resistencias 220 Ω | Protección de LEDs                     |

---

##  Funcionalidades implementadas

  ### Adquisición de datos

  * Lectura de temperatura
  * Lectura de humedad
  
  ### Sistema de control
  
  * Setpoint configurable
  * Control ON/OFF
  * Histéresis para evitar cambios rápidos del actuador
  * Estado del ventilador (`ON` / `OFF`)
  
  ### Validación de datos
  
  * Verificación de lecturas inválidas del sensor
  * Identificación de temperaturas fuera del rango operativo
  * Marcado de registros con `dato_valido = 0`
  * Estado `ERROR` para registros inválidos
  
  ### Visualización local
  
  * Temperatura en pantalla OLED
  * Humedad en pantalla OLED
  * Setpoint
  * Estado del ventilador
  
  ---

## Estructura del dataset generado

Cada lectura enviada por el ESP32 genera un registro con la siguiente estructura:

| Variable      | Descripción                                              |
| ------------- | ---------------------------------------------------------|
| `timestamp`   | Número consecutivo de muestra                            |
| `temperatura` | Temperatura medida (°C)                                  |
| `humedad`     | Humedad relativa (%)                                     |
| `setpoint`    | Temperatura objetivo                                     |
| `error`       | Diferencia entre temperatura y setpoint                  |
| `ventilador`  | Estado binario del ventilador (1/0)                      |
| `estado`      | Estado categórico (`ON`, `OFF`, `ERROR`)                 |
| `dato_valido` | Indicador de calidad del dato (1 = válido, 0 = inválido) |

### Ejemplo de salida CSV

```csv
timestamp,temperatura,humedad,setpoint,error,ventilador,estado,dato_valido
1,24.00,40.00,28.00,-4.00,0,OFF,1
13,48.20,40.00,28.00,20.20,1,ON,1
27,64.10,40.50,28.00,,0,ERROR,0
35,6.80,58.50,28.00,-21.20,0,OFF,1
```

Este archivo constituye el conjunto de datos base para las etapas de análisis en Python.

---

# Flujo de trabajo del proyecto

## Etapa 1 — Simulación del sistema 

* Diseño del circuito en Wokwi
* Conexión del ESP32, DHT22 y OLED
* Verificación del funcionamiento del hardware simulado

## Etapa 2 — Firmware del ESP32 

* Lectura del sensor DHT22
* Control mediante histéresis
* Visualización en OLED
* Registro de datos por el puerto serial

## Etapa 3 — Generación del dataset 

* Captura del puerto serial
* Exportación manual del registro del Serial Monitor a un archivo CSV

## Próximas etapas (En desarrollo) 🚧 🛠️ 💻 

### Etapa 4 — Validación y limpieza de datos

* Identificación de datos inválidos
* Tratamiento de valores fuera de rango
* Verificación de tipos de datos
* Generación del dataset procesado

### Etapa 5 — Análisis Exploratorio (EDA)

Se analizarán variables como:

* Distribución de temperatura
* Distribución de humedad
* Tiempo de funcionamiento del ventilador
* Temperaturas fuera del rango operativo
* Error respecto al setpoint
* Cambios de estado del sistema

### Etapa 6 — Dashboard interactivo

Desarrollo de un dashboard con Streamlit que permitirá:

* KPIs del sistema
* Visualización temporal de temperatura y humedad
* Estado del ventilador
* Indicadores de calidad de datos
* Filtros interactivos

### Etapa 7 — Conclusiones

Evaluación del comportamiento del sistema y análisis del desempeño del algoritmo de control.

---

## Resultados esperados

* Sistema de adquisición de datos funcional
* Dataset estructurado para análisis
* Proceso completo de adquisición → procesamiento → visualización

---

## Autor

**Wara López**

Ingeniera Electrónica • Ciencia de Datos • Python • Visualización de Datos

