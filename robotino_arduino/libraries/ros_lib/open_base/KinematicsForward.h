#ifndef _ROS_SERVICE_KinematicsForward_h
#define _ROS_SERVICE_KinematicsForward_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose2D.h"
#include "open_base/Velocity.h"

namespace open_base
{

static const char KINEMATICSFORWARD[] = "open_base/KinematicsForward";

  class KinematicsForwardRequest : public ros::Msg
  {
    public:
      typedef open_base::Velocity _input_type;
      _input_type input;

    KinematicsForwardRequest():
      input()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->input.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->input.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return KINEMATICSFORWARD; };
    const char * getMD5(){ return "29bd53674d0c2a2c975ed4e5dc6ba2a3"; };

  };

  class KinematicsForwardResponse : public ros::Msg
  {
    public:
      typedef geometry_msgs::Pose2D _output_type;
      _output_type output;

    KinematicsForwardResponse():
      output()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->output.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->output.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return KINEMATICSFORWARD; };
    const char * getMD5(){ return "4dc0c3656ea8ad48f1d7d90c513fe25a"; };

  };

  class KinematicsForward {
    public:
    typedef KinematicsForwardRequest Request;
    typedef KinematicsForwardResponse Response;
  };

}
#endif
