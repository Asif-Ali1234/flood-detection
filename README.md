# Flood-Detection
Flood Detection using IOT

## Project Description

This project is based on the current day technology IOT, which is nothing but operating our surroundings through internet from all over the world. Using this technique, we can develop a system which can monitor floods near dams and also can monitor water level of the dam. Floods can be detected using some parameters mainly temperature and humidity near dams. Temperature and humidity can be measured using IOT sensor named DHT11. To measure the water level, we need ultrasonic sensor.

Ultrasonic sensor when connected to microcontroller will emit signals from it. After some time, these signals will get reflected when they met any obstacle. This reflected signal will be captured by the ultrasonic sensor and we can measure the distance between the obstacle and ultrasonic sensor. Whenever we kept ultrasonic sensor on top of the dam the rays will get reflected whenever they met the water and from this we can measure water level of the damn. DHT11 sensor will give us temperature and humidity of its surrounding area which can be very useful in predicting the flood. We collect all these values from the sensors and then our microcontroller will analyze the sensor values and if those values are matched with flood conditions then a buzzer attached with microcontroller will be activated.

This means that flood is going to occur in some time. This sensor values then will be uploaded to Thing Speak cloud from our microcontroller. This cloud act as a medium in our system. Whenever we get that value in the cloud our mobile application, created using MIT app inventor will fetch those values and show it on your mobile phone screen. Apart from these a message will also be displayed based on the values obtained by the sensors. So the data will flow from sensors to microcontroller and this microcontroller will then upload those values to the Thing Speak cloud. From this cloud, our app will fetch that values and display them in the app. All these three will be synchronized at the same time whenever sensor values are changed.


## Architecture

This model set up the NODEMCU board near the dam and DHT sensor and ultrasonic sensor, float sensor are connected to it. DHT sensor gives the Humidity and Temperature in the air and Ultrasonic sensor gives the water level. Based on this and some other parameters we may decide if the flood is going to occur or not. We connect them to the cloud from where we connect this to the mobile application and we can see the output in our application too.

<img src="https://drive.google.com/uc?export=view&id=1N9UBFo446GLGIfBTRK2PWe5xD_t4Na0B"/>
 
Figure: Architecture of system

The systems have given connections in breadboard as follows, we will fix DHT11 and Buzzer on Breadboard and we will connect them with Nodemcu, Ultrasonnic sensor is connected to Nodemcu and it is fixed on the top of the dam. All the values we got will be uploaded to cloud using WiFi module in Nodemcu. From the cloud our values will get fetched by our application and we display them in our application. A message will also be displayed in the application based on the values we got into the cloud. This process is continuous and until Nodemcu is connected to an external power source it will upload the values and they will be fetched into the application. The cloud we used here is Thing Speak cloud with some field. created in it. This is an open source cloud which is servicing at free of cost. After setting up the fields in the your Thing Speak channel you will get the API keys of your account and we need those later to access you’re your account data.

After configuring Thing Speak cloud we need to create MIT app inventor account and from here we are going to develop the application and connect to our cloud using blocks. In this application we are going to create include some labels to display the values as well as message according to values. After logging and creating the interface will look like this and 

Now we configured both cloud App and now we connect the sensors to our application using jumper wires.

## Connections

<img src="https://drive.google.com/uc?export=view&id=1eggSrhsRnl6BnPkyqpylUDvt8-Uw3j8Z"/>

## MIT app code blocks

<img src="https://drive.google.com/uc?export=view&id=1UpaBqzXNwkyRfIloOgQsNedvYpn4_OgV"/>
