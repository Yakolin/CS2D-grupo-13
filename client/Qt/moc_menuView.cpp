/****************************************************************************
** Meta object code from reading C++ file 'menuView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>

#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>

#include "menuView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menuView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MenuView_t {
    QByteArrayData data[5];
    char stringdata0[48];
};
#define QT_MOC_LITERAL(idx, ofs, len)                                                  \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(                           \
            len, qptrdiff(offsetof(qt_meta_stringdata_MenuView_t, stringdata0) + ofs - \
                          idx * sizeof(QByteArrayData)))
static const qt_meta_stringdata_MenuView_t qt_meta_stringdata_MenuView = {
        {
                QT_MOC_LITERAL(0, 0, 8),    // "MenuView"
                QT_MOC_LITERAL(1, 9, 13),   // "opcionElegida"
                QT_MOC_LITERAL(2, 23, 0),   // ""
                QT_MOC_LITERAL(3, 24, 16),  // "LobbyCommandType"
                QT_MOC_LITERAL(4, 41, 6)    // "opcion"

        },
        "MenuView\0opcionElegida\0\0LobbyCommandType\0"
        "opcion"};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MenuView[] = {

        // content:
        8,      // revision
        0,      // classname
        0, 0,   // classinfo
        1, 14,  // methods
        0, 0,   // properties
        0, 0,   // enums/sets
        0, 0,   // constructors
        0,      // flags
        1,      // signalCount

        // signals: name, argc, parameters, tag, flags
        1, 1, 19, 2, 0x06 /* Public */,

        // signals: parameters
        QMetaType::Void, 0x80000000 | 3, 4,

        0  // eod
};

void MenuView::qt_static_metacall(QObject* _o, QMetaObject::Call _c, int _id, void** _a) {
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto* _t = static_cast<MenuView*>(_o);
        (void)_t;
        switch (_id) {
            case 0:
                _t->opcionElegida((*reinterpret_cast<LobbyCommandType(*)>(_a[1])));
                break;
            default:;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int* result = reinterpret_cast<int*>(_a[0]);
        {
            using _t = void (MenuView::*)(LobbyCommandType);
            if (*reinterpret_cast<_t*>(_a[1]) == static_cast<_t>(&MenuView::opcionElegida)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MenuView::staticMetaObject = {
        {QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
         qt_meta_stringdata_MenuView.data, qt_meta_data_MenuView, qt_static_metacall, nullptr,
         nullptr}};


const QMetaObject* MenuView::metaObject() const {
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void* MenuView::qt_metacast(const char* _clname) {
    if (!_clname)
        return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MenuView.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int MenuView::qt_metacall(QMetaObject::Call _c, int _id, void** _a) {
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void MenuView::opcionElegida(LobbyCommandType _t1) {
    void* _a[] = {nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1)))};
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
