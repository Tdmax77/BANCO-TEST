void mostra_q() {


  /* binA e binB sono gli intervalli di cambio dell'indice del vettore per visualizzare la label col cilindro
      nominalA e nominalB sono i timing
  */
  // Serial.print(F("funzioneA "));
  // auto a = map (angolo in centesimi, mezzo firespace centesimi - timing float centesimi
  auto binA = map(angprint, (motore.fire_spacing) / 2.0 - (motore.fire_spacing) - timing2, 72000 + (motore.fire_spacing ) / 2.0 + (motore.fire_spacing )  - timing2, 1, motore.index + 1 + 2);
  // +1 perchè devo farne uno piu dei cilindri, inoltre ne aggiungo 2 per aver lintevallo negativo prima dello zero
  Serial.println(binA);
  Serial.print("firespacing =  ");
  Serial.println(motore.fire_spacing );
  Serial.print("timing2 ");
  Serial.println(timing2);
  Serial.print("delta ");
  Serial.println(motore.delta);


  // Serial.print("funzioneB ");
  auto binB = map(angprint, (motore.delta) + (motore.fire_spacing) / 2.0 - (motore.fire_spacing) - timing2 , (motore.delta) + 72000 + (motore.fire_spacing) / 2.0 + (motore.fire_spacing) - timing2, 1, motore.index + 1 + 2);

  // Serial.println(binB);
  //  auto nominalA = -motore.fire_spacing + motore.fire_spacing * binA - timing/100 ;
  float nominalA = ((-motore.fire_spacing + motore.fire_spacing * binA - timing2)/100) ;
  float nominalB = ((-motore.fire_spacing + motore.delta + motore.fire_spacing * binB - timing2)/100) ;
  Serial.print("nominal A= ");
  Serial.println(nominalA);
  Serial.print("nominal B= ");
  Serial.println(nominalB);
  // Serial.println(nominalA);

  float gino = 0.0;
  if (abs(nominalA - angstamp) < range) {                                     // se A è nel range stampa
    //   Serial.print("QUESTO LO STAMPO A ");
    //   Serial.println(motore.e[2 * (binA - 1)]);
    lcd.setCursor(12, 2);
    lcd.print(motore.e[2 * (binA - 1)]);
    gino = (angstamp - nominalA);
    if (gino < 0) {
      lcd.setCursor(15, 2);
      lcd.print(gino);
    } else {
      lcd.setCursor(15, 2);
      lcd.print(" ");
      lcd.setCursor(16, 2);
      lcd.print(gino);
    }


  } else if ((abs(nominalB - angstamp) < range) && (motore.cylinder > 10)) {  //se B è nel range ed ho un V (cyl > 10) stampa
    //   Serial.print("QUESTO LO STAMPO B ");
    //   Serial.println(motore.e[2 * (binB - 1) + 1]);
    lcd.setCursor(12, 2);
    lcd.print(motore.e[2 * (binB - 1) + 1]);
    gino = (angstamp - nominalB);
    if (gino < 0) {
      lcd.setCursor(15, 2);
      lcd.print(gino);
    } else {
      lcd.setCursor(15, 2);
      lcd.print(" ");
      lcd.setCursor(16, 2);
      lcd.print(gino);
    }
  }  else {                                                                    // se non è nella condizione di visualizazione pulisce lo schermo
    lcd.setCursor(12, 2);
    lcd.print("         ");
  }



}
