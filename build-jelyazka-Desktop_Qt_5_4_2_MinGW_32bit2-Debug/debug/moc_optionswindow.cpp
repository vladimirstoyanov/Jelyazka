/****************************************************************************
** Meta object code from reading C++ file 'optionswindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../jelyazka/optionswindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'optionswindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OptionsWindow_t {
    QByteArrayData data[19];
    char stringdata[320];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OptionsWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OptionsWindow_t qt_meta_stringdata_OptionsWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "OptionsWindow"
QT_MOC_LITERAL(1, 14, 8), // "onFinish"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "name"
QT_MOC_LITERAL(4, 29, 6), // "finish"
QT_MOC_LITERAL(5, 36, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(6, 58, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(7, 82, 20), // "on_OK_Button_clicked"
QT_MOC_LITERAL(8, 103, 24), // "on_Cancel_Button_clicked"
QT_MOC_LITERAL(9, 128, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(10, 152, 30), // "on_collect_feeds_DoubleClicked"
QT_MOC_LITERAL(11, 183, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(12, 200, 21), // "on_treeWidget_clicked"
QT_MOC_LITERAL(13, 222, 5), // "index"
QT_MOC_LITERAL(14, 228, 26), // "on_cb_enable_proxy_clicked"
QT_MOC_LITERAL(15, 255, 24), // "on_pb_add_filter_clicked"
QT_MOC_LITERAL(16, 280, 19), // "on_pb_remove_filter"
QT_MOC_LITERAL(17, 300, 14), // "on_textChanged"
QT_MOC_LITERAL(18, 315, 4) // "text"

    },
    "OptionsWindow\0onFinish\0\0name\0finish\0"
    "on_pushButton_clicked\0on_pushButton_2_clicked\0"
    "on_OK_Button_clicked\0on_Cancel_Button_clicked\0"
    "on_pushButton_3_clicked\0"
    "on_collect_feeds_DoubleClicked\0"
    "QListWidgetItem*\0on_treeWidget_clicked\0"
    "index\0on_cb_enable_proxy_clicked\0"
    "on_pb_add_filter_clicked\0on_pb_remove_filter\0"
    "on_textChanged\0text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OptionsWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x0a /* Public */,
       5,    0,   79,    2, 0x08 /* Private */,
       6,    0,   80,    2, 0x08 /* Private */,
       7,    0,   81,    2, 0x08 /* Private */,
       8,    0,   82,    2, 0x08 /* Private */,
       9,    0,   83,    2, 0x08 /* Private */,
      10,    1,   84,    2, 0x08 /* Private */,
      12,    1,   87,    2, 0x08 /* Private */,
      14,    1,   90,    2, 0x08 /* Private */,
      15,    0,   93,    2, 0x08 /* Private */,
      16,    0,   94,    2, 0x08 /* Private */,
      17,    1,   95,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, QMetaType::QModelIndex,   13,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,

       0        // eod
};

void OptionsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OptionsWindow *_t = static_cast<OptionsWindow *>(_o);
        switch (_id) {
        case 0: _t->onFinish((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->on_pushButton_clicked(); break;
        case 2: _t->on_pushButton_2_clicked(); break;
        case 3: _t->on_OK_Button_clicked(); break;
        case 4: _t->on_Cancel_Button_clicked(); break;
        case 5: _t->on_pushButton_3_clicked(); break;
        case 6: _t->on_collect_feeds_DoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->on_treeWidget_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: _t->on_cb_enable_proxy_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_pb_add_filter_clicked(); break;
        case 10: _t->on_pb_remove_filter(); break;
        case 11: _t->on_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject OptionsWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_OptionsWindow.data,
      qt_meta_data_OptionsWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OptionsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OptionsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OptionsWindow.stringdata))
        return static_cast<void*>(const_cast< OptionsWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int OptionsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
