//Esta eh a primeira versao deste programa. Eh apenas um protótipo que controla um LED
//A versao definitiva deve usar um mostrador "LED&KEY TM1638"
//
//
//https://www.tinkercad.com/things/1jkNSMmVrc6/editel?returnTo=%2Fdashboard

const int pinLed = 8;
const int pinButtonSet = 2; // Botão para iniciar/cancelar o temporizador
const int pinButtonInc = 3; // Botão para aumentar o tempo
const int pinButtonDec = 4; // Botão para diminuir o tempo

unsigned long previousMillis = 0; // Para medir intervalos de tempo
int countdownTime = 10; // Tempo inicial em segundos
int remainingTime = countdownTime; // Tempo restante
bool isTiming = false; // Flag para controlar o temporizador

void ligaLed() {
  digitalWrite(pinLed, HIGH);
}

void desligaLed() {
  digitalWrite(pinLed, LOW);
}

void aumetaTempo() {
  remainingTime++; // Aumenta o tempo em 1 segundo
  countdownTime++;
  Serial.print("Tempo ajustado para: ");
  Serial.print(remainingTime);
  Serial.println(" segundos");
}

void diminuiTempo() {
  if (remainingTime > 1) { // Garante que o tempo não seja negativo
    remainingTime--;
    countdownTime--;
    Serial.print("Tempo ajustado para: ");
    Serial.print(remainingTime);
    Serial.println(" segundos");
  }
}

void timerStart() {
  if (!isTiming) {
    isTiming = true;
    remainingTime = countdownTime; // Reseta o tempo restante
    previousMillis = millis(); // Marca o momento inicial
    Serial.println("Temporizador iniciado!");
    ligaLed(); // Liga o LED quando o temporizador começa
  }
}

void timerCancel() {
  if (isTiming) {
    isTiming = false; // Cancela o temporizador
    desligaLed(); // Desliga o LED
    Serial.println("Temporizador cancelado!");
  }
}

void timerUpdate() {
  if (isTiming) {
    unsigned long currentMillis = millis();
    
    
    
    // Verifica se 1 segundo passou
    if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis; // Atualiza o último tempo
      remainingTime--; // Decrementa o tempo restante

      Serial.print("Tempo restante: ");
      Serial.print(remainingTime);
      Serial.println(" segundos");

      if (remainingTime <= 0) {
        isTiming = false; // Finaliza o temporizador
        desligaLed(); // Desliga o LED
        Serial.println("Temporizador finalizado!");
      }
    }
  }
}

void checkButtons() {
  // Botão de iniciar/cancelar
  if (digitalRead(pinButtonSet) == LOW) {
    delay(200); // Debounce
    if (isTiming) {
      timerCancel();
    } else {
      timerStart();
    }
  }

  // Botão de aumentar tempo
  if (digitalRead(pinButtonInc) == LOW) {
    delay(200); // Debounce
    aumetaTempo();
  }

  // Botão de diminuir tempo
  if (digitalRead(pinButtonDec) == LOW) {
    delay(200); // Debounce
    diminuiTempo();
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);
  pinMode(pinButtonSet, INPUT_PULLUP);
  pinMode(pinButtonInc, INPUT_PULLUP);
  pinMode(pinButtonDec, INPUT_PULLUP);
  desligaLed();
}

void loop() {
  checkButtons(); // Verifica os botões
  timerUpdate();  // Atualiza o temporizador
}
