#include <Encoder.h>

Encoder AZ(5, 6); //AZimuth ecoder, best to chose pins with innterupts - see Encoder.h help
Encoder ALT(7, 8); //ALTitude above horizon encoder, best to chose pins with innterupts  - see Encoder.h help

void setup() {
  Serial.begin(9600);
  Serial.println("ALT AZ Test:");
}

long positionAZ  = -999;
long positionALT = -999;

void loop() {
  long newAZ, newALT;
  newAZ = AZ.read();
  newALT = ALT.read();
  if (newAZ != positionAZ || newALT != positionALT) {
    Serial.print("AZ = ");
    Serial.print(newAZ);
    Serial.print(", ALT = ");
    Serial.print(newALT);
    Serial.println();
    positionAZ = newAZ;
    positionALT = newALT;
  }

  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both axis to zero");
    AZ.write(0);
    ALT.write(0);
  }
}
