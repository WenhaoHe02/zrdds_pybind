#ifndef ai_trainDataReader_h__
#define ai_trainDataReader_h__
/*************************************************************/
/*           此文件由编译器生成，请勿随意修改                */
/*************************************************************/

#include "ai_train.h"
#include "ZRDDSDataReader.h"

namespace ai_train
{
typedef struct TrainCmdSeq TrainCmdSeq;

typedef DDS::ZRDDSDataReader<TrainCmd, TrainCmdSeq> TrainCmdDataReader;

typedef struct ClientUpdateSeq ClientUpdateSeq;

typedef DDS::ZRDDSDataReader<ClientUpdate, ClientUpdateSeq> ClientUpdateDataReader;

typedef struct ModelBlobSeq ModelBlobSeq;

typedef DDS::ZRDDSDataReader<ModelBlob, ModelBlobSeq> ModelBlobDataReader;

}
#endif

