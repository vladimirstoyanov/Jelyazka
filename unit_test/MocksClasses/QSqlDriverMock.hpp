#ifndef QSQLDRIVERMOCK_H
#define QSQLDRIVERMOCK_H

#include <QtSql/QtSql>


class IQSqlDriver
{
public:
    IQSqlDriver() {}
    virtual ~QSqlDriver() {}
    virtual bool isOpen() const =0;
    virtual bool isOpenError() const =0;

    virtual bool beginTransaction()=0;
    virtual bool commitTransaction()=0;
    virtual bool rollbackTransaction()=0;
    virtual QStringList tables(QSql::TableType tableType) const=0;
    virtual QSqlIndex primaryIndex(const QString &tableName) const=0;
    virtual QSqlRecord record(const QString &tableName) const=0;
    virtual QString formatValue(const QSqlField& field, bool trimStrings = false) const=0;

    virtual QString escapeIdentifier(const QString &identifier, IdentifierType type) const=0;
    virtual QString sqlStatement(StatementType type, const QString &tableName,
                                 const QSqlRecord &rec, bool preparedStatement) const=0;

    virtual QSqlError lastError() const=0;

    virtual QVariant handle() const=0;
    virtual bool hasFeature(DriverFeature f) const = 0;
    virtual void close() = 0;
    virtual QSqlResult *createResult() const = 0;

    virtual bool open(const QString& db,
                      const QString& user = QString(),
                      const QString& password = QString(),
                      const QString& host = QString(),
                      int port = -1,
                      const QString& connOpts = QString()) = 0;
    virtual bool subscribeToNotification(const QString &name)=0;
    virtual bool unsubscribeFromNotification(const QString &name)=0;
    virtual QStringList subscribedToNotifications() const=0;

    virtual bool isIdentifierEscaped(const QString &identifier, IdentifierType type) const=0;
    virtual QString stripDelimiters(const QString &identifier, IdentifierType type) const=0;

    virtual void setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy precisionPolicy)=0;
    virtual QSql::NumericalPrecisionPolicy numericalPrecisionPolicy() const=0;

    virtual DbmsType dbmsType() const=0;

    virtual bool cancelQuery()=0;

    virtual void notification(const QString &name)=0;
    virtual void notification(const QString &name, QSqlDriver::NotificationSource source, const QVariant &payload)=0;
};


#endif
