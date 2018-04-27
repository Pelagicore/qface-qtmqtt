# Dependencies

* Install mqtt library from https://github.com/emqtt/qmqtt
* Run a mosquitto server (https://mosquitto.org/download/)

#Install

    qmake
    make

Run mqttcounter.

# Concept

You will see a window with two buttons and a label. The button increment and decrement a counter.
The counter is controlled using a Mqtt client connection and the logic is
implemented using a mqtt connection using a service API.

By default mqtt does not really know client/server it is a peer/broker model. The service is just a
mqtt connection which allows you to override some callback methods. Beside this client and server use
same connection type.


# Configuration

The MQTT server can be changed using the MQTT_URL environment variable. The default is

    MQTT_URL=tcp://127.0.0.1:1883

You want to set your qt logging rules to

    QT_LOGGING_RULES=*.debug=false;counter.*.debug=true;mqtt.*.debug=true


