// **********************************************************************
//
// Copyright (c) 2002
// MutableRealms, Inc.
// Huntsville, AL, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef ICE_CONNECTION_H
#define ICE_CONNECTION_H

#include <Ice/ConnectionF.h>
#include <Ice/InstanceF.h>
#include <Ice/TransceiverF.h>
#include <Ice/ObjectAdapterF.h>
#include <Ice/EndpointF.h>
#include <Ice/ThreadPoolF.h>
#include <Ice/LoggerF.h>
#include <Ice/TraceLevelsF.h>
#include <Ice/EventHandler.h>

namespace Ice
{

class LocalException;

}

namespace IceInternal
{

class Outgoing;

class Connection : public EventHandler, public JTCRecursiveMutex
{
public:

    Connection(const InstancePtr&, const TransceiverPtr&, const EndpointPtr&, const ::Ice::ObjectAdapterPtr&);
    virtual ~Connection();

    bool destroyed() const;
    void hold();
    void activate();
    void prepareRequest(Outgoing*);
    void sendRequest(Outgoing*, bool);
    void removeRequest(Outgoing*);
    void prepareBatchRequest(Outgoing*);
    void finishBatchRequest(Outgoing*);
    void abortBatchRequest();
    void flushBatchRequest();
    int timeout() const;

    //
    // Operations from EventHandler
    //
    virtual bool server() const;
    virtual bool readable() const;
    virtual void read(BasicStream&);
    virtual void message(BasicStream&);
    virtual void exception(const ::Ice::LocalException&);
    virtual void finished();

private:

    enum State
    {
	StateActive,
	StateHolding,
	StateClosing,
	StateClosed
    };

    void setState(State, const ::Ice::LocalException&);
    void setState(State);
    void closeConnection();
    void warning(const ::Ice::LocalException&) const;

    TransceiverPtr _transceiver;
    EndpointPtr _endpoint;
    ::Ice::ObjectAdapterPtr _adapter;
    ThreadPoolPtr _threadPool;
    ::Ice::LoggerPtr _logger;
    TraceLevelsPtr _traceLevels;
    ::Ice::Int _nextRequestId;
    std::map< ::Ice::Int, Outgoing*> _requests;
    std::map< ::Ice::Int, Outgoing*>::iterator _requestsHint;
    std::auto_ptr< ::Ice::LocalException> _exception;
    BasicStream _batchStream;
    int _responseCount;
    State _state;
    bool _warn;
};

}

#endif
