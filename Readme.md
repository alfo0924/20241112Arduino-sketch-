# sketch_nov12a.ino 
### 結合超音波感測器和LED漸變效果

## 硬體配置
**感測器接腳**
- TrigPin（腳位17）：超音波發射觸發腳
- EchoPin（腳位16）：超音波接收回波腳

**LED接腳**
- greenLED（腳位4）：綠色LED
- redLED（腳位0）：紅色LED

## 常數設定
```cpp
const int MIN_DISTANCE = 5;    // 最小測量距離5公分
const int MAX_DISTANCE = 100;  // 最大測量距離100公分
```

## 程式功能區塊

**初始化設定**
```cpp
void setup() {
    pinMode(TrigPin, OUTPUT);    // 設定超音波觸發腳為輸出
    pinMode(EchoPin, INPUT);     // 設定超音波接收腳為輸入
    pinMode(greenLED, OUTPUT);   // 設定綠色LED腳位為輸出
    pinMode(redLED, OUTPUT);     // 設定紅色LED腳位為輸出
    Serial.begin(9600);          // 啟動串口通訊
}
```

**主要運作邏輯**
```cpp
void loop() {
    // 測量距離並轉換為公分
    unsigned long distance = ping()/58;
    
    // 將距離映射為LED亮度
    int redBrightness = map(distance, MIN_DISTANCE, MAX_DISTANCE, 255, 0);
    int greenBrightness = map(distance, MIN_DISTANCE, MAX_DISTANCE, 0, 255);
```

## 運作原理

**距離測量**
1. 使用`ping()`函數發送超音波並接收回波
2. 將回波時間除以58轉換為公分距離

**LED亮度控制**
1. 使用`map()`函數進行距離到亮度的轉換：
   - 距離越近：紅燈越亮（255），綠燈越暗（0）
   - 距離越遠：紅燈越暗（0），綠燈越亮（255）

2. 使用`constrain()`函數確保亮度在0-255範圍內

## 效果展示
- **近距離**（5cm）：
  - 紅燈最亮（255）
  - 綠燈熄滅（0）

- **遠距離**（100cm）：
  - 紅燈熄滅（0）
  - 綠燈最亮（255）

- **中間距離**：
  - 兩個LED呈現漸變效果
  - 亮度根據距離比例變化

