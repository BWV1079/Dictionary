
QT += qml quick declarative

CONFIG += c++14
TARGET = Dictionary
TEMPLATE = app

SOURCES += \
    main.cpp \
    Abstraction/Subscription/subscription.cpp \
    Abstraction/Model/BuildingBlocks/id.cpp \
    Abstraction/Model/BuildingBlocks/parameters.cpp \
    Abstraction/Model/BuildingBlocks/parameterscontainer.cpp \
    Abstraction/counter.cpp \
    Abstraction/Model/BuildingBlocks/link.cpp \
    Abstraction/Model/BuildingBlocks/creatorlink.cpp \
    Abstraction/Model/BuildingBlocks/registertypelink.cpp \
    Abstraction/Model/BuildingBlocks/node.cpp \
    Abstraction/Model/BuildingBlocks/creatornode.cpp \
    Abstraction/Model/BuildingBlocks/registertypenode.cpp \
    Abstraction/Model/OrganizationBlocks/nodespool.cpp \
    Abstraction/Model/OrganizationBlocks/distributoridnode.cpp \
    Abstraction/Model/OrganizationBlocks/filemanager.cpp \
    Abstraction/Model/OrganizationBlocks/database.cpp \
    Abstraction/Adapters/adaptermodel.cpp \
    Abstraction/Adapters/adaptersimple.cpp \
    Model/TypesNodes/typeaccount.cpp \
    Model/TypesNodes/typelanguage.cpp \
    Model/TypesNodes/typepartofspeech.cpp \
    initializator_general.cpp \
    initializator_details.cpp \
    View/ModulAccount/account_engine.cpp \
    View/ModulAccount/account_view.cpp \
    Model/TypesNodes/typedct.cpp \
    Adapters/adapterhiderows.cpp \
    View/ModulMain/main_view.cpp \
    View/ModulMain/main_engine.cpp \
    Adapters/adaptersimpleref.cpp \
    Adapters/adapterhiderow.cpp \
    Functional/functionalaccounts.cpp \
    Functional/functionalaccount.cpp \
    Functional/functionalll.cpp \
    Model/TypesNodes/typellfordctlk.cpp \
    Functional/functionaldct.cpp \
    Model/TypesNodes/typeword.cpp \
    View/ModulMain/languageswindow.cpp \
    View/ModulAddWord/addword_engine.cpp \
    View/ModulAddWord/addword_view.cpp \
    View/ModulAddWord/translationgroup.cpp \
    Adapters/adapterwords.cpp

HEADERS += \
    initializator.h \
    Abstraction/Subscription/subscription.h \
    Abstraction/inclusion_for_abstraction.h \
    inclusion_for_dictionary.h \
    Abstraction/Model/BuildingBlocks/id.h \
    Abstraction/Model/BuildingBlocks/parameters.h \
    Abstraction/Model/BuildingBlocks/parameterscontainer.h \
    Abstraction/Model/BuildingBlocks/link.h \
    Abstraction/Model/BuildingBlocks/creatorlink.h \
    Abstraction/Model/BuildingBlocks/registertypelink.h \
    Abstraction/Model/BuildingBlocks/node.h \
    Abstraction/Model/BuildingBlocks/creatornode.h \
    Abstraction/Model/BuildingBlocks/registertypenode.h \
    Abstraction/Model/OrganizationBlocks/nodespool.h \
    Abstraction/Model/OrganizationBlocks/saveload.h \
    Abstraction/Model/OrganizationBlocks/distributoridnode.h \
    Abstraction/Model/OrganizationBlocks/filemanager.h \
    Abstraction/Model/OrganizationBlocks/storage.h \
    Abstraction/Model/OrganizationBlocks/database.h \
    Abstraction/Adapters/adaptermodel.h \
    Abstraction/Adapters/adaptersimple.h \
    Model/types.h \
    Model/TypesNodes/typeaccount.h \
    Model/TypesNodes/typelanguage.h \
    Model/TypesNodes/typepartofspeech.h \
    Abstraction/abstraction.h \
    Abstraction/Adapters/adapters.h \
    Adapters/adapters_dictionary.h \
    View/ModulAccount/account_engine.h \
    View/ModulAccount/account_engineinterface.h \
    View/ModulAccount/account_view.h \
    View/ModulAccount/account_viewinterface.h \
    View/ModulAccount/modul_account.h \
    View/baseengine.h \
    View/baseview.h \
    Model/TypesNodes/typedct.h \
    View/ModulMain/main_engineinterface.h \
    Adapters/adapterhiderows.h \
    View/ModulMain/main_view.h \
    View/ModulMain/main_viewinterface.h \
    View/ModulMain/main_engine.h \
    View/ModulMain/modul_main.h \
    Adapters/adaptersimpleref.h \
    Adapters/adapterhiderow.h \
    Functional/functionalaccounts.h \
    Functional/functionalaccount.h \
    Functional/functional.h \
    Functional/functionalll.h \
    Model/TypesNodes/typellfordctlk.h \
    Functional/functionaldct.h \
    Model/TypesNodes/typeword.h \
    View/ModulMain/languageswindow.h \
    View/ModulAddWord/addword_engine.h \
    View/ModulAddWord/addword_engineinterface.h \
    View/ModulAddWord/addword_view.h \
    View/ModulAddWord/addword_viewinterface.h \
    View/ModulAddWord/modul_addword.h \
    View/ModulAddWord/translationgroup.h \
    Adapters/adapterwords.h

RESOURCES +=

DISTFILES +=

FORMS += \
    View/ModulAccount/view_account.ui \
    View/ModulMain/main_view.ui \
    View/ModulAddWord/addword_view.ui \
    View/ModulMain/languageswindow.ui \
    View/ModulAddWord/translationgroup.ui
