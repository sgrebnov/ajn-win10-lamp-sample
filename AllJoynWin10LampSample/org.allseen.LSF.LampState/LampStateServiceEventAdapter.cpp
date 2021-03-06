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

using namespace Microsoft::WRL;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Devices::AllJoyn;
using namespace org::allseen::LSF::LampState;

// Note: Unlike an Interface implementation, which provides a single handler for each member, the event
// model allows for 0 or more listeners to be registered. The EventAdapter implementation deals with this
// difference by implementing a last-writer-wins policy. The lack of any return value (i.e., 0 listeners)
// is handled by returning a null result.

// Methods
IAsyncOperation<LampStateTransitionLampStateResult^>^ LampStateServiceEventAdapter::TransitionLampStateAsync(_In_ AllJoynMessageInfo^ info, _In_ uint64 interfaceMemberTimestamp, _In_ Windows::Foundation::Collections::IMapView<Platform::String^,Platform::Object^>^ interfaceMemberNewState, _In_ uint32 interfaceMemberTransitionPeriod)
{
    auto args = ref new LampStateTransitionLampStateCalledEventArgs(info, interfaceMemberTimestamp, interfaceMemberNewState, interfaceMemberTransitionPeriod);
    AllJoynHelpers::DispatchEvent([=]() {
        TransitionLampStateCalled(this, args);
    });
    return LampStateTransitionLampStateCalledEventArgs::GetResultAsync(args);
}

IAsyncOperation<LampStateApplyPulseEffectResult^>^ LampStateServiceEventAdapter::ApplyPulseEffectAsync(_In_ AllJoynMessageInfo^ info, _In_ Windows::Foundation::Collections::IMapView<Platform::String^,Platform::Object^>^ interfaceMemberFromState, _In_ Windows::Foundation::Collections::IMapView<Platform::String^,Platform::Object^>^ interfaceMemberToState, _In_ uint32 interfaceMemberPeriod, _In_ uint32 interfaceMemberDuration, _In_ uint32 interfaceMemberNumPulses, _In_ uint64 interfaceMemberTimestamp)
{
    auto args = ref new LampStateApplyPulseEffectCalledEventArgs(info, interfaceMemberFromState, interfaceMemberToState, interfaceMemberPeriod, interfaceMemberDuration, interfaceMemberNumPulses, interfaceMemberTimestamp);
    AllJoynHelpers::DispatchEvent([=]() {
        ApplyPulseEffectCalled(this, args);
    });
    return LampStateApplyPulseEffectCalledEventArgs::GetResultAsync(args);
}

// Property Reads
IAsyncOperation<LampStateGetVersionResult^>^ LampStateServiceEventAdapter::GetVersionAsync(_In_ AllJoynMessageInfo^ info)
{
    auto args = ref new LampStateGetVersionRequestedEventArgs(info);
    AllJoynHelpers::DispatchEvent([=]() {
        GetVersionRequested(this, args);
    });
    return LampStateGetVersionRequestedEventArgs::GetResultAsync(args);
}

IAsyncOperation<LampStateGetOnOffResult^>^ LampStateServiceEventAdapter::GetOnOffAsync(_In_ AllJoynMessageInfo^ info)
{
    auto args = ref new LampStateGetOnOffRequestedEventArgs(info);
    AllJoynHelpers::DispatchEvent([=]() {
        GetOnOffRequested(this, args);
    });
    return LampStateGetOnOffRequestedEventArgs::GetResultAsync(args);
}

IAsyncOperation<LampStateGetHueResult^>^ LampStateServiceEventAdapter::GetHueAsync(_In_ AllJoynMessageInfo^ info)
{
    auto args = ref new LampStateGetHueRequestedEventArgs(info);
    AllJoynHelpers::DispatchEvent([=]() {
        GetHueRequested(this, args);
    });
    return LampStateGetHueRequestedEventArgs::GetResultAsync(args);
}

IAsyncOperation<LampStateGetSaturationResult^>^ LampStateServiceEventAdapter::GetSaturationAsync(_In_ AllJoynMessageInfo^ info)
{
    auto args = ref new LampStateGetSaturationRequestedEventArgs(info);
    AllJoynHelpers::DispatchEvent([=]() {
        GetSaturationRequested(this, args);
    });
    return LampStateGetSaturationRequestedEventArgs::GetResultAsync(args);
}

IAsyncOperation<LampStateGetColorTempResult^>^ LampStateServiceEventAdapter::GetColorTempAsync(_In_ AllJoynMessageInfo^ info)
{
    auto args = ref new LampStateGetColorTempRequestedEventArgs(info);
    AllJoynHelpers::DispatchEvent([=]() {
        GetColorTempRequested(this, args);
    });
    return LampStateGetColorTempRequestedEventArgs::GetResultAsync(args);
}

IAsyncOperation<LampStateGetBrightnessResult^>^ LampStateServiceEventAdapter::GetBrightnessAsync(_In_ AllJoynMessageInfo^ info)
{
    auto args = ref new LampStateGetBrightnessRequestedEventArgs(info);
    AllJoynHelpers::DispatchEvent([=]() {
        GetBrightnessRequested(this, args);
    });
    return LampStateGetBrightnessRequestedEventArgs::GetResultAsync(args);
}

// Property Writes
IAsyncOperation<LampStateSetOnOffResult^>^ LampStateServiceEventAdapter::SetOnOffAsync(_In_ AllJoynMessageInfo^ info, _In_ bool value)
{
    auto args = ref new LampStateSetOnOffRequestedEventArgs(info, value);
    AllJoynHelpers::DispatchEvent([=]() {
        SetOnOffRequested(this, args);
    });
    return LampStateSetOnOffRequestedEventArgs::GetResultAsync(args);
}

IAsyncOperation<LampStateSetHueResult^>^ LampStateServiceEventAdapter::SetHueAsync(_In_ AllJoynMessageInfo^ info, _In_ uint32 value)
{
    auto args = ref new LampStateSetHueRequestedEventArgs(info, value);
    AllJoynHelpers::DispatchEvent([=]() {
        SetHueRequested(this, args);
    });
    return LampStateSetHueRequestedEventArgs::GetResultAsync(args);
}

IAsyncOperation<LampStateSetSaturationResult^>^ LampStateServiceEventAdapter::SetSaturationAsync(_In_ AllJoynMessageInfo^ info, _In_ uint32 value)
{
    auto args = ref new LampStateSetSaturationRequestedEventArgs(info, value);
    AllJoynHelpers::DispatchEvent([=]() {
        SetSaturationRequested(this, args);
    });
    return LampStateSetSaturationRequestedEventArgs::GetResultAsync(args);
}

IAsyncOperation<LampStateSetColorTempResult^>^ LampStateServiceEventAdapter::SetColorTempAsync(_In_ AllJoynMessageInfo^ info, _In_ uint32 value)
{
    auto args = ref new LampStateSetColorTempRequestedEventArgs(info, value);
    AllJoynHelpers::DispatchEvent([=]() {
        SetColorTempRequested(this, args);
    });
    return LampStateSetColorTempRequestedEventArgs::GetResultAsync(args);
}

IAsyncOperation<LampStateSetBrightnessResult^>^ LampStateServiceEventAdapter::SetBrightnessAsync(_In_ AllJoynMessageInfo^ info, _In_ uint32 value)
{
    auto args = ref new LampStateSetBrightnessRequestedEventArgs(info, value);
    AllJoynHelpers::DispatchEvent([=]() {
        SetBrightnessRequested(this, args);
    });
    return LampStateSetBrightnessRequestedEventArgs::GetResultAsync(args);
}

