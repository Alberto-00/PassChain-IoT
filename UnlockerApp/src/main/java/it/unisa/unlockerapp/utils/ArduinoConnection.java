package it.unisa.unlockerapp.utils;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;

import java.io.InputStream;

public class ArduinoConnection {
    private final static String devicePortName = "COM3";
    private static SerialPort arduinoPort = null;

    public static void init() {
        SerialPort[] allSerialPorts = SerialPort.getCommPorts();

        for(SerialPort eachComPort: allSerialPorts){
            System.out.println("List of all available serial ports: " + eachComPort.getDescriptivePortName());
            String portName = eachComPort.getDescriptivePortName();

            if (portName.contains(devicePortName)) {
                arduinoPort = eachComPort;
                arduinoPort.openPort();
                break;
            }
        }

        arduinoPort.addDataListener(new SerialPortDataListener() {
            @Override
            public int getListeningEvents() {
                return SerialPort.LISTENING_EVENT_DATA_RECEIVED;
            }

            @Override
            public void serialEvent(SerialPortEvent serialPortEvent) {
                if (serialPortEvent.getEventType() == SerialPort.LISTENING_EVENT_DATA_RECEIVED){
                    byte [] data = serialPortEvent.getReceivedData();
                    String msg = new String(data);
                    System.out.println(msg);
                }
            }
        });
        //arduinoPort.closePort();
    }
}
