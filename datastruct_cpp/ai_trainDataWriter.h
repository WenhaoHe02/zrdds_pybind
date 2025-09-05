#ifndef ai_trainDataWriter_h__
#define ai_trainDataWriter_h__
/*************************************************************/
/*           此文件由编译器生成，请勿随意修改                */
/*************************************************************/

#include "ai_train.h"
#include "ZRDDSDataWriter.h"

namespace ai_train
{

typedef DDS::ZRDDSDataWriter<TrainCmd> TrainCmdDataWriter;


typedef DDS::ZRDDSDataWriter<ClientUpdate> ClientUpdateDataWriter;


typedef DDS::ZRDDSDataWriter<ModelBlob> ModelBlobDataWriter;

}
#endif

