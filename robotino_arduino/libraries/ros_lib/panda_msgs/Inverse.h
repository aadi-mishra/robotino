#ifndef _ROS_SERVICE_Inverse_h
#define _ROS_SERVICE_Inverse_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"

namespace panda_msgs
{

static const char INVERSE[] = "panda_msgs/Inverse";

  class InverseRequest : public ros::Msg
  {
    public:
      typedef geometry_msgs::Pose _pose_type;
      _pose_type pose;
      float current_angles[7];

    InverseRequest():
      pose(),
      current_angles()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->pose.serialize(outbuffer + offset);
      for( uint32_t i = 0; i < 7; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->current_angles[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->pose.deserialize(inbuffer + offset);
      for( uint32_t i = 0; i < 7; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->current_angles[i]));
      }
     return offset;
    }

    const char * getType(){ return INVERSE; };
    const char * getMD5(){ return "b39b7c97851f21a7ef18a242db20d874"; };

  };

  class InverseResponse : public ros::Msg
  {
    public:
      float target_angles[7];

    InverseResponse():
      target_angles()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 7; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->target_angles[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 7; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->target_angles[i]));
      }
     return offset;
    }

    const char * getType(){ return INVERSE; };
    const char * getMD5(){ return "fd734290f050f0cac2c261a4926809cc"; };

  };

  class Inverse {
    public:
    typedef InverseRequest Request;
    typedef InverseResponse Response;
  };

}
#endif
