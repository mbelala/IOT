#include <LiquidCrystal.h>

// adresse du Buzzer (PIN) 
int BUZZER_PIN = 4;
// adresse du BP1 (bouton poussoir 1) 
int Bp1 = 2;
// variable de l'etat de l'appui sur le BP1
int appui_bp1 = 0;
// variable pour son
float demi_periode = (2.27e-3) * 1000000;
//temps du son en milliseconde
float temps = 500;
//variable de calcul du temps de fonctionnement du buzzer
float duree = 0;
float frequenc = 120;
int vibreur = 12;
int baselineTemp = 40;
int celsius = 0;
String demande = "";
int detecteur = A2;
int niveau_senseur = 250;
int pin_led_rouge = 7;
bool gaz = false;

LiquidCrystal lcd(10, 9, 8, 6, 5, 3);

void setup() {

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(Bp1, INPUT);
  digitalWrite(Bp1, HIGH);
  pinMode(detecteur, INPUT);
  pinMode(pin_led_rouge, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);

  pinMode(vibreur, OUTPUT);

  lcd.begin(20, 2);
  lcd.setCursor(0,0);
  lcd.print("DogFit");
  
}

void loop() {
  

  int valeur_detecteur = analogRead(detecteur);

  if (valeur_detecteur >= niveau_senseur) {
    digitalWrite(pin_led_rouge, HIGH);
    lcd.setCursor(0,1);
    lcd.print("Presence de gaz!!!   ");
    lcd.noDisplay();
  	delay(200);
  	lcd.display();
    gaz = true;
    
  } else if (valeur_detecteur < niveau_senseur && gaz) {
    digitalWrite(pin_led_rouge, LOW);
    lcd.setCursor(0,1);
    lcd.print("                 ");
    gaz = false;
  }

  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);

  if (celsius < baselineTemp) {
    digitalWrite(vibreur, LOW);
  } else {
    digitalWrite(vibreur, HIGH);
  }

  appui_bp1 = digitalRead(Bp1);

  if (appui_bp1 == LOW) {
    duree = 0;
    float frequenc;
    while (duree < temps * 1000) {
      digitalWrite(BUZZER_PIN, HIGH);
      delayMicroseconds(demi_periode);
      digitalWrite(BUZZER_PIN, LOW);
      delayMicroseconds(demi_periode);
      duree = duree + 2 * demi_periode;
    }
  }

  if (Serial.available() > 0) {
    
    demande = Serial.readString();
    Serial.print("I received:");
    Serial.println(demande);

    if (demande == "Temp") {
      lcd.setCursor(0,1);
      lcd.print(celsius);
      lcd.setCursor(2,1);
      lcd.print("C.           ");
    } else if (demande == "Loc") {
      lcd.setCursor(0,1);
      lcd.print("Maison            ");
    } else if (demande == "Calm") {
      lcd.setCursor(0,1);
      digitalWrite(vibreur, HIGH);
      delayMicroseconds(demi_periode);
      digitalWrite(vibreur, LOW);
      lcd.print("Nous calmons votre chien");
      
    }
  }
}