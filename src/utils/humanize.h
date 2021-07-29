#ifndef HUMANIZE_H
#define HUMANIZE_H

#include "chrono"
#include <qstring.h>

class Humanize {
public:
    static QString timeSpan(qint64 ns);
    static QString bytes(size_t bytes);
};

#endif // HUMANIZE_H
