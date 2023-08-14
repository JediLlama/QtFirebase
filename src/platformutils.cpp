#include "platformutils.h"

#if defined(Q_OS_ANDROID)
jobject PlatformUtils::nativeWindow = nullptr;
#endif

/*
 * Google Play Services (only available under Android)
 */
#if defined(Q_OS_ANDROID)
GooglePlayServices::Availability GooglePlayServices::getAvailability()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QAndroidJniEnvironment env;
    QAndroidJniObject activity = QtAndroid::androidActivity();

    auto availablity = ::google_play_services::CheckAvailability(env, activity.object());
#else
    QJniEnvironment env;
    auto activity = QJniObject(QNativeInterface::QAndroidApplication::context());

    auto availability = ::google_play_services::CheckAvailability(env.jniEnv(), activity.object());
#endif
    qDebug() << "GooglePlayServices::getAvailability result :" << availability << " (0 is kAvailabilityAvailable)";
    return Availability(availability);
}

bool GooglePlayServices::available()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QAndroidJniEnvironment env;
    QAndroidJniObject activity = QtAndroid::androidActivity();

    auto availablity = ::google_play_services::CheckAvailability(env, activity.object());
#else
    QJniEnvironment env;
    auto activity = QJniObject(QNativeInterface::QAndroidApplication::context());

    auto availability = ::google_play_services::CheckAvailability(env.jniEnv(), activity.object());
#endif
    qDebug() << "GooglePlayServices::available() result :" << availability << " (0 is kAvailabilityAvailable)";
    return ::google_play_services::kAvailabilityAvailable == availability;
}
#endif

/*
 * PlatformUtils
 */
#if defined(Q_OS_ANDROID)
jobject PlatformUtils::getNativeWindow()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QAndroidJniEnvironment env;

    QAndroidJniObject activity = QtAndroid::androidActivity();
#else
    QJniEnvironment env;
    auto activity = QJniObject(QNativeInterface::QAndroidApplication::context());
#endif

    if (!nativeWindow) {
        nativeWindow = env->NewGlobalRef(activity.object());
    }

    return nativeWindow;
}
#else
bool PlatformUtils::getNativeWindow()
{
    qDebug() << Q_FUNC_INFO << "not implemented";
    return true;
}
#endif
