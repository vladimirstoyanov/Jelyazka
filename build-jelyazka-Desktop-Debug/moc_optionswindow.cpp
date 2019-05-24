/****************************************************************************
** Meta object code from reading C++ file 'optionswindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../jelyazka/Options/optionswindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'optionswindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OptionsWindow_t {
    QByteArrayData data[22];
    char stringdata0[376];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OptionsWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OptionsWindow_t qt_meta_stringdata_OptionsWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "OptionsWindow"
QT_MOC_LITERAL(1, 14, 12), // "stateChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "onFinish"
QT_MOC_LITERAL(4, 37, 4), // "name"
QT_MOC_LITERAL(5, 42, 6), // "finish"
QT_MOC_LITERAL(6, 49, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(7, 71, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(8, 95, 20), // "on_OK_Button_clicked"
QT_MOC_LITERAL(9, 116, 24), // "on_Cancel_Button_clicked"
QT_MOC_LITERAL(10, 141, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(11, 165, 30), // "on_collect_feeds_DoubleClicked"
QT_MOC_LITERAL(12, 196, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(13, 213, 21), // "on_treeWidget_clicked"
QT_MOC_LITERAL(14, 235, 11), // "QModelIndex"
QT_MOC_LITERAL(15, 247, 5), // "index"
QT_MOC_LITERAL(16, 253, 26), // "on_cb_enable_proxy_clicked"
QT_MOC_LITERAL(17, 280, 30), // "on_cb_enable_filtering_clicked"
QT_MOC_LITERAL(18, 311, 24), // "on_pb_add_filter_clicked"
QT_MOC_LITERAL(19, 336, 19), // "on_pb_remove_filter"
QT_MOC_LITERAL(20, 356, 14), // "on_textChanged"
QT_MOC_LITERAL(21, 371, 4) // "text"

    },
    "OptionsWindow\0stateChanged\0\0onFinish\0"
    "name\0finish\0on_pushButton_clicked\0"
    "on_pushButton_2_clicked\0on_OK_Button_clicked\0"
    "on_Cancel_Button_clicked\0"
    "on_pushButton_3_clicked\0"
    "on_collect_feeds_DoubleClicked\0"
    "QListWidgetItem*\0on_treeWidget_clicked\0"
    "QModelIndex\0index\0on_cb_enable_proxy_clicked\0"
    "on_cb_enable_filtering_clicked\0"
    "on_pb_add_filter_clicked\0on_pb_remove_filter\0"
    "on_textChanged\0text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OptionsWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   87,    2, 0x0a /* Public */,
       6,    0,   92,    2, 0x08 /* Private */,
       7,    0,   93,    2, 0x08 /* Private */,
       8,    0,   94,    2, 0x08 /* Private */,
       9,    0,   95,    2, 0x08 /* Private */,
      10,    0,   96,    2, 0x08 /* Private */,
      11,    1,   97,    2, 0x08 /* Private */,
      13,    1,  100,    2, 0x08 /* Private */,
      16,    1,  103,    2, 0x08 /* Private */,
      17,    1,  106,    2, 0x08 /* Private */,
      18,    0,  109,    2, 0x08 /* Private */,
      19,    0,  110,    2, 0x08 /* Private */,
      20,    1,  111,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,

       0        // eod
};

void OptionsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OptionsWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->onFinish((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 2: _t->on_pushButton_clicked(); break;
        case 3: _t->on_pushButton_2_clicked(); break;
        case 4: _t->on_OK_Button_clicked(); break;
        case 5: _t->on_Cancel_Button_clicked(); break;
        case 6: _t->on_pushButton_3_clicked(); break;
        case 7: _t->on_collect_feeds_DoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 8: _t->on_treeWidget_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 9: _t->on_cb_enable_proxy_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_cb_enable_filtering_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_pb_add_filter_clicked(); break;
        case 12: _t->on_pb_remove_filter(); break;
        case 13: _t->on_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (OptionsWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OptionsWindow::stateChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject OptionsWindow::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_OptionsWindow.data,
    qt_meta_data_OptionsWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OptionsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OptionsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OptionsWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int OptionsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void OptionsWindow::stateChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
