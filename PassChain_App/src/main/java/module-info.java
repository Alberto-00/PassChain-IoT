module it.unisa.unlockerapp {
    requires javafx.controls;
    requires javafx.fxml;
    requires com.fazecast.jSerialComm;


    opens it.unisa.passchain to javafx.fxml;
    exports it.unisa.passchain;
    exports it.unisa.passchain.utils;
    opens it.unisa.passchain.utils to javafx.fxml;
}