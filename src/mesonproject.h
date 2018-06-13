#pragma once

#include "mesonbuildfileparser.h"
#include "mesonprojectnode.h"
#include "mesonbuildconfiguration.h"

#include <cpptools/cppprojectupdater.h>

#include <projectexplorer/project.h>
#include <projectexplorer/projectnodes.h>

#include <QStringList>
#include <QFutureInterface>
#include <QTimer>
#include <QFuture>

#include <memory>

namespace MesonProjectManager {

class CompileCommandInfo
{
public:
    QMap<QString, QString> defines;
    QStringList includes;
    QString cpp_std;
    QString id;

    bool operator==(const CompileCommandInfo &o) const;
};

class MesonProject : public ProjectExplorer::Project
{
    Q_OBJECT

public:
    explicit MesonProject(const Utils::FileName &proFile);
    virtual ~MesonProject();

    bool setupTarget(ProjectExplorer::Target *t);
    QStringList filesGeneratedFrom(const QString &sourceFile) const override;
    bool needsConfiguration() const override;
    void configureAsExampleProject(const QSet<Core::Id> &platforms) override;
    bool requiresTargetPanel() ;
    ProjectExplorer::ProjectImporter *projectImporter() const override;

    void mesonIntrospectBuildsytemFiles(const MesonBuildConfiguration &cfg, MesonProjectNode *root);
    void mesonIntrospectProjectInfo(const MesonBuildConfiguration &cfg);
    const QHash<CompileCommandInfo, QStringList> parseCompileCommands(const MesonBuildConfiguration &cfg) const;

    void refreshCppCodeModel(const QHash<CompileCommandInfo, QStringList> &);

    QSet<QString> filesInEditableGroups;

private:
    MesonBuildConfiguration *activeBuildConfiguration();
    const Utils::FileName filename;
    CppTools::CppProjectUpdater *cppCodeModelUpdater = nullptr;

protected:
    RestoreResult fromMap(const QVariantMap &map, QString *errorMessage) override;

public slots:
    void refresh();
};

QStringList getAllHeadersFor(const QString &fname);

}
