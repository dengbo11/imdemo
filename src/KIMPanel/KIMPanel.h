#ifndef KIMPANEL_H
#define KIMPANEL_H

#include <QObject>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusServiceWatcher>

#include "KimpanelInputmethod.h"

class KIMPanelAdaptor;
class KIMPanel2Adaptor;

class KIMPanel : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool enable MEMBER enable_ NOTIFY enableChanged)

    // lookup table
    Q_PROPERTY(QVariantList lookupTable MEMBER lookupTable_ NOTIFY lookupTableChanged)
    Q_PROPERTY(bool hasPrev MEMBER hasPrev_ NOTIFY lookupTableChanged)
    Q_PROPERTY(bool hasNext MEMBER hasNext_ NOTIFY lookupTableChanged)
    Q_PROPERTY(qint32 cursor MEMBER cursor_ NOTIFY lookupTableChanged)
    Q_PROPERTY(qint32 layout MEMBER layout_ NOTIFY lookupTableChanged)

public:
    explicit KIMPanel(QObject *parent = nullptr);

signals: // properties signal
    void enableChanged(bool enable);
    void lookupTableChanged();

private slots:
    void onServiceOwnerChanged(const QString &service, const QString &oldOwner, const QString &newOwner);
    void onEnable(bool enable);
    void onExecDialog(const QString &prop);
    void onExecMenu(const QStringList &actions);
    void onRegisterProperties(const QStringList &prop);
    void onRemoveProperty(const QString &prop);
    void onShowAux(bool toshow);
    void onShowLookupTable(bool toshow);
    void onShowPreedit(bool toshow);
    void onUpdateAux(const QString &text, const QString &attr);
    void onUpdateLookupTable(const QStringList &labels,
                             const QStringList &candidates,
                             const QStringList &attrs,
                             bool hasprev,
                             bool hasnext);
    void onUpdateLookupTableCursor(int pos);
    void onUpdatePreeditCaret(int pos);
    void onUpdatePreeditText(const QString &text, const QString &attr);
    void onUpdateProperty(const QString &prop);
    void onUpdateSpotLocation(int x, int y);

    // impanel2
    void onSetLookupTable(const QStringList &label,
                          const QStringList &text,
                          const QStringList &attr,
                          bool hasPrev,
                          bool hasNext,
                          qint32 cursor,
                          qint32 layout);

private:
    QDBusConnection bus_;
    QDBusServiceWatcher *watcher_;
    org::kde::kimpanel::inputmethod *inputmethodIface_;
    KIMPanelAdaptor *kimpanelAdaptor_;
    KIMPanel2Adaptor *kimpanel2Adaptor_;

private: // properties
    bool enable_;

    QVariantList lookupTable_;
    bool hasPrev_;
    bool hasNext_;
    qint32 cursor_;
    qint32 layout_;
};

#endif // !KIMPANEL_H