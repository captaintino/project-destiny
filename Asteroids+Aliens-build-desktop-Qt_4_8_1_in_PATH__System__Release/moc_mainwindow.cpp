/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed Mar 27 20:37:02 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Asteroids+Aliens/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      34,   11,   11,   11, 0x08,
      53,   11,   11,   11, 0x08,
      72,   11,   11,   11, 0x08,
      83,   11,   11,   11, 0x08,
     101,   11,   11,   11, 0x08,
     118,   11,   11,   11, 0x08,
     132,   11,   11,   11, 0x08,
     148,   11,   11,   11, 0x08,
     162,   11,   11,   11, 0x08,
     191,   11,   11,   11, 0x08,
     218,   11,   11,   11, 0x08,
     240,   11,   11,   11, 0x08,
     268,   11,   11,   11, 0x08,
     291,  289,   11,   11, 0x08,
     317,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_btnStart_clicked()\0"
    "rotateBackground()\0update_positions()\0"
    "levelEnd()\0userShipCrashed()\0"
    "makeProjectile()\0deleteLabel()\0"
    "levelFinished()\0resumeLevel()\0"
    "on_btnInstructions_clicked()\0"
    "on_btnHighScores_clicked()\0"
    "on_btnCheat_clicked()\0on_btnMultiplayer_clicked()\0"
    "on_btnLoad_clicked()\0e\0keyPressEvent(QKeyEvent*)\0"
    "on_lnUsername_editingFinished()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_btnStart_clicked(); break;
        case 1: _t->rotateBackground(); break;
        case 2: _t->update_positions(); break;
        case 3: _t->levelEnd(); break;
        case 4: _t->userShipCrashed(); break;
        case 5: _t->makeProjectile(); break;
        case 6: _t->deleteLabel(); break;
        case 7: _t->levelFinished(); break;
        case 8: _t->resumeLevel(); break;
        case 9: _t->on_btnInstructions_clicked(); break;
        case 10: _t->on_btnHighScores_clicked(); break;
        case 11: _t->on_btnCheat_clicked(); break;
        case 12: _t->on_btnMultiplayer_clicked(); break;
        case 13: _t->on_btnLoad_clicked(); break;
        case 14: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 15: _t->on_lnUsername_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
