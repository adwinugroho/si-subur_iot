 // Create a WiFi access point and provide a web server on it.
// Go to http://192.168.4.1 in a web browser connected to this access point to see it.
// Control LED connected to  GPIO2

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

int val;
int i;
// Set these to your desired AP credentials.
const char *ssid = "masasubur";                          //-----untuk setting nama esp kita------
const char *password = "masasubur";           //---------untuk setting password.......

ESP8266WebServer server(80);

void setup() {

  
        Wire.begin(4, 5);                            //--------- 4 = sda, 5 = scl seting input i2c komunikasi dari sensor MLX (sda scl).........
	delay(1000);
	Serial.begin(115200);                        //---------pengaturan baudrate.......
        
        
	Serial.println();
	Serial.print("Configuring access point...");
	WiFi.softAP(ssid);                           // Remove password parameter if you want the AP to be open

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
  
	 server.begin();
	Serial.println("HTTP server started");
}

void loop() {
  
  server.handleClient();
         
 //---------------------------mengirim ke serial monitor---------------------------------- 
 
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  
  val=mlx.readObjectTempC(); //-----------------mengambil perhitungan suhu---pilih 
  Serial.println();
  
//------------------------------------data server------------------------------------------

  server.on("/", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    String webString="";     // String to display
    //webString="<FONT SIZE=+4> ESP8266 Wi-Fi webserver suhu dalam Celcius <BR> ";
    webString +=(val);
    
    server.send(200, "text/html", webString);            // send to someones browser when asked
    
  });
 delay(500);


}




