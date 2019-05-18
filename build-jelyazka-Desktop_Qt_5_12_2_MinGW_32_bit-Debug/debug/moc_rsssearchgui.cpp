/****************************************************************************
** Meta object code from reading C++ file 'rsssearchgui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../jelyazka/rsssearchgui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rsssearchgui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RSSSearchGUI_t {
    QByteArrayData data[15];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RSSSearchGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RSSSearchGUI_t qt_meta_stringdata_RSSSearchGUI = {
    {
QT_MOC_LITERAL(0, 0, 12), // "RSSSearchGUI"
QT_MOC_LITERAL(1, 13, 19), // "on_modelItemChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 14), // "QStandardItem*"
QT_MOC_LITERAL(4, 49, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(5, 71, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(6, 95, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(7, 119, 10), // "onFoundRSS"
QT_MOC_LITERAL(8, 130, 4), // "type"
QT_MOC_LITERAL(9, 135, 4), // "name"
QT_MOC_LITERAL(10, 140, 3), // "url"
QT_MOC_LITERAL(11, 144, 8), // "encoding"
QT_MOC_LITERAL(12, 153, 10), // "web_source"
QT_MOC_LITERAL(13, 164, 7), // "version"
QT_MOC_LITERAL(14, 172, 11) // "onEndOfUrls"

    },
    "RSSSearchGUI\0on_modelItemChanged\0\0"
    "QStandardItem*\0on_pushButton_clicked\0"
    "on_pushButton_3_clicked\0on_pushButton_2_clicked\0"
    "onFoundRSS\0type\0name\0url\0encoding\0"
    "web_source\0version\0onEndOfUrls"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RSSSearchGUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       4,    0,   47,    2, 0x08 /* Private */,
       5,    0,   48,    2, 0x08 /* Private */,
       6,    0,   49,    2, 0x08 /* Private */,
       7,    6,   50,    2, 0x0a /* Public */,
      14,    0,   63,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,    8,    9,   10,   11,   12,   13,
    QMetaType::Void,

       0        // eod
};

void RSSSearchGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RSSSearchGUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_modelItemChanged((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_clicked(); break;
        case 2: _t->on_pushButton_3_clicked(); break;
        case 3: _t->on_pushButton_2_clicked(); break;
        case 4: _t->onFoundRSS((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 5: _t->onEndOfUrls(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RSSSearchGUI::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_RSSSearchGUI.data,
    qt_meta_data_RSSSearchGUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RSSSearchGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RSSSearchGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RSSSearchGUI.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RSSSearchGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
