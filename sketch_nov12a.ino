int TrigPin = 17;
int EchoPin = 16;
int greenLED = 4;    // 綠色LED接在P4
int redLED = 0;      // 紅色LED接在P0

// 定義距離範圍
const int MIN_DISTANCE = 5;    // 最小距離 5cm
const int MAX_DISTANCE = 100;  // 最大距離 100cm

void setup() {
    pinMode(TrigPin, OUTPUT);
    pinMode(EchoPin, INPUT);
    pinMode(greenLED, OUTPUT);
    pinMode(redLED, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    unsigned long distance = ping()/58;
    Serial.print(distance);
    Serial.println("cm");
    
    // 將距離轉換為LED亮度
    int redBrightness = map(distance, MIN_DISTANCE, MAX_DISTANCE, 255, 0);
    int greenBrightness = map(distance, MIN_DISTANCE, MAX_DISTANCE, 0, 255);
    
    // 確保亮度值在有效範圍內
    redBrightness = constrain(redBrightness, 0, 255);
    greenBrightness = constrain(greenBrightness, 0, 255);
    
    // 輸出LED亮度
    analogWrite(redLED, redBrightness);
    analogWrite(greenLED, greenBrightness);
    
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
