#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

// =====================================================
// CONFIGURACIÓN DEL HARDWARE
// =====================================================

#define DHTPIN 15
#define DHTTYPE DHT22

#define LED_VERDE 18
#define LED_ROJO 19

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

const unsigned long INTERVALO_MUESTREO = 5000; // 5 segundos

unsigned long tiempoAnterior = 0;

DHT dht(DHTPIN, DHTTYPE);

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,OLED_RESET);

// =====================================================
// PARÁMETROS DEL SISTEMA
// =====================================================

const float SETPOINT = 28.0;

const float TEMP_ON = 29.0;
const float TEMP_OFF = 27.0;

// Rango operativo válido
const float TEMP_MIN = 0.0;
const float TEMP_MAX = 60.0;

// Estado del ventilador
bool ventilador = false;

// Número de muestra
unsigned long muestra = 0;

// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);

  dht.begin();

  // Inicializar OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {

    Serial.println("ERROR: OLED no encontrada");

    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);

  display.setCursor(15, 10);
  display.println("ESP32 THERMOCONTROL");

  display.setCursor(25, 30);
  display.println("Sistema iniciando");

  display.display();

  delay(2000);

  // Encabezado del dataset
  Serial.println(
    "timestamp,temperatura,humedad,setpoint,error,ventilador,estado,dato_valido"
  );
}

// =====================================================
// LOOP
// =====================================================

void loop() {

  if (millis() - tiempoAnterior < INTERVALO_MUESTREO) {
    return;
  }

  tiempoAnterior = millis();

  muestra++;

  // ---------------------------------------------------
  // LECTURA DEL SENSOR
  // ---------------------------------------------------

  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();

  // ---------------------------------------------------
  // ERROR DE LECTURA DEL SENSOR
  // ---------------------------------------------------

  if (isnan(temperatura) || isnan(humedad)) {

    Serial.print(muestra);
    Serial.println(",,,,,,ERROR,0");

    delay(1000);

    return;
  }

  // ---------------------------------------------------
  // VALIDACIÓN DE TEMPERATURA
  // ---------------------------------------------------

  if (temperatura < TEMP_MIN || temperatura > TEMP_MAX) {

    Serial.print(muestra);
    Serial.print(",");
    Serial.print(temperatura, 2);
    Serial.print(",");
    Serial.print(humedad, 2);
    Serial.print(",");
    Serial.print(SETPOINT, 2);
    Serial.print(",");
    Serial.print(",");
    Serial.print("0");
    Serial.print(",");
    Serial.print("ERROR");
    Serial.println(",0");

    // Apagar ventilador por seguridad
    ventilador = false;

    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_ROJO, LOW);

    // Mostrar error en OLED
    display.clearDisplay();

    display.setTextSize(1);

    display.setCursor(0, 0);
    display.println("THERMOCONTROL V2.1");

    display.setCursor(0, 20);
    display.println("ERROR DE TEMP.");

    display.setCursor(0, 35);
    display.print("Lectura: ");
    display.print(temperatura);
    display.println(" C");

    display.setCursor(0, 50);
    display.println("Dato no valido");

    display.display();

    delay(1000);

    return;
  }

  // ---------------------------------------------------
  // CONTROL CON HISTÉRESIS
  // ---------------------------------------------------

  if (temperatura >= TEMP_ON) {

    ventilador = true;

  }

  else if (temperatura <= TEMP_OFF) {

    ventilador = false;
  }

  // ---------------------------------------------------
  // CONTROL DE LEDs
  // ---------------------------------------------------

  if (ventilador) {

    digitalWrite(LED_ROJO, HIGH);
    digitalWrite(LED_VERDE, LOW);

  }

  else {

    digitalWrite(LED_ROJO, LOW);
    digitalWrite(LED_VERDE, HIGH);
  }

  // ---------------------------------------------------
  // CALCULAR ERROR
  // ---------------------------------------------------

  float error = temperatura - SETPOINT;

  // ---------------------------------------------------
  // DEFINIR ESTADO
  // ---------------------------------------------------

  String estado;

  if (ventilador) {
    estado = "ON";
  }
  else {
    estado = "OFF";
  }

  // ---------------------------------------------------
  // REGISTRO CSV
  // ---------------------------------------------------

  Serial.print(muestra);
  Serial.print(",");

  Serial.print(temperatura, 2);
  Serial.print(",");

  Serial.print(humedad, 2);
  Serial.print(",");

  Serial.print(SETPOINT, 2);
  Serial.print(",");

  Serial.print(error, 2);
  Serial.print(",");

  Serial.print(ventilador ? 1 : 0);
  Serial.print(",");

  Serial.print(estado);
  Serial.print(",");

  Serial.println(1);

  // ---------------------------------------------------
  // OLED
  // ---------------------------------------------------

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println("THERMOCONTROL V2.1");

  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);

  display.setCursor(0, 18);
  display.print("Temp: ");
  display.print(temperatura, 1);
  display.println(" C");

  display.setCursor(0, 30);
  display.print("Hum : ");
  display.print(humedad, 0);
  display.println(" %");

  display.setCursor(0, 42);
  display.print("Set : ");
  display.print(SETPOINT, 1);
  display.println(" C");

  display.setCursor(0, 54);

  if (ventilador) {
    display.print("FAN: ON");
  }
  else {
    display.print("FAN: OFF");
  }

  display.display();

}