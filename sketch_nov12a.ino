int TrigPin = 17;
int EchoPin = 16;

void setup() {
    pinMode(TrigPin, OUTPUT);
    pinMode(EchoPin, INPUT);
    Serial.begin(9600);
}

void loop() {
    unsigned long distance = ping()/58;
    Serial.print(distance);
    Serial.println("cm");
    delay(100);
}

unsigned long ping() {
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);
    return pulseIn(EchoPin, HIGH);
}
