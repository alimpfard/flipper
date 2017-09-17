import qbs 1.0
import qbs.Process
import "BaseDefines.qbs" as App


App{
name: "servitor"
consoleApplication:false
type:"application"
qbsSearchPaths: sourceDirectory + "/modules"
Depends { name: "Qt.core"}
Depends { name: "Qt.sql" }
Depends { name: "Qt.core" }
Depends { name: "Qt.widgets" }
Depends { name: "Qt.network" }
Depends { name: "Qt.gui" }
Depends { name: "Qt.quick" }
Depends { name: "Qt.concurrent" }
Depends { name: "Qt.quickwidgets" }
Depends { name: "cpp" }
Depends { name: "logger" }

cpp.defines: base.concat(["L_TREE_CONTROLLER_LIBRARY", "L_LOGGER_LIBRARY"])
cpp.includePaths: [
                sourceDirectory,
                sourceDirectory + "/include",
                sourceDirectory + "/libs",
                sourceDirectory + "/zlib",
                sourceDirectory + "/libs/Logger/include",


]

files: [
        "UI/servitorwindow.ui",
        "include/fandomparser.h",
        "include/favparser.h",
        "include/ffnparserbase.h",
        "include/ficparser.h",
        "include/init_database.h",
        "include/pagegetter.h",
        "include/parse.h",
        "include/querybuilder.h",
        "include/queryinterfaces.h",
        "include/regex_utils.h",
        "include/section.h",
        "include/service_functions.h",
        "include/servitorwindow.h",
        "include/storyfilter.h",
        "include/url_utils.h",
        "sqlite/sqlite3.c",
        "sqlite/sqlite3.h",
        "src/fandomparser.cpp",
        "src/favparser.cpp",
        "src/ffnparserbase.cpp",
        "src/ficparser.cpp",
        "src/init_database.cpp",
        "src/main_servitor.cpp",
        "src/pagegetter.cpp",
        "src/querybuilder.cpp",
        "src/regex_utils.cpp",
        "src/section.cpp",
        "src/service_functions.cpp",
        "src/servitorwindow.cpp",
        "src/url_utils.cpp",
    ]

cpp.staticLibraries: ["logger", "zlib", "quazip"]
}