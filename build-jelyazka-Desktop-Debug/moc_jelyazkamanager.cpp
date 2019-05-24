/****************************************************************************
** Meta object code from reading C++ file 'jelyazkamanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../jelyazka/jelyazkamanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jelyazkamanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_JelyazkaManager_t {
    QByteArrayData data[17];
    char stringdata0[280];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JelyazkaManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JelyazkaManager_t qt_meta_stringdata_JelyazkaManager = {
    {
QT_MOC_LITERAL(0, 0, 15), // "JelyazkaManager"
QT_MOC_LITERAL(1, 16, 12), // "stateChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 17), // "onHideAboutWindow"
QT_MOC_LITERAL(4, 48, 16), // "onHideHelpWindow"
QT_MOC_LITERAL(5, 65, 16), // "onHideInitWindow"
QT_MOC_LITERAL(6, 82, 16), // "onHideMainWindow"
QT_MOC_LITERAL(7, 99, 18), // "onHideOptionWindow"
QT_MOC_LITERAL(8, 118, 21), // "onHideRssSearchWindow"
QT_MOC_LITERAL(9, 140, 14), // "onHideTrayIcon"
QT_MOC_LITERAL(10, 155, 17), // "onShowAboutWindow"
QT_MOC_LITERAL(11, 173, 16), // "onShowHelpWindow"
QT_MOC_LITERAL(12, 190, 16), // "onShowInitWindow"
QT_MOC_LITERAL(13, 207, 16), // "onShowMainWindow"
QT_MOC_LITERAL(14, 224, 18), // "onShowOptionWindow"
QT_MOC_LITERAL(15, 243, 21), // "onShowRssSearchWindow"
QT_MOC_LITERAL(16, 265, 14) // "onShowTrayIcon"

    },
    "JelyazkaManager\0stateChanged\0\0"
    "onHideAboutWindow\0onHideHelpWindow\0"
    "onHideInitWindow\0onHideMainWindow\0"
    "onHideOptionWindow\0onHideRssSearchWindow\0"
    "onHideTrayIcon\0onShowAboutWindow\0"
    "onShowHelpWindow\0onShowInitWindow\0"
    "onShowMainWindow\0onShowOptionWindow\0"
    "onShowRssSearchWindow\0onShowTrayIcon"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JelyazkaManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   92,    2, 0x0a /* Public */,
       4,    0,   93,    2, 0x0a /* Public */,
       5,    0,   94,    2, 0x0a /* Public */,
       6,    0,   95,    2, 0x0a /* Public */,
       7,    0,   96,    2, 0x0a /* Public */,
       8,    0,   97,    2, 0x0a /* Public */,
       9,    0,   98,    2, 0x0a /* Public */,
      10,    0,   99,    2, 0x0a /* Public */,
      11,    0,  100,    2, 0x0a /* Public */,
      12,    0,  101,    2, 0x0a /* Public */,
      13,    0,  102,    2, 0x0a /* Public */,
      14,    0,  103,    2, 0x0a /* Public */,
      15,    0,  104,    2, 0x0a /* Public */,
      16,    0,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void JelyazkaManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<JelyazkaManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->onHideAboutWindow(); break;
        case 2: _t->onHideHelpWindow(); break;
        case 3: _t->onHideInitWindow(); break;
        case 4: _t->onHideMainWindow(); break;
        case 5: _t->onHideOptionWindow(); break;
        case 6: _t->onHideRssSearchWindow(); break;
        case 7: _t->onHideTrayIcon(); break;
        case 8: _t->onShowAboutWindow(); break;
        case 9: _t->onShowHelpWindow(); break;
        case 10: _t->onShowInitWindow(); break;
        case 11: _t->onShowMainWindow(); break;
        case 12: _t->onShowOptionWindow(); break;
        case 13: _t->onShowRssSearchWindow(); break;
        case 14: _t->onShowTrayIcon(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (JelyazkaManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&JelyazkaManager::stateChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject JelyazkaManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_JelyazkaManager.data,
    qt_meta_data_JelyazkaManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *JelyazkaManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JelyazkaManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_JelyazkaManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int JelyazkaManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void JelyazkaManager::stateChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
