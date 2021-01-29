#ifndef _ROS_open_base_Velocity_h
#define _ROS_open_base_Velocity_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace open_base
{

  class Velocity : public ros::Msg
  {
    public:
      typedef float _v_left_type;
      _v_left_type v_left;
      typedef float _v_back_type;
      _v_back_type v_back;
      typedef float _v_right_type;
      _v_right_type v_right;

    Velocity():
      v_left(0),
      v_back(0),
      v_right(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->v_left);
      offset += serializeAvrFloat64(outbuffer + offset, this->v_back);
      offset += serializeAvrFloat64(outbuffer + offset, this->v_right);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->v_left));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->v_back));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->v_right));
     return offset;
    }

    const char * getType(){ return "open_base/Velocity"; };
    const char * getMD5(){ return "e8a5c19f362eee9352ab07da80a7261d"; };

  };

}
#endif
