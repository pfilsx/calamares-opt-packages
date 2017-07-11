include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )
calamares_add_plugin( optionalpackages
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        OptionalPackagesJob.cpp
        OptionalPackagesPage.cpp
        OptionalPackagesViewStep.cpp
    UI
    LINK_PRIVATE_LIBRARIES
        calamaresui
    SHARED_LIB
)
