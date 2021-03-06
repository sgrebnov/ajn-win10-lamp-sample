//-----------------------------------------------------------------------------
// <auto-generated> 
//   This code was generated by a tool. 
// 
//   Changes to this file may cause incorrect behavior and will be lost if  
//   the code is regenerated.
//
//   Tool: AllJoynCodeGenerator.exe
//
//   This tool is located in the Windows 10 SDK and the Windows 10 AllJoyn 
//   Visual Studio Extension in the Visual Studio Gallery.  
//
//   The generated code should be packaged in a Windows 10 C++/CX Runtime  
//   Component which can be consumed in any UWP-supported language using 
//   APIs that are available in Windows.Devices.AllJoyn.
//
//   Using AllJoynCodeGenerator - Invoke the following command with a valid 
//   Introspection XML file and a writable output directory:
//     AllJoynCodeGenerator -i <INPUT XML FILE> -o <OUTPUT DIRECTORY>
// </auto-generated>
//-----------------------------------------------------------------------------
#include "pch.h"

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Devices::AllJoyn;
using namespace org::allseen::LSF::LampState;

std::map<alljoyn_interfacedescription, WeakReference*> LampStateConsumer::SourceInterfaces;

LampStateConsumer::LampStateConsumer(AllJoynBusAttachment^ busAttachment)
    : m_busAttachment(busAttachment),
    m_proxyBusObject(nullptr),
    m_busObject(nullptr),
    m_sessionListener(nullptr),
    m_sessionId(0)
{
    m_weak = new WeakReference(this);
    m_signals = ref new LampStateSignals();
    m_nativeBusAttachment = AllJoynHelpers::GetInternalBusAttachment(m_busAttachment);
}

LampStateConsumer::~LampStateConsumer()
{
    AllJoynBusObjectManager::ReleaseBusObject(m_nativeBusAttachment, AllJoynHelpers::PlatformToMultibyteString(ServiceObjectPath).data());
    if (SessionListener != nullptr)
    {
        alljoyn_busattachment_setsessionlistener(m_nativeBusAttachment, m_sessionId, nullptr);
        alljoyn_sessionlistener_destroy(SessionListener);
    }
    if (nullptr != ProxyBusObject)
    {
        alljoyn_proxybusobject_destroy(ProxyBusObject);
    }
    delete m_weak;
}

void LampStateConsumer::OnSessionLost(_In_ alljoyn_sessionid sessionId, _In_ alljoyn_sessionlostreason reason)
{
    if (sessionId == m_sessionId)
    {
        AllJoynSessionLostEventArgs^ args = ref new AllJoynSessionLostEventArgs(static_cast<AllJoynSessionLostReason>(reason));
        AllJoynHelpers::DispatchEvent([=]() {
            SessionLost(this, args);
        });
    }
}

void LampStateConsumer::OnSessionMemberAdded(_In_ alljoyn_sessionid sessionId, _In_ PCSTR uniqueName)
{
    if (sessionId == m_sessionId)
    {
        auto args = ref new AllJoynSessionMemberAddedEventArgs(AllJoynHelpers::MultibyteToPlatformString(uniqueName));
        AllJoynHelpers::DispatchEvent([=]() {
            SessionMemberAdded(this, args);
        });
    }
}

void LampStateConsumer::OnSessionMemberRemoved(_In_ alljoyn_sessionid sessionId, _In_ PCSTR uniqueName)
{
    if (sessionId == m_sessionId)
    {
        auto args = ref new AllJoynSessionMemberRemovedEventArgs(AllJoynHelpers::MultibyteToPlatformString(uniqueName));
        AllJoynHelpers::DispatchEvent([=]() {
            SessionMemberRemoved(this, args);
        });
    }
}

QStatus LampStateConsumer::AddSignalHandler(_In_ alljoyn_busattachment busAttachment, _In_ alljoyn_interfacedescription interfaceDescription, _In_ PCSTR methodName, _In_ alljoyn_messagereceiver_signalhandler_ptr handler)
{
    alljoyn_interfacedescription_member member;
    if (!alljoyn_interfacedescription_getmember(interfaceDescription, methodName, &member))
    {
        return ER_BUS_INTERFACE_NO_SUCH_MEMBER;
    }

    return alljoyn_busattachment_registersignalhandler(busAttachment, handler, member, NULL);
}

IAsyncOperation<LampStateJoinSessionResult^>^ LampStateConsumer::JoinSessionAsync(
    _In_ AllJoynServiceInfo^ serviceInfo, _Inout_ LampStateWatcher^ watcher)
{
    return create_async([serviceInfo, watcher]() -> LampStateJoinSessionResult^
    {
        auto result = ref new LampStateJoinSessionResult();
        result->Status = AllJoynStatus::Ok;
        result->Consumer = nullptr;

        result->Consumer = ref new LampStateConsumer(watcher->BusAttachment);
        result->Status = result->Consumer->JoinSession(serviceInfo);

        return result;
    });
}

IAsyncOperation<LampStateTransitionLampStateResult^>^ LampStateConsumer::TransitionLampStateAsync(_In_ uint64 interfaceMemberTimestamp, _In_ Windows::Foundation::Collections::IMapView<Platform::String^,Platform::Object^>^ interfaceMemberNewState, _In_ uint32 interfaceMemberTransitionPeriod)
{
    return create_async([this, interfaceMemberTimestamp, interfaceMemberNewState, interfaceMemberTransitionPeriod]() -> LampStateTransitionLampStateResult^
    {
        auto result = ref new LampStateTransitionLampStateResult();
        
        alljoyn_message message = alljoyn_message_create(m_nativeBusAttachment);
        size_t argCount = 3;
        alljoyn_msgarg inputs = alljoyn_msgarg_array_create(argCount);

        TypeConversionHelpers::SetAllJoynMessageArg(alljoyn_msgarg_array_element(inputs, 0), "t", interfaceMemberTimestamp);
        TypeConversionHelpers::SetAllJoynMessageArg(alljoyn_msgarg_array_element(inputs, 1), "a{sv}", interfaceMemberNewState);
        TypeConversionHelpers::SetAllJoynMessageArg(alljoyn_msgarg_array_element(inputs, 2), "u", interfaceMemberTransitionPeriod);
        
        QStatus status = alljoyn_proxybusobject_methodcall(
            ProxyBusObject,
            "org.allseen.LSF.LampState",
            "TransitionLampState",
            inputs,
            argCount,
            message,
            c_MessageTimeoutInMilliseconds,
            0);
        result->Status = static_cast<int>(status);
        if (ER_OK == status) 
        {
            result->Status = AllJoynStatus::Ok;
            uint32 argument0;
            status = static_cast<QStatus>(TypeConversionHelpers::GetAllJoynMessageArg(alljoyn_message_getarg(message, 0), "u", &argument0));
            result->LampResponseCode = argument0;

            if (status != ER_OK)
            {
                result->Status = static_cast<int>(status);
            }
        }
        else if (ER_BUS_REPLY_IS_ERROR_MESSAGE == status)
        {
            alljoyn_msgarg errorArg = alljoyn_message_getarg(message, 1);
            if (nullptr != errorArg)
            {
                uint16 errorStatus;
                status = alljoyn_msgarg_get_uint16(errorArg, &errorStatus);
                if (ER_OK == status)
                {
                    status = static_cast<QStatus>(errorStatus);
                }
            }
            result->Status = static_cast<int>(status);
        }
        
        alljoyn_message_destroy(message);
        alljoyn_msgarg_destroy(inputs);

        return result;
    });
}
IAsyncOperation<LampStateApplyPulseEffectResult^>^ LampStateConsumer::ApplyPulseEffectAsync(_In_ Windows::Foundation::Collections::IMapView<Platform::String^,Platform::Object^>^ interfaceMemberFromState, _In_ Windows::Foundation::Collections::IMapView<Platform::String^,Platform::Object^>^ interfaceMemberToState, _In_ uint32 interfaceMemberPeriod, _In_ uint32 interfaceMemberDuration, _In_ uint32 interfaceMemberNumPulses, _In_ uint64 interfaceMemberTimestamp)
{
    return create_async([this, interfaceMemberFromState, interfaceMemberToState, interfaceMemberPeriod, interfaceMemberDuration, interfaceMemberNumPulses, interfaceMemberTimestamp]() -> LampStateApplyPulseEffectResult^
    {
        auto result = ref new LampStateApplyPulseEffectResult();
        
        alljoyn_message message = alljoyn_message_create(m_nativeBusAttachment);
        size_t argCount = 6;
        alljoyn_msgarg inputs = alljoyn_msgarg_array_create(argCount);

        TypeConversionHelpers::SetAllJoynMessageArg(alljoyn_msgarg_array_element(inputs, 0), "a{sv}", interfaceMemberFromState);
        TypeConversionHelpers::SetAllJoynMessageArg(alljoyn_msgarg_array_element(inputs, 1), "a{sv}", interfaceMemberToState);
        TypeConversionHelpers::SetAllJoynMessageArg(alljoyn_msgarg_array_element(inputs, 2), "u", interfaceMemberPeriod);
        TypeConversionHelpers::SetAllJoynMessageArg(alljoyn_msgarg_array_element(inputs, 3), "u", interfaceMemberDuration);
        TypeConversionHelpers::SetAllJoynMessageArg(alljoyn_msgarg_array_element(inputs, 4), "u", interfaceMemberNumPulses);
        TypeConversionHelpers::SetAllJoynMessageArg(alljoyn_msgarg_array_element(inputs, 5), "t", interfaceMemberTimestamp);
        
        QStatus status = alljoyn_proxybusobject_methodcall(
            ProxyBusObject,
            "org.allseen.LSF.LampState",
            "ApplyPulseEffect",
            inputs,
            argCount,
            message,
            c_MessageTimeoutInMilliseconds,
            0);
        result->Status = static_cast<int>(status);
        if (ER_OK == status) 
        {
            result->Status = AllJoynStatus::Ok;
            uint32 argument0;
            status = static_cast<QStatus>(TypeConversionHelpers::GetAllJoynMessageArg(alljoyn_message_getarg(message, 0), "u", &argument0));
            result->LampResponseCode = argument0;

            if (status != ER_OK)
            {
                result->Status = static_cast<int>(status);
            }
        }
        else if (ER_BUS_REPLY_IS_ERROR_MESSAGE == status)
        {
            alljoyn_msgarg errorArg = alljoyn_message_getarg(message, 1);
            if (nullptr != errorArg)
            {
                uint16 errorStatus;
                status = alljoyn_msgarg_get_uint16(errorArg, &errorStatus);
                if (ER_OK == status)
                {
                    status = static_cast<QStatus>(errorStatus);
                }
            }
            result->Status = static_cast<int>(status);
        }
        
        alljoyn_message_destroy(message);
        alljoyn_msgarg_destroy(inputs);

        return result;
    });
}

IAsyncOperation<LampStateGetVersionResult^>^ LampStateConsumer::GetVersionAsync()
{
    return create_async([this]() -> LampStateGetVersionResult^
    {
        PropertyGetContext<uint32> getContext;
        
        alljoyn_proxybusobject_getpropertyasync(
            ProxyBusObject,
            "org.allseen.LSF.LampState",
            "Version",
            [](QStatus status, alljoyn_proxybusobject obj, const alljoyn_msgarg value, void* context)
            {
                UNREFERENCED_PARAMETER(obj);
                auto propertyContext = static_cast<PropertyGetContext<uint32>*>(context);

                if (ER_OK == status)
                {
                    uint32 argument;
                    TypeConversionHelpers::GetAllJoynMessageArg(value, "u", &argument);

                    propertyContext->SetValue(argument);
                }
                propertyContext->SetStatus(status);
                propertyContext->SetEvent();
            },
            c_MessageTimeoutInMilliseconds,
            &getContext);

        getContext.Wait();

        auto result = ref new LampStateGetVersionResult();
        result->Status = getContext.GetStatus();
        result->Version = getContext.GetValue();
        return result;
    });
}

IAsyncOperation<LampStateSetOnOffResult^>^ LampStateConsumer::SetOnOffAsync(_In_ bool value)
{
    return create_async([this, value]() -> LampStateSetOnOffResult^
    {
        PropertySetContext setContext;

        alljoyn_msgarg inputArgument = alljoyn_msgarg_create();
        TypeConversionHelpers::SetAllJoynMessageArg(inputArgument, "b", value);

        alljoyn_proxybusobject_setpropertyasync(
            ProxyBusObject,
            "org.allseen.LSF.LampState",
            "OnOff",
            inputArgument,
            [](QStatus status, alljoyn_proxybusobject obj, void* context)
            {
                UNREFERENCED_PARAMETER(obj);
                auto propertyContext = static_cast<PropertySetContext*>(context);
                propertyContext->SetStatus(status);
                propertyContext->SetEvent();
            },
            c_MessageTimeoutInMilliseconds,
            &setContext);

        alljoyn_msgarg_destroy(inputArgument);

        setContext.Wait();

        auto result = ref new LampStateSetOnOffResult();
        result->Status = setContext.GetStatus();
        return result;
    });
}

IAsyncOperation<LampStateGetOnOffResult^>^ LampStateConsumer::GetOnOffAsync()
{
    return create_async([this]() -> LampStateGetOnOffResult^
    {
        PropertyGetContext<bool> getContext;
        
        alljoyn_proxybusobject_getpropertyasync(
            ProxyBusObject,
            "org.allseen.LSF.LampState",
            "OnOff",
            [](QStatus status, alljoyn_proxybusobject obj, const alljoyn_msgarg value, void* context)
            {
                UNREFERENCED_PARAMETER(obj);
                auto propertyContext = static_cast<PropertyGetContext<bool>*>(context);

                if (ER_OK == status)
                {
                    bool argument;
                    TypeConversionHelpers::GetAllJoynMessageArg(value, "b", &argument);

                    propertyContext->SetValue(argument);
                }
                propertyContext->SetStatus(status);
                propertyContext->SetEvent();
            },
            c_MessageTimeoutInMilliseconds,
            &getContext);

        getContext.Wait();

        auto result = ref new LampStateGetOnOffResult();
        result->Status = getContext.GetStatus();
        result->OnOff = getContext.GetValue();
        return result;
    });
}

IAsyncOperation<LampStateSetHueResult^>^ LampStateConsumer::SetHueAsync(_In_ uint32 value)
{
    return create_async([this, value]() -> LampStateSetHueResult^
    {
        PropertySetContext setContext;

        alljoyn_msgarg inputArgument = alljoyn_msgarg_create();
        TypeConversionHelpers::SetAllJoynMessageArg(inputArgument, "u", value);

        alljoyn_proxybusobject_setpropertyasync(
            ProxyBusObject,
            "org.allseen.LSF.LampState",
            "Hue",
            inputArgument,
            [](QStatus status, alljoyn_proxybusobject obj, void* context)
            {
                UNREFERENCED_PARAMETER(obj);
                auto propertyContext = static_cast<PropertySetContext*>(context);
                propertyContext->SetStatus(status);
                propertyContext->SetEvent();
            },
            c_MessageTimeoutInMilliseconds,
            &setContext);

        alljoyn_msgarg_destroy(inputArgument);

        setContext.Wait();

        auto result = ref new LampStateSetHueResult();
        result->Status = setContext.GetStatus();
        return result;
    });
}

IAsyncOperation<LampStateGetHueResult^>^ LampStateConsumer::GetHueAsync()
{
    return create_async([this]() -> LampStateGetHueResult^
    {
        PropertyGetContext<uint32> getContext;
        
        alljoyn_proxybusobject_getpropertyasync(
            ProxyBusObject,
            "org.allseen.LSF.LampState",
            "Hue",
            [](QStatus status, alljoyn_proxybusobject obj, const alljoyn_msgarg value, void* context)
            {
                UNREFERENCED_PARAMETER(obj);
                auto propertyContext = static_cast<PropertyGetContext<uint32>*>(context);

                if (ER_OK == status)
                {
                    uint32 argument;
                    TypeConversionHelpers::GetAllJoynMessageArg(value, "u", &argument);

                    propertyContext->SetValue(argument);
                }
                propertyContext->SetStatus(status);
                propertyContext->SetEvent();
            },
            c_MessageTimeoutInMilliseconds,
            &getContext);

        getContext.Wait();

        auto result = ref new LampStateGetHueResult();
        result->Status = getContext.GetStatus();
        result->Hue = getContext.GetValue();
        return result;
    });
}

IAsyncOperation<LampStateSetSaturationResult^>^ LampStateConsumer::SetSaturationAsync(_In_ uint32 value)
{
    return create_async([this, value]() -> LampStateSetSaturationResult^
    {
        PropertySetContext setContext;

        alljoyn_msgarg inputArgument = alljoyn_msgarg_create();
        TypeConversionHelpers::SetAllJoynMessageArg(inputArgument, "u", value);

        alljoyn_proxybusobject_setpropertyasync(
            ProxyBusObject,
            "org.allseen.LSF.LampState",
            "Saturation",
            inputArgument,
            [](QStatus status, alljoyn_proxybusobject obj, void* context)
            {
                UNREFERENCED_PARAMETER(obj);
                auto propertyContext = static_cast<PropertySetContext*>(context);
                propertyContext->SetStatus(status);
                propertyContext->SetEvent();
            },
            c_MessageTimeoutInMilliseconds,
            &setContext);

        alljoyn_msgarg_destroy(inputArgument);

        setContext.Wait();

        auto result = ref new LampStateSetSaturationResult();
        result->Status = setContext.GetStatus();
        return result;
    });
}

IAsyncOperation<LampStateGetSaturationResult^>^ LampStateConsumer::GetSaturationAsync()
{
    return create_async([this]() -> LampStateGetSaturationResult^
    {
        PropertyGetContext<uint32> getContext;
        
        alljoyn_proxybusobject_getpropertyasync(
            ProxyBusObject,
            "org.allseen.LSF.LampState",
            "Saturation",
            [](QStatus status, alljoyn_proxybusobject obj, const alljoyn_msgarg value, void* context)
            {
                UNREFERENCED_PARAMETER(obj);
                auto propertyContext = static_cast<PropertyGetContext<uint32>*>(context);

                if (ER_OK == status)
                {
                    uint32 argument;
                    TypeConversionHelpers::GetAllJoynMessageArg(value, "u", &argument);

                    propertyContext->SetValue(argument);
                }
                propertyContext->SetStatus(status);
                propertyContext->SetEvent();
            },
            c_MessageTimeoutInMilliseconds,
            &getContext);

        getContext.Wait();

        auto result = ref new LampStateGetSaturationResult();
        result->Status = getContext.GetStatus();
        result->Saturation = getContext.GetValue();
        return result;
    });
}

IAsyncOperation<LampStateSetColorTempResult^>^ LampStateConsumer::SetColorTempAsync(_In_ uint32 value)
{
    return create_async([this, value]() -> LampStateSetColorTempResult^
    {
        PropertySetContext setContext;

        alljoyn_msgarg inputArgument = alljoyn_msgarg_create();
        TypeConversionHelpers::SetAllJoynMessageArg(inputArgument, "u", value);

        alljoyn_proxybusobject_setpropertyasync(
            ProxyBusObject,
            "org.allseen.LSF.LampState",
            "ColorTemp",
            inputArgument,
            [](QStatus status, alljoyn_proxybusobject obj, void* context)
            {
                UNREFERENCED_PARAMETER(obj);
                auto propertyContext = static_cast<PropertySetContext*>(context);
                propertyContext->SetStatus(status);
                propertyContext->SetEvent();
            },
            c_MessageTimeoutInMilliseconds,
            &setContext);

        alljoyn_msgarg_destroy(inputArgument);

        setContext.Wait();

        auto result = ref new LampStateSetColorTempResult();
        result->Status = setContext.GetStatus();
        return result;
    });
}

IAsyncOperation<LampStateGetColorTempResult^>^ LampStateConsumer::GetColorTempAsync()
{
    return create_async([this]() -> LampStateGetColorTempResult^
    {
        PropertyGetContext<uint32> getContext;
        
        alljoyn_proxybusobject_getpropertyasync(
            ProxyBusObject,
            "org.allseen.LSF.LampState",
            "ColorTemp",
            [](QStatus status, alljoyn_proxybusobject obj, const alljoyn_msgarg value, void* context)
            {
                UNREFERENCED_PARAMETER(obj);
                auto propertyContext = static_cast<PropertyGetContext<uint32>*>(context);

                if (ER_OK == status)
                {
                    uint32 argument;
                    TypeConversionHelpers::GetAllJoynMessageArg(value, "u", &argument);

                    propertyContext->SetValue(argument);
                }
                propertyContext->SetStatus(status);
                propertyContext->SetEvent();
            },
            c_MessageTimeoutInMilliseconds,
            &getContext);

        getContext.Wait();

        auto result = ref new LampStateGetColorTempResult();
        result->Status = getContext.GetStatus();
        result->ColorTemp = getContext.GetValue();
        return result;
    });
}

IAsyncOperation<LampStateSetBrightnessResult^>^ LampStateConsumer::SetBrightnessAsync(_In_ uint32 value)
{
    return create_async([this, value]() -> LampStateSetBrightnessResult^
    {
        PropertySetContext setContext;

        alljoyn_msgarg inputArgument = alljoyn_msgarg_create();
        TypeConversionHelpers::SetAllJoynMessageArg(inputArgument, "u", value);

        alljoyn_proxybusobject_setpropertyasync(
            ProxyBusObject,
            "org.allseen.LSF.LampState",
            "Brightness",
            inputArgument,
            [](QStatus status, alljoyn_proxybusobject obj, void* context)
            {
                UNREFERENCED_PARAMETER(obj);
                auto propertyContext = static_cast<PropertySetContext*>(context);
                propertyContext->SetStatus(status);
                propertyContext->SetEvent();
            },
            c_MessageTimeoutInMilliseconds,
            &setContext);

        alljoyn_msgarg_destroy(inputArgument);

        setContext.Wait();

        auto result = ref new LampStateSetBrightnessResult();
        result->Status = setContext.GetStatus();
        return result;
    });
}

IAsyncOperation<LampStateGetBrightnessResult^>^ LampStateConsumer::GetBrightnessAsync()
{
    return create_async([this]() -> LampStateGetBrightnessResult^
    {
        PropertyGetContext<uint32> getContext;
        
        alljoyn_proxybusobject_getpropertyasync(
            ProxyBusObject,
            "org.allseen.LSF.LampState",
            "Brightness",
            [](QStatus status, alljoyn_proxybusobject obj, const alljoyn_msgarg value, void* context)
            {
                UNREFERENCED_PARAMETER(obj);
                auto propertyContext = static_cast<PropertyGetContext<uint32>*>(context);

                if (ER_OK == status)
                {
                    uint32 argument;
                    TypeConversionHelpers::GetAllJoynMessageArg(value, "u", &argument);

                    propertyContext->SetValue(argument);
                }
                propertyContext->SetStatus(status);
                propertyContext->SetEvent();
            },
            c_MessageTimeoutInMilliseconds,
            &getContext);

        getContext.Wait();

        auto result = ref new LampStateGetBrightnessResult();
        result->Status = getContext.GetStatus();
        result->Brightness = getContext.GetValue();
        return result;
    });
}

void LampStateConsumer::OnPropertyChanged(_In_ alljoyn_proxybusobject obj, _In_ PCSTR interfaceName, _In_ const alljoyn_msgarg changed, _In_ const alljoyn_msgarg invalidated)
{
    UNREFERENCED_PARAMETER(obj);
    UNREFERENCED_PARAMETER(interfaceName);
    UNREFERENCED_PARAMETER(changed);
    UNREFERENCED_PARAMETER(invalidated);
}

void LampStateConsumer::CallLampStateChangedSignalHandler(_In_ const alljoyn_interfacedescription_member* member, _In_ alljoyn_message message)
{
    auto source = SourceInterfaces.find(member->iface);
    if (source == SourceInterfaces.end())
    {
        return;
    }

    auto consumer = source->second->Resolve<LampStateConsumer>();
    if (consumer->Signals != nullptr)
    {
        auto callInfo = ref new AllJoynMessageInfo(AllJoynHelpers::MultibyteToPlatformString(alljoyn_message_getsender(message)));
        auto eventArgs = ref new LampStateLampStateChangedReceivedEventArgs();
        eventArgs->MessageInfo = callInfo;

        Platform::String^ argument0;
        TypeConversionHelpers::GetAllJoynMessageArg(alljoyn_message_getarg(message, 0), "s", &argument0);

        eventArgs->LampID = argument0;

        consumer->Signals->CallLampStateChangedReceived(consumer->Signals, eventArgs);
    }
}

int32 LampStateConsumer::JoinSession(_In_ AllJoynServiceInfo^ serviceInfo)
{
    alljoyn_sessionlistener_callbacks callbacks =
    {
        AllJoynHelpers::SessionLostHandler<LampStateConsumer>,
        AllJoynHelpers::SessionMemberAddedHandler<LampStateConsumer>,
        AllJoynHelpers::SessionMemberRemovedHandler<LampStateConsumer>
    };

    alljoyn_busattachment_enableconcurrentcallbacks(AllJoynHelpers::GetInternalBusAttachment(m_busAttachment));

    SessionListener = alljoyn_sessionlistener_create(&callbacks, m_weak);
    alljoyn_sessionopts sessionOpts = alljoyn_sessionopts_create(ALLJOYN_TRAFFIC_TYPE_MESSAGES, true, ALLJOYN_PROXIMITY_ANY, ALLJOYN_TRANSPORT_ANY);

    std::vector<char> sessionNameUtf8 = AllJoynHelpers::PlatformToMultibyteString(serviceInfo->UniqueName);
    RETURN_IF_QSTATUS_ERROR(alljoyn_busattachment_joinsession(
        m_nativeBusAttachment,
        &sessionNameUtf8[0],
        serviceInfo->SessionPort,
        SessionListener,
        &m_sessionId,
        sessionOpts));
    alljoyn_sessionopts_destroy(sessionOpts);

    ServiceObjectPath = serviceInfo->ObjectPath;
    std::vector<char> objectPath = AllJoynHelpers::PlatformToMultibyteString(ServiceObjectPath);

    if (objectPath.empty())
    {
        return AllJoynStatus::Fail;
    }

    ProxyBusObject = alljoyn_proxybusobject_create(m_nativeBusAttachment, &sessionNameUtf8[0], &objectPath[0], m_sessionId);
    if (nullptr == ProxyBusObject)
    {
        return AllJoynStatus::Fail;
    }


    alljoyn_interfacedescription description = alljoyn_busattachment_getinterface(m_nativeBusAttachment, "org.allseen.LSF.LampState");
    if (nullptr == description)
    {
        return AllJoynStatus::Fail;
    }

    RETURN_IF_QSTATUS_ERROR(AllJoynBusObjectManager::GetBusObject(m_nativeBusAttachment, AllJoynHelpers::PlatformToMultibyteString(ServiceObjectPath).data(), &m_busObject));
   
    if (!AllJoynBusObjectManager::BusObjectIsRegistered(m_nativeBusAttachment, m_busObject))
    {
        RETURN_IF_QSTATUS_ERROR(alljoyn_busobject_addinterface(BusObject, description));
    }

    QStatus result = AddSignalHandler(
        m_nativeBusAttachment,
        description,
        "LampStateChanged",
        [](const alljoyn_interfacedescription_member* member, PCSTR srcPath, alljoyn_message message) { UNREFERENCED_PARAMETER(srcPath); CallLampStateChangedSignalHandler(member, message); });
    if (result != ER_OK)
    {
        return static_cast<int32>(result);
    }

    SourceInterfaces[description] = m_weak;

    unsigned int noneMechanismIndex = 0;
    bool authenticationMechanismsContainsNone = m_busAttachment->AuthenticationMechanisms->IndexOf(AllJoynAuthenticationMechanism::None, &noneMechanismIndex);
    QCC_BOOL interfaceIsSecure = alljoyn_interfacedescription_issecure(description);

    // If the current set of AuthenticationMechanisms supports authentication, 
    // determine whether to secure the connection.
    if (AllJoynHelpers::CanSecure(m_busAttachment->AuthenticationMechanisms))
    {
        // Secure the connection if the org.alljoyn.Bus.Secure XML annotation
        // is specified, or if None is not present in AuthenticationMechanisms.
        if (!authenticationMechanismsContainsNone || interfaceIsSecure)
        {
            RETURN_IF_QSTATUS_ERROR(alljoyn_proxybusobject_secureconnection(ProxyBusObject, QCC_FALSE));
            RETURN_IF_QSTATUS_ERROR(AllJoynBusObjectManager::TryRegisterBusObject(m_nativeBusAttachment, BusObject, true));
        }
        else
        {
            RETURN_IF_QSTATUS_ERROR(AllJoynBusObjectManager::TryRegisterBusObject(m_nativeBusAttachment, BusObject, false));
        }
    }
    else
    {
        // If the current set of AuthenticationMechanisms does not support authentication
        // but the interface requires security, report an error.
        if (interfaceIsSecure)
        {
            return static_cast<int32>(ER_BUS_NO_AUTHENTICATION_MECHANISM);
        }
        else
        {
            RETURN_IF_QSTATUS_ERROR(AllJoynBusObjectManager::TryRegisterBusObject(m_nativeBusAttachment, BusObject, false));
        }
    }

    RETURN_IF_QSTATUS_ERROR(alljoyn_proxybusobject_addinterface(ProxyBusObject, description));
    
    m_signals->Initialize(BusObject, m_sessionId);

    return AllJoynStatus::Ok;
}
