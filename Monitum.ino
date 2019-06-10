const int trykkPlateKunde = 4; //Trykkplate forran kasse kobles her
const int mottakerVibrasjon = 13; //Vibrasjonskablene fra mottakerne kobles her
const int trykkPlateAnsatt = 2; //Trykkplate bak kasse kobles her
const int mottakerKnapp = 12; //Knappene fra mottakerne kobles her

//Lagrer tilstanden fra de forskjellige bryterne
int mkTilstand;
int tpkTilstand;
int tpaTilstand;

//Lagrer tilstand til vibrasjonen
int vibrasjonTilstand; 

//Lagrer sist kjente tilstand fra bryterne
int forrigemkTilstand = LOW;
int forrigetpkTilstand = LOW;
int forrigetpaTilstand = LOW;

//Teller tiden siden bryterne ble trykket
unsigned long mkTid = 0;
unsigned long tpkTid = 0;
unsigned long tpaTid = 0;

unsigned long debounceDelay = 50; //Lager en forsinkelse for å unngå feil klikk

unsigned long trykkPlateKundeDelay = 3000; //Trykkplaten har et større delay

void setup() {
  //Setter opp signalene
  pinMode(trykkPlateKunde, INPUT);
  pinMode(mottakerVibrasjon, OUTPUT);
  pinMode(trykkPlateAnsatt, INPUT);
  pinMode(mottakerKnapp, INPUT);
}

void loop() {
  //Debounce mottakerKnapp

  //Leser tilstanden fra mottakerknappene
  int leseAMKnapp = digitalRead(mottakerKnapp);

  //Hvis bryteren endret, på grunn av støy eller trykk
  if (leseAMKnapp != forrigemkTilstand) {

    //Tilbakestill mottakerknappenes tid
    mkTid = millis();
  }

  //Vil gå videre hvis det har gått lenger tid enn debounce-forsinkelsen
  if ((millis() - mkTid) > debounceDelay) {

    //Hvis tilstanden har endret seg
    if (leseAMKnapp != mkTilstand) {
      mkTilstand = leseAMKnapp;

      //Bare skift vibrasjonens tilstand hvis mottakerKnappen er HIGH
      if (mkTilstand == HIGH) {
        vibrasjonTilstand = LOW;
      }
    }
  }

  //Debounce trykkPlateAnsatt

  //Leser tilstanden fra trykkPlateAnsatt
  int leseTPAKnapp = digitalRead(trykkPlateAnsatt);

  //Hvis bryteren endret, på grunn av støy eller trykk
  if (leseTPAKnapp != forrigetpaTilstand) {

    //Tilbakestill trykkPlateAnsatt tid
    tpaTid = millis();
  }

  //Vil gå videre hvis det har gått lenger tid enn debounce-forsinkelsen
  if ((millis() - tpaTid) > debounceDelay) {

    //Hvis tilstanden har endret seg
    if (leseTPAKnapp != tpaTilstand) {
      tpaTilstand = leseTPAKnapp;

      //Bare skift vibrasjonens tilstand hvis trykkPlateAnsatt er HIGH
      if (tpaTilstand == HIGH ) {
        vibrasjonTilstand = LOW;
      }
    }
  }

  //Debounce trykkPlateKunde

  //Leser tilstanden fra trykkPlateKunde
  int leseTPKnapp = digitalRead(trykkPlateKunde);

  //Hvis bryteren endret, på grunn av støy eller trykk
  if (leseTPKnapp != forrigetpkTilstand) {

    //Tilbakestill trykkPlateKunde tid
    tpkTid = millis();
  }

  //Vil gå videre hvis det har gått lenger tid enn debounce-forsinkelsen
  if ((millis() - tpkTid) > trykkPlateKundeDelay) {

    //Hvis tilstanden har endret seg
    if (leseTPKnapp != tpkTilstand) {
      tpkTilstand = leseTPKnapp;
      
      //Vibrasjonen er på/av basert på om trykkplaten er trykket eller ikke
      vibrasjonTilstand = tpkTilstand;
    }
  }
  //Lagrer lesningen
  forrigemkTilstand = leseAMKnapp;
  forrigetpaTilstand = leseTPAKnapp;
  forrigetpkTilstand = leseTPKnapp;

  //Sett vibrasjonen
  digitalWrite(mottakerVibrasjon, vibrasjonTilstand);
}
