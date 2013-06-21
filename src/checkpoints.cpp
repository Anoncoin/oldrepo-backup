// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (       1, uint256("0x8fe2901fc0999bc86ea2668c58802ee87165438166d18154f1bd4f917bf25e0f"))
        (       7, uint256("0x4530df06d98fc77d04dab427630fc63b45f10d2b0ad3ad3a651883938986d629"))
        (     42, uint256("0x6a4fbf1b3d569ff01ceaedd7b9447a8f13c815cbe7024c4f6f6865d2428aa603"))
        (     77, uint256("0x00c714c55e396cd7a39d824aae8438e5633e62a4a0e56461e792ed3254731e03"))
        (   420, uint256("0x51a8f5e247354b8c39632b984970f2c7c006b341524da3668d1a9a4a94fb2a32"))
        (   777, uint256("0x13682ff40afe0a643f574efe41de35453655f84644aa31fc78657c47edc3afb8"))
        ( 1000, uint256("0x21bd2ccfbabce89927e58eb946c84cf243630c52ec4bf88b3c0fd912e58573ea"))
        ( 7777, uint256("0xae3094030b34a422c44b9832c84fe602d0d528449d6940374bd43b4472b4df5e"))
        ( 10000, uint256("0x3c29f365a04d8bf17b68d604c4cb6ed3e14c1b42a16a8ab923d9a978eff18e16"))
        (12000,  uint256("0x3190cc82c2092c11bab35b246a3e17f9252d912090d1b071dbfa5588842f0e0e"))
        (14000,  uint256("0xb728b67772af1b2994dbcaca7aab239f639886e7354e3a610c10e5556261a971"))
       ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;

        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
