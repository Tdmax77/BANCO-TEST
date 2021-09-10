#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <RF24Network.h>
#include <RF24.h>
#include <printf.h>

/* variabile display*/
LiquidCrystal_I2C lcd(0x27, 20, 4);
/* variabile display*/

/*Variabili Offset servono ad inserire il valore usando i 3 pulsanti*/
const int button_B = 6;
const int button_C = 5;  //numero pin a cui è collegato il pulsante di UP
const int button_A = 7;  //numero pin a cui è collegato il pulsnte di DOWN
const int button_D = 3;
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


/* variabili per setup motore*/
int engine = 0;  //variabile da aumentare o diminuire come valore            serve per setup motore                   
const int engineMax = 14; //limite massimo valore della variabile
const int engineMin = 1; //limite minimo valore della variabile
byte engine_setup = 0;

int timing = 1800;  //variabile da aumentare o diminuire come valore            serve per setup motore
float timing2 = 0;
const int timingMax = 3000; //limite massimo valore della variabile
const int timingMin = 1000; //limite minimo valore della variabile
float timing_displayed;
/* variabili per setup motore*/




void setup() {

  /*Parte Variabile Offset*/
  pinMode (button_C, INPUT_PULLUP);   //impostazione button_C come ingresso
  pinMode (button_A, INPUT_PULLUP); //impostazione button_A come ingresso
  pinMode (button_B, INPUT_PULLUP);   //impostazione button_B come ingresso
  pinMode (button_D, INPUT_PULLUP);     //impostazione button_D come ingresso
  /*Parte Variabile Offset*/

  Serial.begin(38400);
  printf_begin();
  /* parte display i2c */
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.clear();
  /* parte display i2c */
}

void loop() {

  Engine_setup();
  lcd.setCursor(11, 0);
  lcd.print("tim");
  lcd.setCursor(15, 0);
  lcd.print(timing_displayed);
}

//////////////////
//////////////////
//////////////////


void Engine_setup() {

  while (engine_setup == 0) {
    while (digitalRead(button_B) == HIGH) {
      lcd.setCursor(0, 0);
      lcd.print("Select ENGINE: ");
      lcd.setCursor(0, 3);
      lcd.print("prev  ok  next");

      readButtonState();  //Lettura stato buttons con controllo antirimbalzo

      if (buttonUpState == HIGH || buttonDownState == HIGH) {
        if ((repeatEnable == HIGH && ((millis() - timerPauseRepeat) > time_pause)) || repeatEnable == LOW) {
          if ((millis() - timerButtonPushed) > time_add_10) {
            if ((millis() - timerButtonPushed) > time_add_100) {
              if (buttonUpState == HIGH) engine = engine + 100;
              if (buttonDownState == HIGH) engine = engine - 100;
            } else {
              int resto = 0;
              if (buttonUpState == HIGH) resto = 10 - (engine % 10);
              if (buttonDownState == HIGH) resto = (engine % 10);
              if (resto == 0) {
                if (buttonUpState == HIGH) engine = engine + 10;
                if (buttonDownState == HIGH) engine = engine - 10;
              } else {
                if (buttonUpState == HIGH) engine = engine + resto;
                if (buttonDownState == HIGH) engine = engine - resto;
              }
            }
          } else {
            if (buttonUpState == HIGH) engine++;
            if (buttonDownState == HIGH) engine--;
          }
          timerPauseRepeat = millis();
          repeatEnable = HIGH;
          if (engine > engineMax) engine = engineMax;
          if (engine < engineMin) engine = engineMin;
          Serial.print("engine ");
          Serial.println(engine);
          lcd.setCursor(6, 1);
          lista();
        }
      } else {
        timerButtonPushed = millis();
        timerPauseRepeat = millis();
        repeatEnable = LOW;
      }
    }
    if (digitalRead(button_B) == LOW) {
      Serial.println("premuto pulsante OK");
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("insert Timing: ");
    lcd.setCursor(0, 3);
    lcd.print("prev  ok  next");
    while (digitalRead(button_B) == HIGH) {


      readButtonState();  //Lettura stato buttons con controllo antirimbalzo

      if (buttonUpState == HIGH || buttonDownState == HIGH) {
        if ((repeatEnable == HIGH && ((millis() - timerPauseRepeat) > time_pause)) || repeatEnable == LOW) {
          if ((millis() - timerButtonPushed) > time_add_10) {
            if ((millis() - timerButtonPushed) > time_add_100) {
              if (buttonUpState == HIGH) timing = timing + 100;
              if (buttonDownState == HIGH) timing = timing - 100;
            } else {
              int resto2 = 0;
              if (buttonUpState == HIGH) resto2 = 10 - (timing % 10);
              if (buttonDownState == HIGH) resto2 = (timing % 10);
              if (resto2 == 0) {
                if (buttonUpState == HIGH) timing = timing + 10;
                if (buttonDownState == HIGH) timing = timing - 10;
              } else {
                if (buttonUpState == HIGH) timing = timing + resto2;
                if (buttonDownState == HIGH) timing = timing - resto2;
              }
            }
          } else {
            if (buttonUpState == HIGH) timing++;
            if (buttonDownState == HIGH) timing--;
          }
          timerPauseRepeat = millis();
          repeatEnable = HIGH;
          if (timing > timingMax) timing = timingMax;
          if (timing < timingMin) timing = timingMin;
          timing2 = timing;
          timing_displayed = timing2 / 100;
          lcd.setCursor (4, 1);
          lcd.print(timing_displayed);
          Serial.print("timing =");
          Serial.println(timing_displayed);
          lcd.setCursor(4, 1);
        }
      } else {
        timerButtonPushed = millis();
        timerPauseRepeat = millis();
        repeatEnable = LOW;
      }
    }
    if (digitalRead(button_B) == LOW) {
      engine_setup = 1 ;
      Serial.print("engine setup ");
      Serial.println(engine_setup);
      lcd.clear();
    }
  }

  lcd.setCursor(0, 0);
  lista();
}

void readButtonState() {

  int readingUp = digitalRead(button_C); //Lettura ingresso digitale del pulsante di UP
  int readingDown = digitalRead(button_A); //Lettura ingresso digitale del pulsante di Down

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

void lista() {
  switch (engine) {
    case 1:
      lcd.print("16V46DF CW   ");
      break;
    case 2:
      lcd.print("16V46DF CCW  ");
      break;
    case 3:
      lcd.print("14V46DF CW   ");
      break;
    case 4:
      lcd.print("14V46DF CCW  ");
      break;
    case 5:
      lcd.print("12V46DF CW ");
      break;
    case 6:
      lcd.print("12V46DF CCW");
      break;
    case 7:
      lcd.print(" 9L46DF CW ");
      break;
    case 8:
      lcd.print(" 9L46DF CCW");
      break;
    case 9:
      lcd.print(" 8L46DF CW ");
      break;
    case 10:
      lcd.print(" 8L46DF CCW");
      break;
    case 11:
      lcd.print(" 7L46DF CW ");
      break;
    case 12:
      lcd.print(" 7L46DF CCW");
      break;
    case 13:
      lcd.print(" 6L46DF CW ");
      break;
    case 14:
      lcd.print(" 6L46DF CCW");
      break;
  }
}
