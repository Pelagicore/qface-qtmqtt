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
    pip install -q qface-qtmqtt

Create a simple `qface` interface document `counter.qface`

    module counter 1.0

    interface Counter {
        int count
        void increment();
        void decrement();
    }

Run the code generation

    qface-qtmqtt counter.qface out

Now you can open the `out/out.pro` document.

# Playground

The playgorund folder contains some sample projects using Mqtt clients.


