module it.unisa.unlockerapp {
    requires javafx.controls;
    requires javafx.fxml;


    opens it.unisa.unlockerapp to javafx.fxml;
    exports it.unisa.unlockerapp;
}