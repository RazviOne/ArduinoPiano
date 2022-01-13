#include <LiquidCrystal.h>

int notes[] = {262, 294, 330, 349}; // Frequency for C4, D4, E4, F4

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

bool b1;
bool b2;
bool b3;
bool b4;

int button = 0;
int analogVal;
char REC = 0;

int recorded_button[200];
int pev_button;

int recorded_time [200];
char time_index;

char button_index = 0;

unsigned long start_time;
int note_time;

void setup() {

  Serial.begin(9600);
  pinMode (6, INPUT);
  pinMode (5, INPUT_PULLUP);
  pinMode (4, INPUT_PULLUP);
  pinMode (3, INPUT_PULLUP);
  pinMode (2, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.print("Arduino Piano"); //Display a intro message

  delay(2000);
  lcd.clear();
}

void loop() 
{

  while (digitalRead(6) == 0) //Toggle switch for Recording mode
  {
    lcd.setCursor(0, 0); lcd.print("Recording...");
    lcd.setCursor(0, 1);

    Detect_button();
    Play_tone();
  }

 
  while (digitalRead(6) == 1) //Toggle switch for Playing mode
  {
  lcd.clear();
  lcd.setCursor(0, 0);  lcd.print("Now Playing...");

  for (int i = 0; i < sizeof(recorded_button) / 2; i++)
  {
    delay((recorded_time[i]) * 10);

    if (recorded_button[i] == 0)
      noTone(7);
    else
      tone(7, notes[(recorded_button[i] - 1)]);
  }
  }
}

void Detect_button()
{
  b1 = digitalRead(5);
  b2 = digitalRead(4);
  b3 = digitalRead(3);
  b4 = digitalRead(2);

  pev_button = button;

  if(b1 == false)
  {
    button = 1;
  }
  else if(b2 == false)
  {
    button = 2;
  }
  else if(b3 == false)
  {
    button = 3;
  }
  else if(b4 == false)
  {
    button = 4;
  }
  else
  {
    button = 0;
  }

  if (button != pev_button && pev_button != 0)
  {
    recorded_button[button_index] = pev_button; 
    button_index++;
    recorded_button[button_index] = 0;
    button_index++;
  }
}

void Play_tone()
{
  if (button != pev_button)
  {
    lcd.clear();
    note_time = (millis() - start_time) / 10;

    recorded_time[time_index] = note_time;
    time_index++;

    start_time = millis();
  }

  if (button == 0)
  {
    noTone(7);
    lcd.print("0 -> Pause...");
  }

  if (button == 1)
  {
    tone(7, notes[0]);
    lcd.print("1 -> NOTE_C4");
  }

  if (button == 2)
  {
    tone(7, notes[1]);
    lcd.print("2 -> NOTE_D4");
  }

  if (button == 3)
  {
    tone(7, notes[2]);
    lcd.print("3 -> NOTE_E4");
  }

  if (button == 4)
  {
    tone(7, notes[3]);
    lcd.print("4 -> NOTE_F4");
  }
}