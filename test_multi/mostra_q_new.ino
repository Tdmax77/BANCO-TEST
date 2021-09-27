void mostra_q() {


  /* binA e binB sono gli intervalli di cambio dell'indice del vettore per visualizzare la label col cilindro
      nominalA e nominalB sono i timing
  */
  auto binA = map(/*angprint*/angstamp*100, (motore.fire_spacing) / 2.0 - (motore.fire_spacing) - timing2, 72000 + (motore.fire_spacing ) / 2.0 + (motore.fire_spacing )  - timing2, 1, motore.index + 1 + 2);
  auto binB = map(/*angprint*/angstamp*100, (motore.delta) + (motore.fire_spacing) / 2.0 - (motore.fire_spacing) - timing2 , (motore.delta) + 72000 + (motore.fire_spacing) / 2.0 + (motore.fire_spacing) - timing2, 1, motore.index + 1 + 2);

  
  float nominalA = ((-motore.fire_spacing + motore.fire_spacing * binA - timing2)/100) ;
  float nominalB = ((-motore.fire_spacing + motore.delta + motore.fire_spacing * binB - timing2)/100) ;

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
    lcd.print("        ");
  }



}
