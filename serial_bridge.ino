#define LED_PIN LED_BUILTIN
#define BLINK_DURATION 20

bool ledState = false;
int ledLastBlink = 0;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    Serial2.write(Serial.read());
    blink();
  }

  if (Serial2.available()) {
    Serial.write(Serial2.read());
    blink();
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
