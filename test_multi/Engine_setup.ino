void Engine_setup() {

  while ((engine_setup == 0) || (timing_setup == 0)) {

    //   Serial.print("engine ");
    //   Serial.println(engine);
    //   lcd.setCursor(6, 1);
    //   lista();

    testo_richiesta_inserimento_Engine();           //chiedo numero dell'engine
    while (digitalRead(button_B) == HIGH) {
      readButtonState();  //Lettura stato buttons con controllo antirimbalzo

      if (buttonUpState == HIGH || buttonDownState == HIGH) {
        if ((repeatEnable == HIGH && ((millis() - timerPauseRepeat) > time_pause)) || repeatEnable == LOW) {
          if ((millis() - timerButtonPushed) > time_add_10) {
            if ((millis() - timerButtonPushed) > time_add_100) {
              if (buttonUpState == HIGH) engine = engine + 100;
              if (buttonDownState == HIGH) engine = engine - 100;
            } else {
              byte resto = 0;
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
          Serial.print(F("engine "));
          Serial.println(engine);
          lcd.setCursor(4, 1);
          lista();
        }
      } else {
        timerButtonPushed = millis();
        timerPauseRepeat = millis();
        repeatEnable = LOW;
      }
    }
    if (digitalRead(button_B) == LOW) {
      Serial.println(F("premuto pulsante OK"));
      engine_setup = 1 ;
      delay(200);
      Serial.print(F("engine setup "));
      Serial.println(engine_setup);
    }
    testo_richiesta_inserimento_Timing();
    Serial.print(F("timing setup "));
    Serial.println(timing_setup);

    while ((digitalRead(button_B) == HIGH) && timing_setup == 0) {
      readButtonState();  //Lettura stato buttons con controllo antirimbalzo
      if (buttonUpState == HIGH || buttonDownState == HIGH) {
        if ((repeatEnable == HIGH && ((millis() - timerPauseRepeat) > time_pause)) || repeatEnable == LOW) {
          if ((millis() - timerButtonPushed) > time_add_10) {
            if ((millis() - timerButtonPushed) > time_add_100) {
              if (buttonUpState == HIGH) timing = timing + 100;
              if (buttonDownState == HIGH) timing = timing - 100;
            } else {
              byte resto2 = 0;
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
          timing_float = timing2 / 100;
          lcd.setCursor (8, 1);
          lcd.print(timing_float);
          Serial.print(F("timing ="));
          Serial.println(timing_float);
        }
      } else {
        timerButtonPushed = millis();
        timerPauseRepeat = millis();
        repeatEnable = LOW;
      }
    }
    if (digitalRead(button_B) == LOW) {

      timing_setup = 1 ;
      // lcd.clear();
    }
  }

}
