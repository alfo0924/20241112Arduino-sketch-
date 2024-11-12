
# sketch_nov12a.ino

## 硬體設定
- 使用了兩個腳位：
  - TrigPin（腳位17）: 觸發信號輸出
  - EchoPin（腳位16）: 回波信號輸入

## 程式結構分析

**設定階段 (setup)**
```cpp
void setup() {
    pinMode(TrigPin, OUTPUT);    // 設定觸發腳為輸出模式
    pinMode(EchoPin, INPUT);     // 設定回波腳為輸入模式
    Serial.begin(9600);          // 初始化串口通訊，設定鮑率為9600
}
```

**主要循環 (loop)**
```cpp
void loop() {
    unsigned long distance = ping()/58;  // 計算距離（公分）
    Serial.print(distance);              // 輸出距離數值
    Serial.println("cm");                // 輸出單位
    delay(100);                          // 延遲100毫秒
}
```

**測距函數 (ping)**
```cpp
unsigned long ping() {
    digitalWrite(TrigPin, LOW);      // 先將觸發腳位設為低電位
    delayMicroseconds(5);            // 等待5微秒
    digitalWrite(TrigPin, HIGH);     // 發送10微秒的高電位脈衝
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);      // 將觸發腳位恢復低電位
    return pulseIn(EchoPin, HIGH);   // 測量回波時間
}
```

## 工作原理

1. 感測器發送超音波：通過TrigPin發送10微秒的觸發信號

2. 等待回波：
   - 超音波遇到障礙物後反射回來
   - 通過EchoPin接收回波信號

3. 距離計算：
   - 使用公式：距離 = 回波時間 / 58
   - 58這個係數是根據聲波速度（340m/s）計算得出

## 注意事項

- 程式每100毫秒測量一次距離
- 距離單位為公分（cm）
- 測量結果會通過串口監視器顯示
