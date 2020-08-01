// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2019 The PIVX developers
//Copyright (c) 2020 The KoinMudra developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "bignum.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (      0, uint256("0x0000021c47d6132a5bebca5c656d25e3c094213f6bad5315dcfc3523cc94dd2d"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1595310000, // * UNIX timestamp of last checkpoint block
    0,     // * total number of transactions between genesis and last checkpoint (the tx=... number in the SetBestChain debug.log lines)
    1440        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x00000ed928bd79ff94c1d6cddd48741530db56f01385edf352010f5d1a477d5f"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1595320000, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint (the tx=... number in the SetBestChain debug.log lines)
    1440        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x00000ed928bd79ff94c1d6cddd48741530db56f01385edf352010f5d1a477d5f"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1595320000, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint (the tx=... number in the SetBestChain debug.log lines)
    1440        // * estimated number of transactions per day after checkpoint
};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID                      = CBaseChainParams::MAIN;
        strNetworkID                   = "main";

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0]             = 0x20;
        pchMessageStart[1]             = 0xcb;
        pchMessageStart[2]             = 0x25;
        pchMessageStart[3]             = 0xce;
        vAlertPubKey                   = ParseHex("04cfe8280e3af2a1572c991dac99cf9c7c5d754534576050edabcb6b1876cc9e9d4e7ae01740a127f9d89c508d9f386bf5d23ad5a6eb7c8d5bc52fad7c60f39df2");
        nDefaultPort                   = 40009;
        nSubsidyHalvingInterval        = 1050000;
        nMaxReorganizationDepth        = 100;
        nEnforceBlockUpgradeMajority   = 750;
        nRejectBlockOutdatedMajority   = 950;
        nToCheckBlockUpgradeMajority   = 1000;
        nMinerThreads                  = 0;

        bnProofOfWorkLimit             = ~uint256(0) >> 20;
        nTargetTimespan                =  1 * 60; 
        nTargetSpacing                 =  1 * 60;  // KMI: 1 minute blocks during POW (block 1-200)

        bnProofOfStakeLimit            = ~uint256(0) >> 20;
        nTargetTimespanPOS             = 40 * 60; 
        nTargetSpacingPOS              =  1 * 60;  // KMI: 1 minute blocks during POS

        nMaturity                      = 5; // 6 block maturity (+1 elsewhere)
        nMasternodeCountDrift          = 20;
        nMaxMoneyOut                   = 20000000 * COIN; // 20 million max supply

        /** Height or Time Based Activations **/
        nLastPOWBlock                  = 2000;
        nModifierUpdateBlock           = 1;

/*
---------------
algorithm: quark
pzTimestamp: Coronavirus India Updates, July 21: Two vaccines in Phase I and II trials; fatality rate drops to 2.43%. July 21, 2020.
pubkey: 040ec90902813b0528228715b76d72ad505772b5c462b4b11c668b5d0da3a5e9d236fd7754cdc23a245ec9e54d9afab53440700c6b8a61fbdd6d864c28672d583a
bits: 504365040
time: 1595310000
merkle root hash: 2b42c0b32229cf6bf75c200d7c36dd51fbff360cacc3b04460d013c4d6631b19
Searching for genesis hash...
nonce: 1548099
genesis hash: 0000021c47d6132a5bebca5c656d25e3c094213f6bad5315dcfc3523cc94dd2d
*/

        const char* pszTimestamp       = "Coronavirus India Updates, July 21: Two vaccines in Phase I and II trials; fatality rate drops to 2.43%. July 21, 2020.";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig         = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue           = 0 * COIN;
        txNew.vout[0].scriptPubKey     = CScript() << ParseHex("040ec90902813b0528228715b76d72ad505772b5c462b4b11c668b5d0da3a5e9d236fd7754cdc23a245ec9e54d9afab53440700c6b8a61fbdd6d864c28672d583a") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock          = 0;
        genesis.hashMerkleRoot         = genesis.BuildMerkleTree();
        genesis.nVersion               = 1;
        genesis.nTime                  = 1595310000;
        genesis.nBits                  = 504365040;
        genesis.nNonce                 = 1548099;


        hashGenesisBlock               = genesis.GetHash();
        assert(hashGenesisBlock        == uint256("0x0000021c47d6132a5bebca5c656d25e3c094213f6bad5315dcfc3523cc94dd2d"));
        assert(genesis.hashMerkleRoot  == uint256("0x2b42c0b32229cf6bf75c200d7c36dd51fbff360cacc3b04460d013c4d6631b19"));
 
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,  45);  // Start with 'K' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,  50);  // Start with 'M' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 193);  // from https://en.bitcoin.it/wiki/List_of_address_prefixes
        
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x78)(0xC2)(0x1E).convert_to_container<std::vector<unsigned char> >(); // SecureCloud BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x03)(0x78)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >(); // SecureCloud BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x81)(0x00)(0x92)(0xf1).convert_to_container<std::vector<unsigned char> >(); // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 109 	0x800092f1

        vFixedSeeds.clear();
        vSeeds.clear();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        vSeeds.push_back(CDNSSeedData("seed01.koinmudra.com", "seed01.koinmudra.com"));
        vSeeds.push_back(CDNSSeedData("seed02.koinmudra.com", "seed02.koinmudra.com"));
        vSeeds.push_back(CDNSSeedData("seed03.koinmudra.com", "seed03.koinmudra.com"));
        vSeeds.push_back(CDNSSeedData("seed04.koinmudra.com", "seed04.koinmudra.com"));
        vSeeds.push_back(CDNSSeedData("explorer.koinmudra.com", "explorer.koinmudra.com"));
        vSeeds.push_back(CDNSSeedData("koinmudra.com", "koinmudra.com"));

        fMiningRequiresPeers           = true;
        fAllowMinDifficultyBlocks      = false;
        fDefaultConsistencyChecks      = false;
        fRequireStandard               = true;
        fMineBlocksOnDemand            = false;
        fSkipProofOfWorkCheck          = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive     = false;

        nPoolMaxTransactions           = 3;
        strSporkKey                    = "0446c867d14ac892741c068436c05b6b161957aed0261dfa52e830eb124030fb19d96a206563c3011bec319e268b0284d42e48e59c24da7fd1b2012986e9bcef7f";
        strMasternodePoolDummyAddress  = "KDzaDvzEZKuKvMMRRBs6j5hEPwizepJiYx";
        nStartMasternodePayments       = 1595320000; 

        nBudget_Fee_Confirmations      = 6; // Number of confirmations for the finalization fee

        strTreasuryAddress             = "KFigrrPcu64pB4cBbNucak5EtXTEDDv2DT";
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID                      = CBaseChainParams::TESTNET;
        strNetworkID                   = "test";
        pchMessageStart[0]             = 0x42;
        pchMessageStart[1]             = 0x2c;
        pchMessageStart[2]             = 0x31;
        pchMessageStart[3]             = 0xbd;
        vAlertPubKey                   = ParseHex("042deb967096edb561309f45312c75f8d581326b4fb409213456f1214f89d87053956fffd9d1b45bc2ec649bd8a0fa38b5f57e10b273c4687e062bc1e835065deb");
        nDefaultPort                   = 40007;
        nEnforceBlockUpgradeMajority   = 51;
        nRejectBlockOutdatedMajority   = 75;
        nToCheckBlockUpgradeMajority   = 100;
        nMinerThreads                  = 0;

        bnProofOfWorkLimit             = ~uint256(0) >> 20;
        nTargetTimespan                =  1 * 60; 
        nTargetSpacing                 =  1 * 60;  // KMI: 1 minute blocks during POW (block 1-200) on testnet

        bnProofOfStakeLimit            = ~uint256(0) >> 20;
        nTargetTimespanPOS             =  40 * 60; 
        nTargetSpacingPOS              =   1 * 60;  // KMI: 1 minute blocks during POS on testnet

        nLastPOWBlock                  = 1000;
        nMaturity                      = 5;
        nMasternodeCountDrift          = 4;
        nModifierUpdateBlock           = 1;
        nMaxMoneyOut                   = 250000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime                  = 1595320000;
        genesis.nBits                  = 504365040;
        genesis.nNonce                 = 1844015;

        hashGenesisBlock               = genesis.GetHash();
        assert(hashGenesisBlock        == uint256("0x00000ed928bd79ff94c1d6cddd48741530db56f01385edf352010f5d1a477d5f"));
        assert(genesis.hashMerkleRoot  == uint256("0x2b42c0b32229cf6bf75c200d7c36dd51fbff360cacc3b04460d013c4d6631b19"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,  108);  // Start with 'k' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 110);  // Start with 'm' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 193);  // from https://en.bitcoin.it/wiki/List_of_address_prefixes

        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >(); // SecureCloud BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >(); // SecureCloud BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();
        // Testnet KMI BIP44 coin type is '1' (All coin's testnet default)
        
        vFixedSeeds.clear();
        vSeeds.clear();

        fMiningRequiresPeers           = true;
        fAllowMinDifficultyBlocks      = false;
        fDefaultConsistencyChecks      = false;
        fRequireStandard               = false;
        fMineBlocksOnDemand            = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions           = 2;
        strSporkKey                    = "04de3deedb9fc1202793e23121aee132f08ba4617cfd5ee6c664abbc1936f6a0b763f3606f1ebff78f0894932bfaff2ceae93737b3e53bb15c49ee271d2b8ddd53";
        strMasternodePoolDummyAddress  = "kFUy3uzz9rMHf1evwzfsgu4oYZLiNh2EP8";
        nStartMasternodePayments       = genesis.nTime + 86400; // 24 hours after genesis
        nBudget_Fee_Confirmations      = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet

        strTreasuryAddress             = "kHk54sqsqmU4z2bxty1vak3iDAt1ApP15y";
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x20;
        pchMessageStart[1] = 0xee;
        pchMessageStart[2] = 0x32;
        pchMessageStart[3] = 0xbc;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // KMI: 1 day
        nTargetSpacing = 2 * 60;        // KMI: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1595320000;
        genesis.nBits = 504365040;
        genesis.nNonce = 1844015;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 40005;
        assert(hashGenesisBlock == uint256("0x00000ed928bd79ff94c1d6cddd48741530db56f01385edf352010f5d1a477d5f"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 30003;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
