// **********************************************************************
//
// Copyright (c) 2003-2018 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <TestI.h>
#include <TestHelper.h>

using namespace std;

class Server : public Test::TestHelper
{
public:

    void run(int, char**);
};

void
Server::run(int argc, char** argv)
{
    Ice::CommunicatorHolder communicator = initialize(argc, argv);
    Ice::ObjectAdapterPtr adpt = communicator->createObjectAdapter("ReplicatedAdapter");
    Ice::PropertiesPtr properties = communicator->getProperties();
    Ice::ObjectPtr object = new TestI(properties);
    adpt->add(object, Ice::stringToIdentity(properties->getProperty("Ice.ProgramName")));
    adpt->add(object, Ice::stringToIdentity(properties->getProperty("Identity")));
    try
    {
        adpt->activate();
        communicator->getAdmin();
    }
    catch(const Ice::ObjectAdapterDeactivatedException&)
    {
    }
    catch(const Ice::CommunicatorDestroyedException&)
    {
        //
        // getAdmin might raise this if communicator is shutdown by
        // servant.
        //
    }
    communicator->waitForShutdown();
}

DEFINE_TEST(Server)
