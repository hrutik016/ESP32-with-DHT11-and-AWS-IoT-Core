# ESP32 AWS IoT Temperature and Humidity Sensor

This project showcases how to connect an ESP32 microcontroller with a DHT11 temperature and humidity sensor to AWS IoT Core for real-time monitoring and data collection.

## Features

- Reads temperature and humidity data from the DHT11 sensor
- Publishes sensor data to AWS IoT Core using MQTT protocol
- Subscribes to messages from AWS IoT Core for remote control or monitoring
- Securely connects to AWS IoT Core using TLS encryption and X.509 certificates

## Dependencies

- WiFiClientSecure
- PubSubClient
- ArduinoJson
- DHT sensor library

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Inspired by [AWS IoT Core Arduino SDK](https://github.com/aws/aws-iot-device-sdk-arduino)
- DHT sensor library by Adafruit
- Video Tutorial from [How to Electronics](https://www.youtube.com/watch?v=idf-gGXvIu4).
