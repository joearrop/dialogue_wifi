/****************************************************************************
** Meta object code from reading C++ file 'LinkThreadGUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../slave00/LinkThreadGUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LinkThreadGUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LinkThreadGUI_t {
    QByteArrayData data[7];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LinkThreadGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LinkThreadGUI_t qt_meta_stringdata_LinkThreadGUI = {
    {
QT_MOC_LITERAL(0, 0, 13), // "LinkThreadGUI"
QT_MOC_LITERAL(1, 14, 14), // "feedback_PCSOL"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 3), // "msg"
QT_MOC_LITERAL(4, 34, 16), // "feedback_Chariot"
QT_MOC_LITERAL(5, 51, 10), // "UI_Command"
QT_MOC_LITERAL(6, 62, 3) // "cmd"

    },
    "LinkThreadGUI\0feedback_PCSOL\0\0msg\0"
    "feedback_Chariot\0UI_Command\0cmd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LinkThreadGUI[] = {

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
       4,    1,   32,    2, 0x06 /* Public */,
       5,    1,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void LinkThreadGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LinkThreadGUI *_t = static_cast<LinkThreadGUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->feedback_PCSOL((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->feedback_Chariot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->UI_Command((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (LinkThreadGUI::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinkThreadGUI::feedback_PCSOL)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (LinkThreadGUI::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinkThreadGUI::feedback_Chariot)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (LinkThreadGUI::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinkThreadGUI::UI_Command)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject LinkThreadGUI::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LinkThreadGUI.data,
      qt_meta_data_LinkThreadGUI,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *LinkThreadGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LinkThreadGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LinkThreadGUI.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LinkThreadGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void LinkThreadGUI::feedback_PCSOL(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LinkThreadGUI::feedback_Chariot(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LinkThreadGUI::UI_Command(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
