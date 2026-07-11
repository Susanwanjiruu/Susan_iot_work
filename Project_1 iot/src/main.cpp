#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <secrets.h>



WebServer Susan(80);
String page(){
   return R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Control Panel</title>
    <style>
        body {
            height: 100vh;
            width: 100vw;
            background-color: white;
            display: flex;
            flex-direction: column;
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        header {
            height: 30vh;
            align-items: center;
        }
        section {
            text-align: center;
        }
        main {
            height: 50vh;
        }
        .container1 {
            height: 100%;
            display: flex;
            flex-direction: row;
            align-items: center;
            gap: 100px;
            justify-content: center;
        }
        .child1 {
            display: flex;
            flex-direction: column;
            align-items: center;
            height: 450px;
            width: 450px;
            margin-top: 200px;
        }
        .child2 {
            display: flex;
            flex-direction: column;
            align-items: center;
            height: 450px;
            width: 450px;
            margin-top: 200px;
        }
        .buttons {
            display: flex;
            flex-direction: row;
            gap: 20px;
        }
        button {
            height: 50px;
            width: 200px;
            background-color: green;
            border-radius: 15px;
            color: white;
            font-size: larger;
            cursor: pointer;
        }
        .button1 {
            background-color: green;
            color: white;
            font-size: larger;
        }
        .button2 {
            background-color: red;
            color: white;
            font-size: larger;
        }
    </style>
</head>
<body>
    <header>
        <section>
            <h1>ESP32</h1>
            <p>
                The ESP32 is a cheap, powerful chip that makes building smart devices easy. It packs fast dual-core processing, Wi-Fi, and Bluetooth onto a single board. You can program it using C++ or Python on simple tools like Arduino or professional frameworks. It is the ultimate go-to board for building connected gadgets
            </p>
        </section>
    </header>
    <main>
      <div class="container1">
            <div class="child1">
                <h2>Nearby Wi-Fi Scanner</h2>
                <button type="button" onclick="scanWifi()">Scan Nearby Wi-Fi</button>
                <h3 id="strongest">Strongest Wi-Fi: --</h3>
                <h3 id="weakest">Weakest Wi-Fi: --</h3>
            </div>
            <div class="child2">
                <h2>LED Control</h2>
                <h3 id="led-status">Current Status: OFF</h3>
                <div class="buttons">
                    <button class="button1" type="button" onclick="controlLed('on')">LED On</button>
                    <button class="button2" type="button" onclick="controlLed('off')">LED Off</button>
                </div>  
            </div>
        </div>
    </main>
    <footer></footer>
       <script>
     
        function controlLed(state) {
            fetch('/led?state=' + state)
                .then(response => response.text())
                .then(data => {
                    document.getElementById('led-status').innerText = "Current Status: " + data;
                });
        }
                 function scanWifi() {
            document.getElementById('strongest').innerText = "Scanning...";
            document.getElementById('weakest').innerText = "Scanning...";
            
            fetch('/scan')
                .then(response => response.json())
                .then(data => {
                    document.getElementById('strongest').innerText = "Strongest Wi-Fi: " + data.strongest;
                    document.getElementById('weakest').innerText = "Weakest Wi-Fi: " + data.weakest;
                })
                .catch(err => {
                    document.getElementById('strongest').innerText = "Error scanning";
                    document.getElementById('weakest').innerText = "Error scanning";
                });
        }
                 </script>
</body>
</html>
)rawliteral";
}


void handleRoot()
{
  Susan.send(200, "text/html", page());
}

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to wifi ...");
  }
  Serial.println("Connected to wifi");
  Serial.println(WiFi.localIP());

  Susan.on("/", handleRoot);
  Susan.begin();
}
void loop()
{
  Susan.handleClient();
}