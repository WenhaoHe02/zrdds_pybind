/**
 * @file:       ZRMemPool.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRMemPool_h__
#define ZRMemPool_h__

#include "OsResource.h"
#include "ZRDDSCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct ZRMemPool ZRMemPool;

#ifdef _MEMORY_USE_TRACK_

#define ZRMalloc(_MEM_POOL_, _SIZE_) ZRMallocWCallInfo(_MEM_POOL_, _SIZE_, __FILE__, __FUNCTION__, __LINE__)

DCPSDLL extern void* ZRMallocWCallInfo(struct ZRMemPool* pool, DDS_ULong size, const char* fileName, const char* funcName, size_t line);

#else

/**
 * @fn  DCPSDLL extern void* ZRMalloc(ZRMemPool* pool, DDS_ULong size);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   从内存池中分配指定长度的空间。
 *
 * @param [in,out]  pool    指定内存池。
 * @param   size            指定大小。
 *
 * @return  NULL表示分配失败，否则指向分配成功的空间。
 */

DCPSDLL extern void* ZRMalloc(ZRMemPool* pool, DDS_ULong size);

#endif /* _MEMORY_USE_TRACK_ */

/**
 * @fn  DCPSDLL extern void ZRDealloc(ZRMemPool* pool, void* mem);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   在内存池中释放指定的空间。
 *
 * @param [in,out]  pool    指定内存池。
 * @param [in,out]  mem     指定需要释放的空间。
 */

DCPSDLL extern void ZRDealloc(ZRMemPool* pool, void* mem);

/**
 * @fn  DCPSDLL void ZRInitialGlobalMemPool();
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   初始化全局内存空间。
 */

DCPSDLL void ZRInitialGlobalMemPool();

/**
 * @fn  DCPSDLL void ZRFinalizeGlobalMemPool();
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   析构全局数据空间。
 */

DCPSDLL void ZRFinalizeGlobalMemPool();

#ifdef __cplusplus
}
#endif

#endif /* ZRMemPool_h__*/
