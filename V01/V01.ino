/*Software per la taratura delle pompe nafta del 46F
   Arduino A processa il programma, legge il sensore di pressione e legge il comparatore dello Start of inj, arduino B legge il comparatore del Quantity
   V101 16 giugno 2021 aggiunto pulsante in avvio per escludere i compartatori
   V012 23 giugno 2012 modificato Inj in Tim a display
   V1.04 test per modulo radio : modificata la logica dei pulsanti, sul coto sono a 0 e li porto a 5 , qui sono a 5 e li porto a zero
  quasi tutto va, da sistemare il secondo comparatore che non legge.
   V 1.10 dual boot funzionante, sembra tutto ok
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <RF24Network.h>
#include <RF24.h>
#include <printf.h>

const float vers = 1.10; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< INSERIRE LA REVISIONE SE SI MODIFICA
byte f0 = 0;    // variabili per spi
byte f1 = 0;    // variabili per spi
int num2 = 0;   // variabili per spi

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
float PressioneBar;   //Pressione Misurata
float PM = 0;         //Pressione Massima
float PT = 0;         //Pressione Target
// variabili sensore pressione

char tasto = 0;

int Comp1 = 0;     // lettura comparatore inj
int Comp2 = 0;     // lettura comparatore quantity
int off = 0;       // variabile per azzeramento
int off2 = 0;       // variabile per azzeramento


/* variabile display*/
LiquidCrystal_I2C lcd(0x27, 16, 2);
int Comp1prec = 0;     // variabile per definire se il dato è nuovo (e aggiornare il display)
int Comp2prec = 0;     // variabile per definire se il dato è nuovo (e aggiornare il display)
float PMprec = 0;         //Pressione Massima
float PTprec = 0;         //Pressione Target
/* variabile display*/

// da coto
RF24 radio(9/*CE*/, 10/*CSN*/);             // Coto (9,10)  Kren (7, 8)  RF - NANO with ext ant. (9, 10) RF - NANO without ext ant (10, 9)

RF24Network network(radio);     // Network uses that radio
const uint16_t this_node = 00;  // Address of our node in Octal format ( 04,031, etc)   this is the master (raspy display)
const uint16_t node_5 = 05;     // Address of the encoder node in Octal format          this is ENCODER

struct payload_t {              // Structure of  payload received from slaves
  long num_sent;                // this is the data readed from COMP, it is the value readed from Mitutoyo Comparator
  int control;                  // this is a control variable that continuously incrases on every data transmission, i need it for to understand if COMP is alive
  int OffsetReq;                // if 1 Offset is requested, used only by node_5
  int VO;                       // Offset value
};
payload_t payload;

long valoreangolocorrettoPrev;  // needed for data verify
int mostraangolo = 0;           // needed for redisplay after lost conn
float angprint;                 // needed for to convert long data into float (we receive a long from the net)
float angstamp;                 // needed for to convert long data into float (we receive a long from the net)

payload_t data;                 // create to arrays payload_t data
int counter ;                   // Array defined for validation of data (ses main loop)
int Nnosignal (30);             // number of acceptable failed reads

unsigned long tempo;            // need for the y counter
int y = 1;                      // need for block OFFSET Request loop

/*Variabili Offset servono ad inserire il valore usando i 3 pulsanti*/
const int buttonOkPin = 6;
const int buttonUpPin = 5;  //numero pin a cui è collegato il pulsante di UP
const int buttonDownPin = 7;  //numero pin a cui è collegato il pulsnte di DOWN
int buttonOkState;
int buttonUpState;  //stato attuale del pulsante di UP
int buttonDownState;  //stato attuale del pulsante di Down
long UpDebounceTime;  //Variabilie di appoggio per calcolare il tempo di cambio di stato del pulsante di UP
long DownDebounceTime;  //Variabilie di appoggio per calcolare il tempo di cambio di stato del pulsante di Down
long timerButtonPushed; //tempo che indica da quanto è stato premuto il pulsante
long timerPauseRepeat;  //tempo che indica da quanto è stata fatta l'ultima ripetizione
long time_add_10 = 1200;  //costante per attivare ripetizione da +10  era 1000
long time_add_100 = 9000; //costante per attivare ripetizione da +100  era 5000
long time_pause = 250;  //costante che determina il tempo di ripetizione di UP e di DOWN
long debounceDelay = 80; //Tempo di debounce per i pulsanti UP e DOWN
boolean repeatEnable = LOW; //memoria che indica il repeat del pulsante attivo

int var = 0;  //variabile da aumentare o diminuire come valore
const int varMax = 720; //limite massimo valore della variabile
const int varMin = 0; //limite minimo valore della variabile

int readingUp = 0;  //Lettura ingresso digitale del pulsante di UP
int readingDown = 0;  //Lettura ingresso digitale del pulsante di Down

/*Variabili Offset servono ad inserire il valore usando i 3 pulsanti*/

int counterprec;
// da coto

int AA = 0;
const int buttonMode = 3;
const int Arduino2_PWR = A1;


int bypass = digitalRead(buttonMode);   //

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////     SETUP      ////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


void setup() {


  /*Parte Variabile Offset*/
  pinMode (buttonUpPin, INPUT_PULLUP);   //impostazione buttonUpPin come ingresso
  pinMode (buttonDownPin, INPUT_PULLUP); //impostazione buttonDownPin come ingresso
  pinMode (buttonOkPin, INPUT_PULLUP);   //impostazione buttonOkPin come ingresso
  pinMode (buttonMode, INPUT_PULLUP);     //impostazione buttonMode come ingresso
  /*Parte Variabile Offset*/

  delay (500);
  Wire.begin();
  Serial.begin(38400);
  SPI.begin();                                               // initialize SPI
  printf_begin();

  radio.begin();                                             // initialize radio module
  radio.setDataRate(RF24_250KBPS);
  radio.printDetails();
  Serial.print("Version ");
  Serial.println(vers);
  network.begin(/*channel*/ 110, /*node address*/ this_node); // start network

  data.num_sent = 7777;                                // num_sent starts from 7777
  data.control = 0;                                    // control starts from 0
  counter = 0;                                         // reset counter


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
  lcd.print("TestBench v");
  lcd.setCursor(12, 1);
  lcd.print(vers);
  delay(3000);
  lcd.clear();
  int bypass = digitalRead(buttonMode);   //
  /* parte display i2c */
  if (bypass == LOW) {   //se clicco il 4 pulsante parto in modalità testbench, altrimenti parte in modalità volano
    AA = 1;
    write_lcdBG_AA();
    //digitalWrite(Arduino2_PWR, HIGH);
  } else {
    AA = 0;
    write_lcdBG_bench();
    //digitalWrite(Arduino2_PWR, LOW);
  }

}



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////     LOOP     ////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


void loop() {



  if (AA == 0) {  //CONFIGURAZIONE BANCO

    read_mitutoyo();          // legge il comparatore1 onboard
    read_slave();             // legge il comparatore2 sull'arduino in wire
    read_sensor();            // legge sensore pressione onboard
    read_serialmonitor();     //legge la seriale (per azzeramenti debug)
    pulsanti_bench();
    PM = max(PressioneBar, PM);     // confronta la pressione istantanea con quella massima ed assegna a PM il valore piu alto
    PT = PM / 2;                    // pressione Target = pressione Massima /2
    Comp1 = num + off;              // assegna alla variabile Comp1 la lettura dopo l'azzeramento  (valore iniziale + offset azzeramento)
    Comp2 = num2 + off2;
    //write_serial();                 // scrive sulla seriale i dati
    //write_lcdBG_bench();
    write_lcd_bench();
  }

  if (AA == 1) { // CONFIGURAZIONE MONTAGGIO
    read_sensor();            // legge sensore pressione onboard
    read_serialmonitor();     //legge la seriale (per azzeramenti debug)
    pulsanti_AA();

    PM = max(PressioneBar, PM);     // confronta la pressione istantanea con quella massima ed assegna a PM il valore piu alto
    PT = PM / 2;                    // pressione Target = pressione Massima /2

    // parte radio e angolo
    if (millis() > tempo + 1000) {                              // y is always 1 so i can enter into Offset task,
      y = 1;                                                   // when Offset is setted y become 0 so the Offset task can't loop.
    } else {                                                   // after 100 milliseconds y become 1 so it is possible to execute Offset task.
      y = 0;
    }


    network.update();           // looking for news on the network
    delay(5);                   // needed at least 1 ms of delay or display stay in NOT CONN state (i don't know why ...
    while ( network.available() ) {                             // if network is up  ... I need at least one slave active for to keep active the network, otherwise no network will be available
      if (mostraangolo == 1) {                                  // after a lost connection it need to refresh display also if value is not changed
        lcd.setCursor(8, 0);
        lcd.print(angstamp);
        mostraangolo = 0;                                     // reset value
      }

      int cnt (0);                                             // reset counter
      RF24NetworkHeader header;                                // declare the address of this node: every packet sent from slaves to header will be readed from this node (00, the master)
      network.read(header, &payload, sizeof(payload));         // read the packet netwotk sent for this node
      size_t node_id = header.from_node;                       // create a variable node_id that stores the source of the packet ( who is sending it to me? COMP1 with 01 , COMP2 with 02 and so on..
      //    Serial.println(payload.OffsetReq);
      //    Serial.println(payload.VO );
      //   Serial.println(y );
      //    Serial.println("///////////////////////////////////////////////////////////////////////////");
      if ((payload.OffsetReq == 5) && (payload.VO = 9999) && (y == 1)) {     // if Offset is request i start the Offset task
        testo_richiesta_inserimento_offset();                                // ask for offset
        while (digitalRead(buttonOkPin) == HIGH )                             // insert value and wait for OK button pressed
        {

          PROCEDURA_OFFSET();
          //read_serialmonitor();// Offset procedure

        }
        payload.OffsetReq = 0;                                                // reset the Offset request
        payload.VO = var;                                                     // assign offset value to payload
        RF24NetworkHeader header5(05);                                        // define encoder network address
        network.write(header5, &payload, sizeof(payload));                    // send payload to encoder
        delay(100);                                                           // little delay
        tempo = millis();                                                     // set variable for y status
        y = 0;                                                                // put y to 0
        write_lcdBG_AA();
      }
    }

    if (data.control != payload.control) {      // if control readed from network is different from control stored i assume that the packet is new, so the slave is alive and the data is valid
      data.num_sent = payload.num_sent;         // so i store readed values in data.num_sent ( this is encoder value)
      data.control = payload.control;           // update data.control to new value received  (this is the counter sent from encoder that increase on every sending)
      counter = 0;                              // reset couter of the node i readed in this cycle.
    } else {
      counter = counter += 1;                   // icrease counter
    }

    if (counter >= Nnosignal) {                 // if counter reach Nnosignal
      display_no_conn();                        // display no conn for 2 seconds
      delay(2000);
      mostraangolo = 1;                         // but variable to 1 for refresh display next cycle
    } else {
      display_angolo();                         // if all ok display value
    }

    
    write_lcd_AA();
  }


}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////



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
  PressioneBar = (ValoreADC - 97 ) * 0.0072763;
}

void read_serialmonitor() {  // legge i comandi da seriale più per debug che altro
  tasto = Serial.read();
  switch (tasto) {
    case '1':
      radio.printDetails();
      break;
    case '2':
      digitalWrite(Arduino2_PWR, HIGH);
      Serial.print("stato Arduino2_PWR ");
      Serial.println(Arduino2_PWR);
      break;
    case '5':
      digitalWrite(Arduino2_PWR, LOW);
      Serial.print("stato Arduino2_PWR ");
      Serial.println(Arduino2_PWR);
      break;

    case '3':
      Serial.println(payload.OffsetReq);
      Serial.println(payload.VO );
      Serial.println(y );
      Serial.println("///////////////////////////////////////////////////////////////////////////");
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
    case 's':
      Serial.print("stato Arduino2_PWR ");
      Serial.println(Arduino2_PWR);
      break;
    case 'r':
      payload.OffsetReq = 5;
      break;
  }
}

void write_serial() {
  Serial.print(" Comp1= ");
  Serial.print(Comp1);
  Serial.print(" ");
  Serial.print("  Comp2= ");
  Serial.print(Comp2);
  Serial.print(" ");
  Serial.print("  Pressione: ");
  Serial.print(PressioneBar);
  Serial.print("  Pressione Max: ");
  Serial.print(PM);
  Serial.print("  TargetPress= ");
  Serial.print(PT);
  Serial.println("     M,T,A");
}

void write_lcd_bench() {     // scrive i dati sul display solo se cambiano di valore
  if (Comp1 != Comp1prec) {
    Comp1prec = Comp1;
    lcd.setCursor(4, 0);
    lcd.print("     ");
    lcd.setCursor(4, 0);
    lcd.print(Comp1);
  }
  if (Comp2 != Comp2prec) {
    Comp2prec = Comp2;
    lcd.setCursor(4, 1);
    lcd.print("     ");
    lcd.setCursor(4, 1);
    lcd.print(Comp2);
  }
  if (PressioneBar != PMprec) {
    PMprec = PM;
    lcd.setCursor(12, 0);
    lcd.print("     ");
    lcd.setCursor(12, 0);
    lcd.print(PressioneBar);

  }
  if (PT >= PTprec) {
    PTprec = PT;
    lcd.setCursor(12, 1);
    lcd.print("     ");
    lcd.setCursor(12, 1);
    lcd.print(PT);
  }
}

void write_lcd_AA() {     // scrive i dati sul display solo se cambiano di valore

  if (PressioneBar != PMprec) {
    PMprec = PM;
    lcd.setCursor(3, 1);
    lcd.print("     ");
    lcd.setCursor(3, 1);
    lcd.print(PressioneBar);

  }
  if (PT >= PTprec) {
    PTprec = PT;
    lcd.setCursor(12, 1);
    lcd.print("       ");
    lcd.setCursor(12, 1);
    lcd.print(PT);
  }
}

void write_lcdBG_bench() {  // scrive il "background" che non viene mai aggiornato (non serve e così non flashano le scritte
  lcd.setCursor(0, 0);
  lcd.print("Tim=       ");
  lcd.setCursor(0, 1);
  lcd.print("Qty=       ");
  lcd.setCursor(9, 0);
  lcd.print("P =     ");
  lcd.setCursor(9, 1);
  lcd.print("PT=     ");
}

void write_lcdBG_AA() {  // scrive il "background" che non viene mai aggiornato (non serve e così non flashano le scritte
  lcd.setCursor(0, 0);
  lcd.print("ANG=            ");
  lcd.setCursor(0, 1);
  lcd.print("P=     ");
  lcd.setCursor(8, 1);
  lcd.print("Pt=      ");

}

void pulsanti_AA() {
  if (digitalRead(buttonUpPin) == LOW) {          // se premuto azzera il valore di PT (target)
    PT = 0;
    PTprec = 0;
    PM = 0;
    PressioneBar = 0;
    Serial.println("PULSANTE UP");
  }
}

void pulsanti_bench() {

  if (digitalRead(buttonDownPin) == LOW) {          // se premuto azzera il valore di inj
    lcd.setCursor(4, 0);
    lcd.print("     ");
    off = -num;
    Serial.println("PULSANTE DOWN");
  }
  if (digitalRead(buttonOkPin) == LOW) {          // se premuto azzera il valore di qty
    lcd.setCursor(4, 1);
    lcd.print("     ");
    off2 = -num2;
    Serial.println("PULSANTE OK");
  }
  if (digitalRead(buttonUpPin) == LOW) {          // se premuto azzera il valore di PT (target)
    PT = 0;
    PTprec = 0;
    PM = 0;
    PressioneBar = 0;
    Serial.println("PULSANTE UP");
  }
}

void display_no_conn() {

  lcd.setCursor(0, 0);
  lcd.println("NO CONNECTION   ");
  Serial.println("noconn");
}

void testo_richiesta_inserimento_offset() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println("INSERIRE VALORE ");
  lcd.setCursor(0, 1);
  lcd.println("ANGOLO VOLANO   ");
}

void display_angolo() {
  if (payload.num_sent != valoreangolocorrettoPrev)     // refresh display only if angle changes
  {
    valoreangolocorrettoPrev = payload.num_sent;        // read angle value
    angprint = payload.num_sent;                       //convert from long to float
    angstamp = angprint / 100;                         // add the comma

    lcd.setCursor(4, 0);
    lcd.print("          ");
    lcd.setCursor(4, 0);
    lcd.print(angstamp);
    Serial.println(angstamp);
  }
}

void readButtonState() {

  int readingUp = digitalRead(buttonUpPin); //Lettura ingresso digitale del pulsante di UP
  int readingDown = digitalRead(buttonDownPin); //Lettura ingresso digitale del pulsante di Down

  //if (readingUp == HIGH) { //sul coto sono a 0 e li porto a 5
  if (readingUp == LOW) {
    if ((millis() - UpDebounceTime) > debounceDelay) {
      buttonUpState = HIGH;
    }
  } else {
    buttonUpState = LOW;
    UpDebounceTime = millis();
  }

  //if (readingDown == HIGH) {  //sul coto sono a 0 e li porto a 5
  if (readingDown == LOW) {
    if ((millis() - DownDebounceTime) > debounceDelay) {
      buttonDownState = HIGH;

    }
  } else {
    buttonDownState = LOW;
    DownDebounceTime = millis();
  }
}

void PROCEDURA_OFFSET() { // mi restituisce un valore var che ho inserito come offset

  readButtonState();  //Lettura stato buttons con controllo antirimbalzo

  if (buttonUpState == HIGH || buttonDownState == HIGH) {
    if ((repeatEnable == HIGH && ((millis() - timerPauseRepeat) > time_pause)) || repeatEnable == LOW) {
      if ((millis() - timerButtonPushed) > time_add_10) {
        if ((millis() - timerButtonPushed) > time_add_100) {
          if (buttonUpState == HIGH) var = var + 100;
          if (buttonDownState == HIGH) var = var - 100;
        } else {
          int resto = 0;
          if (buttonUpState == HIGH) resto = 10 - (var % 10);
          if (buttonDownState == HIGH) resto = (var % 10);
          if (resto == 0) {
            if (buttonUpState == HIGH) var = var + 10;
            if (buttonDownState == HIGH) var = var - 10;
          } else {
            if (buttonUpState == HIGH) var = var + resto;
            if (buttonDownState == HIGH) var = var - resto;
          }
        }
      } else {
        if (buttonUpState == HIGH) var++;
        if (buttonDownState == HIGH) var--;
      }
      timerPauseRepeat = millis();
      repeatEnable = HIGH;
      if (var > varMax) var = varMax;
      if (var < varMin) var = varMin;
      lcd.setCursor(0, 0);
      lcd.print("                 ");    //disegnare caratteri vuoti dovrebbe essere piu veloce del clear
      lcd.setCursor(0, 1);
      lcd.print("                 ");
      lcd.setCursor(0, 0);
      lcd.print("Inserire Offset:");
      lcd.setCursor(1, 1);
      lcd.print(var);
      lcd.setCursor(10, 1);
      lcd.print("Gradi");
      delay(200);
    }
  } else {
    timerButtonPushed = millis();
    timerPauseRepeat = millis();
    repeatEnable = LOW;
  }
}
