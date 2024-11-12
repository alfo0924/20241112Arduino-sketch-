// 定義腳位
int TrigPin = 17;    // 超音波感測器的觸發腳位
int EchoPin = 16;    // 超音波感測器的接收腳位
int greenLED = 4;    // 綠色LED連接到P4腳位
int redLED = 0;      // 紅色LED連接到P0腳位

// 定義測量的距離範圍
const int MIN_DISTANCE = 5;    // 最小測量距離為5公分
const int MAX_DISTANCE = 100;  // 最大測量距離為100公分

// 初始化設定
void setup() {
    pinMode(TrigPin, OUTPUT);    // 設定觸發腳為輸出模式
    pinMode(EchoPin, INPUT);     // 設定接收腳為輸入模式
    pinMode(greenLED, OUTPUT);   // 設定綠色LED腳位為輸出模式
    pinMode(redLED, OUTPUT);     // 設定紅色LED腳位為輸出模式
    Serial.begin(9600);          // 啟動串列通訊，設定鮑率為9600
}

// 主要程式循環
void loop() {
    // 取得距離數值並轉換為公分
    unsigned long distance = ping()/58;
    // 輸出距離到串列監視器
    Serial.print(distance);
    Serial.println("cm");
    
    // 將測量的距離轉換為LED亮度值
    // 距離越近，紅光越亮（255）；距離越遠，紅光越暗（0）
    int redBrightness = map(distance, MIN_DISTANCE, MAX_DISTANCE, 255, 0);
    // 距離越近，綠光越暗（0）；距離越遠，綠光越亮（255）
    int greenBrightness = map(distance, MIN_DISTANCE, MAX_DISTANCE, 0, 255);
    
    // 確保LED亮度值在0-255的範圍內
    redBrightness = constrain(redBrightness, 0, 255);
    greenBrightness = constrain(greenBrightness, 0, 255);
    
    // 輸出LED亮度值到對應的腳位
    analogWrite(redLED, redBrightness);     // 設定紅色LED亮度
    analogWrite(greenLED, greenBrightness); // 設定綠色LED亮度
    
    delay(100);    // 延遲100毫秒後再次執行
}

// 超音波測距函數
unsigned long ping() {
    digitalWrite(TrigPin, LOW);     // 先將觸發腳位設為低電位
    delayMicroseconds(5);           // 等待5微秒
    digitalWrite(TrigPin, HIGH);    // 發送10微秒的高電位脈衝
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);     // 將觸發腳位恢復為低電位
    return pulseIn(EchoPin, HIGH);  // 測量並回傳回波時間
}
