/****************************************************************************
** Meta object code from reading C++ file 'web_search.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../jelyazka/web_search.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'web_search.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WebSearchInterface_t {
    QByteArrayData data[15];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WebSearchInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WebSearchInterface_t qt_meta_stringdata_WebSearchInterface = {
    {
QT_MOC_LITERAL(0, 0, 18), // "WebSearchInterface"
QT_MOC_LITERAL(1, 19, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(4, 66, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(5, 90, 19), // "on_modelItemChanged"
QT_MOC_LITERAL(6, 110, 14), // "QStandardItem*"
QT_MOC_LITERAL(7, 125, 10), // "onFoundRSS"
QT_MOC_LITERAL(8, 136, 4), // "type"
QT_MOC_LITERAL(9, 141, 4), // "name"
QT_MOC_LITERAL(10, 146, 3), // "url"
QT_MOC_LITERAL(11, 150, 8), // "encoding"
QT_MOC_LITERAL(12, 159, 10), // "web_source"
QT_MOC_LITERAL(13, 170, 7), // "version"
QT_MOC_LITERAL(14, 178, 11) // "onEndOfUrls"

    },
    "WebSearchInterface\0on_pushButton_clicked\0"
    "\0on_pushButton_3_clicked\0"
    "on_pushButton_2_clicked\0on_modelItemChanged\0"
    "QStandardItem*\0onFoundRSS\0type\0name\0"
    "url\0encoding\0web_source\0version\0"
    "onEndOfUrls"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WebSearchInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    1,   47,    2, 0x08 /* Private */,
       7,    6,   50,    2, 0x0a /* Public */,
      14,    0,   63,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,    8,    9,   10,   11,   12,   13,
    QMetaType::Void,

       0        // eod
};

void WebSearchInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WebSearchInterface *_t = static_cast<WebSearchInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_pushButton_3_clicked(); break;
        case 2: _t->on_pushButton_2_clicked(); break;
        case 3: _t->on_modelItemChanged((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 4: _t->onFoundRSS((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 5: _t->onEndOfUrls(); break;
        default: ;
        }
    }
}

const QMetaObject WebSearchInterface::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WebSearchInterface.data,
      qt_meta_data_WebSearchInterface,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WebSearchInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WebSearchInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WebSearchInterface.stringdata0))
        return static_cast<void*>(const_cast< WebSearchInterface*>(this));
    return QWidget::qt_metacast(_clname);
}

int WebSearchInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
