#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "ESP32_DHT11"                         
 
const char WIFI_SSID[] = " ";               //enter wifi name
const char WIFI_PASSWORD[] = " ";           //enter wifi password
const char AWS_IOT_ENDPOINT[] = " ";       //wnter the data endpoint from your aws profile
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----

// Copy and paste content from Root CA 1 

-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
 
// copy and paste device certificate

-----END CERTIFICATE-----
 
 
)KEY";
 
// Device Private Key                                               
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----

// copy and paste private key 
 
-----END RSA PRIVATE KEY-----
 
 
)KEY";