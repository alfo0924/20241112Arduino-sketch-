#include <Wire.h>                    // 引入I2C通訊函式庫
#include <LiquidCrystal_I2C.h>      // 引入LCD I2C控制函式庫

// 定義I2C通訊使用的腳位
#define SDA_PIN 26                   // 設定SDA資料線為26腳位
#define SCL_PIN 25                   // 設定SCL時脈線為25腳位

// 建立LCD物件，設定I2C位址為0x27，16字元×2行的LCD
LiquidCrystal_I2C lcd(0x27,16,2);   // 如果無法顯示，可能要改為0x3F

void setup(){
    // 初始化I2C通訊，設定SDA和SCL腳位
    Wire.begin(SDA_PIN,SCL_PIN);
    
    lcd.init();       // 初始化LCD
    lcd.backlight();  // 開啟LCD背光
    lcd.clear();      // 清除LCD畫面
}

void loop(){
    // 設定游標位置到第一行第一個位置(0,0)
    lcd.setCursor(0,0);
    lcd.print("Hello,From");    // 在第一行顯示文字
    
    // 設定游標位置到第二行第一個位置(0,1)
    lcd.setCursor(0,1);
    lcd.print("Nodemcu!");      // 在第二行顯示文字

    delay(1000);                // 延遲1秒
    lcd.clear();               // 清除螢幕顯示
}
