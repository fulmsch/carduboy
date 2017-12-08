#include "reaktionstester.h"

long startDelay;
long reactionTime;
long helpTime;

void reaktionstester() {
  while(1) {
    start:
    while(digitalRead(A_BUTTON) && digitalRead(B_BUTTON));
    delay(15);
    if(!digitalRead(B_BUTTON)) {
      bPrevState = 0;
      return;
    }
    while(!digitalRead(A_BUTTON));
    delay(15);
  
    lcd.clear();
    lcd.home();
    lcd.print("Achtung...");
  
    startDelay = random(2000, 5000);
    helpTime = millis(); 
    while((millis() - helpTime) < startDelay) {
      if(!digitalRead(A_BUTTON)) {
        lcd.clear();
        lcd.home();
        lcd.print("Nicht schummeln!");
  
        while(!digitalRead(A_BUTTON));
        delay(50);
        goto start;
      }
    }
    lcd.clear();
    lcd.home();
    lcd.print("Los!");
    helpTime = millis();
    while(digitalRead(A_BUTTON));
    reactionTime = millis() - helpTime;
  
    lcd.home();
    lcd.print("Reaktionszeit:");
    lcd.setCursor(0,1);
    lcd.print(reactionTime);
    lcd.print(" ms");
  
    while(!digitalRead(A_BUTTON));
    delay(50);
  }
}

