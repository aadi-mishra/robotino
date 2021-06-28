#ifndef _ROS_SERVICE_Fk_h
#define _ROS_SERVICE_Fk_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"
#include "sensor_msgs/JointState.h"

namespace panda_msgs
{

static const char FK[] = "panda_msgs/Fk";

  class FkRequest : public ros::Msg
  {
    public:
      typedef sensor_msgs::JointState _joint_states_type;
      _joint_states_type joint_states;

    FkRequest():
      joint_states()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->joint_states.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->joint_states.deserialize(inbuffer + offset);
     return offset;
    }

    virtual const char * getType() override { return FK; };
    virtual const char * getMD5() override { return "482cc7b23f4d6ca5e5aac26ecce1ce01"; };

  };

  class FkResponse : public ros::Msg
  {
    public:
      typedef geometry_msgs::Pose _pose_type;
      _pose_type pose;

    FkResponse():
      pose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->pose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->pose.deserialize(inbuffer + offset);
     return offset;
    }

    virtual const char * getType() override { return FK; };
    virtual const char * getMD5() override { return "f192399f711a48924df9a394d37edd67"; };

  };

  class Fk {
    public:
    typedef FkRequest Request;
    typedef FkResponse Response;
  };

}
#endif
