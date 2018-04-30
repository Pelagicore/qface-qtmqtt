import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import org.example 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    RowLayout {
        anchors.centerIn: parent
        Button {
            text: "-"
            onClicked: client.decrement()
        }
        Label {
            text: client.count
        }
        Button {
            text: '+'
//            onClicked: client.increment()
//            onClicked: mqtt.publish("count/Counter/count", {count:5});
            onClicked: mqtt.publish("count/Counter/increment");
        }
    }

    MqttClient {
        id: mqtt
        onReceived: {
            console.log(topic, JSON.stringify(data));
        }

        Component.onCompleted: {
            subscribe("count/Counter/#")
        }
    }

    CounterClient {
        id: client
    }

    CounterService {
        id: service
    }
}
