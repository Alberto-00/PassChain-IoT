package it.unisa.unlockerapp;

import it.unisa.unlockerapp.utils.ArduinoConnection;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

import java.io.IOException;

public class UnlockApplication extends Application {

    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("fxml/authentication.fxml"));
        ArduinoConnection.init();

        Scene scene = new Scene(fxmlLoader.load());
        stage.setTitle("Unlocker IoT");
        stage.setScene(scene);
        stage.setResizable(false);
        stage.getIcons().add(new Image("D:\\Progetti GitHub\\PassChain-IoT\\UnlockerApp\\src\\main\\resources\\it\\unisa\\unlockerapp\\assets\\icon.png"));
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}