/*
   arduino library for gy-25 module:
   https://github.com/Ni3nayka/BTS7960_PRO

   author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
   write:  July 2024
   modify: July 2024

   links:
   https://arduinoplus.ru/74hc595-arduino/
*/  

#pragma once

#define QUANTITY_MOTORS 4

#define LATCH_PIN 7
#define CLOCK_PIN 4
#define DATA_PIN  2

class BTS7960_PRO {
  public:
    int speed[QUANTITY_MOTORS];
    bool block[QUANTITY_MOTORS];
    void setup() {
      pinMode(LATCH_PIN, OUTPUT);
      pinMode(DATA_PIN, OUTPUT);
      pinMode(CLOCK_PIN, OUTPUT);
      for (int i = 0; i<QUANTITY_MOTORS; i++) {
        BTS7960_PRO::speed[i] = 0;
        BTS7960_PRO::block[i] = 0;
      }
    }
    void run(int number, int speed=0, bool block=0) {
      if (number<1 || number>QUANTITY_MOTORS) return;
      BTS7960_PRO::speed[number-1] = speed;
      BTS7960_PRO::block[number-1] = block;
      BTS7960_PRO::update();
    }
    void update() { // full
      // bitSet(direction, currentLED);
      int direction = 0;
      for (int i = 0; i<QUANTITY_MOTORS; i++) {
        int a = 0;
        if (BTS7960_PRO::block[i]) a = 3;
        else if (BTS7960_PRO::speed[i]>0) a = 1;
        else if (BTS7960_PRO::speed[i]<0) a = 2;
        direction = direction<<2 + a;
      }
      digitalWrite(LATCH_PIN, LOW);
      shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, direction);
      digitalWrite(LATCH_PIN, HIGH);
      
    }
  private:
};