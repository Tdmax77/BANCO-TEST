void lista() {
  switch (engine) {

    case 1:
      lcd.print("16V46DF CW   ");           // label che verrà printata
      motore.cylinder = 16;                 // numero cilindri
      motore.fire_spacing = 9000;            // distanza tra gli scoppi
      motore.cw = 1;                        // senso di rotazione
      for (byte i = 0; i < 16; i++) {       // quando scelgo il motore nel setup, copio i dati del vettore nella struct
        motore.e[i] = e1[i];
      };
      motore.e[16] = e1[0];
      motore.index = 8;                     // serve a calcolare binA e binB e corrisponde ai cilinddi per bancata
      motore.delta = 4000;                    // sfasamento tra le bancate

      break;
    case 2:
      lcd.print("16V46DF CCW  ");
      motore.cylinder = 16;
      motore.fire_spacing = 9000;
      motore.cw = 0;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e2[i];
      };
      motore.e[16] = e2[0];
      motore.index = 8;
      motore.delta = 5000;
      break;
    case 3:
      lcd.print("14V46DF CW   ");
      motore.cylinder = 14;
      motore.fire_spacing = 10285;
      motore.cw = 1;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e3[i];
      };
      motore.e[14] = e3[0];
      motore.index = 7;
      motore.delta = 5290; /////////////////////////////////////////////////////////////////
      break;
    case 4:
      lcd.print("14V46DF CCW  ");
      motore.cylinder = 14;
      motore.fire_spacing = 10285;
      motore.cw = 0;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e4[i];
      };
      motore.e[14] = e4[0];
      motore.index = 7;
      motore.delta = 5000; /////////////////////////////////////////////////////////////////
      break;
    case 5:
      lcd.print("12V46DF CW   ");
      motore.cylinder = 12;
      motore.fire_spacing = 12000;
      motore.cw = 1;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e5[i];
      };
      motore.e[12] = e5[0];
      motore.index = 6;
      motore.delta = 5000;  // nel caso del CCW il valore è diverso per via del fatto che gira in senso opposto  quindi 120-50
      break;
    case 6:
      lcd.print("12V46DF CCW  ");
      motore.cylinder = 12;
      motore.fire_spacing = 12000;
      motore.cw = 0;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e6[i];
      };
      motore.e[12] = e6[0];
      motore.index = 6;
      motore.delta = 7000;
      break;
    case 7:
      lcd.print(" 9L46DF CW   ");
      motore.cylinder = 9;
      motore.fire_spacing = 8000;
      motore.cw = 1;
      for (byte i = 0; i < 16; i++) {
        motore.e[2 * i] = e7[i];              // devo mettere i valori del linea solo nelle caselle dispari per far apparire sempre
      };                                      // la lettera A (altrimenti userebbe la mappaB)
      motore.e[18] = e7[0];                   // copio il primo intervallo sull ultimo per gestire i gradi negativi (visto che sono in ciclo 0-720 non ci sono)
      motore.index = 9;
      break;
    case 8:
      lcd.print(" 9L46DF CCW  ");
      motore.cylinder = 9;
      motore.fire_spacing = 8000;
      motore.cw = 0;
      for (byte i = 0; i < 16; i++) {
        motore.e[2 * i] = e8[i];
      };
      motore.e[18] = e8[0];
      motore.index = 9;
      break;
    case 9:
      lcd.print(" 8L46DF CW   ");
      motore.cylinder = 8;
      motore.fire_spacing = 9000;
      motore.cw = 1;
      for (byte i = 0; i < 16; i++) {
        motore.e[2 * i] = e9[i];
      };
      motore.e[16] = e9[0];
      motore.index = 8;
      break;
    case 10:
      lcd.print(" 8L46DF CCW  ");
      motore.cylinder = 8;
      motore.fire_spacing = 9000;
      motore.cw = 0;
      for (byte i = 0; i < 16; i++) {
        motore.e[2 * i] = e10[i];
      };
      motore.e[16] = e10[0];
      motore.index = 8;
      break;
    case 11:
      lcd.print(" 7L46DF CW   ");
      motore.cylinder = 7;
      motore.fire_spacing = 10285;
      motore.cw = 1;
      for (byte i = 0; i < 16; i++) {
        motore.e[2 * i] = e11[i];
      };
      motore.index = 7;
      motore.e[14] = e12[0];
      break;
    case 12:
      lcd.print(" 7L46DF CCW  ");
      motore.cylinder = 7;
      motore.fire_spacing = 10285;
      motore.cw = 0;
      for (byte i = 0; i < 16; i++) {
        motore.e[2 * i] = e12[i];
      };
      motore.e[14] = e12[0];
      motore.index = 7;
      break;
    case 13:
      lcd.print(" 6L46DF CW   ");
      motore.cylinder = 6;
      motore.fire_spacing = 12000;
      motore.cw = 1 ;
      for (byte i = 0; i < 16; i++) {
        motore.e[2 * i] = e13[i];
      };
      motore.e[12] = e13[0];
      motore.index = 6;
      break;
    case 14:
      lcd.print(" 6L46DF CCW  ");
      motore.cylinder = 6;
      motore.fire_spacing = 12000;
      motore.cw = 0;
      for (byte i = 0; i < 16; i++) {
        motore.e[2 * i] = e13[i];
      };
      motore.e[12] = e13[0];
      motore.index = 6;
      break;
  };
}

/*                             LOGICA DI FUNZIONAMENTO :

                   A1   B1     A5   B5    ...  ...     A4   B4     A1
                ...|....|......|....|......|....|......|....|......|...               punto morto
                   0    70    120  190    ...  ...    600  670    720

             |.....1.....|.....2.....|.....*.....|.....12....|.....1.....|             mappa A
            -60          60         120         ...         660         790

                  |.....1.....|.....2.....|.....*.....|.....12....|.....1.....|        mappa B
                 -10          110        ...         590         710         820

   Creo 2 mappe per dividere i 720 gradi in un mumero di intervalli = ai cilindri per bancata +1
   perchè per coprire i gradi prima dello zero su A1 (che non possono essere negativi per via della ciclicità)
   devo far si che un -10 sia interpretato come un 710. Creando un intervallo in più faccio si che il programma usi:
   0°-60°   il primo blocco
   660°- 0° il secondo
   Ogni blocco ha ampiezza uguale alla distanza tra gli scoppi.
   Nell'esempio, un 12 cilindri, corrisponde a 120°).

   Le mappe generate in tal modo, vengono confrontate con l'angolo letto restituendo un numero che sarà
   l'indice di un puntatore che a sua volta andrà a leggere il vettore con il firing order visualizzando l'etichetta
   qualora l'angolo letto rispetti la condizione impostata ovvero che il suo valore si discosti di +- un range (impostato nel setup)
   Questo criterio permette di avere la label solo in prossimità del punto di scoppio perchè discrimina se usare la mappa A o la mappa B

   Esempio: 12 cilindri con un range = +- 2 gradi
    A 68°  sono contemporanemente in mapA = 2  e mapB = 2
    questi 2 puntatori mi restituscono il primo ed il secondo valore del vettore motor.e
    char *e5[] = {"A1","B1","A5","B5","A3","B3","A6","B6","A2","B2","A4","B4"}; // 12V46DF  CW

    siccome l'accensione di A1 avviene a 0°  e di B1 a 70° nessuno dei due è nel range (718°-2° per A1  68°-72° per B1) quindi nessuna label viene visualizzata.

    A 68.5°sono sempre in mapA = 1  e mapB = 2  ma stavolta sono nel range di B1 quindi visualizzerò B1 a schermo.


*/
