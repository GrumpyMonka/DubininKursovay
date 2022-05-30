/****************************************************************************
** Meta object code from reading C++ file 'sparqlblockwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Kurs/sparqlblockwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sparqlblockwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SparqlBlockWindow_t {
    QByteArrayData data[11];
    char stringdata0[151];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SparqlBlockWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SparqlBlockWindow_t qt_meta_stringdata_SparqlBlockWindow = {
    {
QT_MOC_LITERAL(0, 0, 17), // "SparqlBlockWindow"
QT_MOC_LITERAL(1, 18, 21), // "newSparqlBlockCreated"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 17), // "BasedBlockSetting"
QT_MOC_LITERAL(4, 59, 10), // "updateSize"
QT_MOC_LITERAL(5, 70, 12), // "updateSlider"
QT_MOC_LITERAL(6, 83, 12), // "itemSelected"
QT_MOC_LITERAL(7, 96, 12), // "DiagramItem*"
QT_MOC_LITERAL(8, 109, 10), // "addNewArea"
QT_MOC_LITERAL(9, 120, 12), // "addNewObject"
QT_MOC_LITERAL(10, 133, 17) // "createSparqlBlock"

    },
    "SparqlBlockWindow\0newSparqlBlockCreated\0"
    "\0BasedBlockSetting\0updateSize\0"
    "updateSlider\0itemSelected\0DiagramItem*\0"
    "addNewArea\0addNewObject\0createSparqlBlock"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SparqlBlockWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   52,    2, 0x0a /* Public */,
       5,    0,   53,    2, 0x0a /* Public */,
       6,    1,   54,    2, 0x0a /* Public */,
       8,    0,   57,    2, 0x0a /* Public */,
       9,    0,   58,    2, 0x0a /* Public */,
      10,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SparqlBlockWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SparqlBlockWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newSparqlBlockCreated((*reinterpret_cast< BasedBlockSetting(*)>(_a[1]))); break;
        case 1: _t->updateSize(); break;
        case 2: _t->updateSlider(); break;
        case 3: _t->itemSelected((*reinterpret_cast< DiagramItem*(*)>(_a[1]))); break;
        case 4: _t->addNewArea(); break;
        case 5: _t->addNewObject(); break;
        case 6: _t->createSparqlBlock(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SparqlBlockWindow::*)(BasedBlockSetting );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SparqlBlockWindow::newSparqlBlockCreated)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SparqlBlockWindow::staticMetaObject = { {
    &DiagramView::staticMetaObject,
    qt_meta_stringdata_SparqlBlockWindow.data,
    qt_meta_data_SparqlBlockWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SparqlBlockWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SparqlBlockWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SparqlBlockWindow.stringdata0))
        return static_cast<void*>(this);
    return DiagramView::qt_metacast(_clname);
}

int SparqlBlockWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DiagramView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void SparqlBlockWindow::newSparqlBlockCreated(BasedBlockSetting _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
