#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <RF24Network.h>
#include <RF24.h>
#include <printf.h>
#include <math.h>

int e1[12]={11,21,15,25,13,23,16,26,12,22,14,24};
int e2[12]={11,24,14,22,12,26,16,23,13,25,15,21};
byte cylinder = 12;
float scoppio = 0;
int fire_spacing = 120;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (38400);
}

void mostra_cilindro() {

  for ( int i = 1; i < cylinder + 1; i++) {
    double mod = fmod(i, 2);
    Serial.print("mod = ");
    Serial.print(mod);

    if (mod == 1.0)  {  // 1 3 5
      scoppio = ((i - 1) / 2) * fire_spacing  /*- timing_float*/;
      Serial.print(" cilindro = A");
        int cyl = e2[i-1]-10;
      Serial.print(cyl);

    }
    else { // 2 4 6
      scoppio = (i/2 * fire_spacing ) - fire_spacing + 50/*- timing_float*/;
      Serial.print(" cilindro = B");
      int cyl = e2[i-1]-20;
      Serial.print(cyl);

    }
    Serial.print(" scoppio= ");
    Serial.println(scoppio);
  }


  Serial.println("scritti tutti");
}
