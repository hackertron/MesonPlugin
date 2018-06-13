#pragma once

#include "mesonbuildconfiguration.h"
#include "mesonbuildinfo.h"

#include <projectexplorer/buildinfo.h>
#include <projectexplorer/kitmanager.h>
#include <projectexplorer/projectimporter.h>

namespace MesonProjectManager {

class MesonProjectImporter: public ProjectExplorer::ProjectImporter
{
    Q_OBJECT

public:
    MesonProjectImporter(const Utils::FileName &path);
    QStringList importCandidates() override;

protected:
    QList<void *> examineDirectory(const Utils::FileName &importPath) const override;
    bool matchKit(void *data, const ProjectExplorer::Kit *k) const override;
    ProjectExplorer::Kit *createKit(void *directoryData) const override;
    QList<ProjectExplorer::BuildInfo *> buildInfoListForKit(const ProjectExplorer::Kit *k, void *directoryData) const override;
    void deleteDirectoryData(void *data) const override;
};

}
