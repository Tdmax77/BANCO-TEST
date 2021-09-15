void lista() {
  switch (engine) {

    case 1:
      lcd.print("16V46DF CW   ");
      motore.cylinder = 16;
      motore.fire_spacing = 120;
      motore.cw = 1;
 /*     for (byte i = 0; i < 16; i++) {
        motore.e[i] = e1[i];
        motore.h[i] = e1[i]-range;
        motore.l[i] = e1[i]+range;
      };
 */     break;
    case 2:
      lcd.print("16V46DF CCW  ");
      motore.cylinder = 16;
      motore.fire_spacing = 120;
      motore.cw = 0;
/*      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e2[i];
        motore.h[i] = e2[i]-range;
        motore.l[i] = e2[i]+range;
      };
*/      break;
    case 3:
      lcd.print("14V46DF CW   ");
      motore.cylinder = 14;
      motore.fire_spacing = 120;
      motore.cw = 1;
/*      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e3[i];
        motore.h[i] = e3[i]-range;
        motore.l[i] = e3[i]+range;
      };
 */     break;
    case 4:
      lcd.print("14V46DF CCW  ");
      motore.cylinder = 14;
      motore.fire_spacing = 120;
      motore.cw = 0;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e4[i];
        motore.h[i] = e4[i]-range;
        motore.l[i] = e4[i]+range;
      };
      break;
    case 5:
      lcd.print("12V46DF CW ");
      motore.cylinder = 12;
      motore.fire_spacing = 120;
      motore.cw = 1;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e5[i];
        motore.h[i] = e5[i]-range;
        motore.l[i] = e5[i]+range;
      };
      break;
    case 6:
      lcd.print("12V46DF CCW");
      motore.cylinder = 12;
      motore.fire_spacing = 120;
      motore.cw = 0;
/*      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e6[i];
        motore.h[i] = e6[i]-range;
        motore.l[i] = e6[i]+range;
      };
*/      break;
    case 7:
      lcd.print(" 9L46DF CW ");
      motore.cylinder = 9;
      motore.fire_spacing = 80;
      motore.cw = 1;
 /*     for (byte i = 0; i < 16; i++) {
        motore.e[i] = e7[i];
        motore.h[i] = e7[i]-range;
        motore.l[i] = e7[i]+range;
      };
 */     break;
    case 8:
      lcd.print(" 9L46DF CCW");
      motore.cylinder = 9;
      motore.fire_spacing = 80;
      motore.cw = 0;
/*      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e8[i];
        motore.h[i] = e8[i]-range;
        motore.l[i] = e8[i]+range;
      };
 */     break;
    case 9:
      lcd.print(" 8L46DF CW ");
      motore.cylinder = 8;
      motore.fire_spacing = 90;
      motore.cw = 1;
 /*    for (byte i = 0; i < 16; i++) {
        motore.e[i] = e9[i];
        motore.h[i] = e9[i]-range;
        motore.l[i] = e9[i]+range;
      };
 */     break;
    case 10:
      lcd.print(" 8L46DF CCW");
      motore.cylinder = 8;
      motore.fire_spacing = 90;
      motore.cw = 0;
 /*    for (byte i = 0; i < 16; i++) {
        motore.e[i] = e10[i];
        motore.h[i] = e10[i]-range;
        motore.l[i] = e10[i]+range;
      };
 */     break;
    case 11:
      lcd.print(" 7L46DF CW ");
      motore.cylinder = 7;
      motore.fire_spacing = 0;
      motore.cw = 1;
/*       for (byte i = 0; i < 16; i++) {
        motore.e[i] = e11[i];
        motore.h[i] = e11[i]-range;
        motore.l[i] = e11[i]+range;
    };
*/     break;
    case 12:
      lcd.print(" 7L46DF CCW");
      motore.cylinder = 7;
      motore.fire_spacing = 0;
      motore.cw = 0;
/*       for (byte i = 0; i < 16; i++) {
        motore.e[i] = e12[i];
        motore.h[i] = e12[i]-range;
        motore.l[i] = e12[i]+range;
      };
 */     break;
    case 13:
      lcd.print(" 6L46DF CW ");
      motore.cylinder = 6;
      motore.fire_spacing = 120;
      motore.cw = 1 ;
 /*      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e13[i];
        motore.h[i] = e13[i]-range;
        motore.l[i] = e13[i]+range;
      };
 */     break;
    case 14:
      lcd.print(" 6L46DF CCW");
      motore.cylinder = 6;
      motore.fire_spacing = 120;
      motore.cw = 0;
 /*      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e14[i];
        motore.h[i] = e14[i]-range;
        motore.l[i] = e14[i]+range;
      };
 */     break;
  };
}
