### DoOogFit la collier et l'application nouvel génération pour votre TouTou ##

- Permettra à son propriétaire d’obtenir de précieuses informations en ce qui concerne la santé de son animal à quatre pattes.

- Mouvements, rythme cardiaque et respiratoire, niveau d’activité physique, temps de sommeil, dépenses énergétiques, détente relaxation.

- Synchronisation bluetooth, wifi à l'application mobile DogFit
- Collecte les données
- Conseils de santé, nutrition, suivi vétérinaire, calendrier pour le suivi des vaccins.
- un accéléromètre tri-axial, d’une radio basse fréquence, traceur, pulsion éducatif (anti aboiement), vibration caresse pour se détendre
- Le collier : matière, étanche, résistant, batterie rechargeable tout les 7jours durant 45min, 1h, 

- le produit : une mini trousse avec le collier, le manuel d'utilisation, clé allen, dragonne, cable, adaptateur. 

## 1.  Le COLLIER

![collier](https://user-images.githubusercontent.com/37441518/85844797-9d031a80-b7a3-11ea-8f35-d7946d3c39d0.JPG)

## 2. Caractéristique  :

- Interrupteur marche/arrêt pour allonger l'autonomie de la batterie

- Indicateur de batterie faible.

- Résistant et étanche jusqu'à 10m de profondeur

- Arrêt de sécurité automatique : la stimulation cesse au bout de 80 secondes

- Capteurs de sons et vibrations Perfect Bark™ : seuls les aboiements de votre chien provoquent la stimulation, ainsi le stress qui peut resentir.

## - L'APPLICATION  **Do0ogFit**

- Voici 3 images exemples de l'application qui sera créée :  
<img src="https://github.com/mbelala/IOT/blob/master/application/accueil.PNG" width="250" /><img src="https://github.com/mbelala/IOT/blob/master/application/histo_repas.PNG" width="250" /><img src="https://github.com/mbelala/IOT/blob/master/application/rassurer_mon_chien.PNG" width="250" />



## 3.  Tinkercad

Lien du Tinkercad: https://www.tinkercad.com/things/04eStbwhBkL-swanky-waasa/editel?sharecode=ME6cqpK3tBEvkP4woR5JJM26MQwJbvO6z_dlUD_uqwU

<img src="https://github.com/mbelala/IOT/blob/master/images/Trinker_on.png"/>

**Liste des composants :**  
- Accéléromètre et gyroscope : nécessaire pour détecter les mouvements et suivi du sommeil.  
- Capteur pulsation du coeur (<a href="https://www.amazon.fr/ICQUANZX-capteur-dimpulsions-Cardiaque-fr%C3%A9quence/dp/B07VJ9XB7T/">Lien exemple</a>)  
- Puce GPS (<a href="https://www.amazon.fr/AZDelivery-NEO-6M-module-GPS-identique/dp/B01N38EMBF/">Lien exemple</a>): nécessaire pour relever la position du chien  
- Capteur de températeur (**TMP36** sur Tinkercad) : Relève la température du chien  
- Capteur RFID (<a href"https://www.amazon.fr/Kongnijiwa-S%C3%A9rie-522-Porte-cl%C3%A9s-Compatible-Raspberry/dp/B07JFSL42L/">lien exemple</a>)  
- Outil générateur de pulsation éléctrique à faire maison pour envoyer des légers court-circuit au chien : Permet de dresser ou corriger le chien  
- Moteur vibration (**Vibration motor** sur Tinkercad) : Envoie des vibration afin de calmer le chien  

Code commenté sur le Tinketcad :  
```
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
// adresse du Vibreur (PIN) 
int vibreur = 12;
// seuil de température fixer
int baselineTemp = 40;
//initialisation de variables
int celsius = 0;
String demande = "";
// adresse du capteur de gaz (PIN) 
int detecteur = A2;
// seuil de gaz dans l'air fixer
int niveau_senseur = 250;
// adresse du led rouge (PIN) 
int pin_led_rouge = 7;
bool gaz = false;
// adresse du lcd (PIN) 
LiquidCrystal lcd(10, 9, 8, 6, 5, 3);

void setup() {
// Initialisation des composants  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(Bp1, INPUT);
  digitalWrite(Bp1, HIGH);
  pinMode(detecteur, INPUT);
  pinMode(pin_led_rouge, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(vibreur, OUTPUT);
  
 // taille du serial
  Serial.begin(9600);
  
//initialisation de l'écran LCD et affichage du nom de l'application 
  lcd.begin(20, 2);
  lcd.setCursor(0,0);
  lcd.print("DogFit");
  
}

void loop() {
  
// récupération de la valeur du détécteur
  int valeur_detecteur = analogRead(detecteur);
// Si la présence de gaz est supérieur au seuil fixer (niveau_senceur) on fait clignoter le led rouge et affiche un message sur l'écran LCD
  if (valeur_detecteur >= niveau_senseur) {
    digitalWrite(pin_led_rouge, HIGH);
    lcd.setCursor(0,1);
    lcd.print("Presence de gaz!!!   ");
    lcd.noDisplay();
  	delay(200);
  	lcd.display();
    gaz = true;
    
  } 
  //sinon éteindre la led rouge et effacer le message sur l'écran LED
  else if (valeur_detecteur < niveau_senseur && gaz) {
    digitalWrite(pin_led_rouge, LOW);
    lcd.setCursor(0,1);
    lcd.print("                 ");
    gaz = false;
  }
// Récupération et calcul de la température en C° 
  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);

// si la température est inférieure au seuil fixer à 40 le vibreur ne s'active pas sinon il s'active pour calmer le chien 
  if (celsius < baselineTemp) {
    digitalWrite(vibreur, LOW);
  } else {
    digitalWrite(vibreur, HIGH);
  }

 // Récupération de l'état du bouton
  appui_bp1 = digitalRead(Bp1);
// si le bouton est appuyer on allume le buzzer le temps de la 
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
// commande sur le moniteur série
// vérification qu'une information à été prise en entrée
  if (Serial.available() > 0) {
    
    demande = Serial.readString();
    Serial.print("I received:");
    Serial.println(demande);
 // Action "Temp" affiche la température du chien 

    if (demande == "Temp") {
      lcd.setCursor(0,1);
      lcd.print(celsius);
      lcd.setCursor(2,1);
      lcd.print("C.           ");
    } 
// Action "Loc" envoie la localisation du chien 

    else if (demande == "Loc") {
      lcd.setCursor(0,1);
      lcd.print("Maison            ");
    } 
// Action "Calm" Active le vibreur pour calmer le chien 
    
    else if (demande == "Calm") {
      lcd.setCursor(0,1);
      digitalWrite(vibreur, HIGH);
      delayMicroseconds(demi_periode);
      digitalWrite(vibreur, LOW);
      lcd.print("Nous calmons votre chien");
      
    }
  }
}
```



