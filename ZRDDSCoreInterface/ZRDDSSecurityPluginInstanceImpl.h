/**
 * @file:       ZRDDSSecurityPluginInstanceImpl.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRDDSSecurityPluginInstanceImpl_h__
#define ZRDDSSecurityPluginInstanceImpl_h__

#include "ZROSDefine.h"
#ifdef _ZRDDSSECURITY

#include "DDSBuiltinSecurityCommon.h"
#include "Authentication.h"
#include "AccessControl.h"
#include "CryptoKeyFactory.h"
#include "CryptoKeyExchange.h"
#include "CryptoTransform.h"

struct ZRDDSSecurityPluginInstanceImpl
{
    Authentication* authentication;
    AccessControl* access_control;
    CryptoKeyFactory* crypto_key_factory;
    CryptoKeyExchange* crypto_key_exchange;
    CryptoTransform* crypto_transform;
    DDS_Time_t retry_time;
    DDS_Time_t max_wait_time;
    DDS_ULong max_retry_number;
};

void ZRDDSSecurityPluginInstanceTransform(
    ZRDDSSecurityPluginInstance& src,
    ZRDDSSecurityPluginInstanceImpl& dst);

#endif /* _ZRDDSSECURITY */

#endif /* ZRDDSSecurityPluginInstanceImpl_h__ */
