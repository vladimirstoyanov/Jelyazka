/****************************************************************************
** Meta object code from reading C++ file 'refresh_rss_data.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../jelyazka/RSS/refresh_rss_data.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'refresh_rss_data.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RefreshRssData_t {
    QByteArrayData data[14];
    char stringdata0[205];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RefreshRssData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RefreshRssData_t qt_meta_stringdata_RefreshRssData = {
    {
QT_MOC_LITERAL(0, 0, 14), // "RefreshRssData"
QT_MOC_LITERAL(1, 15, 14), // "rssDataUpdated"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 20), // "std::vector<RSSData>"
QT_MOC_LITERAL(4, 52, 18), // "onDownloadFinished"
QT_MOC_LITERAL(5, 71, 22), // "onFavoriteFeedsChanged"
QT_MOC_LITERAL(6, 94, 21), // "onStartRssRefreshData"
QT_MOC_LITERAL(7, 116, 20), // "onStopRssRefreshData"
QT_MOC_LITERAL(8, 137, 9), // "onTimeout"
QT_MOC_LITERAL(9, 147, 18), // "onTimeValueChanged"
QT_MOC_LITERAL(10, 166, 9), // "time_msec"
QT_MOC_LITERAL(11, 176, 11), // "onWriteData"
QT_MOC_LITERAL(12, 188, 7), // "RSSData"
QT_MOC_LITERAL(13, 196, 8) // "rss_data"

    },
    "RefreshRssData\0rssDataUpdated\0\0"
    "std::vector<RSSData>\0onDownloadFinished\0"
    "onFavoriteFeedsChanged\0onStartRssRefreshData\0"
    "onStopRssRefreshData\0onTimeout\0"
    "onTimeValueChanged\0time_msec\0onWriteData\0"
    "RSSData\0rss_data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RefreshRssData[] = {

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
       4,    0,   57,    2, 0x0a /* Public */,
       5,    0,   58,    2, 0x0a /* Public */,
       6,    0,   59,    2, 0x0a /* Public */,
       7,    0,   60,    2, 0x0a /* Public */,
       8,    0,   61,    2, 0x0a /* Public */,
       9,    1,   62,    2, 0x0a /* Public */,
      11,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, 0x80000000 | 12,   13,

       0        // eod
};

void RefreshRssData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RefreshRssData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rssDataUpdated((*reinterpret_cast< std::vector<RSSData>(*)>(_a[1]))); break;
        case 1: _t->onDownloadFinished(); break;
        case 2: _t->onFavoriteFeedsChanged(); break;
        case 3: _t->onStartRssRefreshData(); break;
        case 4: _t->onStopRssRefreshData(); break;
        case 5: _t->onTimeout(); break;
        case 6: _t->onTimeValueChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 7: _t->onWriteData((*reinterpret_cast< const RSSData(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RefreshRssData::*)(std::vector<RSSData> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RefreshRssData::rssDataUpdated)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RefreshRssData::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_RefreshRssData.data,
    qt_meta_data_RefreshRssData,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RefreshRssData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RefreshRssData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RefreshRssData.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RefreshRssData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void RefreshRssData::rssDataUpdated(std::vector<RSSData> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
