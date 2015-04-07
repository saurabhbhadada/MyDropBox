/****************************************************************************
** Meta object code from reading C++ file 'userfiles.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MyDropBox/userfiles.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'userfiles.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UserFiles_t {
    QByteArrayData data[7];
    char stringdata[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UserFiles_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UserFiles_t qt_meta_stringdata_UserFiles = {
    {
QT_MOC_LITERAL(0, 0, 9), // "UserFiles"
QT_MOC_LITERAL(1, 10, 15), // "listItemOnClick"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(4, 44, 17), // "sharedItemOnClick"
QT_MOC_LITERAL(5, 62, 6), // "logOut"
QT_MOC_LITERAL(6, 69, 10) // "uploadFile"

    },
    "UserFiles\0listItemOnClick\0\0QListWidgetItem*\0"
    "sharedItemOnClick\0logOut\0uploadFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UserFiles[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       4,    1,   37,    2, 0x0a /* Public */,
       5,    0,   40,    2, 0x08 /* Private */,
       6,    0,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UserFiles::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UserFiles *_t = static_cast<UserFiles *>(_o);
        switch (_id) {
        case 0: _t->listItemOnClick((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->sharedItemOnClick((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->logOut(); break;
        case 3: _t->uploadFile(); break;
        default: ;
        }
    }
}

const QMetaObject UserFiles::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UserFiles.data,
      qt_meta_data_UserFiles,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UserFiles::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UserFiles::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UserFiles.stringdata))
        return static_cast<void*>(const_cast< UserFiles*>(this));
    return QWidget::qt_metacast(_clname);
}

int UserFiles::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
