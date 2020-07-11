/****************************************************************************
** Meta object code from reading C++ file 'rss_search_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../jelyazka/GUI/rss_search_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rss_search_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RSSSearchGUI_t {
    QByteArrayData data[16];
    char stringdata0[210];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RSSSearchGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RSSSearchGUI_t qt_meta_stringdata_RSSSearchGUI = {
    {
QT_MOC_LITERAL(0, 0, 12), // "RSSSearchGUI"
QT_MOC_LITERAL(1, 13, 12), // "stateChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 16), // "onChangeUrlLabel"
QT_MOC_LITERAL(4, 44, 3), // "url"
QT_MOC_LITERAL(5, 48, 11), // "onEndOfUrls"
QT_MOC_LITERAL(6, 60, 10), // "onFoundRSS"
QT_MOC_LITERAL(7, 71, 4), // "name"
QT_MOC_LITERAL(8, 76, 8), // "encoding"
QT_MOC_LITERAL(9, 85, 10), // "web_source"
QT_MOC_LITERAL(10, 96, 7), // "version"
QT_MOC_LITERAL(11, 104, 22), // "on_addRssFeeds_clicked"
QT_MOC_LITERAL(12, 127, 23), // "on_removeButton_clicked"
QT_MOC_LITERAL(13, 151, 23), // "on_searchButton_clicked"
QT_MOC_LITERAL(14, 175, 19), // "on_modelItemChanged"
QT_MOC_LITERAL(15, 195, 14) // "QStandardItem*"

    },
    "RSSSearchGUI\0stateChanged\0\0onChangeUrlLabel\0"
    "url\0onEndOfUrls\0onFoundRSS\0name\0"
    "encoding\0web_source\0version\0"
    "on_addRssFeeds_clicked\0on_removeButton_clicked\0"
    "on_searchButton_clicked\0on_modelItemChanged\0"
    "QStandardItem*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RSSSearchGUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   57,    2, 0x0a /* Public */,
       5,    0,   60,    2, 0x0a /* Public */,
       6,    5,   61,    2, 0x0a /* Public */,
      11,    0,   72,    2, 0x08 /* Private */,
      12,    0,   73,    2, 0x08 /* Private */,
      13,    0,   74,    2, 0x08 /* Private */,
      14,    1,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,    7,    4,    8,    9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,    2,

       0        // eod
};

void RSSSearchGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RSSSearchGUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->onChangeUrlLabel((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->onEndOfUrls(); break;
        case 3: _t->onFoundRSS((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const int(*)>(_a[5]))); break;
        case 4: _t->on_addRssFeeds_clicked(); break;
        case 5: _t->on_removeButton_clicked(); break;
        case 6: _t->on_searchButton_clicked(); break;
        case 7: _t->on_modelItemChanged((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RSSSearchGUI::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RSSSearchGUI::stateChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RSSSearchGUI::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void RSSSearchGUI::stateChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
