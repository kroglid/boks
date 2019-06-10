const int trykkPlate = 4;
const int vibrasjonsMotor = 13;
const int ansattKasse = 2;
const int ansattMobile = 12;

int amStatus;
int tpStatus;
int akStatus;
int forrigeAMStatus = LOW;
int forrigeTPStatus = LOW;
int forrigeAKStatus = LOW;
unsigned long amTid = 0;
unsigned long tpTid = 0;
unsigned long akTid = 0;
unsigned long vmTid = 0;

int vibrasjonsStatus = LOW;
int vibrasjonsVeksling = LOW;

int vibrasjonsInterval = 500;

unsigned long debounceDelay = 50;

unsigned long trykkPlateDelay = 3000;

void setup() {
  pinMode(trykkPlate, INPUT);
  pinMode(vibrasjonsMotor, OUTPUT);
  pinMode(ansattKasse, INPUT);
  pinMode(ansattMobile, INPUT);

  Serial.begin(9600);
}

void ansattKnapper(){
  
}

void loop() {
  //ansattMobile knapp
  int leseAMKnapp = digitalRead(ansattMobile);
  
  if (leseAMKnapp != forrigeAMStatus) {
    amTid = millis();
  }
  
  if ((millis() - amTid) > debounceDelay) {
    if (leseAMKnapp != amStatus) {
      amStatus = leseAMKnapp;
      if (amStatus == HIGH) {
        Serial.println("AnsattMobile har blitt klikket");
        //vibrasjonsStatus == LOW;
        digitalWrite(vibrasjonsMotor, LOW);
      }
    }
  }
  
  forrigeAMStatus = leseAMKnapp;

  //AnsattKasse knapp
  int leseAKKnapp = digitalRead(ansattKasse);
  
  if (leseAKKnapp != forrigeAKStatus) {
    akTid = millis();
  }
  
  if ((millis() - akTid) > debounceDelay) {
    if (leseAKKnapp != akStatus) {
      akStatus = leseAKKnapp;
      if (akStatus == HIGH ) {
        Serial.println("AnsattKasse har blitt klikket");
        //vibrasjonsStatus == LOW;
        digitalWrite(vibrasjonsMotor, LOW);
      }
    }
  }
  
  forrigeAKStatus = leseAKKnapp;

  //trykkPlate knapp
  int leseTPKnapp = digitalRead(trykkPlate);
  
  if (leseTPKnapp != forrigeTPStatus) {
    tpTid = millis();
  }
  
  if ((millis() - tpTid) > trykkPlateDelay) {
    if (leseTPKnapp != tpStatus) {
      tpStatus = leseTPKnapp;
      Serial.println("Trykkplate har blitt klikket");
      digitalWrite(vibrasjonsMotor, tpStatus);
      /*/vibrasjonsVeksling = tpStatus;
      if (!tpStatus){
        vibrasjonsVeksling = LOW;
        digitalWrite(vibrasjonsMotor, LOW);
      }/*/
    }
  }
  
  forrigeTPStatus = leseTPKnapp;

  //Vibrasjon
  /*/if (vibrasjonsVeksling){
    if (millis() - vmTid >= vibrasjonsInterval) {
      // save the last time you blinked the LED
      vmTid = millis();
  
      // if the LED is off turn it on and vice-versa:
      vibrasjonsStatus = !vibrasjonsStatus;
  
      // set the LED with the ledState of the variable:
      digitalWrite(vibrasjonsMotor, vibrasjonsStatus);
    }
  }/*/
}
