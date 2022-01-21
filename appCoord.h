//
// Created by HarcioGG on 5/18/2021.
//

#ifndef GUIHOMEWORK_APPCOORD_H
#define GUIHOMEWORK_APPCOORD_H


class appCoord : public QWidget {
private:
    QPushButton *adminButton, *userButton, *closeButton;
public:
    appCoord();

private:
    void initGUI();
    void connectSignalsAndSlots();

    static void runAdminMode();
    static void runUserMode();
    void closeApp();
};

#endif //GUIHOMEWORK_APPCOORD_H
