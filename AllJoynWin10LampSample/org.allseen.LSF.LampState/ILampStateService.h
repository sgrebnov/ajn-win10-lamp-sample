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
#pragma once

namespace org { namespace allseen { namespace LSF { namespace LampState {

public interface class ILampStateService
{
public:
    // Implement this function to handle calls to the TransitionLampState method.
    Windows::Foundation::IAsyncOperation<LampStateTransitionLampStateResult^>^ TransitionLampStateAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info , _In_ uint64 interfaceMemberTimestamp, _In_ Windows::Foundation::Collections::IMapView<Platform::String^,Platform::Object^>^ interfaceMemberNewState, _In_ uint32 interfaceMemberTransitionPeriod);

    // Implement this function to handle calls to the ApplyPulseEffect method.
    Windows::Foundation::IAsyncOperation<LampStateApplyPulseEffectResult^>^ ApplyPulseEffectAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info , _In_ Windows::Foundation::Collections::IMapView<Platform::String^,Platform::Object^>^ interfaceMemberFromState, _In_ Windows::Foundation::Collections::IMapView<Platform::String^,Platform::Object^>^ interfaceMemberToState, _In_ uint32 interfaceMemberPeriod, _In_ uint32 interfaceMemberDuration, _In_ uint32 interfaceMemberNumPulses, _In_ uint64 interfaceMemberTimestamp);

    // Implement this function to handle requests for the value of the Version property.
    //
    // Currently, info will always be null, because no information is available about the requestor.
    Windows::Foundation::IAsyncOperation<LampStateGetVersionResult^>^ GetVersionAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info);

    // Implement this function to handle requests for the value of the OnOff property.
    //
    // Currently, info will always be null, because no information is available about the requestor.
    Windows::Foundation::IAsyncOperation<LampStateGetOnOffResult^>^ GetOnOffAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info);

    // Implement this function to handle requests to set the OnOff property.
    //
    // Currently, info will always be null, because no information is available about the requestor.
    Windows::Foundation::IAsyncOperation<LampStateSetOnOffResult^>^ SetOnOffAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info, bool value);

    // Implement this function to handle requests for the value of the Hue property.
    //
    // Currently, info will always be null, because no information is available about the requestor.
    Windows::Foundation::IAsyncOperation<LampStateGetHueResult^>^ GetHueAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info);

    // Implement this function to handle requests to set the Hue property.
    //
    // Currently, info will always be null, because no information is available about the requestor.
    Windows::Foundation::IAsyncOperation<LampStateSetHueResult^>^ SetHueAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info, uint32 value);

    // Implement this function to handle requests for the value of the Saturation property.
    //
    // Currently, info will always be null, because no information is available about the requestor.
    Windows::Foundation::IAsyncOperation<LampStateGetSaturationResult^>^ GetSaturationAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info);

    // Implement this function to handle requests to set the Saturation property.
    //
    // Currently, info will always be null, because no information is available about the requestor.
    Windows::Foundation::IAsyncOperation<LampStateSetSaturationResult^>^ SetSaturationAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info, uint32 value);

    // Implement this function to handle requests for the value of the ColorTemp property.
    //
    // Currently, info will always be null, because no information is available about the requestor.
    Windows::Foundation::IAsyncOperation<LampStateGetColorTempResult^>^ GetColorTempAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info);

    // Implement this function to handle requests to set the ColorTemp property.
    //
    // Currently, info will always be null, because no information is available about the requestor.
    Windows::Foundation::IAsyncOperation<LampStateSetColorTempResult^>^ SetColorTempAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info, uint32 value);

    // Implement this function to handle requests for the value of the Brightness property.
    //
    // Currently, info will always be null, because no information is available about the requestor.
    Windows::Foundation::IAsyncOperation<LampStateGetBrightnessResult^>^ GetBrightnessAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info);

    // Implement this function to handle requests to set the Brightness property.
    //
    // Currently, info will always be null, because no information is available about the requestor.
    Windows::Foundation::IAsyncOperation<LampStateSetBrightnessResult^>^ SetBrightnessAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info, uint32 value);

};

} } } } 
