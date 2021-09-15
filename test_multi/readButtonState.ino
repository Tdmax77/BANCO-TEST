void readButtonState() {

  byte readingUp = digitalRead(button_C); //Lettura ingresso digitale del pulsante di UP
  byte readingDown = digitalRead(button_A); //Lettura ingresso digitale del pulsante di Down

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
