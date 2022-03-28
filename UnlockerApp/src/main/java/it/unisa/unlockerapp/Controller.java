package it.unisa.unlockerapp;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TextField;
import javafx.scene.control.TextFormatter;

import java.net.URL;
import java.util.ResourceBundle;
import java.util.function.UnaryOperator;
import java.util.regex.Pattern;

public class Controller implements Initializable {
    @FXML
    private TextField otp1;

    @FXML
    private TextField otp2;

    @FXML
    private TextField otp3;

    @FXML
    private TextField otp4;

    @FXML
    private TextField otp5;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        otp1.setStyle("-fx-background-color: rgba(91, 155, 233, 0.78); " +
                "-fx-highlight-fill: transparent; " +
                "-fx-text-fill: white; ");
        setOtpCharacters(otp1);

        otp2.setStyle("-fx-background-color: rgba(91, 155, 233, 0.78); " +
                "-fx-highlight-fill: transparent; " +
                "-fx-text-fill: white; ");
        setOtpCharacters(otp2);

        otp3.setStyle("-fx-background-color: rgba(91, 155, 233, 0.78); " +
                "-fx-highlight-fill: transparent; " +
                "-fx-text-fill: white; ");
        setOtpCharacters(otp3);

        otp4.setStyle("-fx-background-color: rgba(91, 155, 233, 0.78); " +
                "-fx-highlight-fill: transparent; " +
                "-fx-text-fill: white; ");
        setOtpCharacters(otp4);

        otp5.setStyle("-fx-background-color: rgba(91, 155, 233, 0.78); " +
                "-fx-highlight-fill: transparent; " +
                "-fx-text-fill: white; ");
        setOtpCharacters(otp5);
    }

    protected void setOtpCharacters(TextField otp){
        var pattern = Pattern.compile(".?");
        TextFormatter formatter = new TextFormatter((UnaryOperator<TextFormatter.Change>)
                change -> pattern.matcher(change.getControlNewText()).matches() ? change : null);
        otp.setTextFormatter(formatter);
    }
}