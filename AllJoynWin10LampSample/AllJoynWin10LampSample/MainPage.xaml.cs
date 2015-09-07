using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;


using org.allseen.LSF.LampState;
using Windows.Devices.AllJoyn;
using System.Diagnostics;



// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace AllJoynWin10LampSample
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private LampStateConsumer _lampState;

        public MainPage()
        {
            this.InitializeComponent();

            FindLamp();
        }

        public void FindLamp()
        {
            Debug.WriteLine("Discovering AllJoyn lamps ...");

            AllJoynBusAttachment busAttachment = new AllJoynBusAttachment();

            LampStateWatcher watcher = new LampStateWatcher(busAttachment);
            watcher.Added += LampFound;
            watcher.Start();
        }
        
        private async void LampFound(LampStateWatcher sender, AllJoynServiceInfo args)
        {
            Debug.WriteLine("Lamp found, attempt to join session..");

            var joinResult = await LampStateConsumer.JoinSessionAsync(args, sender);

            if (joinResult.Status == AllJoynStatus.Ok)
            {
                _lampState = joinResult.Consumer;
                Debug.WriteLine("Consumer has been susccessfully initialized");

                await _lampState.SetOnOffAsync(PowerSwitch.IsOn);
                await _lampState.SetBrightnessAsync(/* 10% */ Convert.ToUInt32(UInt32.MaxValue * 0.1));
            }
            else
            {
                Debug.WriteLine("Ubable to join session");
            }
        }

        private async void PowerSwitch_Toggled(object sender, Windows.UI.Xaml.RoutedEventArgs e)
        {
            if (_lampState != null)
            {
                await _lampState.SetOnOffAsync(PowerSwitch.IsOn);
            }
        }

        private async void Brightness_ValueChanged(object sender, RangeBaseValueChangedEventArgs e)
        {
            if (_lampState != null)
            {
                var value = Convert.ToUInt32(UInt32.MaxValue * (e.NewValue / 100.0));
                await _lampState.SetBrightnessAsync(value);
            }
        }
    }
}
