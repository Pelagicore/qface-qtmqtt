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

    git clone git@github.com:Pelagicore/qface.git
    pip install -e qface --upgrade

Clone and install latest `qface-qtmqtt` solution

    git clone git@gitlab.com:jryannel/qface-qtmqtt.git
    pip install -e qface-qtmqtt --upgrade

Create a simple `qface` interface document `counter.qface`

    module counter 1.0
    
    interface Counter {
        int count
        void increment();
        void decrement();
    }

Run the code generation

    qface-qtmqtt counter.qface out

To generate the code in the out folder. Now you can open the `out/out.pro` document.

To not generate the app and the service implementation use 

    qface-qtmqtt counter.qface out --no-scaffold

It will just generate the libraries in the out folder and it's up to you to integrate it into your project.

Note: Please be aware the project makes use a SOURCE_DIR and BUILD_DIR qmake variables specified in a `.qmake.conf` file.

# Playground

The playgorund folder contains some sample projects using Mqtt clients.


