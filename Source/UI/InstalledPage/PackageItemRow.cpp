#include "PackageItemRow.h"

#include "Core/Utils/CoreUtils.h"

#include <qstandarditemmodel.h>

PackageItemRow::PackageItemRow(InstalledPackage *package) : package(package)
{
    Name = new QStandardItem(package->GetName());
    QFont boldFont = Name->font();
    boldFont.setBold(true);
    Name->setFont(boldFont);
    Name->setData(package->GetIcon(), Qt::DecorationRole);

    Description = new QStandardItem(package->GetDescription());
    Size = new QStandardItem(CoreUtils::bitsToGigabytes(package->GetSize()));
    InstallDate = new QStandardItem(package->GetInstallDate().toString("HH:mm dd.MM.yyyy"));

    Source = new QStandardItem(package->GetSource());
    auto lastLaunch = package->GetLastLaunchDate();
    LastLaunchDate =
	new QStandardItem(lastLaunch.has_value() ? lastLaunch.value().toString("HH:mm dd.MM.yyyy") : "None");

    Uptime = new QStandardItem("-");
    auto uptimeTime = package->GetUptime();
    if (uptimeTime.has_value())
    {
	Uptime->setText(QString("%1 h %2 min").arg(uptimeTime.value().hour()).arg(uptimeTime.value().minute()));
    }

    Status = new QStandardItem(PackageStatus::ePackageStatusToString(package->GetStatus()));

    // Binding ==================
    updateBinding = connect(package, &InstalledPackage::statusChanged, this, [this, package](ePackageStatus newStatus) {
	Status->setText(PackageStatus::ePackageStatusToString(newStatus));
	auto lastLaunch = package->GetLastLaunchDate();
	LastLaunchDate->setText(lastLaunch.has_value() ? lastLaunch.value().toString("HH:mm dd.MM.yyyy") : "None");
    });
}
PackageItemRow::~PackageItemRow()
{
    disconnect(updateBinding);
}

QList<QStandardItem *> PackageItemRow::GetItems()
{
    return {Name, Description, Size, InstallDate, Source, LastLaunchDate, Uptime, Status};
}