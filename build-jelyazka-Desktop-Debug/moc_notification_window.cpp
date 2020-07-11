/****************************************************************************
** Meta object code from reading C++ file 'notification_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../jelyazka/GUI/notification_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'notification_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NotificationWindow_t {
    QByteArrayData data[7];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NotificationWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NotificationWindow_t qt_meta_stringdata_NotificationWindow = {
    {
QT_MOC_LITERAL(0, 0, 18), // "NotificationWindow"
QT_MOC_LITERAL(1, 19, 23), // "onHideAnimationFinished"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 16), // "onRssDataUpdated"
QT_MOC_LITERAL(4, 61, 20), // "std::vector<RSSData>"
QT_MOC_LITERAL(5, 82, 19), // "onShowAnimateWindow"
QT_MOC_LITERAL(6, 102, 23) // "onShowAnimationFinished"

    },
    "NotificationWindow\0onHideAnimationFinished\0"
    "\0onRssDataUpdated\0std::vector<RSSData>\0"
    "onShowAnimateWindow\0onShowAnimationFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NotificationWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    1,   35,    2, 0x0a /* Public */,
       5,    1,   38,    2, 0x0a /* Public */,
       6,    0,   41,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

       0        // eod
};

void NotificationWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NotificationWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onHideAnimationFinished(); break;
        case 1: _t->onRssDataUpdated((*reinterpret_cast< std::vector<RSSData>(*)>(_a[1]))); break;
        case 2: _t->onShowAnimateWindow((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->onShowAnimationFinished(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NotificationWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_NotificationWindow.data,
    qt_meta_data_NotificationWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NotificationWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NotificationWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NotificationWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int NotificationWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
