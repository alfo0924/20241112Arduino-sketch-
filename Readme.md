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


控制LED亮度漸變的關鍵程式碼：

```cpp
// 將距離轉換為LED亮度
int redBrightness = map(distance, MIN_DISTANCE, MAX_DISTANCE, 255, 0);
int greenBrightness = map(distance, MIN_DISTANCE, MAX_DISTANCE, 0, 255);
```

## map函數原理說明

`map()`函數的格式為：
```cpp
map(要轉換的值, 原始範圍最小值, 原始範圍最大值, 目標範圍最小值, 目標範圍最大值)
```

以紅色LED為例：
```cpp
map(distance, 5, 100, 255, 0)
```
- 當距離是5cm時：映射為亮度255（最亮）
- 當距離是100cm時：映射為亮度0（熄滅）
- 當距離在5-100cm之間時：亮度會按比例在0-255之間變化

## 實際數值示例

假設距離值在5cm到100cm之間變化：

| 距離(cm) | 紅色LED亮度 | 綠色LED亮度 |
|----------|-------------|-------------|
| 5        | 255（最亮） | 0（熄滅）   |
| 25       | 191         | 64          |
| 50       | 127         | 128         |
| 75       | 64          | 191         |
| 100      | 0（熄滅）   | 255（最亮） |

## 運作流程

1. **近距離情況**（5cm）：
   - 紅色LED：map(5, 5, 100, 255, 0) = 255（最亮）
   - 綠色LED：map(5, 5, 100, 0, 255) = 0（熄滅）

2. **遠距離情況**（100cm）：
   - 紅色LED：map(100, 5, 100, 255, 0) = 0（熄滅）
   - 綠色LED：map(100, 5, 100, 0, 255) = 255（最亮）

3. **中間距離**（例如50cm）：
   - 紅色LED：map(50, 5, 100, 255, 0) ≈ 127（中等亮度）
   - 綠色LED：map(50, 5, 100, 0, 255) ≈ 128（中等亮度）
