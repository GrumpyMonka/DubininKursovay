/****************************************************************************
** Meta object code from reading C++ file 'diagramview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Kurs/diagramview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'diagramview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DiagramView_t {
    QByteArrayData data[9];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DiagramView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DiagramView_t qt_meta_stringdata_DiagramView = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DiagramView"
QT_MOC_LITERAL(1, 12, 5), // "paint"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 8), // "setScene"
QT_MOC_LITERAL(4, 28, 13), // "DiagramScene*"
QT_MOC_LITERAL(5, 42, 5), // "scene"
QT_MOC_LITERAL(6, 48, 13), // "updatePosForm"
QT_MOC_LITERAL(7, 62, 12), // "DiagramItem*"
QT_MOC_LITERAL(8, 75, 14) // "updatePosScene"

    },
    "DiagramView\0paint\0\0setScene\0DiagramScene*\0"
    "scene\0updatePosForm\0DiagramItem*\0"
    "updatePosScene"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DiagramView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    1,   40,    2, 0x0a /* Public */,
       5,    0,   43,    2, 0x0a /* Public */,
       6,    1,   44,    2, 0x0a /* Public */,
       8,    0,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    0x80000000 | 4,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,

       0        // eod
};

void DiagramView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DiagramView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->paint(); break;
        case 1: _t->setScene((*reinterpret_cast< DiagramScene*(*)>(_a[1]))); break;
        case 2: { DiagramScene* _r = _t->scene();
            if (_a[0]) *reinterpret_cast< DiagramScene**>(_a[0]) = std::move(_r); }  break;
        case 3: _t->updatePosForm((*reinterpret_cast< DiagramItem*(*)>(_a[1]))); break;
        case 4: _t->updatePosScene(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DiagramScene* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DiagramView::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_DiagramView.data,
    qt_meta_data_DiagramView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DiagramView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DiagramView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DiagramView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DiagramView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
