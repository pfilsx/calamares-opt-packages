/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
 *
 *   Portions from the Manjaro Installation Framework
 *   by Roland Singer <roland@manjaro.org>
 *   Copyright (C) 2007 Free Software Foundation, Inc.
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OPTIONALPACKAGESPAGE_H
#define OPTIONALPACKAGESPAGE_H

#include "Typedefs.h"

#include <QObject>
#include <QVariantMap>

#include <QWidget>

/*namespace Ui {
class Page_OptionalPackages;
}*/

class QLabel;
class QScrollArea;
class QVBoxLayout;
class OptionalPackagesViewStep;

class OptionalPackagesPage : public QWidget
{
    Q_OBJECT
public:
    explicit OptionalPackagesPage(const OptionalPackagesViewStep* thisViewStep, QWidget* parent = nullptr );
    virtual ~OptionalPackagesPage();

    bool isReady();

    QList< Calamares::job_ptr > createJobs();

    void onActivate();

    void setPackages(const QStringList& packages);

    void createContentWidget();

signals:
    void checkReady( bool );

private:

    const OptionalPackagesViewStep* m_thisViewStep;

    QStringList m_packages;

    QVBoxLayout* m_layout = nullptr;
    QWidget* m_contentWidget = nullptr;
    QScrollArea* m_scrollArea;
};

#endif // OPTIONALPACKAGESPAGE_H
