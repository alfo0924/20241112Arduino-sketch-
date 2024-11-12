
#include <Wire.h>                    // I2C通訊函式庫
#include <LiquidCrystal_I2C.h>      // LCD I2C函式庫
#include "DHT.h"                     // DHT感測器函式庫

// 定義腳位
#define SDA_PIN 26                   // LCD的SDA接腳
#define SCL_PIN 25                   // LCD的SCL接腳
#define DHTPIN 4                     // DHT11的數據接腳
#define DHTTYPE DHT11               // 定義使用的感測器型號為DHT11

// 初始化LCD和DHT物件
LiquidCrystal_I2C lcd(0x27,16,2);   // LCD位址，設定16x2顯示
DHT dht(DHTPIN, DHTTYPE);           // 建立DHT物件

void setup() {
    // 初始化I2C通訊
    Wire.begin(SDA_PIN,SCL_PIN);
    
    // 初始化LCD
    lcd.init();
    lcd.backlight();
    lcd.clear();
    
    // 初始化DHT感測器
    dht.begin();
}

void loop() {
    // 讀取溫濕度數據
    float h = dht.readHumidity();    // 讀取濕度
    float t = dht.readTemperature(); // 讀取溫度
    
    // 檢查是否讀取失敗
    if (isnan(h) || isnan(t)) {
        lcd.setCursor(0,0);
        lcd.print("Failed DHT");
        return;
    }
    
    // 顯示溫度在第一行
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print(" C");
    
    // 顯示濕度在第二行
    lcd.setCursor(0,1);
    lcd.print("Humi: ");
    lcd.print(h);
    lcd.print(" %");
    
    // 等待2秒後更新數據
    delay(2000);
    lcd.clear();
}
