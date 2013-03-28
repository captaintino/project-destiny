/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Mar 27 20:22:19 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *btnStart;
    QPushButton *btnInstructions;
    QPushButton *btnHighScores;
    QPushButton *btnMultiplayer;
    QPushButton *btnLoad;
    QPushButton *btnCheat;
    QSpinBox *spinCheat;
    QLabel *lblLevel;
    QLineEdit *lnUsername;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(800, 600);
        MainWindow->setMaximumSize(QSize(800, 600));
        MainWindow->setMouseTracking(true);
        MainWindow->setContextMenuPolicy(Qt::NoContextMenu);
        MainWindow->setAutoFillBackground(false);
        label = new QLabel(MainWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(true);
        label->setGeometry(QRect(0, 0, 800, 600));
        label->setCursor(QCursor(Qt::PointingHandCursor));
        label->setMouseTracking(true);
        label->setAutoFillBackground(true);
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/Main_Menu.jpg")));
        label->setScaledContents(true);
        layoutWidget = new QWidget(MainWindow);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(240, 220, 321, 281));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btnStart = new QPushButton(layoutWidget);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        QFont font;
        font.setFamily(QString::fromUtf8("FreeMono"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        btnStart->setFont(font);
        btnStart->setCursor(QCursor(Qt::PointingHandCursor));
        btnStart->setFlat(true);

        verticalLayout->addWidget(btnStart);

        btnInstructions = new QPushButton(layoutWidget);
        btnInstructions->setObjectName(QString::fromUtf8("btnInstructions"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("FreeMono"));
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        btnInstructions->setFont(font1);
        btnInstructions->setFlat(true);

        verticalLayout->addWidget(btnInstructions);

        btnHighScores = new QPushButton(layoutWidget);
        btnHighScores->setObjectName(QString::fromUtf8("btnHighScores"));
        btnHighScores->setFont(font);
        btnHighScores->setFlat(true);

        verticalLayout->addWidget(btnHighScores);

        btnMultiplayer = new QPushButton(layoutWidget);
        btnMultiplayer->setObjectName(QString::fromUtf8("btnMultiplayer"));
        btnMultiplayer->setFont(font);
        btnMultiplayer->setFlat(true);

        verticalLayout->addWidget(btnMultiplayer);

        btnLoad = new QPushButton(layoutWidget);
        btnLoad->setObjectName(QString::fromUtf8("btnLoad"));
        btnLoad->setFont(font);
        btnLoad->setFlat(true);

        verticalLayout->addWidget(btnLoad);

        btnCheat = new QPushButton(layoutWidget);
        btnCheat->setObjectName(QString::fromUtf8("btnCheat"));
        btnCheat->setFont(font);
        btnCheat->setFlat(true);

        verticalLayout->addWidget(btnCheat);

        spinCheat = new QSpinBox(MainWindow);
        spinCheat->setObjectName(QString::fromUtf8("spinCheat"));
        spinCheat->setGeometry(QRect(420, 500, 60, 27));
        spinCheat->setFrame(false);
        spinCheat->setMinimum(1);
        lblLevel = new QLabel(MainWindow);
        lblLevel->setObjectName(QString::fromUtf8("lblLevel"));
        lblLevel->setGeometry(QRect(340, 500, 81, 20));
        lblLevel->setFont(font1);
        lnUsername = new QLineEdit(MainWindow);
        lnUsername->setObjectName(QString::fromUtf8("lnUsername"));
        lnUsername->setGeometry(QRect(340, 180, 113, 27));
        label->raise();
        layoutWidget->raise();
        lblLevel->raise();
        spinCheat->raise();
        lnUsername->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Asteroids & Aliens", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        btnStart->setText(QApplication::translate("MainWindow", "Start Game", 0, QApplication::UnicodeUTF8));
        btnInstructions->setText(QApplication::translate("MainWindow", "Instructions", 0, QApplication::UnicodeUTF8));
        btnHighScores->setText(QApplication::translate("MainWindow", "High Scores", 0, QApplication::UnicodeUTF8));
        btnMultiplayer->setText(QApplication::translate("MainWindow", "Multiplayer", 0, QApplication::UnicodeUTF8));
        btnLoad->setText(QApplication::translate("MainWindow", "Load Game", 0, QApplication::UnicodeUTF8));
        btnCheat->setText(QApplication::translate("MainWindow", "Cheat Mode: OFF", 0, QApplication::UnicodeUTF8));
        lblLevel->setText(QApplication::translate("MainWindow", "Level:", 0, QApplication::UnicodeUTF8));
        lnUsername->setText(QApplication::translate("MainWindow", "Player", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
