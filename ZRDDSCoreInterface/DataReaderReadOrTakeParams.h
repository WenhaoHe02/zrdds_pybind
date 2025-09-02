#ifndef DataReaderReadOrTakeParams_h__
#define DataReaderReadOrTakeParams_h__

typedef struct DataReaderReadOrTakeParams
{
    ZR_BOOLEAN isLoan;
    void** dataPtrArray;
    ZR_UINT32 dataCount;
    DDS_SampleInfoSeq* sampleInfos;
    ZR_INT32 dataSeqLen;
    ZR_INT32 dataSeqMaxLen;
    ZR_BOOLEAN dataSeq_has_ownership;
    ZR_INT8* dataSeqBuffer;
    ZR_UINT32 dataSize;
    /**   
     * @brief   C/C++中的dataSeqBuffer为连续内存，而在Java等不暴露内存的语言中dataSeqBuffer还是为非连续内存，
     *          因而需要此成员区分，0表示连续内存，1表示非连续内存。 
     */
    ZR_UINT32 dataSeqBufferType;
    ZR_INT32 maxSamples;
    const DDS_InstanceHandle_t* handle;
    ZR_BOOLEAN isNext;
    DDS_SampleStateMask sampleMask;
    DDS_ViewStateMask viewMask;
    DDS_InstanceStateMask instanceMask;
    ZR_BOOLEAN isTake;
    void* userCondition;
    void* readCondition;
}DataReaderReadOrTakeParams;

#endif // DataReaderReadOrTakeParams_h__
