/****************************************************************************
** Meta object code from reading C++ file 'main_window_state.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../jelyazka/JelayzkaStateMachine/main_window_state.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window_state.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindowState_t {
    QByteArrayData data[4];
    char stringdata0[47];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindowState_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindowState_t qt_meta_stringdata_MainWindowState = {
    {
QT_MOC_LITERAL(0, 0, 15), // "MainWindowState"
QT_MOC_LITERAL(1, 16, 14), // "hideMainWindow"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 14) // "showMainWindow"

    },
    "MainWindowState\0hideMainWindow\0\0"
    "showMainWindow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindowState[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindowState::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindowState *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->hideMainWindow(); break;
        case 1: _t->showMainWindow(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindowState::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindowState::hideMainWindow)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindowState::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindowState::showMainWindow)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MainWindowState::staticMetaObject = { {
    &Jelyazka::IState::staticMetaObject,
    qt_meta_stringdata_MainWindowState.data,
    qt_meta_data_MainWindowState,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindowState::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindowState::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindowState.stringdata0))
        return static_cast<void*>(this);
    return Jelyazka::IState::qt_metacast(_clname);
}

int MainWindowState::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Jelyazka::IState::qt_metacall(_c, _id, _a);
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
void MainWindowState::hideMainWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindowState::showMainWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
