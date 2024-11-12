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
  

# sketch_nov12b.ino
###  install DHT sensor library ver:1.4.6
###  install DHT sensor library for ESPx ver:1.19.0

這兩個是用於Arduino開發環境的DHT溫濕度感測器函式庫：

## DHT sensor library (版本1.4.6)

這是Adafruit開發的標準DHT函式庫：
- 支援DHT11、DHT22（AM2302）等溫濕度感測器
- 適用於一般Arduino開發板
- 提供基本的溫度和濕度讀取功能
- 是最常用且穩定的DHT函式庫[1]

## DHT sensor library for ESPx (版本1.19.0)

這是專門為ESP32/ESP8266優化的DHT函式庫：
- 特別針對ESP系列微控制器優化
- 提供更好的ESP32相容性
- 修正了負溫度讀取的問題
- 提供更多進階功能[3][5]

## 主要差異

**功能比較**：
- 標準版：基本溫濕度讀取
- ESP版：額外提供：
  - 自動感測器類型檢測
  - 更精確的計時控制
  - 更好的錯誤處理

**使用場景**：
- 使用Arduino開發板：選擇標準版（1.4.6）
- 使用ESP32/ESP8266：建議使用ESP版（1.19.0）

**安裝方式**：
- 兩個函式庫都可以通過Arduino IDE的程式庫管理員安裝
- ESP版需要搜尋"DHT ESP"
- 標準版搜尋"DHT sensor library"


## 基本設定
```cpp
#include "DHT.h"              // 引入DHT函式庫
#define DHTPIN 4              // 設定DHT11的數據腳位為4
#define DHTTYPE DHT11         // 指定使用的感測器類型為DHT11

DHT dht(DHTPIN, DHTTYPE);    // 建立DHT物件
```

## 初始化設定
```cpp
void setup() {
  Serial.begin(9600);         // 啟動串列通訊，設定鮑率9600
  Serial.println("DHT11 test!"); // 輸出測試訊息
  dht.begin();               // 初始化DHT感測器
}
```

## 主要運作邏輯
```cpp
void loop() {
  delay(2000);  // 延遲2秒，DHT11需要至少2秒的測量間隔
  
  // 讀取濕度和溫度數據
  float h = dht.readHumidity();     // 讀取濕度
  float t = dht.readTemperature();  // 讀取溫度（攝氏）
  
  // 檢查讀取是否成功
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // 輸出測量結果
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("% Temperature: ");
  Serial.print(t);
  Serial.println("°C");
}
```

## 功能說明

**感測器讀取**
- `dht.readHumidity()`：讀取濕度值（範圍：20-90%）
- `dht.readTemperature()`：讀取溫度值（範圍：0-50°C）

**錯誤檢查**
- 使用`isnan()`函數檢查讀取值是否有效
- 如果讀取失敗，會顯示錯誤訊息

**輸出格式**
- 每2秒更新一次數據
- 顯示格式例如：
  ```
  Humidity: 45.00% Temperature: 25.00°C
  ```

## 注意事項

1. DHT11的測量限制：
   - 溫度測量範圍：0-50°C
   - 濕度測量範圍：20-90%
   - 精確度：溫度±2°C，濕度±5%

2. 讀取間隔：
   - 必須至少等待2秒才能進行下一次讀取
   - 讀取過於頻繁可能導致數據不準確

3. 接線方式：
   - 數據腳接到Pin 4
   - 需要接上適當的上拉電阻
   - 供電電壓：3.3V-5V

4. 可能的問題排除：
   - 如果持續讀取失敗，檢查接線
   - 確認供電電壓是否穩定
   - 檢查上拉電阻是否正確
