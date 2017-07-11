/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
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

#include <OptionalPackagesJob.h>

#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsSystem.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QTextStream>


OptionalPackagesJob::OptionalPackagesJob( const QString& package)
    : Calamares::Job()
    , m_package( package )
{
}


QString
OptionalPackagesJob::prettyName() const
{
    return tr( "Installing optional packages: %1" ).arg(m_package);
}


QString
OptionalPackagesJob::prettyDescription() const
{
    return tr( "Installing optional packages: %1" ).arg(m_package);
}


QString
OptionalPackagesJob::prettyStatusMessage() const
{
    return tr( "Installing optional packages: %1" ).arg(m_package);
}


Calamares::JobResult
OptionalPackagesJob::exec()
{
    int ec = CalamaresUtils::System::instance()->targetEnvCall( { "yaourt",
                                       "-S",
                                       "--noconfirm",
                                       m_package
                                        } );
    return Calamares::JobResult::ok();
}
