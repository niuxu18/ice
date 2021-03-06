// **********************************************************************
//
// Copyright (c) 2003-2018 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

namespace Ice
{
    namespace servantLocator
    {
        public sealed class TestActivationI : Test.TestActivationDisp_
        {
            override public void activateServantLocator(bool activate, Ice.Current current)
            {
                if(activate)
                {
                    current.adapter.addServantLocator(new ServantLocatorI(""), "");
                    current.adapter.addServantLocator(new ServantLocatorI("category"), "category");
                }
                else
                {
                    var locator = current.adapter.removeServantLocator("");
                    locator.deactivate("");
                    locator = current.adapter.removeServantLocator("category");
                    locator.deactivate("category");
                }
            }
        }
    }
}
