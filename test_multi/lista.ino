void lista() {
  switch (engine) {

    case 1:
      lcd.print("16V46DF CW   ");
      motore.cylinder = 16;
      motore.fire_spacing = 120;
      motore.cw = 1;
      
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e1[i];
      };
      motore.index = 8;
      break;
    case 2:
      lcd.print("16V46DF CCW  ");
      motore.cylinder = 16;
      motore.fire_spacing = 120;
      motore.cw = 0;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e2[i];
      };
      motore.index = 8;
      break;
    case 3:
      lcd.print("14V46DF CW   ");
      motore.cylinder = 14;
      motore.fire_spacing = 120;
      motore.cw = 1;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e3[i];
      };
      motore.index = 7;
      break;
    case 4:
      lcd.print("14V46DF CCW  ");
      motore.cylinder = 14;
      motore.fire_spacing = 120;
      motore.cw = 0;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e4[i];
      };
      motore.index = 7;
      break;
    case 5:
      lcd.print("12V46DF CW ");
      motore.cylinder = 12;
      motore.fire_spacing = 120;
      motore.cw = 1;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e5[i];
      };
      motore.e[12] = e5[0];
      motore.index = 6;
      break;
    case 6:
      lcd.print("12V46DF CCW");
      motore.cylinder = 12;
      motore.fire_spacing = 120;
      motore.cw = 0;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e6[i];
      };
      motore.index = 6;
      break;
    case 7:
      lcd.print(" 9L46DF CW ");
      motore.cylinder = 9;
      motore.fire_spacing = 80;
      motore.cw = 1;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e7[i];
      };
      motore.index = 9;
      break;
    case 8:
      lcd.print(" 9L46DF CCW");
      motore.cylinder = 9;
      motore.fire_spacing = 80;
      motore.cw = 0;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e8[i];
      };
      motore.index = 9;
      break;
    case 9:
      lcd.print(" 8L46DF CW ");
      motore.cylinder = 8;
      motore.fire_spacing = 90;
      motore.cw = 1;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e9[i];
      };
      motore.index = 8;
      break;
    case 10:
      lcd.print(" 8L46DF CCW");
      motore.cylinder = 8;
      motore.fire_spacing = 90;
      motore.cw = 0;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e10[i];
      };
      motore.index = 8;
      break;
    case 11:
      lcd.print(" 7L46DF CW ");
      motore.cylinder = 7;
      motore.fire_spacing = 0;
      motore.cw = 1;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e11[i];
      };
      motore.index = 7;
      break;
    case 12:
      lcd.print(" 7L46DF CCW");
      motore.cylinder = 7;
      motore.fire_spacing = 0;
      motore.cw = 0;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e12[i];
      };
      motore.index = 7;
      break;
    case 13:
      lcd.print(" 6L46DF CW ");
      motore.cylinder = 6;
      motore.fire_spacing = 120;
      motore.cw = 1 ;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e13[i];
      };
      motore.index = 6;
      break;
    case 14:
      lcd.print(" 6L46DF CCW");
      motore.cylinder = 6;
      motore.fire_spacing = 120;
      motore.cw = 0;
      for (byte i = 0; i < 16; i++) {
        motore.e[i] = e14[i];
      };
      motore.index = 6;
      break;
  };
}
