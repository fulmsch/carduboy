#include <LiquidCrystal.h>
#include "reaktionstester.h"

#define B_BUTTON 3
#define A_BUTTON 2
#define L_BUTTON 4
#define R_BUTTON 5

#define R_ARROW B01111110


LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

byte menuEbene = 0;
byte menuSpiel = 0;
byte menuCursor = 0;

byte playGame = 0;

const byte menu0Elements = 2;
const char *menu0[menu0Elements] = {"Jumper", "Reaktionstester"};
const byte menu1Elements = 2;
const char *menu1[menu1Elements] = {"Start", "Highscores"};

bool aPrevState = 0;
bool bPrevState = 0;
bool lPrevState = 0;
bool rPrevState = 0;

void setup() {
  pinMode(A_BUTTON, INPUT_PULLUP);
  pinMode(B_BUTTON, INPUT_PULLUP);
  pinMode(L_BUTTON, INPUT_PULLUP);
  pinMode(R_BUTTON, INPUT_PULLUP);
  lcd.begin(20, 4);
  
  drawMenu();

}

void loop() {
  

  if(!digitalRead(A_BUTTON)) {
    if(aPrevState) {
      delay(20);
      if(!digitalRead(A_BUTTON)) {
        switch(menuEbene) {
          case 0:
            menuSpiel = menuCursor;
            menuCursor = 0;
            menuEbene = 1;
            break;
          case 1:
            switch(menuCursor) {
              case 0:
                switch(menuSpiel) {
                  case 0:
                    playGame = 1;
                    break;
                  case 1:
                    playGame = 2;
                    break;
                  break;
                }
                break;
              case 1:
                break;
              break;
            }
          break;
        }
        drawMenu();
        aPrevState = 0;
      }
    }
  }else {
    aPrevState = 1;
  }
  
  if(!digitalRead(B_BUTTON)) {
    if(bPrevState) {
      delay(20);
      if(!digitalRead(B_BUTTON)) {
        if(menuEbene > 0) {
          menuEbene--;
          menuCursor = 0;
        }
        drawMenu();
        bPrevState = 0;
      }
    }
  }else {
    bPrevState = 1;
  }

  
  if(!digitalRead(L_BUTTON)) {
    if(lPrevState) {
      delay(20);
      if(!digitalRead(L_BUTTON)) {
        if(menuCursor > 0) menuCursor--;
        drawMenu();
        lPrevState = 0;
      }
    }
  }else {
    lPrevState = 1;
  }

  if(!digitalRead(R_BUTTON)) {
    if(rPrevState) {
      delay(20);
      if(!digitalRead(R_BUTTON)) {
        switch(menuEbene) {
          case 0:
            if(menuCursor < menu0Elements-1) menuCursor++;
            break;
          case 1:
            if(menuCursor < menu1Elements-1) menuCursor++;
            break;
          break;
        }        
        drawMenu();
        rPrevState = 0;
      }
    }
  }else {
    rPrevState = 1;
  }

  if(playGame) {
    switch(playGame) {
      case 1:
        jumper();
        break;
      case 2:
        reaktionstester();
        break;
      break;
    }
    playGame = 0;
    drawMenu();
  }
  
}

void drawMenu() {
  lcd.clear();
  lcd.setCursor(0, menuCursor + 1);
  lcd.write(R_ARROW);
  switch(menuEbene) {
    case 0:
      lcd.setCursor(0,0);
      lcd.print("Spiel auswaehlen");
      for(byte i = 0; i < menu0Elements; i++) {
        lcd.setCursor(1, i+1);
        lcd.print(menu0[i]);
      }
      break;

    case 1:
      lcd.setCursor(0,0);
      lcd.print(menu0[menuSpiel]);
      for(byte i = 0; i < menu1Elements; i++) {
        lcd.setCursor(1, i+1);
        lcd.print(menu1[i]);
      }
      break;
    break;
  }
}

