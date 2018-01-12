
#ifndef _CO2_SENSOR_H_
#define _CO2_SENSOR_H_

#include <WioLTEforArduino.h>

class Co2Sensor {
public:

  Co2Sensor();
  void begin(HardwareSerial* co2Serial);
  bool readData();
  void calibration();
  int getCo2();
  int getTemperature();

private:
  const char _cmd_get_sensor[9] =
  {
      0xff, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79
  };
  const char _cmd_calibrate[9] = 
  {
      0xff, 0x87, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf2
  };

  void sendCommand(const char *buf);
  bool recvData(char *buf);

  char getCheckSum(char *buf);

  HardwareSerial* _co2Serial;
  char _buf[9];
  int _co2ppm;
  int _temperature;
};

#endif
