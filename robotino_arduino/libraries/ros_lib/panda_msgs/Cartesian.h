#ifndef _ROS_panda_msgs_Cartesian_h
#define _ROS_panda_msgs_Cartesian_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"

namespace panda_msgs
{

  class Cartesian : public ros::Msg
  {
    public:
      typedef geometry_msgs::Pose _pose_type;
      _pose_type pose;

    Cartesian():
      pose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->pose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->pose.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "panda_msgs/Cartesian"; };
    const char * getMD5(){ return "f192399f711a48924df9a394d37edd67"; };

  };

}
#endif
