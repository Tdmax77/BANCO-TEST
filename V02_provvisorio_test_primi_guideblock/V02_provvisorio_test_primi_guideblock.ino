
// MASTER + COMPARATORE + ARDUINO NANO
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
byte f0 = 0;
byte f1 = 0;
int num2 = 0;

//variabili mitutoyo
int req = 8; //assegna a req il piedino 11 (D8) through q1 (arduino high pulls request line low)
int dat = 2; // assegna a dat il piedino 5  (D2)   Linea Dati del calibro
int clk = 4; // assegna a clk il piedino 7  (D4)  clock del calibro

int i = 0; int j = 0; int k = 0;
byte mydata[14];
int num;
int sign;
//variabili mitutoyo

// variabili sensore pressione
int ValoreADC;
float PB;   //Pressione Misurata
float PM = 0;         //Pressione Massima
float PT = 0;         //Pressione Target
// variabili sensore pressione

char tasto = 0;

int Comp1 = 0;
int Comp2 = 0;
int off = 0;
int off2 = 0;


/* variabile display*/
LiquidCrystal_I2C lcd(0x27, 16, 2);
int Comp1prec = 0;
int Comp2prec = 0;
float PMprec = 0;         //Pressione Massima
float PTprec = 0;         //Pressione Target
float PBprec = 0;         //Pressione
/* variabile display*/



void setup() {

  Wire.begin();
  Serial.begin(115200);

  //variabili mitutoyo
  pinMode(req, OUTPUT);         // setta il pin 11 come OUTPUT
  pinMode(clk, INPUT_PULLUP);   // setta il pin 7 come Input abilitando la resistenza di pullup
  pinMode(dat, INPUT_PULLUP);   // setta il pin 5 come input abilitando la resistenza di pullup
  digitalWrite(req, LOW);       // porta a LOW il pin 11
  //variabili mitutoyo

  /* parte display i2c */
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Guideblock");
  lcd.setCursor(0, 1);
  lcd.print("TestBench v.02");
  delay(3000);
  lcd.clear();
  write_lcdBG();
  /* parte display i2c */

  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
}


void loop() {
  int  r1 = digitalRead(10);
  if (r1 == LOW) {
    PT = 0;
    PTprec = 0;
    PM = 0;
    PB = 0;
  }
  // read_mitutoyo();
  // read_slave();
  // read_sensor();
  //  read_serialmonitor();
  ValoreADC = analogRead(A0);
  PB = (ValoreADC - 97 ) * 0.0072763;



  PM = max(PB, PM);
  if (PM != PMprec) {
    PMprec = PM;
    // lcd.setCursor(12, 0);
    // lcd.print(PM);
  }

  PT = PM / 2; //pressione Target = pressione Massima /2
  //  Comp1 = num + off;
  // Comp2 = num2 + off2;
  // write_serial();
  // write_lcd();


  if (PB != PBprec) {
    PBprec = PB;
    lcd.setCursor(12, 0);
    lcd.print(PB);
    delay(200);
  }

  if (PT != PTprec) {
    PTprec = PT;
    lcd.setCursor(12, 1);
    lcd.print(PT);
  }
}




void read_mitutoyo() {  //legge il comparatore collegato sul arduino master
  digitalWrite(req, HIGH);      // genera set request portando il pin 11 a HIGH
  for (i = 0; i < 13; i++ ) {
    k = 0;
    for (j = 0; j < 4; j++) {
      while ( digitalRead(clk) == LOW) { // hold until clock is high
      }
      while ( digitalRead(clk) == HIGH) { // hold until clock is low
      }
      bitWrite(k, j, (digitalRead(dat) & 0x1)); // read data bits, and reverse order )
    }
    // estrai i dati da mydata
    mydata[i] = k;
  }
  // sign = mydata[4]    decimal = mydata[11]  units = mydata[12];
  sign = mydata[4];
  // assemble measurement from bytes
  char buf[8];
  for (int lp = 0; lp < 6; lp++) {
    buf[lp] = mydata[lp + 5] + '0';
    buf[6] = 0;
    num = atol(buf); //converte la riga in long integer
    if (sign == 8) {
      num = num - (2 * num);
    }
  }
}


void read_slave() {  //legge il comapratore collegato sul secondo arduino
  Wire.requestFrom(2, 2); //richiede 2 Bytes dall'arduino SLAVE 2
  f0 = Wire.read();
  f1 = Wire.read();
  num2 = ((f1 << 8) | f0);
}


void read_sensor() { // legge il sensore di pressione sul arduino master
  ValoreADC = analogRead(A0);
  PB = (ValoreADC - 97 ) * 0.0072763;
}

void read_serialmonitor() {
  tasto = Serial.read();
  switch (tasto) {
    case '1':
      off = -num;
      break;
    case '2':
      off2 = -num2;
    case 'm':
      PM = 0;
      break;
    case 'M':
      PM = 0;
      break;
    case 't':
      PT = 0;
      break;
    case 'T':
      PT = 0;
      break;
    case 'a':
      PT = 0;
      PM = 0;
      break;
    case 'A':
      PT = 0;
      PM = 0;
      break;
  }

}

void write_serial() {
  Serial.print("Comp1= ");
  Serial.print(Comp1);    //manda in seriale il vaore del comparatore letto dall'arduino master
  Serial.print(" ");    //manda in seriale il segno , come separatore
  Serial.print("Comp2= ");
  Serial.print(Comp2);
  Serial.print(" ");
  Serial.print("Pressione: ");
  Serial.print(PB);   //manda in seriale il segno , come separatore
  Serial.print("Pressione Max: ");
  Serial.print(PM);
  Serial.print("   TargetPress= ");
  Serial.print(PT);
  Serial.println("     M,T,A");
}
void write_lcd() {

  if (Comp1 != Comp1prec) {
    Comp1prec = Comp1;
    lcd.setCursor(4, 0);
    lcd.print("    ");
    lcd.setCursor(4, 0);
    lcd.print(Comp1);
  }
  if (Comp2 != Comp2prec) {
    Comp2prec = Comp2;
    lcd.setCursor(4, 1);
    lcd.print("    ");
    lcd.setCursor(4, 1);
    lcd.print(Comp2);
  }

  if (PM != PMprec) {
    PMprec = PM;
    lcd.setCursor(12, 0);
    lcd.print(PM);
  }

  if (PT != PTprec) {
    PTprec = PT;
    lcd.setCursor(12, 1);
    lcd.print(PT);
  }


}

void write_lcdBG() {
  lcd.setCursor(0, 0);
  lcd.print("Inj=     ");
  lcd.setCursor(0, 1);
  lcd.print("Qty=     ");
  lcd.setCursor(8, 0);
  lcd.print("PM=     ");
  lcd.setCursor(8, 1);
  lcd.print("PT=     ");
}
