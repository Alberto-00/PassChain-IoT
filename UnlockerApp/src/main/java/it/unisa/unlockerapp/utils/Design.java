package it.unisa.unlockerapp.utils;

import javafx.animation.FadeTransition;
import javafx.animation.TranslateTransition;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.TextFormatter;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.util.Duration;

import java.util.function.UnaryOperator;
import java.util.regex.Pattern;

public class Design {

    public static void setSidebar(AnchorPane panel1, AnchorPane panel2, ImageView menu){
        panel1.setVisible(false);

        FadeTransition fadeTransition = new FadeTransition(Duration.seconds(0.4),panel1);
        fadeTransition.setFromValue(1);
        fadeTransition.setToValue(0);
        fadeTransition.play();

        TranslateTransition translateTransition = new TranslateTransition(Duration.seconds(0.4),panel2);
        translateTransition.setByX(-600);
        translateTransition.play();

        menu.setOnMouseClicked(event -> {
            panel1.setVisible(true);

            FadeTransition fadeTransition1 = new FadeTransition(Duration.seconds(0.4),panel1);
            fadeTransition1.setFromValue(0);
            fadeTransition1.setToValue(0.15);
            fadeTransition1.play();

            TranslateTransition translateTransition1 = new TranslateTransition(Duration.seconds(0.4),panel2);
            translateTransition1.setByX(+600);
            translateTransition1.play();
        });

        panel1.setOnMouseClicked(event -> {
            FadeTransition fadeTransition1 = new FadeTransition(Duration.seconds(0.4),panel1);
            fadeTransition1.setFromValue(0.15);
            fadeTransition1.setToValue(0);
            fadeTransition1.play();

            fadeTransition1.setOnFinished(event1 -> panel1.setVisible(false));

            TranslateTransition translateTransition1 = new TranslateTransition(Duration.seconds(0.4),panel2);
            translateTransition1.setByX(-600);
            translateTransition1.play();
        });
    }

    public static void setCredentials(TextField webName, TextField username, TextField password) {
        webName.setStyle("-fx-background-color: rgba(91, 155, 233, 0.78); " +
                "-fx-text-fill: white; ");
        webName.setPromptText("Name Application");

        username.setStyle("-fx-background-color: rgba(91, 155, 233, 0.78); " +

                "-fx-text-fill: white; ");
        username.setPromptText("Username");

        password.setStyle("-fx-background-color: rgba(91, 155, 233, 0.78); " +

                "-fx-text-fill: white; ");
        password.setPromptText("Password");
    }

    public static void textAreaNotEditable(TextArea txtArea) {
        txtArea.setEditable(false);
        txtArea.setMouseTransparent(true);
        txtArea.setFocusTraversable(false);
    }
}
