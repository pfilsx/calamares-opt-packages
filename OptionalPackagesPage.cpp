/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2017, Teo Mrnjavac <teo@kde.org>
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

#include "OptionalPackagesPage.h"
//#include "ui_page_optionalpackages.h"
#include "OptionalPackagesJob.h"
#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"

#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>
#include <QCheckBox>
#include <QList>



OptionalPackagesPage::OptionalPackagesPage(const OptionalPackagesViewStep* thisViewStep, QWidget* parent)
    : QWidget()
    , m_thisViewStep( thisViewStep )
    , m_scrollArea( new QScrollArea( this ) )
    , m_contentWidget( nullptr )
{
    Q_ASSERT( m_thisViewStep );

    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->setContentsMargins( 0, 0, 0, 0 );

    QLabel* headerLabel = new QLabel( this );
    headerLabel->setText( tr( "Install optional packages" ) );

    QLabel* footerLabel = new QLabel( this );
    footerLabel->setText( tr( "Some packages may slow your installation process. You can install them later using yaourt." ) );

    layout->addWidget( headerLabel );
    layout->addWidget( m_scrollArea );
    layout->addWidget(footerLabel);


    m_scrollArea->setWidgetResizable( true );
    m_scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    m_scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    m_scrollArea->setFrameStyle( QFrame::NoFrame );
    m_scrollArea->setContentsMargins( 0, 0, 0, 0 );    
    
}


OptionalPackagesPage::~OptionalPackagesPage()
{
}


bool
OptionalPackagesPage::isReady()
{
    return true;
}


QList< Calamares::job_ptr >
OptionalPackagesPage::createJobs()
{
    QList< Calamares::job_ptr > list;
    if ( !isReady() )
        return list;

    QList<QCheckBox *> l_checkboxes = m_layout->findChildren<QCheckBox *>();

    for (int i = 0; i < l_checkboxes.count(); i++){
        if (l_checkboxes.at(i)->isChecked()){
            Calamares::Job* j;
            j = new OptionalPackagesJob( l_checkboxes.at(i)->text() );
            list.append( Calamares::job_ptr( j ) );
        }
    }

    
    return list;
}


void
OptionalPackagesPage::onActivate()
{
    createContentWidget();
    QChar l_first = ' ';
    for (int i = 0; i < m_packages.count(); i++){
        if (m_packages[i].at(0) != l_first){
            l_first = m_packages[i].at(0);

            QLabel* label = new QLabel(l_first);
            QFont fnt = font();
            fnt.setWeight( QFont::Bold );
            fnt.setPointSize( CalamaresUtils::defaultFontSize()*1.2);
            label->setFont( fnt );
            label->setContentsMargins( 0, 0, 0, 0 );
            m_layout->addWidget(label);
        }
        QCheckBox* dynamic = new QCheckBox(m_packages[i].replace('_', '-'));
        dynamic->setChecked (false);
        dynamic->setContentsMargins( 0, 0, 0, 0 );
        m_layout->addWidget(dynamic);
    }
    m_layout->addStretch();
}

void
OptionalPackagesPage::setPackages(const QStringList& packages) {
    m_packages = packages;
    m_packages.sort();
}

void
OptionalPackagesPage::createContentWidget()
{
    delete m_contentWidget;
    m_contentWidget = new QWidget;
    m_layout = new QVBoxLayout( m_contentWidget );
    CalamaresUtils::unmarginLayout( m_layout );
    m_scrollArea->setWidget( m_contentWidget );
}