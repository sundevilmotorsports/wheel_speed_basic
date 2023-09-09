#include <SD.h>

File dataSD;
int runNumber;
String strSDName;

void setup(void)
{

  Serial.begin(115200);

  pinMode(13, OUTPUT);

  // 12 is the hall effect sensor pc2)
  pinMode(12, INPUT);
  digitalWrite(12, LOW); // disable internal pullup

  strSDName = "mainrun1.csv";
  runNumber = 1;

  while(SD.exists(strSDName)) {
    runNumber += 1;
    strSDName = "mainrun" + String(runNumber) + ".csv";
  }

  Serial.println(strSDName);
  dataSD = SD.open(strSDName, FILE_WRITE);
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
      dataSD = SD.open(strSDName, FILE_WRITE);
      dataSD.println(millis());
      dataSD.close();
    }
    delay(1);
  }

  written = false;
}
