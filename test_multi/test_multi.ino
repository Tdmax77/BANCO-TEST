

/*Software per la taratura delle pompe nafta del 46F
   Arduino A processa il programma, legge il sensore di pressione e legge il comparatore dello Start of inj, arduino B legge il comparatore del Quantity
   V101 16 giugno 2021 aggiunto pulsante in avvio per escludere i compartatori
   V012 23 giugno 2012 modificato Inj in Tim a display
   V1.04 test per modulo radio : modificata la logica dei pulsanti, sul coto sono a 0 e li porto a 5 , qui sono a 5 e li porto a zero
  quasi tutto va, da sistemare il secondo comparatore che non legge.
   V 1.10 dual boot funzionante, sembra tutto ok
   V1.11  sto aggiungendo la confiogurazione engine ed ho messo il display a 2004 al posto del 1602
   V1.12 aggiungendo la scrittura del cilindro
   v1.14 creati vettori con scoppi, creati vettori con limiti  da implementare la visualizzazione corretta
   v1.15 visualizza correttamente i cilindri, da sistemare la soglia di attivazione della finestra ( parametro h) e sistamare il primo cilindro (valore negativo)
   v1.17 sembra andare tutto compreso il 14v , da ottimizzare
   v 1.18 sitemato cw e ccw
   v1.19 ok
   v1.20 correzione inserimento offset CCW e modificati ritardi e y=0 nel while network per evitare la doppia richiesta del offset volano
   v1.21 corretto errore su 12 cilindri (sfasamento bancate)
   v1.22 modificata visualizzazione del valore di timing sul cilindro 
   

*/

//#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//#include <Wire.h>
//#include <LiquidTWI.h>
//#include <SPI.h>
#include <RF24Network.h>
#include <RF24.h>
#include <printf.h>
//#include <Vector.h>


const float vers = 1.22; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< INSERIRE LA REVISIONE SE SI MODIFICA
/*
  //variabili per spi
  byte f0 = 0;    // variabili per spi
  byte f1 = 0;    // variabili per spi
  int num2 = 0;   // variabili per spi
  //variabili per spi
*/

/*
  //variabili mitutoyo
  int req = 8; //assegna a req il piedino 11 (D8) through q1 (arduino high pulls request line low)
  int dat = 2; // assegna a dat il piedino 5  (D2)   Linea Dati del calibro
  int clk = 4; // assegna a clk il piedino 7  (D4)  clock del calibro

  int i = 0; int j = 0; int k = 0;
  byte mydata[14];
  int num;
  int sign;

  int Comp1 = 0;     // lettura comparatore inj
  int Comp2 = 0;     // lettura comparatore quantity
  int off = 0;       // variabile per azzeramento
  int off2 = 0;      // variabile per azzeramento
  int Comp1prec = 0;     // variabile per definire se il dato è nuovo (e aggiornare il display)
  int Comp2prec = 0;     // variabile per definire se il dato è nuovo (e aggiornare il display)

  //variabili mitutoyo
*/

// variabili sensore pressione
int ValoreADC;
float PressioneBar;   //Pressione Misurata
float PM = 0;         //Pressione Massima
float PT = 0;         //Pressione Target
float PMprec = 0;         //Pressione Massima
float PTprec = 0;         //Pressione Target

// variabili sensore pressione


// variabile per seriale debug
char tasto = 0;
// variabile per seriale debug



/* variabile display*/
//LiquidTWI lcd(0);
LiquidCrystal_I2C lcd(0x27, 20, 4);

/* variabile display*/

// variabili network
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
byte mostraangolo = 0;           // needed for redisplay after lost conn
float angprint;                 // needed for to convert long data into float (we receive a long from the net)
float angstamp = 0.0;                 // needed for to convert long data into float (we receive a long from the net)

payload_t data;                 // create to arrays payload_t data
byte counter ;                   // Array defined for validation of data (ses main loop)
byte Nnosignal (30);             // number of acceptable failed reads

unsigned long tempo;            // need for the y counter
byte y = 1;                      // need for block OFFSET Request loop



/*Variabili Offset servono ad inserire il valore usando i 3 pulsanti*/
const byte button_B = 6;
const byte button_C = 5;  //numero pin a cui è collegato il pulsante di UP
const byte button_A = 7;  //numero pin a cui è collegato il pulsnte di DOWN
const byte button_D = 3;
byte buttonOkState;
byte buttonUpState;  //stato attuale del pulsante di UP
byte buttonDownState;  //stato attuale del pulsante di Down
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

byte readingUp = 0;  //Lettura ingresso digitale del pulsante di UP
byte readingDown = 0;  //Lettura ingresso digitale del pulsante di Down

/*Variabili Offset servono ad inserire il valore usando i 3 pulsanti*/


/* variabili per setup motore*/
byte engine = 0;  //variabile da aumentare o diminuire come valore            serve per setup motore
const byte engineMax = 14; //limite massimo valore della variabile
const byte engineMin = 1; //limite minimo valore della variabile
byte engine_setup = 0;

int timing = 1999;  //variabile da aumentare o diminuire come valore            serve per setup motore
float timing2 = 0;
const int timingMax = 3000; //limite massimo valore della variabile
const int timingMin = 1000; //limite minimo valore della variabile
float timing_float;
byte timing_setup = 0;
/* variabili per setup motore*/



int counterprec;
// da coto

//byte AA = 0;

//const byte Arduino2_PWR = A1;


//byte bypass = digitalRead(button_D);   //

// variabili per mettere il nome del cilindro
struct motore {
  byte cylinder = 0;
  int fire_spacing = 0;
  byte cw = 0;
  byte index = 0;
  char *e[17];
  int delta = 0;
  //  int h[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  //  int l[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  //  int n[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // int *aa;
};
motore motore;
float scoppio = 0;
byte cyl = 0;
byte range = 5; // tolleranza di visualizzazione in gradi
char *e1[] = {"A1", "B1", "A3", "B3", "A2", "B2", "A5", "B5", "A8", "B8", "A6", "B6", "A7", "B7", "A4", "B4"}; // 16V46DF  CW
char *e2[] = {"A1", "B4", "A4", "B7", "A7", "B6", "A6", "B8", "A8", "B5", "A5", "B2", "A2", "B3", "A3", "B1"}; // 16V46DF  CCW
char *e3[] = {"A1", "B1", "A3", "B3", "A5", "B5", "A7", "B7", "A6", "B6", "A4", "B4", "A1", "B1",}; // 14V46DF  CW
char *e4[] = {"A1", "B2", "A2", "B4", "A4", "B6", "A6", "B7", "A7", "B8", "A8", "B3", "A3", "B1",}; // 14V46DF  CCW
char *e5[] = {"A1", "B1", "A5", "B5", "A3", "B3", "A6", "B6", "A2", "B2", "A4", "B4"}; // 12V46DF  CW
char *e6[] = {"A1", "B4", "A4", "B2", "A2", "B6", "A6", "B3", "A3", "B5", "A5", "B1"}; // 12V46DF CCW
char *e7[] = {"A1", "A5", "A9", "A4", "A7", "A8", "A2", "A3", "A6"};                   // 9L46DF  CW
char *e8[] = {"A1", "A6", "A3", "A2", "A8", "A7", "A4", "A9", "A5"};                   // 9L46DF CCW
char *e9[] = {"A1", "A6", "A2", "A4", "A8", "A3", "A7", "A5"};       // 8L46DF  CW
char *e10[] = {"A1", "A5", "A7", "A3", "A8", "A4", "A2", "A6"};     // 8L46DF CCW
char *e11[] = {"A1", "A3", "A5", "A7", "A6", "A4", "A2",};     // 7L46DF  CW
char *e12[] = {"A1", "A2", "A4", "A6", "A7", "A5", "A3",};    // 7L46DF CCW
char *e13[] = {"A1", "A2", "A4", "A6", "A5", "A3"}; // 6L46DF  CW
char *e14[] = {"A1", "A3", "A5", "A6", "A4", "A2"}; // 6L46DF CCW

float q = 0;
byte h = 2;

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////     SETUP      ////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


void setup() {


  /*Parte Variabile Offset*/
  pinMode (button_C, INPUT_PULLUP);   //impostazione button_C come ingresso
  pinMode (button_A, INPUT_PULLUP); //impostazione button_A come ingresso
  pinMode (button_B, INPUT_PULLUP);   //impostazione button_B come ingresso
  pinMode (button_D, INPUT_PULLUP);     //impostazione button_D come ingresso
  /*Parte Variabile Offset*/
  delay (500);
  //Wire.begin();
  Serial.begin(38400);
  // SPI.begin();                                               // initialize SPI
  printf_begin();

  radio.begin();                                             // initialize radio module
  radio.setDataRate(RF24_250KBPS);
  radio.printDetails();
  Serial.print(F("Version "));
  Serial.println(vers);
  network.begin(/*channel*/ 110, /*node address*/ this_node); // start network

  data.num_sent = 7777;                                // num_sent starts from 7777
  data.control = 0;                                    // control starts from 0
  counter = 0;                                         // reset counter

  /*
    //variabili mitutoyo
    pinMode(req, OUTPUT);         // setta il pin 11 come OUTPUT
    pinMode(clk, INPUT_PULLUP);   // setta il pin 7 come Input abilitando la resistenza di pullup
    pinMode(dat, INPUT_PULLUP);   // setta il pin 5 come input abilitando la resistenza di pullup
    digitalWrite(req, LOW);       // porta a LOW il pin 11
    //variabili mitutoyo
  */


  /* parte display i2c */
  // lcd.begin(20,4);
  // lcd.setBacklight(LOW);
  lcd.init();                      // liquid
  lcd.backlight();                  //liquid
  lcd.setCursor(0, 0);
  lcd.print("     Fuel Pump     ");
  lcd.setCursor(0, 1);
  lcd.print("   Timing Checker   ");
  lcd.setCursor(7, 2);
  lcd.print(vers);
  delay(3000);
  //  lcd.clear();



  /*
    byte bypass = digitalRead(button_D);   // per attivare il doppio menu

    if (bypass == HIGH) {   //se clicco il 4 pulsante parto in modalità testbench, altrimenti parte in modalità montaggio
    AA = 1;
    //write_lcdBG_AA();

    } else {
    AA = 0;
    //   write_lcdBG_bench();
    }
  */
  Engine_setup();
  calcolo_array(); // calcola gli array min e max
  //Serial.end();
}



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////     LOOP     ////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


void loop() {


  ////// // if (AA == 0) banchetto();
  ////// // if (AA == 1) { // CONFIGURAZIONE sul motore
  ////// // mostra_array();
  mostra_q();
  read_sensor();            // legge sensore pressione onboard
  read_serialmonitor();     //legge la seriale (per azzeramenti debug)
  pulsanti_AA();
  condition_for_offset();

  network.update();           // looking for news on the network
  // delay(5);                   // needed at least 1 ms of delay or display stay in NOT CONN state (i don't know why ...
   delay(7);                   // needed at least 1 ms of delay or display stay in NOT CONN state (i don't know why ...

  While_network();  // receive data from encoder, if needed start offset routine and drawing background

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

  if (digitalRead(button_A) == LOW) {
    firing_order();
  }

  //  write_pressure();
  //  }  // uso co doppio boot


}

/*
  //////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////


  /*
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
*/

/*
  void read_slave() {  //legge il comapratore collegato sul secondo arduino
  Wire.requestFrom(2, 2); //richiede 2 Bytes dall'arduino SLAVE 2
  f0 = Wire.read();
  f1 = Wire.read();
  num2 = ((f1 << 8) | f0);
  }
*/



void read_serialmonitor() {  // legge i comandi da seriale più per debug che altro
  tasto = Serial.read();
  switch (tasto) {
    case '1':
      radio.printDetails();
      break;
    case '3':
      Serial.println(payload.OffsetReq);
      Serial.println(payload.VO );
      Serial.println(y );
      Serial.println("///////////////////////////////////////////////////////////////////////////");
      break;
    case 'c':
      lcd.clear();
      break;
    case 'b':
      write_lcdBG_AA();
      break;
    case 'r':
      read_sensor();
      break;
    case 'f':
      firing_order();
      break;


  }
}

/*void write_serial() {
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
*/
/*
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
*/

void write_pressure() {     // scrive i dati della pressione

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
    lcd.print(F("       "));
    lcd.setCursor(12, 1);
    lcd.print(PT);
  }
}
/*
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
*/



void pulsanti_AA() {
  if (digitalRead(button_C) == LOW) {          // se premuto azzera il valore di PT (target)
    PT = 0;
    PTprec = 0;
    PM = 0;
    PressioneBar = 0;
    Serial.println(F("PULSANTE UP"));
  }
}

/*
  void pulsanti_bench() {

  if (digitalRead(button_A) == LOW) {          // se premuto azzera il valore di inj
    lcd.setCursor(4, 1);
    lcd.print("     ");
    off = -num;
    Serial.println("PULSANTE DOWN");
  }
  if (digitalRead(button_B) == LOW) {          // se premuto azzera il valore di qty
    lcd.setCursor(4, 2);
    lcd.print("     ");
    off2 = -num2;
    Serial.println("PULSANTE OK");
  }
  if (digitalRead(button_C) == LOW) {          // se premuto azzera il valore di PT (target)
    PT = 0;
    PTprec = 0;
    PM = 0;
    PressioneBar = 0;
    Serial.println("PULSANTE UP");
  }
  }
*/



/*
  void banchetto() {  //CONFIGURAZIONE BANCO

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
*/
