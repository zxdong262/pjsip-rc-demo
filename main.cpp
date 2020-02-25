#include "config.hpp"
#include <pjsua2.hpp>
#include <iostream>

using namespace pj;

class MyAccount : public Account {
public:
    virtual void onRegState(OnRegStateParam &prm) {
        AccountInfo ai = getInfo();
        std::cout << (ai.regIsActive? "*** Register:" : "*** Unregister:")
                  << " code=" << prm.code << std::endl;
    }
};

int main()
{
    Endpoint ep;
    ep.libCreate();
    EpConfig ep_cfg;
    ep.libInit( ep_cfg );
    TransportConfig tcfg;
    tcfg.port = 5060;
    try {
        ep.transportCreate(PJSIP_TRANSPORT_UDP, tcfg);
    } catch (Error &err) {
        std::cout << err.info() << std::endl;
        return 1;
    }
    ep.libStart();
    std::cout << "*** PJSUA2 STARTED ***" << std::endl;

    // Configure an AccountConfig
    AccountConfig acfg;
    acfg.idUri = "sip:" + userName + "@sip.ringcentral.com";
    acfg.regConfig.registrarUri = "sip:" + registrarUri;
    // const pj::StringVector outboundProxyStr = { "sip:" + outboundProxy };
    acfg.sipConfig.proxies = { "sip:" + outboundProxy };
    AuthCredInfo cred("digest", "*", authorizationId, 0, password);
    acfg.sipConfig.authCreds.push_back( cred );

    MyAccount acc =  MyAccount();
    acc.create(acfg);

    pj_thread_sleep(300000);
    return 0;
}