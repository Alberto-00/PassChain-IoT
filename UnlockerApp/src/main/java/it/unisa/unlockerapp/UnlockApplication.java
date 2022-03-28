package it.unisa.unlockerapp;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

import java.io.IOException;

public class UnlockApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(UnlockApplication.class.getResource("authentication.fxml"));
        Scene scene = new Scene(fxmlLoader.load());
        stage.setTitle("Unlocker IoT");
        stage.setScene(scene);
        stage.setResizable(false);
        stage.getIcons().add(new Image("D:\\Progetti GitHub\\Progetto-IoT\\UnlockerApp\\src\\main\\resources\\it\\unisa\\unlockerapp\\assets\\iconApp.png"));
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}