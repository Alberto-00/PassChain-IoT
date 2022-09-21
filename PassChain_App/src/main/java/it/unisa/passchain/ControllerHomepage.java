package it.unisa.passchain;

import it.unisa.passchain.utils.Design;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.control.TextArea;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class ControllerHomepage implements Initializable {

    @FXML
    private AnchorPane panel1, panel2, rootPane;

    @FXML
    private ImageView menu;

    @FXML
    private TextArea txtArea;

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        Design.setSidebar(panel1, panel2, menu);
        Design.textAreaNotEditable(txtArea);
    }

    @FXML
    private void loadHomePage() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("fxml/homepage.fxml"));
        AnchorPane pane = fxmlLoader.load();
        rootPane.getChildren().setAll(pane);
    }

    @FXML
    private void loadAddPage() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("fxml/add.fxml"));
        AnchorPane pane = fxmlLoader.load();
        rootPane.getChildren().setAll(pane);
    }

    @FXML
    private void loadUpdatePage() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("fxml/update.fxml"));
        AnchorPane pane = fxmlLoader.load();
        rootPane.getChildren().setAll(pane);
    }
}
