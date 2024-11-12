#include "DHT.h"              // 引入DHT溫濕度感測器的函式庫
#define DHTPIN 4              // 定義DHT11的數據接腳為Pin 4
#define DHTTYPE DHT11         // 定義使用的感測器類型為DHT11型號

DHT dht(DHTPIN, DHTTYPE);     // 建立DHT物件，設定接腳及類型

void setup() {
  Serial.begin(9600);         // 初始化串列通訊，設定鮑率為9600
  Serial.println("DHT11 test!"); // 輸出測試訊息
  dht.begin();               // 啟動DHT感測器
}

void loop() {
  // 每次測量之間至少要間隔2秒，這是DHT11的硬體限制
  delay(2000);
  
  // 讀取感測器數據
  float h = dht.readHumidity();     // 讀取濕度值，單位為百分比(%)
  float t = dht.readTemperature();  // 讀取溫度值，單位為攝氏溫度(°C)
  
  // 檢查是否成功讀取到數據
  // isnan()函數會檢查讀取到的值是否為無效數值
  if (isnan(h) || isnan(t)) {
    Serial.println("無法從DHT感測器讀取數據！");
    return;
  }
  
  // 將讀取到的數據透過串列埠輸出
  Serial.print("濕度: ");    // 輸出濕度標籤
  Serial.print(h);           // 輸出濕度數值
  Serial.print("% 溫度: ");  // 輸出溫度標籤
  Serial.print(t);           // 輸出溫度數值
  Serial.println("°C");      // 輸出溫度單位並換行
}
