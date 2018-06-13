#pragma once
#include <projectexplorer/buildconfiguration.h>
#include <projectexplorer/kit.h>
#include <projectexplorer/namedwidget.h>

namespace MesonProjectManager {

class MesonBuildConfiguration : public ProjectExplorer::BuildConfiguration
{
    Q_OBJECT

public:
    explicit MesonBuildConfiguration(ProjectExplorer::Target *parent);

public:
    void initialize(const ProjectExplorer::BuildInfo *info) override;

    ProjectExplorer::NamedWidget *createConfigWidget() override;
    BuildType buildType() const override;

    QString mesonPath() const;
    void setMesonPath(const QString &mesonPath);

    bool fromMap(const QVariantMap &map) override;
    QVariantMap toMap() const override;

private:
    QString m_mesonPath;

    friend class MesonBuildConfigationWidget;
};

class MesonBuildConfigationWidget: public ProjectExplorer::NamedWidget
{
    Q_OBJECT
public:
    explicit MesonBuildConfigationWidget(MesonBuildConfiguration *config, QWidget *parent=nullptr);
private:
    MesonBuildConfiguration *config;
};

class MesonBuildConfigurationFactory : public ProjectExplorer::IBuildConfigurationFactory
{
public:
    MesonBuildConfigurationFactory();

    QList<ProjectExplorer::BuildInfo *> availableBuilds(const ProjectExplorer::Target *parent) const override;
    QList<ProjectExplorer::BuildInfo *> availableSetups(const ProjectExplorer::Kit *k, const QString &projectPath) const override;

    ProjectExplorer::BuildInfo *createBuildInfo(const ProjectExplorer::Kit *k, const QString &projectPath, ProjectExplorer::BuildConfiguration::BuildType type) const;

private:
    bool correctProject(const ProjectExplorer::Target *parent) const;
};

}
