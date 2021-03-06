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
    namespace objects
    {
        public sealed class EI : Test.E
        {
            public EI() : base(1, "hello")
            {
            }

            public bool checkValues()
            {
                return i == 1 && s.Equals("hello");
            }
        }
    }
}
