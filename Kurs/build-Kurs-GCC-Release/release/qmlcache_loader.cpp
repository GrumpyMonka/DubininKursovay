#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>

static const unsigned char qt_resource_tree[] = {
0,
0,0,0,0,2,0,0,0,1,0,0,0,1,0,0,0,
8,0,2,0,0,0,3,0,0,0,2,0,0,0,92,0,
0,0,0,0,1,0,0,0,0,0,0,0,28,0,0,0,
0,0,1,0,0,0,0,0,0,0,52,0,0,0,0,0,
1,0,0,0,0};
static const unsigned char qt_resource_names[] = {
0,
1,0,0,0,47,0,47,0,7,9,169,7,83,0,115,0,
99,0,114,0,105,0,112,0,116,0,115,0,9,9,7,134,
83,0,115,0,99,0,114,0,105,0,112,0,116,0,46,0,
106,0,115,0,17,13,213,239,243,0,88,0,77,0,76,0,
72,0,116,0,116,0,112,0,82,0,101,0,113,0,117,0,
101,0,115,0,116,0,46,0,106,0,115,0,11,8,37,142,
211,0,112,0,114,0,111,0,103,0,114,0,101,0,115,0,
115,0,46,0,106,0,115};
static const unsigned char qt_resource_empty_payout[] = { 0, 0, 0, 0, 0 };
QT_BEGIN_NAMESPACE
extern Q_CORE_EXPORT bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
QT_END_NAMESPACE
namespace QmlCacheGeneratedCode {
namespace _scripts_progress_js { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _scripts_XMLHttpRequest_js { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _scripts_script_js { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
        resourcePathToCachedUnit.insert(QStringLiteral("/scripts/progress.js"), &QmlCacheGeneratedCode::_scripts_progress_js::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/scripts/XMLHttpRequest.js"), &QmlCacheGeneratedCode::_scripts_XMLHttpRequest_js::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/scripts/script.js"), &QmlCacheGeneratedCode::_scripts_script_js::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.version = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
QT_PREPEND_NAMESPACE(qRegisterResourceData)(/*version*/0x01, qt_resource_tree, qt_resource_names, qt_resource_empty_payout);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_diagramscene)() {
    ::unitRegistry();
    Q_INIT_RESOURCE(diagramscene_qmlcache);
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_diagramscene))
int QT_MANGLE_NAMESPACE(qCleanupResources_diagramscene)() {
    Q_CLEANUP_RESOURCE(diagramscene_qmlcache);
    return 1;
}
