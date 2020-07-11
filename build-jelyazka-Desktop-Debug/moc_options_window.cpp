/****************************************************************************
** Meta object code from reading C++ file 'options_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../jelyazka/GUI/options_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'options_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OptionsWindow_t {
    QByteArrayData data[14];
    char stringdata0[235];
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
QT_MOC_LITERAL(3, 28, 19), // "on_okButton_clicked"
QT_MOC_LITERAL(4, 48, 23), // "on_cancelButton_clicked"
QT_MOC_LITERAL(5, 72, 21), // "on_treeWidget_clicked"
QT_MOC_LITERAL(6, 94, 11), // "QModelIndex"
QT_MOC_LITERAL(7, 106, 5), // "index"
QT_MOC_LITERAL(8, 112, 26), // "on_cb_enable_proxy_clicked"
QT_MOC_LITERAL(9, 139, 30), // "on_cb_enable_filtering_clicked"
QT_MOC_LITERAL(10, 170, 24), // "on_pb_add_filter_clicked"
QT_MOC_LITERAL(11, 195, 19), // "on_pb_remove_filter"
QT_MOC_LITERAL(12, 215, 14), // "on_textChanged"
QT_MOC_LITERAL(13, 230, 4) // "text"

    },
    "OptionsWindow\0stateChanged\0\0"
    "on_okButton_clicked\0on_cancelButton_clicked\0"
    "on_treeWidget_clicked\0QModelIndex\0"
    "index\0on_cb_enable_proxy_clicked\0"
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
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   62,    2, 0x08 /* Private */,
       4,    0,   63,    2, 0x08 /* Private */,
       5,    1,   64,    2, 0x08 /* Private */,
       8,    1,   67,    2, 0x08 /* Private */,
       9,    1,   70,    2, 0x08 /* Private */,
      10,    0,   73,    2, 0x08 /* Private */,
      11,    0,   74,    2, 0x08 /* Private */,
      12,    1,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,

       0        // eod
};

void OptionsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OptionsWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_okButton_clicked(); break;
        case 2: _t->on_cancelButton_clicked(); break;
        case 3: _t->on_treeWidget_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->on_cb_enable_proxy_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_cb_enable_filtering_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_pb_add_filter_clicked(); break;
        case 7: _t->on_pb_remove_filter(); break;
        case 8: _t->on_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
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
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
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
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void OptionsWindow::stateChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
