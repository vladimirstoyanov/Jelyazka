/****************************************************************************
** Meta object code from reading C++ file 'rssthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../jelyazka/rssthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rssthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RSSThread_t {
    QByteArrayData data[9];
    char stringdata0[65];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RSSThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RSSThread_t qt_meta_stringdata_RSSThread = {
    {
QT_MOC_LITERAL(0, 0, 9), // "RSSThread"
QT_MOC_LITERAL(1, 10, 17), // "showAnimateWindow"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 4), // "data"
QT_MOC_LITERAL(4, 34, 7), // "loadRSS"
QT_MOC_LITERAL(5, 42, 4), // "name"
QT_MOC_LITERAL(6, 47, 3), // "url"
QT_MOC_LITERAL(7, 51, 6), // "Finish"
QT_MOC_LITERAL(8, 58, 6) // "finish"

    },
    "RSSThread\0showAnimateWindow\0\0data\0"
    "loadRSS\0name\0url\0Finish\0finish"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RSSThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    2,   32,    2, 0x06 /* Public */,
       7,    2,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    5,    8,

       0        // eod
};

void RSSThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RSSThread *_t = static_cast<RSSThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showAnimateWindow((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->loadRSS((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->Finish((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RSSThread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RSSThread::showAnimateWindow)) {
                *result = 0;
            }
        }
        {
            typedef void (RSSThread::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RSSThread::loadRSS)) {
                *result = 1;
            }
        }
        {
            typedef void (RSSThread::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RSSThread::Finish)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject RSSThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RSSThread.data,
      qt_meta_data_RSSThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RSSThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RSSThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RSSThread.stringdata0))
        return static_cast<void*>(const_cast< RSSThread*>(this));
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(const_cast< RSSThread*>(this));
    return QObject::qt_metacast(_clname);
}

int RSSThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void RSSThread::showAnimateWindow(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RSSThread::loadRSS(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RSSThread::Finish(QString _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
