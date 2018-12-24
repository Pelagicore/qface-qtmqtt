# QFace QtMqtt Code Generator

*WORK IN PROGRESS*

# Installation

Make a new folder called `mqtt`

    mkdir mqtt && cd mqtt

Clone and build `qmqtt`

    git clone https://github.com/emqtt/qmqtt.git
    cd qmqtt
    mkdir build && cd build
    qmake .. && make && make install

Create a `python3` virtual environment

    virtualenv -p python3 venv
    source venv/bin/activate

Clone and install the lates `qface`    

    pip install git+https://github.com/Pelagicore/qface.git#master


Clone latest `qface-qtmqtt` solution

    git clone git@github.com:Pelagicore/qface-qtmqtt.git

Create a simple `qface` interface document `counter.qface`

    module counter 1.0
    
    interface Counter {
        int count
        void increment();
        void decrement();
    }

Run the code generation

    qface --rules qface-mqtt/rules.yml --target out counter.qface out

To generate the code in the out folder. Now you can open the `out/out.pro` document.

To not generate the app and the service implementation use 

    qface --rules qface-mqtt/rules.yml --target out --no-feature scaffold counter.qface

It will just generate the libraries in the out folder and it's up to you to integrate it into your project.

Note: Please be aware the project makes use a SOURCE_DIR and BUILD_DIR qmake variables specified in a `.qmake.conf` file.


# Design

Based on the above counter example the design of the generated code will look like this.

                                             lib_counter
    +--------------------------------------------------+
    |                                                  |
    |             +------------+                       |
    |          +--+ MqttClient +---------+             |
    |          |  +------------+         |             |
    |          |                         |             |
    |          |                         |             |
    |  +-------+-------+   +-------------+----------+  |
    |  | CounterClient |   | AbstractCounterService |  |
    |  +-------+-------+   +-------------+----------+  |
    |          |                         |             |
    +--------------------------------------------------+
               |                         |
               |                +--------+-------+
               |                | CounterService |
               |                +--------+-------+
               |                         |
               |                         |
        +------+------+             +----+----+
        | Application |             |  Server |
        +-------------+             +---------+




The `CounterClient` uses the generic `MqttClient` to publish messages and subscribe to topics. The `CounterClient` offers a concrete client API (e.g. count property, increment, decrement methods).
The `AbstractCounterService` uses the `MqttClient` to subscribe to the module topic and to provide abstract set/get count methods which needs to be implemented in the concrete `CounterService`. The Server startes the main loop and creates the CounterService in one process. The Application uses the client in another process. Both are connected via a MQTT Broker.


# Playground

The playgorund folder contains some sample projects using Mqtt clients.


