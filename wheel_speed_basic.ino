#include <STM32SD.h>

#ifndef SD_DETECT_PIN
#define SD_DETECT_PIN SD_DETECT_NONE
#endif

File dataSD;
int runNumber;
String strSDName;

void setup(void)
{


  Serial.begin(115200);

  while(!SD.begin()) {
    Serial.println("failure");
    delay(1);
  }
  pinMode(13, OUTPUT);

  // 12 is the hall effect sensor pc2)
  pinMode(12, INPUT);
  digitalWrite(12, LOW); // disable internal pullup

  strSDName = "mainrun1.csv";
  runNumber = 1;

  while(SD.exists(strSDName.c_str())) {
    runNumber += 1;
    strSDName = "mainrun" + String(runNumber) + ".csv";
  }

  Serial.println(strSDName);
  dataSD = SD.open(strSDName.c_str());
  if(!dataSD) {
    while(1) {
      Serial.println("fail to open");
      Serial.println(strSDName.c_str());
      delay(2);
    }
  }
  dataSD.println("Time of pulse (ms)");
  dataSD.close();

  digitalWrite(13, HIGH);
}

bool written = false;
void loop(void)
{
  while(digitalRead(12)){
    Serial.println(digitalRead(12));
    if(!written){
      written = true;
      dataSD = SD.open(strSDName.c_str());
      String time = String(millis());
      dataSD.println(time.c_str());
      dataSD.close();
    }
    delay(1);
  }

  written = false;
}
