/*
 * Copyright (C) 2023 by Erik Verbruggen <erik@verbruggen.consulting>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#include "newversionavailabledialog.h"
#include "theme.h"
#include "ui_newversionavailabledialog.h"

#include <QDialogButtonBox>
#include <QPushButton>

namespace OCC {

NewVersionAvailableDialog::NewVersionAvailableDialog(QWidget *parent, const QString &statusMessage)
    : QWidget(parent)
    , _ui(new ::Ui::Ui_NewVersionAvailableDialog)
{
    _ui->setupUi(this);

    _ui->icon->setPixmap(Theme::instance()->applicationIcon().pixmap(128, 128));
    _ui->label->setText(statusMessage);

    QPushButton *skipButton = _ui->buttonBox->addButton(tr("Skip this version"), QDialogButtonBox::ResetRole);
    QPushButton *getUpdateButton = _ui->buttonBox->addButton(tr("Get update"), QDialogButtonBox::AcceptRole);
    QPushButton *rejectButton = _ui->buttonBox->addButton(tr("Skip this time"), QDialogButtonBox::AcceptRole);

    connect(skipButton, &QAbstractButton::clicked, this, &NewVersionAvailableDialog::skipVersion);
    connect(rejectButton, &QAbstractButton::clicked, this, &NewVersionAvailableDialog::notNow);
    connect(getUpdateButton, &QAbstractButton::clicked, this, &NewVersionAvailableDialog::getUpdate);
}

NewVersionAvailableDialog::~NewVersionAvailableDialog()
{
    delete _ui;
}

void NewVersionAvailableDialog::skipVersion()
{
    Q_EMIT versionSkipped();
    Q_EMIT finished();
}

void NewVersionAvailableDialog::notNow()
{
    Q_EMIT noUpdateNow();
    Q_EMIT finished();
}

void NewVersionAvailableDialog::getUpdate()
{
    Q_EMIT updateNow();
    Q_EMIT finished();
}

} // OCC namespace
