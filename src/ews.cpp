#include "ews.h"

#define EWS_HAS_OPTIONAL
#define EWS_HAS_NOEXCEPT_SPECIFIER
#define EWS_HAS_MAKE_UNIQUE
#define EWS_HAS_TYPE_ALIAS
#define EWS_HAS_DEFAULT_TEMPLATE_ARGS_FOR_FUNCTIONS
#define EWS_HAS_THREAD_LOCAL_STORAGE
#define EWS_HAS_DEFAULT_AND_DELETE
#define EWS_HAS_VARIADIC_TEMPLATES
#define EWS_HAS_NON_BUGGY_TYPE_TRAITS
#define EWS_HAS_CXX17_STATIC_ASSERT
#define EWS_HAS_ROBUST_NONMODIFYING_SEQ_OPS
#define EWS_HAS_INITIALIZER_LISTS
#define EWS_HAS_VARIANT
#define EWS_HAS_FILESYSTEM_HEADER
#include <ews/ews.hpp>

#include <QDebug>

Ews::Ews(const QString& server, const QString& domain, const QString& login, const QString& password)
{
    ews::set_up();

    const ews::basic_credentials credentials(login.toStdString(), password.toStdString());
    ews::autodiscover_hints hints;
    hints.autodiscover_url = QString(server + "/autodiscover/autodiscover.xml").toStdString();
    const auto autodiscover_result = ews::get_exchange_web_services_url<ews::internal::http_request>(login.toStdString(), credentials, hints);
    qDebug() << QString::fromUtf8(autodiscover_result.external_ews_url.c_str());

    auto service = ews::service(autodiscover_result.external_ews_url, domain.toStdString(), login.toStdString(), password.toStdString());

    ews::distinguished_folder_id folder_id = ews::standard_folder::inbox;

    ews::folder folder;
//    try {
        folder = service.get_folder(folder_id);

        qDebug() << "Display name: " << QString::fromUtf8(folder.get_display_name().c_str());
        qDebug() << "Item count: " << folder.get_total_count();
        qDebug() << "Unread item count: " << folder.get_unread_count();
        qDebug() << "Sub folder count: " << folder.get_child_folder_count();
//    }
//    catch (const ews::http_error &er) {
//        qDebug() << er.what();
//        qDebug() << "Display name: " << QString::fromUtf8(folder.get_display_name().c_str());
//    }
}

Ews::~Ews()
{
    ews::tear_down();
}
