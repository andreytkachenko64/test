#ifndef SVPROCESSOR_H
#define SVPROCESSOR_H

#include <time.h>

#include<QObject>
#include<QThread>
#include<QDebug>

#include "svimage.h"
#include "svworker.h"
#include "svabstractkernel.h"
#include "svkernelv1.h"
#include "svkernelv2.h"

class SvProcessor: public QObject
{
    Q_OBJECT

protected:
    QThread*            m_threads;
    SvWorker*           m_workers;
    SvAbstractKernel*   m_kernel;
    unsigned int        m_numberOfWorkers;
    unsigned int        m_workersFinished;
    unsigned int        m_startTime;

public:
    explicit SvProcessor(QObject *parent = 0);
    SvProcessor(SvImage *left, SvImage *right, SvImage *result, int numberOfWorkers = 1, int version = 1);
    ~SvProcessor();
    void execute();

protected slots:
    void workerFinished(int workerId);

public slots:
    void start();
    void stop();

signals:
    void started();
    void finished(int elapsedTime);
    void stopped(int elapsedTime);
};

#endif // SVPROCESSOR_H
