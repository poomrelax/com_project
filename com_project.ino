#include <WiFi.h>
#include <WebServer.h>
// #include <ESPAsyncWebServer.h>
#include <DNSServer.h>

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

void hoot() {
  server.send(200, "text/html; charset=utf-8",  "<!DOCTYPE html>"
    "<html>"
    "<head><meta charset='UTF-8'><title>Hi</title></head>"
    "<body>"
    "<h1>Welcome เด้อ</h1>"
    "</body>"
    "</html>");
}

void setup() {
  Serial.begin(115200);
  

  WiFi.softAP(ssid, password);
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
  // put your main code here, to run repeatedly:
  dnsServer.processNextRequest();
  server.handleClient();

}
