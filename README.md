# ESP8266_MQTT_GCloud
ESP8266 board with HX711 load cells connected to google cloud IOT using the mqtt protocol

## Configuration.
please open arduino_secret.h file and change the settings below with your system configuration


// WIFI
const char* ssid = "YOUR WIFI ID"; // Livebox-C4CF
const char* password = "WIFI PASSWORD"; // ch91ou94Pr

// Cloud iot details.
const char* project_id = "google cloud project id";
const char* location = "gougle cloud project location";
const char* registry_id = "iot registry id";
const char* device_id = "your device id";
const String topic = "/weight_values";


// To get the private key run (where private-key.pem is the ec private key
// used to create the certificate uploaded to google cloud iot):
// openssl ec -in <private-key.pem> -noout -text
// and copy priv: part.
// The key length should be exactly the same as the key length bellow (32 pairs
// of hex digits). If it's bigger and it starts with "00:" delete the "00:". If
// it's smaller add "00:" to the start. If it's too big or too small something
// is probably wrong with your key.
const char* private_key_str = "your private key str"

* please download your ca.crt from google cloud console and put it in the /data folder. you will to upload it first into the board
using esp8266 skecth data upload
