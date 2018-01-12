#include <Co2Sensor.h>

Co2Sensor::Co2Sensor()
{

}

void Co2Sensor::begin(HardwareSerial* co2Serial)
{
  _co2Serial = co2Serial;
  _co2Serial->begin(9600);
}

bool Co2Sensor::readData()
{
  //コマンド送信
  sendCommand(_cmd_get_sensor);

  delay(10);

  //受信データ確認
  if(!recvData(_buf)) {
    return false;
  }

  // SUM値チェック
  if(getCheckSum(_buf) != _buf[8]) {
    return false;
  }

  _co2ppm = ((int)_buf[2]) << 8 | (int)_buf[3];
  _temperature = (int)_buf[4] - 40;

  return true;
}

void Co2Sensor::calibration()
{
  //コマンド送信
  sendCommand(_cmd_calibrate);
}

int Co2Sensor::getCo2()
{
  return _co2ppm;
}

int Co2Sensor::getTemperature()
{
  return _temperature;
}

void Co2Sensor::sendCommand(const char *buf)
{         
  for(int i=0;i<9; i++){
      _co2Serial->write(buf[i]);
  }
}

bool Co2Sensor::recvData(char *buf)
{
  if(_co2Serial->available())
  {
      while(_co2Serial->available())
      {
          for(int i=0;i<9; i++)
          {
              buf[i] = _co2Serial->read();
          }
      }
      return true;
  }
  return false;
}

char Co2Sensor::getCheckSum(char *buf)
{
  char checksum = 0;
  for( int i = 1; i < 8; i++){
    checksum += buf[i];
  }
  checksum = 0xff ^ checksum;
  checksum += 1;

  return checksum;
}