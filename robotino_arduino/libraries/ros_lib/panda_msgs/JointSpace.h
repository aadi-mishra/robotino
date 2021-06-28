#ifndef _ROS_panda_msgs_JointSpace_h
#define _ROS_panda_msgs_JointSpace_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Float64MultiArray.h"

namespace panda_msgs
{

  class JointSpace : public ros::Msg
  {
    public:
      typedef std_msgs::Float64MultiArray _current_angles_type;
      _current_angles_type current_angles;

    JointSpace():
      current_angles()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->current_angles.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->current_angles.deserialize(inbuffer + offset);
     return offset;
    }

    virtual const char * getType() override { return "panda_msgs/JointSpace"; };
    virtual const char * getMD5() override { return "776bf5a76abc5cac1c242d5b5703be37"; };

  };

}
#endif
