# Seeed ArduPy DHT [![Build Status](https://api.travis-ci.com/Seeed-Studio/seeed-ardupy-dht.svg?branch=main)](https://travis-ci.com/github/Seeed-Studio/seeed-ardupy-dht)

## Introduction

This is the ArduPy library for Grove - Temperature & Humidity Sensor (DHT11). 
Grove - DHT11 Temperature & Humidity Sensor is a high quality, low-cost digital temperature, and humidity sensor based on the DHT11 sensor. It uses the upgraded version of DHT11. The new version of the DHT11 module replaces resistive humidity components with capacitive humidity components. The temperature and humidity measurement range is wider and the temperature resolution is higher. 

Learn more [here](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html).

<p style="text-align:center;"><a href="https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html"><img src="https://static-cdn.seeedstudio.site/media/catalog/product/cache/9d0ce51a71ce6a79dfa2a98d65a0f0bd/g/r/grove-temperature-humidity-sensor-dht11-preview.png" width="450"></a></p>

## How to bind with ArduPy
- Install [AIP](https://github.com/Seeed-Studio/ardupy-aip)
- Build firmware with Seeed ArduPy DHT
```shell
aip install Seeed-Studio/seeed-ardupy-dht
aip build
```
- Flash new firmware to you ArduPy board
```shell
aip flash
#aip flash [path of the new firmware]
```
For more examples of using AIP, please refer to [AIP](https://github.com/Seeed-Studio/ardupy-aip).

## Usage

```python
from arduino import grove_dht
import time

dht = grove_dht(0,11) # pin number, DHT type 

while True:
    print ("Temperature: ", dht.temperature, "C")
    print ("Humidity: ", dht.humidity, "RH%")
    print ("30C to F", dht.ctof(30), "F")
    time.sleep(1)
```

## API Reference

- **temperature** : Obtain Temperature in Celcius 
```python
print(dht.temperature)
```

- **humidity**: Obtain Humidity in Relative Humidity %
```python
 print(dht.humidity)
```

- **ctof**: Convert Celcius values into Farenheit values
```python
 print(dht.ctof())
```
----
## License
This software is written by seeed studio<br>
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.<br>

Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed Studio is an open hardware facilitation company based in Shenzhen, China. <br>
Benefiting from local manufacture power and convenient global logistic system, <br>
we integrate resources to serve new era of innovation. Seeed also works with <br>
global distributors and partners to push open hardware movement.<br>
