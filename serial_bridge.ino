#define LED_PIN LED_BUILTIN
#define BLINK_DURATION 20

int ledState = false;
int ledLastBlink = 0;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    blink();
    Serial2.write(Serial.read());
  }

  if (Serial2.available()) {
    blink();
    Serial.write(Serial2.read());
  }

  handle_blink();
}

void blink() {
  if (!ledState) {
    ledState = true;
    ledLastBlink = millis();
  }
}

void handle_blink() {
  bool timeElapsed = millis() - ledLastBlink > BLINK_DURATION;

  if (!ledState) return;
  
  if (timeElapsed) {
    digitalWrite(LED_PIN, LOW);
    ledState = false;
  } else  {
    digitalWrite(LED_PIN, HIGH);
  }
}
