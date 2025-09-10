#define BLYNK_TEMPLATE_ID "TMPL6g9eEk-Hk"
#define BLYNK_TEMPLATE_NAME "MY Home"
#define BLYNK_AUTH_TOKEN "Gcg446CmY-cLTf_y2A3KEOpUH2R3RWUe"
#define BTN 4
#define DDAA 16
#define LED 2

#include <WiFi.h>
#include <Wire.h>
#include <WebServer.h>
// #include <WebServer.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DNSServer.h>


const char* ssid = "Poomrelax";
const char* password = "poom03022553";

const char* ssid_web = "Project_com";
const char* password_web = "12345678";
IPAddress apIP(1, 1, 1, 1);

bool status = false;

Adafruit_SSD1306 display(128, 64, &Wire, -1);

WebServer server(80);
DNSServer dnsServer;

String htmlindex_on = R"rawliteral(
  <!DOCTYPE html>
<html>
  <head>
  <meta charset="UTF-8">
  <meta http-equiv='refresh' content='3'>

    <title>Hello, World!</title>
    <link rel="stylesheet" href="styles.css" />
    <style>
      
      *{
        margin: 0;
        padding: 0;
        box-sizing: border-box;
      }
    
      h1{
        font-size: 20px;
        font-family: Arial;
        text-align: center;
      }
      
      p{
        color: rgba(0,0,0,0.5);
        text-align: center;
        font-size: 13px;
        font-family: Courier;
        margin-top: 10px;
      }
      
      .btn{
        /*border: 1px solid red;*/
        display: flex;
        justify-content: center;
        align-content: center;
        margin-top: 10rem;
      }
      
      button{
        padding: 2rem 4rem;
        border: none;
        background: green;
        color: #fff;
        border-radius: 5px;
        text-size: 20px;
      }
      
      footer{
        position: absolute;
        bottom: 0;
        background: #ccc;
        width: 100%;
        
      }
      
      
    </style>
  </head>
  <body>
     <h1 id="">NO/OFF LIGHT</h1>
     <p>เว็ปนี้เป็นเว็ปจำลองการเปิดปิดไฟ ของวิชาเทคโนโลยีและการออกแบบ</p>
     <div class="btn">
     <form action='/tootle'>
      <button type='submit'>เปิด</button>
     </form>
     </div>
     <!--<footer>-->
     <!--  &copy; ห้อง4/1-->
     <!--</footer>-->
  </body>
</html>
)rawliteral";

String htmlindex_off = R"rawliteral(
  <!DOCTYPE html>
<html>
  <head>
  <meta charset="UTF-8">
  <meta http-equiv='refresh' content='3'>

    <title>Hello, World!</title>
    <link rel="stylesheet" href="styles.css" />
    <style>
      
      *{
        margin: 0;
        padding: 0;
        box-sizing: border-box;
      }
    
      h1{
        font-size: 20px;
        font-family: Arial;
        text-align: center;
      }
      
      p{
        color: rgba(0,0,0,0.5);
        text-align: center;
        font-size: 13px;
        font-family: Courier;
        margin-top: 10px;
      }
      
      .btn{
        /*border: 1px solid red;*/
        display: flex;
        justify-content: center;
        align-content: center;
        margin-top: 10rem;
      }
      
      button{
        padding: 2rem 4rem;
        border: none;
        background: red;
        color: #fff;
        border-radius: 5px;
        text-size: 20px;
      }
      
      footer{
        position: absolute;
        bottom: 0;
        background: #ccc;
        width: 100%;
        
      }
      
      
    </style>
  </head>
  <body>
     <h1 id="">NO/OFF LIGHT</h1>
     <p>เว็ปนี้เป็นเว็ปจำลองการเปิดปิดไฟ ของวิชาเทคโนโลยีและการออกแบบ</p>
     <div class="btn">
      <form action='/tootle'>
      <button type='submit'>ปิด</button>
     </form>
     </div>
     <!--<footer>-->
     <!--  &copy; ห้อง4/1-->
     <!--</footer>-->
  </body>
</html>
)rawliteral";

void hoot() {
  if (status == false) {
    server.send(200, "text/html; charset=utf-8", htmlindex_on);
  } else {
    server.send(200, "text/html; charset=utf-8", htmlindex_off);
  }
}

void tootle() {
  status = !status;
  digitalWrite(DDAA, status ? LOW : HIGH);
  digitalWrite(LED, status ? HIGH : LOW);
  Blynk.virtualWrite(V1, status ? true : false);
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "");
}


void chang_oled() {
   if(status == true) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("IP Address: ");
    display.setCursor(0, 40);
    display.setTextSize(1);
    display.println(WiFi.softAPIP());
    display.setTextSize(1);
    display.setCursor(116, 0);
    display.print("ON");




    display.display();
  }else{
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.println("IP Address: ");
      display.setCursor(0, 40);
      display.setTextSize(1);
      display.println(WiFi.softAPIP());
      display.setCursor(110, 0);
      display.setTextSize(1);
      display.print("OFF");




      display.display();
  }


}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.mode(WIFI_AP_STA);


  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  Serial.println("success display");
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(46, 20);
  display.print("ON");

  display.display();

  dnsServer.start(53, "*", apIP);



  Serial.println("connect Wifi อยู่เด้อ...");

  pinMode(LED, OUTPUT);
  pinMode(DDAA, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);

  digitalWrite(DDAA, HIGH);
  digitalWrite(LED, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    Serial.println(".");
  }

  WiFi.softAP(ssid_web);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

  server.on("/", hoot);
  server.on("/tootle", tootle);
  server.on("/generate_204", hoot);
  server.on("/gen_204", hoot);
  server.on("/hotspot-detect.html", hoot);
  server.on("/library/test/success.html", hoot);
  server.on("/connecttest.txt", hoot);
  server.on("/ncsi.txt", hoot);
  server.on("/redirect", hoot);
  server.onNotFound(hoot);

  server.begin();

  Serial.println("IP Address: ");
  Serial.print(WiFi.softAPIP().toString());
  Blynk.virtualWrite(V1, status ? true : false);


  delay(3000);

}

void chang_status() {
    digitalWrite(DDAA, status ? LOW : HIGH);
    digitalWrite(LED, status ? HIGH : LOW);
    Blynk.virtualWrite(V1, status ? true : false);
}

void loop() {
  Blynk.run();
  chang_oled();
  dnsServer.processNextRequest();
  server.handleClient();

  bool btn_read = digitalRead(BTN);

  // chang_status();

  if(btn_read == LOW) {
    status = !status;
    chang_oled();
    chang_status();
    delay(500);
  }

}

BLYNK_WRITE(V1) {
  int pinValue = param.asInt();   // อ่านค่าเป็น int
  if(pinValue == 1) {
    chang_oled();
    digitalWrite(DDAA, LOW);
    digitalWrite(LED, HIGH);
    status = true;
  }else{
    chang_oled();
    digitalWrite(DDAA, HIGH);
    digitalWrite(LED, LOW);
    status = false;
  }
}
