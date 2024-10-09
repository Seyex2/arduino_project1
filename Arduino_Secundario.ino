int TENTATIVA_BUTTON = 6, INCREMENTO_BUTTON = 7;
bool jogo;
char valueByte = 0;
byte num_secundario = 0b0;
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 20;

void setup() {
  Serial.begin(9600);
  jogo = false;

  pinMode(INCREMENTO_BUTTON, INPUT_PULLUP);
  pinMode(TENTATIVA_BUTTON, INPUT_PULLUP);

  for (int i = 8; i <= 12; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
}

void piscar (int num) {
  
  for (int j = 0; j < num; j++) {
    delay(300);
    for (int i = 8; i <= 12; i++) {
      digitalWrite(i, HIGH); 
    }
    delay(300);
    for (int i = 8; i <= 12; i++) {
      digitalWrite(i, LOW); 
    }
  }
}

void loop() {

  if (jogo==false && Serial.available() > 0) {
    valueByte = Serial.read();
    if (valueByte == 'S') {
      jogo = true;
      delay(300);
       for (int i = 8; i <= 12; i++) {
      digitalWrite(i, LOW); 
    }
      piscar(3);
  
    } 
  }

  if (jogo) {
    int estado_botao1 = !digitalRead(TENTATIVA_BUTTON);
    int estado_botao2 = !digitalRead(INCREMENTO_BUTTON);

    if (estado_botao1 != lastButtonState) {
      lastDebounceTime = millis();
    }

    if (estado_botao1 != lastButtonState) {
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {


    int INCREMENTO_BUTTONState = digitalRead(INCREMENTO_BUTTON);
    if (INCREMENTO_BUTTONState == LOW) {
      num_secundario++;
      for (int i = 8; i <= 12; i++) {
        digitalWrite(i, (num_secundario >> (i - 8)) & 1);
      }
      delay(300);
    }


    int TENTATIVA_BUTTONState = digitalRead(TENTATIVA_BUTTON);
    if (TENTATIVA_BUTTONState == LOW) {
      Serial.write(num_secundario);
      delay(100);
    }



 //NO
    if (Serial.available() > 0) {
      valueByte = Serial.read();
      if (valueByte == 'N') {
        num_secundario = 0b0;
        //Desligar luzes
        for (int i = 8; i <= 12; i++) {
          digitalWrite(i, LOW);
        }
        
//YES
      } else if (valueByte == 'Y') {
        //Ligar luzes
        for (int i = 8; i <= 12; i++) {
          digitalWrite(i, HIGH);
        }
        jogo = false;
      }
      //restart
      else if(valueByte == 'S'){
        jogo = true;
        num_secundario = 0b0;
        piscar(3);
        delay(300);

      }
}
}
}
}