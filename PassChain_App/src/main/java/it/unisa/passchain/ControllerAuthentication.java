package it.unisa.passchain;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.control.TextFormatter;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.function.UnaryOperator;
import java.util.regex.Pattern;

public class ControllerAuthentication implements Initializable {
    @FXML
    private TextField otp1, otp2, otp3, otp4, otp5, otp6,
            otp7, otp8, otp9, otp10;

    @FXML
    private Button btnAuthentication;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        setColorOtp(otp1, otp2, otp3, otp4, otp5);
        setColorOtp(otp6, otp7, otp8, otp9, otp10);
    }

    private void setColorOtp(TextField otp1, TextField otp2, TextField otp3, TextField otp4, TextField otp5) {
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

    private void setOtpCharacters(TextField otp){
        var pattern = Pattern.compile(".?");
        TextFormatter formatter = new TextFormatter((UnaryOperator<TextFormatter.Change>)
                change -> pattern.matcher(change.getControlNewText()).matches() ? change : null);
        otp.setTextFormatter(formatter);
    }

    @FXML
    private void handleButtonAction () throws IOException {
        Stage stage = (Stage) btnAuthentication.getScene().getWindow();
        stage.close();

        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("fxml/homepage.fxml"));
        Scene scene = new Scene(fxmlLoader.load());
        stage.setTitle("Unlocker IoT");
        stage.setScene(scene);
        stage.setResizable(false);
        stage.show();
    }
}