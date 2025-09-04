#include <WiFi.h>
#include <WebServer.h>
// #include <ESPAsyncWebServer.h>
#include <DNSServer.h>

#define BTN 4
#define DDAA 15

const char *ssid = "BordForRelax";
const char *password = "poomrelax11699";
IPAddress apIP(1,1,1,1);

WebServer server(80);
DNSServer dnsServer;
// AsyncWebServer server(80);



void handleNotFound() {
  server.sendHeader("Location", String("http://") + WiFi.softAPIP().toString(), true);
  server.send(302, "text/plain", "");
}

// void hoot() {
//   server.send(200, "text/html; charset=utf-8",  "<!DOCTYPE html>"
//     "<html>"
//     "<head><meta charset='UTF-8'><title>Hi</title></head>"
//     "<body>"
//     "<h1>Welcome เด้อ</h1>"
//     "</body>"
//     "</html>");
// }

String htmlindex = R"rawliteral(
  <!DOCTYPE html>
<html>
  <head>
  <meta charset="UTF-8">
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
        margin-top: 5rem;
      }
      
      button{
        padding: 1rem 2rem;
        border: none;
        background: green;
        color: #fff;
        border-radius: 5px;
        
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
       <button>เปิด</button>
     </div>
     <!--<footer>-->
     <!--  &copy; ห้อง4/1-->
     <!--</footer>-->
  </body>
</html>
)rawliteral";

void hoot() {
  server.send(200, "text/html"; , htmlindex);
}

void setup() {
  Serial.begin(115200);
  
  pinMode(BTN, INPUT_PULLUP);
  pinMode(DDAA, OUTPUT);

  WiFi.softAP(ssid);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255,255,255,0));

  Serial.println("start");

  Serial.print("ip addess: ");
  Serial.println(WiFi.softAPIP());

  dnsServer.start(53, "*", apIP);

  server.on("/", hoot);
  server.on("/generate_204", hoot);
  server.on("/gen_204", hoot);
  server.on("/hotspot-detect.html", hoot);
  server.on("/library/test/success.html", hoot);
  server.on("/connecttest.txt", hoot);
  server.on("/ncsi.txt", hoot);
  

  
  server.begin();
}

void loop() {
  bool ReadBTN = digitalRead(BTN);
  // put your main code here, to run repeatedly:
  dnsServer.processNextRequest();
  server.handleClient();

  if(ReadBTN == 0) {
    digitalWrite(DDAA, HIGH);
  }else{
    digitalWrite(DDAA, LOW);
  }

}
