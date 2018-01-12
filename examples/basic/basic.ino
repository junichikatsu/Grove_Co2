#include <WioLTEforArduino.h>
#include <Co2Sensor.h>

Co2Sensor co2;

WioLTE Wio;

void setup() {
  Wio.Init();
  Wio.PowerSupplyGrove(true);
  co2.begin(&Serial);
  co2.calibration();
}

void loop() {
  if(co2.readData()){
    SerialUSB.print("Temperature: ");
    SerialUSB.print(co2.getTemperature());
    SerialUSB.print("  CO2: ");
    SerialUSB.print(co2.getCo2());
    SerialUSB.println("");
  }
  delay(1000);
}