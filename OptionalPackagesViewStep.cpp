/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include "OptionalPackagesViewStep.h"

#include "OptionalPackagesPage.h"

#include "JobQueue.h"
#include "GlobalStorage.h"

 CALAMARES_PLUGIN_FACTORY_DEFINITION( OptionalPackagesViewStepFactory, registerPlugin<OptionalPackagesViewStep>(); )

OptionalPackagesViewStep::OptionalPackagesViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new OptionalPackagesPage(this) )
{
    emit nextStatusChanged( true );
    connect( m_widget, &OptionalPackagesPage::checkReady,
             this, &OptionalPackagesViewStep::nextStatusChanged );
}


OptionalPackagesViewStep::~OptionalPackagesViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
        m_widget->deleteLater();
}


QString
OptionalPackagesViewStep::prettyName() const
{
    return tr( "Packages" );
}


QWidget*
OptionalPackagesViewStep::widget()
{
    return m_widget;
}


void
OptionalPackagesViewStep::next()
{
    emit done();
}


void
OptionalPackagesViewStep::back()
{}


bool
OptionalPackagesViewStep::isNextEnabled() const
{
    return m_widget->isReady();
}


bool
OptionalPackagesViewStep::isBackEnabled() const
{
    return true;
}


bool
OptionalPackagesViewStep::isAtBeginning() const
{
    return true;
}


bool
OptionalPackagesViewStep::isAtEnd() const
{
    return true;
}


QList< Calamares::job_ptr >
OptionalPackagesViewStep::jobs() const
{
    return m_jobs;
}


void
OptionalPackagesViewStep::onActivate()
{
    m_widget->onActivate();
}


void
OptionalPackagesViewStep::onLeave()
{
    m_jobs.clear();
    m_widget->createContentWidget();
}


void
OptionalPackagesViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    //m_widget->setPackages(configurationMap);
    if ( configurationMap.contains( "packages" ) &&
         configurationMap.value( "packages" ).type() == QVariant::List )
    {
        m_widget->setPackages(configurationMap.value( "packages" ).toStringList());
        
    }
    /*Calamares::JobQueue::instance()->globalStorage()->insert( "opt_packages",
                        m_packagesList );*/
}

