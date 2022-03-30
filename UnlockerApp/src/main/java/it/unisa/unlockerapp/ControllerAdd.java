package it.unisa.unlockerapp;

import it.unisa.unlockerapp.utils.Design;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;

import java.net.URL;
import java.util.ResourceBundle;

public class ControllerAdd implements Initializable {

    @FXML
    private TextField webName, username, password;

    @FXML
    private TextArea txtArea;

    @FXML
    private AnchorPane panel1, panel2;

    @FXML
    private ImageView menu;

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        Design.setSidebar(panel1, panel2, menu);

        webName.setStyle("-fx-background-color: rgba(91, 155, 233, 0.78); " +
                "-fx-text-fill: white; ");
        webName.setPromptText("Name Application");

        username.setStyle("-fx-background-color: rgba(91, 155, 233, 0.78); " +

                "-fx-text-fill: white; ");
        username.setPromptText("Username");

        password.setStyle("-fx-background-color: rgba(91, 155, 233, 0.78); " +

                "-fx-text-fill: white; ");
        password.setPromptText("Password");

        txtArea.setEditable(false);
        txtArea.setMouseTransparent(true);
        txtArea.setFocusTraversable(false);
    }
}
