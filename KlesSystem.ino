const int trykkPlateKunde = 4;
const int mottakerVibrasjon = 13;
const int trykkPlateAnsatt = 2;
const int mottakerKnapp = 12;

int mkStatus;
int tpkStatus;
int tpaStatus;
int forrigemkStatus = LOW;
int forrigetpkStatus = LOW;
int forrigetpaStatus = LOW;
unsigned long mkTid = 0;
unsigned long tpkTid = 0;
unsigned long tpaTid = 0;
unsigned long vmTid = 0;

int vibrasjonsStatus = LOW;
int vibrasjonsVeksling = LOW;

int vibrasjonsInterval = 500;

unsigned long debounceDelay = 50;

unsigned long trykkPlateKundeDelay = 3000;

void setup() {
  pinMode(trykkPlateKunde, INPUT);
  pinMode(mottakerVibrasjon, OUTPUT);
  pinMode(trykkPlateAnsatt, INPUT);
  pinMode(mottakerKnapp, INPUT);

  Serial.begin(9600);
}

void loop() {
  //Debounce mottakerKnapp
  int leseAMKnapp = digitalRead(mottakerKnapp);
  
  if (leseAMKnapp != forrigemkStatus) {
    mkTid = millis();
  }
  
  if ((millis() - mkTid) > debounceDelay) {
    if (leseAMKnapp != mkStatus) {
      mkStatus = leseAMKnapp;
      if (mkStatus == HIGH) {
        digitalWrite(mottakerVibrasjon, LOW);
      }
    }
  }
  
  forrigemkStatus = leseAMKnapp;

  //Debounce trykkPlateAnsatt

  int leseAKKnapp = digitalRead(trykkPlateAnsatt);
  
  if (leseAKKnapp != forrigetpaStatus) {
    tpaTid = millis();
  }
  
  if ((millis() - tpaTid) > debounceDelay) {
    if (leseAKKnapp != tpaStatus) {
      tpaStatus = leseAKKnapp;
      if (tpaStatus == HIGH ) {
        digitalWrite(mottakerVibrasjon, LOW);
      }
    }
  }
  
  forrigetpaStatus = leseAKKnapp;

  //Debounce trykkPlateKunde
  int leseTPKnapp = digitalRead(trykkPlateKunde);
  
  if (leseTPKnapp != forrigetpkStatus) {
    tpkTid = millis();
  }
  
  if ((millis() - tpkTid) > trykkPlateKundeDelay) {
    if (leseTPKnapp != tpkStatus) {
      tpkStatus = leseTPKnapp;
      digitalWrite(mottakerVibrasjon, tpkStatus);
    }
  }
  
  forrigetpkStatus = leseTPKnapp;
}
