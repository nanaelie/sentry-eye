#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define pirPin 2
#define ledPin 3
#define BUZZER_PIN 7

int pirState = LOW;
int val = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void alerte(int mode) {
    if(mode == 1) {
      tone(BUZZER_PIN, 600);
    }else {
      noTone(BUZZER_PIN);
    }
}

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("System Armed...");
  Serial.println("Système prêt. En attente de mouvement...");
}

void loop() {
  val = digitalRead(pirPin);

  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);
    alerte(1);
    if (pirState == LOW) {
      Serial.println("Mouvement détecté !");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Mouvement detecte!");
      lcd.setCursor(0, 1);
      lcd.print("Zone en alerte!");
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW);
    alerte(0);
    if (pirState == HIGH) {
      Serial.println("Zone sécurisée.");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Aucun Mouvement");
      lcd.setCursor(0, 1);
      lcd.print("Zone securisee");
      pirState = LOW;
    }
  }

  delay(100);
}
