/**
 * @file:       DomainEntity.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_DOMAINENTITY_H)
#define _DOMAINENTITY_H

#include "ZRDDSCommon.h"
#include "Entity.h"

namespace DDS {

/**
 * @class   DomainEntity
 *
 * @ingroup CppInfrastruct
 *
 * @brief   该类是所有域参与者子实体的父类，没有实际意义，仅仅根据协议定义。
 */

class DCPSDLL DomainEntity 
    : virtual public Entity
{
public:
    DomainEntity(){}
    virtual ~DomainEntity(){}
};

} // namespace DDS

#endif  //_DOMAINENTITY_H
