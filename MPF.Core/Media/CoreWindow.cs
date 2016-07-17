﻿using MPF.Interop;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MPF.Media
{
    public class CancellableEventArgs : EventArgs
    {
        public bool Cancelled { get; set; }
    }

    public sealed class CoreWindow
    {
        private readonly INativeWindow _nativeWindow;
        private readonly IDeviceContext _deviceContext;

        public event EventHandler<CancellableEventArgs> Closing;

        public bool HasMaximize
        {
            get { return _nativeWindow.HasMaximize; }
            set { _nativeWindow.HasMaximize = value; }
        }

        public string Title
        {
            get { return _nativeWindow.Title; }
            set { _nativeWindow.Title = value; }
        }

        public CoreWindow()
        {
            _nativeWindow = Platform.CreateNativeWindow(OnNativeWindowMessage);
            _deviceContext = Platform.CreateDeviceContext(_nativeWindow);
        }

        private void OnNativeWindowMessage(NativeWindowMessages message)
        {
            switch (message)
            {
                case NativeWindowMessages.Closing:
                    OnClosing();
                    break;
                default:
                    break;
            }
        }

        private void OnClosing()
        {
            var e = new CancellableEventArgs();
            Closing?.Invoke(this, e);
            if (!e.Cancelled)
                _nativeWindow.Destroy();
        }

        public void Show()
        {
            _nativeWindow.Show();
        }

        public void Hide()
        {
            _nativeWindow.Hide();
        }
    }
}
