module it.unisa.unlockerapp {
    requires javafx.controls;
    requires javafx.fxml;
    requires com.fazecast.jSerialComm;


    opens it.unisa.unlockerapp to javafx.fxml;
    exports it.unisa.unlockerapp;
    exports it.unisa.unlockerapp.utils;
    opens it.unisa.unlockerapp.utils to javafx.fxml;
}