#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../CPlusPlusInterface/Subscriber.h"
#include "../CPlusPlusInterface/Entity.h"
#include "../CPlusPlusInterface/DataReader.h"
#include "../CPlusPlusInterface/TopicDescription.h"
#include "../CPlusPlusInterface/DataReaderListener.h"
#include "../CPlusPlusInterface/ZRDDSDataWriter.h"
#include "../CPlusPlusInterface/DomainParticipant.h"
#include "../CPlusPlusInterface/SubscriberListener.h"
#include "../CPlusPlusInterface/DomainParticipantFactory.h"
#include "../CPlusPlusInterface/DomainParticipantListener.h"
#include "../CPlusPlusInterface/DataWriter.h"
#include "../CPlusPlusInterface/Publisher.h"
#include "../ZRDDSCoreInterface/DataReaderQos.h"
#include "../ZRDDSCoreInterface/InstanceHandle_t.h"
#include "../ZRDDSCoreInterface/PublisherQos.h"
#include "../ZRDDSCoreInterface/DomainParticipantFactoryQos.h"
#include "../ZRDDSCoreInterface/DefaultQos.h"
#include "../datastruct_cpp/ai_trainTypeSupport.h"

namespace py = pybind11;

void bind_core(pybind11::module &m);
void bind_listeners(pybind11::module &m);
void bind_data(pybind11::module &m);

PYBIND11_MODULE(DDS_All, m)
a
{
    bind_core(m);
    bind_listeners(m);
    bind_data(m);
}