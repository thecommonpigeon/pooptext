#ifndef POOPCHAR_H
#define POOPCHAR_H

#include <QObject>
#include <QFont>

class PoopChar : public QObject
{
    Q_OBJECT
public:
    explicit PoopChar(QObject *parent = nullptr);

    QChar value = 'a';
    QFont font;
    int position;

signals:
    void italicChanged(bool italic);
    void boldChanged(int weight);
    void sizeChanged(qreal size);
    void fontChanged(QString family);
    void charChanged(QString value);
public slots:
    void setChar(QString str);
    void setFamily(QString fam);
    void setSize(int size);
    void setItalic(bool italic);
    void setBold (bool bold);
};

#endif // POOPCHAR_H
