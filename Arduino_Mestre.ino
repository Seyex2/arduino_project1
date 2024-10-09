const int BUTTON_MESTRE = 7;
int num_aleatorio = 0;
int BUTTON_MESTRE_lastState = 0;
int value_byte = 0;

int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_MESTRE, INPUT_PULLUP);
  for (int i = 8; i <= 12; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  randomSeed(analogRead(0));
  delay(1000);
}

void loop() {
  int BUTTON_MESTRE_State = !digitalRead(BUTTON_MESTRE);

  if (BUTTON_MESTRE_State != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (BUTTON_MESTRE_State != buttonState) {
      buttonState = BUTTON_MESTRE_State;

      if (buttonState == HIGH) {
        int num_shift = 0;

        if (BUTTON_MESTRE_lastState != BUTTON_MESTRE_State) {
          if (BUTTON_MESTRE_State == 1) {
            num_aleatorio = random(0, 32);
          }

          for (int i = 8; i <= 12; i++) {
            digitalWrite(i, (num_aleatorio >> num_shift) & 1);
            num_shift = num_shift + 1;
          }

          Serial.println(num_aleatorio);
          Serial.write('S');
          Serial.println();
        }
      }
    }
  }
  lastButtonState = BUTTON_MESTRE_State;

  if (Serial.available() > 0) {
    value_byte = Serial.read();
    Serial.println(value_byte);

    int num_secundario = (int) value_byte;
//Yes
    if (num_secundario == num_aleatorio) {
      Serial.println('Y');
        delay(1000);
  
        for (int i = 8; i <= 12; i++) {
          digitalWrite(i, HIGH);
        }
//NO
    } else {
        Serial.println('N');
    }

  }
}