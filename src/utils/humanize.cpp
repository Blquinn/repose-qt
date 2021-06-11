#include "humanize.h"
#include "math.h"

const qint64 nanosec = 1;
const qint64 microsec = nanosec * 1000;
const qint64 msec = microsec * 1000;
const qint64 sec = msec * 1000;
const qint64 minute = sec * 60;
const qint64 hour = minute * 60;

QString Humanize::timeSpan(qint64 ns) {
    if (ns > minute) {
        double d = ns;
        d /= minute;
        return QString("%1m").arg(d, 0, 'f', 2);
    }

    if (ns > sec) {
        double d = ns;
        d /= sec;
        return QString("%1s").arg(d, 0, 'f', 2);
    }

    if (ns > msec) {
        double d = ns;
        d /= msec;
        return QString("%1ms").arg(d, 0, 'f', 2);
    }

    if (ns > microsec) {
        double d = ns;
        d /= microsec;
        return QString("%1µs").arg(d, 0, 'f', 2);
    }

    return QString("%1ns").arg(ns);
}

double logn(double n, double b)
{
    return log(n) / log(b);
}

const QString sizes[] = {"B", "kB", "MB", "GB", "TB", "PB", "EB"};

QString Humanize::bytes(size_t s)
{
    double b = 1000;

    if (s < 10) {
        return QString("%1 B").arg(s);
    }

    auto e = floor(logn(s, b));
    auto suffix = sizes[(int)e];
    auto pp = pow(b, e);
    auto val = floor(s / pp*10+0.5) / 10;
    if (val < 10) {
        return QString("%1 %2").arg(val, 0, 'f', 1).arg(suffix);
    }
    return QString("%1 %2").arg(val, 0, 'f', 0).arg(suffix);
}
