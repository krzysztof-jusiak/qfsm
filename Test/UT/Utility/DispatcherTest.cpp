//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>
#include "Common/MsgTraits.hpp"
#include "QFsm/Utility/Dispatcher.hpp"

namespace QFsm
{

using namespace Test::Common;

namespace Utility
{
namespace UT
{

class HandlerStub
{
public:
    HandlerStub()
        : processEventCalls(0)
    { }

    template<typename Event> void processEvent(const Event&) { processEventCalls++; }

    int processEventCalls;
};

template<int expected> class HandlerMock
{
public:
    template<typename Event> void processEvent(const Event& p_event)
    {
        EXPECT_EQ(expected, *reinterpret_cast<const int*>(&p_event));
    }
};

template<int expected> class HandlerMockArg1
{
public:
    template<typename Event> void processEvent(const Event&, int p_arg1)
    {
        EXPECT_EQ(expected, p_arg1);
    }
};

template<int expected1, int expected2> class HandlerMockArg2
{
public:
    template<typename Event> void processEvent(const Event&, int p_arg1, int p_arg2)
    {
        EXPECT_EQ(expected1, p_arg1);
        EXPECT_EQ(expected2, p_arg2);
    }
};

class Handler
{
public:
    typedef boost::mpl::vector<Msg1, Msg2> Events;

    Handler()
        : processEventCalls(0)
    { }

    template<typename Event> void processEvent(const Event&) { processEventCalls++; }

    int processEventCalls;
};

struct Event1
{
    enum {value = 1};

    explicit Event1(int data)
        : data(data)
    { }

    int data;
};

template<int expected> class EventHandlerMock
{
public:
    template<typename T> void processEvent(const T& p_event)
    {
        EXPECT_EQ(expected, T::value);
        EXPECT_EQ(expected, p_event.data);
    }
};

template<typename Msg, typename Dispatcher, typename Handler>
void verifyHandler(bool p_expected, Dispatcher& p_dispatcher, Handler& p_handler)
{
    p_handler.processEventCalls = 0;
    EXPECT_EQ(p_expected, p_dispatcher.dispatch(createEvent<MsgTraits<Msg>::value>()));
    EXPECT_EQ(p_expected, p_handler.processEventCalls);
}

template<typename Msg, typename Dispatcher, typename Handler>
void verifyHandlerExtended(bool p_expected, bool p_handlerExpected, Dispatcher& p_dispatcher, Handler& p_handler)
{
    p_handler.processEventCalls = 0;
    EXPECT_EQ(p_expected, p_dispatcher.dispatch(createEvent<MsgTraits<Msg>::value>()));
    EXPECT_EQ(p_handlerExpected, p_handler.processEventCalls);
}

template<typename TRawEvent, typename TKey, typename TExecuteEvent> class Arg1DispatchType
{
public:
    typedef std::map<TKey, TExecuteEvent> type;

    template<typename T> static inline void init(T&) { }
    template<typename T> static inline bool check(T& p_entries, const TKey& p_key) { return p_entries.find(p_key) != p_entries.end(); }
    template<typename T> static inline boost::tuple<T, int> create(const TRawEvent& p_event) { return boost::tuple<T, int>(T(*p_event), T::value); }
    template<typename T> static inline TKey getId(const T& p_event) { return *p_event; }
    template<typename T> struct GetId { enum { value = T::value }; };
    template<typename T> struct GetType { typedef typename T::type type; };
};

template<typename TRawEvent, typename TKey, typename TExecuteEvent> class Arg2DispatchType
{
public:
    typedef std::map<TKey, TExecuteEvent> type;

    template<typename T> static inline void init(T&) { }
    template<typename T> static inline bool check(T& p_entries, const TKey& p_key) { return p_entries.find(p_key) != p_entries.end(); }
    template<typename T> static inline boost::tuple<T, int, int> create(const TRawEvent& p_event) { return boost::tuple<T, int, int>(T(*p_event), T::value, T::value); }
    template<typename T> static inline TKey getId(const T& p_event) { return *p_event; }
    template<typename T> struct GetId { enum { value = T::value }; };
    template<typename T> struct GetType { typedef typename T::type type; };
};

TEST(Dispatcher, DefaultsPolicies)
{
    //given
    Utility::Dispatcher<> l_dispatcher;
    const int id = 1;
    EventHandlerMock<id> l_handler;
    boost::shared_ptr<const int> l_event(new int(1));
    l_dispatcher.registerHandler< boost::mpl::vector<Event1> >(l_handler);

    //when & then
    EXPECT_TRUE(l_dispatcher.dispatch(l_event));
}

TEST(Dispatcher, Empty)
{
    //given
    Dispatcher<> l_dispatcher;

    //when & then
    EXPECT_FALSE(l_dispatcher.dispatch(createEvent<0>()));
}

TEST(Dispatcher, SimpleHandlerNotDispatched)
{
    //given
    Dispatcher<> l_dispatcher;
    HandlerStub l_handler;
    l_dispatcher.registerHandler< boost::mpl::vector<Msg1> >(l_handler);

    //when & then
    EXPECT_FALSE(l_dispatcher.dispatch(createEvent<0>()));
    EXPECT_EQ(0, l_handler.processEventCalls);
}

TEST(Dispatcher, SimpleHandlerDispatchedSuccessful)
{
    //given
    Dispatcher<> l_dispatcher;
    HandlerStub l_handler;
    l_dispatcher.registerHandler< boost::mpl::vector<Msg1> >(l_handler);

    //when & then
    EXPECT_TRUE(l_dispatcher.dispatch(createEvent<MsgTraits<Msg1>::value>()));
    EXPECT_EQ(1, l_handler.processEventCalls);
}

TEST(Dispatcher, DispatchSingleMsgInHandler)
{
    //given
    Dispatcher<> l_dispatcher;
    HandlerStub l_handler;
    l_dispatcher.registerHandler<Msg1>(l_handler);

    //when & then
    EXPECT_TRUE(l_dispatcher.dispatch(createEvent<MsgTraits<Msg1>::value>()));
    EXPECT_EQ(1, l_handler.processEventCalls);
}

TEST(Dispatcher, DispatchedSuccessfulTwoHandlers)
{
    //given
    Dispatcher<> l_dispatcher;
    HandlerStub l_handler1;
    HandlerStub l_handler2;

    l_dispatcher.registerHandler< boost::mpl::vector<Msg1> >(l_handler1);
    l_dispatcher.registerHandler< boost::mpl::vector<Msg1> >(l_handler2);

    //when & then
    EXPECT_TRUE(l_dispatcher.dispatch(createEvent<MsgTraits<Msg1>::value>()));
    EXPECT_EQ(1, l_handler1.processEventCalls);
    EXPECT_EQ(1, l_handler2.processEventCalls);
}

TEST(Dispatcher, DispatchedSuccessfulTwoHandlersOneOk)
{
    //given
    Dispatcher<> l_dispatcher;
    HandlerStub l_handler1;
    HandlerStub l_handler2;

    l_dispatcher.registerHandler< boost::mpl::vector<Msg1> >(l_handler1);
    l_dispatcher.registerHandler< boost::mpl::vector<Msg2> >(l_handler2);

    //when & then
    EXPECT_TRUE(l_dispatcher.dispatch(createEvent<MsgTraits<Msg1>::value>()));
    EXPECT_EQ(1, l_handler1.processEventCalls);
    EXPECT_EQ(0, l_handler2.processEventCalls);
}

TEST(Dispatcher, DispatchedManyHandlersFail)
{
    //given
    Dispatcher<> l_dispatcher;
    HandlerStub l_handler1;
    HandlerStub l_handler2;

    l_dispatcher.registerHandler< boost::mpl::vector<Msg1> >(l_handler1);
    l_dispatcher.registerHandler< boost::mpl::vector<Msg2> >(l_handler2);

    //when & then
    EXPECT_FALSE(l_dispatcher.dispatch(createEvent<MsgTraits<Msg5>::value>()));
    EXPECT_EQ(0, l_handler1.processEventCalls);
    EXPECT_EQ(0, l_handler2.processEventCalls);
}

TEST(Dispatcher, DispatchedManyMsgs)
{
    //given
    Dispatcher<> l_dispatcher;
    HandlerStub l_handler;

    l_dispatcher.registerHandler< boost::mpl::vector<Msg5, Msg6, Msg7, Msg8, Msg9> >(l_handler);

    //when & then
    verifyHandler<Msg1>(false, l_dispatcher, l_handler);
    verifyHandler<Msg2>(false, l_dispatcher, l_handler);
    verifyHandler<Msg3>(false, l_dispatcher, l_handler);
    verifyHandler<Msg4>(false, l_dispatcher, l_handler);
    verifyHandler<Msg5>(true,  l_dispatcher, l_handler);
    verifyHandler<Msg6>(true,  l_dispatcher, l_handler);
    verifyHandler<Msg7>(true,  l_dispatcher, l_handler);
    verifyHandler<Msg8>(true,  l_dispatcher, l_handler);
    verifyHandler<Msg9>(true,  l_dispatcher, l_handler);
}

TEST(Dispatcher, VerifyPayload)
{
    //given
    Dispatcher<> l_dispatcher;

    //expected
    HandlerMock<MsgTraits<Msg1>::value> l_handler;

    l_dispatcher.registerHandler< boost::mpl::vector<Msg1> >(l_handler);

    //when & then
    EXPECT_TRUE(l_dispatcher.dispatch(createEvent<MsgTraits<Msg1>::value>()));
}

TEST(Dispatcher, DispatchUsingId)
{
    //given
    Dispatcher<> l_dispatcher;
    HandlerStub l_handler;

    l_dispatcher.registerHandler< boost::mpl::vector<MsgTraitsValue<1>, MsgTraitsValue<2>, MsgTraitsValue<3>, MsgTraitsValue<4> > >(l_handler);

    //when & then
    verifyHandler<Msg1>(true, l_dispatcher, l_handler);
    verifyHandler<Msg2>(true, l_dispatcher, l_handler);
    verifyHandler<Msg3>(true, l_dispatcher, l_handler);
    verifyHandler<Msg4>(true, l_dispatcher, l_handler);
    verifyHandler<Msg5>(false, l_dispatcher, l_handler);
}

TEST(Dispatcher, DispatchMix)
{
    //given
    Dispatcher<> l_dispatcher;

    HandlerStub l_handler1;
    HandlerStub l_handler2;

    l_dispatcher.registerHandler< boost::mpl::vector<MsgTraitsValue<1>, MsgTraitsValue<2> > >(l_handler1);
    l_dispatcher.registerHandler< boost::mpl::vector<Msg1, Msg5> >(l_handler2);

    //when & then
    verifyHandlerExtended<Msg1>(true, true, l_dispatcher, l_handler1);
    verifyHandlerExtended<Msg2>(true, true, l_dispatcher, l_handler1);
    verifyHandlerExtended<Msg5>(true, false, l_dispatcher, l_handler1);
    verifyHandlerExtended<Msg6>(false, false, l_dispatcher, l_handler1);

    verifyHandlerExtended<Msg1>(true, true, l_dispatcher, l_handler2);
    verifyHandlerExtended<Msg2>(true, false, l_dispatcher, l_handler2);
    verifyHandlerExtended<Msg5>(true, true, l_dispatcher, l_handler2);
    verifyHandlerExtended<Msg6>(false, false, l_dispatcher, l_handler2);
}

TEST(Dispatcher, DispatchMixInOneHandler)
{
    //given
    Dispatcher<> l_dispatcher;
    HandlerStub l_handler;

    l_dispatcher.registerHandler< boost::mpl::vector<Msg1, MsgTraitsValue<2>, Msg3, MsgTraitsValue<4> > >(l_handler);

    //when & then
    verifyHandler<Msg1>(true,  l_dispatcher, l_handler);
    verifyHandler<Msg2>(true,  l_dispatcher, l_handler);
    verifyHandler<Msg3>(true,  l_dispatcher, l_handler);
    verifyHandler<Msg4>(true,  l_dispatcher, l_handler);
    verifyHandler<Msg5>(false, l_dispatcher, l_handler);
}

TEST(Dispatcher, EventsInsideHandler)
{
    //given
    Dispatcher<> l_dispatcher;
    Handler l_handler;

    l_dispatcher.registerHandler(l_handler);

    //when & then
    verifyHandler<Msg1>(true,  l_dispatcher, l_handler);
    verifyHandler<Msg2>(true,  l_dispatcher, l_handler);
    verifyHandler<Msg3>(false, l_dispatcher, l_handler);
    verifyHandler<Msg4>(false, l_dispatcher, l_handler);
    verifyHandler<Msg5>(false, l_dispatcher, l_handler);
}

TEST(Dispatcher, AdditionalArgument)
{
    //given
    Dispatcher<int, boost::shared_ptr<const int>, Arg1DispatchType> l_dispatcher;

    //expected
    HandlerMockArg1<MsgTraits<Msg1>::value> l_handler;
    l_dispatcher.registerHandler< boost::mpl::vector<Msg1> >(l_handler);

    //when & then
    EXPECT_TRUE(l_dispatcher.dispatch(createEvent<MsgTraits<Msg1>::value>()));
}

TEST(Dispatcher, AdditionalArguments)
{
    //given
    Dispatcher<int, boost::shared_ptr<const int>, Arg2DispatchType> l_dispatcher;

    //expected
    HandlerMockArg2<MsgTraits<Msg1>::value, MsgTraits<Msg1>::value> l_handler;
    l_dispatcher.registerHandler< boost::mpl::vector<Msg1> >(l_handler);

    //when & then
    EXPECT_TRUE(l_dispatcher.dispatch(createEvent<MsgTraits<Msg1>::value>()));
}

} // namespace UT
} // namespace Utility
} // namespace QFsm

