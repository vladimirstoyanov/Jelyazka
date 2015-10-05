/****************************************************************************
** Meta object code from reading C++ file 'web_search_interface_thread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../jelyazka/web_search_interface_thread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'web_search_interface_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WebSearchInterfaceThread_t {
    QByteArrayData data[10];
    char stringdata[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WebSearchInterfaceThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WebSearchInterfaceThread_t qt_meta_stringdata_WebSearchInterfaceThread = {
    {
QT_MOC_LITERAL(0, 0, 24), // "WebSearchInterfaceThread"
QT_MOC_LITERAL(1, 25, 8), // "FoundRSS"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 4), // "type"
QT_MOC_LITERAL(4, 40, 4), // "name"
QT_MOC_LITERAL(5, 45, 3), // "url"
QT_MOC_LITERAL(6, 49, 8), // "encoding"
QT_MOC_LITERAL(7, 58, 10), // "web_source"
QT_MOC_LITERAL(8, 69, 7), // "version"
QT_MOC_LITERAL(9, 77, 9) // "EndOfUrls"

    },
    "WebSearchInterfaceThread\0FoundRSS\0\0"
    "type\0name\0url\0encoding\0web_source\0"
    "version\0EndOfUrls"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WebSearchInterfaceThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    6,   24,    2, 0x06 /* Public */,
       9,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,    3,    4,    5,    6,    7,    8,
    QMetaType::Void,

       0        // eod
};

void WebSearchInterfaceThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WebSearchInterfaceThread *_t = static_cast<WebSearchInterfaceThread *>(_o);
        switch (_id) {
        case 0: _t->FoundRSS((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 1: _t->EndOfUrls(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WebSearchInterfaceThread::*_t)(int , QString , QString , QString , QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WebSearchInterfaceThread::FoundRSS)) {
                *result = 0;
            }
        }
        {
            typedef void (WebSearchInterfaceThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WebSearchInterfaceThread::EndOfUrls)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject WebSearchInterfaceThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WebSearchInterfaceThread.data,
      qt_meta_data_WebSearchInterfaceThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WebSearchInterfaceThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WebSearchInterfaceThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WebSearchInterfaceThread.stringdata))
        return static_cast<void*>(const_cast< WebSearchInterfaceThread*>(this));
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(const_cast< WebSearchInterfaceThread*>(this));
    return QObject::qt_metacast(_clname);
}

int WebSearchInterfaceThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void WebSearchInterfaceThread::FoundRSS(int _t1, QString _t2, QString _t3, QString _t4, QString _t5, int _t6)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WebSearchInterfaceThread::EndOfUrls()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
