#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define pirPin 2
#define ledPin 3
#define BUZZER_PIN 7
#define echoPin 4
#define trigPin 5

int pirState = LOW;
int val = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void beep(int mode) {
    if (mode == 1) {
        tone(BUZZER_PIN, 600);
    } else {
        noTone(BUZZER_PIN);
    }
}

int calc_distance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    float duree = pulseIn(echoPin, HIGH);
    
    return (duree * 0.034) / 2;
}

void setup() {
    pinMode(pirPin, INPUT);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    
    // variant "A02"

    lcd.setCursor(0, 0);
    lcd.print("Systeme armé...");
    Serial.println("Système prêt. En attente de mouvement...");
}

void loop() {
    val = digitalRead(pirPin);
    float distance = calc_distance();
    
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println("cm");
    if (val == HIGH || distance <= 20) {
        digitalWrite(ledPin, HIGH);
        beep(1);
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
        beep(0);
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
