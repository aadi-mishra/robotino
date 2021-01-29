#ifndef _ROS_SERVICE_KinematicsInverse_h
#define _ROS_SERVICE_KinematicsInverse_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose2D.h"
#include "open_base/Velocity.h"

namespace open_base
{

static const char KINEMATICSINVERSE[] = "open_base/KinematicsInverse";

  class KinematicsInverseRequest : public ros::Msg
  {
    public:
      typedef geometry_msgs::Pose2D _input_type;
      _input_type input;

    KinematicsInverseRequest():
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

    const char * getType(){ return KINEMATICSINVERSE; };
    const char * getMD5(){ return "455441d3bb20342e466f79502bdf614e"; };

  };

  class KinematicsInverseResponse : public ros::Msg
  {
    public:
      typedef open_base::Velocity _output_type;
      _output_type output;

    KinematicsInverseResponse():
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

    const char * getType(){ return KINEMATICSINVERSE; };
    const char * getMD5(){ return "17afbbcc9d7e674dabef0f5797d91090"; };

  };

  class KinematicsInverse {
    public:
    typedef KinematicsInverseRequest Request;
    typedef KinematicsInverseResponse Response;
  };

}
#endif
