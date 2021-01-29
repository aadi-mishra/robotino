#ifndef _ROS_SERVICE_FrameToFrame_h
#define _ROS_SERVICE_FrameToFrame_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose2D.h"

namespace open_base
{

static const char FRAMETOFRAME[] = "open_base/FrameToFrame";

  class FrameToFrameRequest : public ros::Msg
  {
    public:
      typedef geometry_msgs::Pose2D _input_type;
      _input_type input;

    FrameToFrameRequest():
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

    const char * getType(){ return FRAMETOFRAME; };
    const char * getMD5(){ return "455441d3bb20342e466f79502bdf614e"; };

  };

  class FrameToFrameResponse : public ros::Msg
  {
    public:
      typedef geometry_msgs::Pose2D _output_type;
      _output_type output;

    FrameToFrameResponse():
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

    const char * getType(){ return FRAMETOFRAME; };
    const char * getMD5(){ return "4dc0c3656ea8ad48f1d7d90c513fe25a"; };

  };

  class FrameToFrame {
    public:
    typedef FrameToFrameRequest Request;
    typedef FrameToFrameResponse Response;
  };

}
#endif
