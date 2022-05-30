/****************************************************************************
** Meta object code from reading C++ file 'outputwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Kurs/outputwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'outputwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OutputWidget_t {
    QByteArrayData data[11];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OutputWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OutputWidget_t qt_meta_stringdata_OutputWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "OutputWidget"
QT_MOC_LITERAL(1, 13, 7), // "setText"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 6), // "Script"
QT_MOC_LITERAL(4, 29, 22), // "QVector<DiagramItem*>&"
QT_MOC_LITERAL(5, 52, 12), // "createScript"
QT_MOC_LITERAL(6, 65, 10), // "loadScript"
QT_MOC_LITERAL(7, 76, 11), // "getHtmlLine"
QT_MOC_LITERAL(8, 88, 4), // "line"
QT_MOC_LITERAL(9, 93, 5), // "style"
QT_MOC_LITERAL(10, 99, 21) // "on_pushButton_clicked"

    },
    "OutputWidget\0setText\0\0Script\0"
    "QVector<DiagramItem*>&\0createScript\0"
    "loadScript\0getHtmlLine\0line\0style\0"
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OutputWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x0a /* Public */,
       3,    1,   52,    2, 0x0a /* Public */,
       5,    1,   55,    2, 0x0a /* Public */,
       6,    1,   58,    2, 0x0a /* Public */,
       7,    2,   61,    2, 0x0a /* Public */,
       7,    1,   66,    2, 0x2a /* Public | MethodCloned */,
      10,    0,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::QString, QMetaType::Int,    2,
    QMetaType::QString, QMetaType::QString,    2,
    QMetaType::QString, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::QString, QMetaType::QString,    8,
    QMetaType::Void,

       0        // eod
};

void OutputWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OutputWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->Script((*reinterpret_cast< QVector<DiagramItem*>(*)>(_a[1]))); break;
        case 2: { QString _r = _t->createScript((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 3: { QString _r = _t->loadScript((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 4: { QString _r = _t->getHtmlLine((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 5: { QString _r = _t->getHtmlLine((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject OutputWidget::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_OutputWidget.data,
    qt_meta_data_OutputWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OutputWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OutputWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OutputWidget.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int OutputWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
