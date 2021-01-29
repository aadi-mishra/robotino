#ifndef _ROS_open_base_MovementGeneric_h
#define _ROS_open_base_MovementGeneric_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose2D.h"

namespace open_base
{

  class MovementGeneric : public ros::Msg
  {
    public:
      typedef uint8_t _type_type;
      _type_type type;
      typedef uint8_t _frame_type;
      _frame_type frame;
      typedef geometry_msgs::Pose2D _target_type;
      _target_type target;

    MovementGeneric():
      type(0),
      frame(0),
      target()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->type >> (8 * 0)) & 0xFF;
      offset += sizeof(this->type);
      *(outbuffer + offset + 0) = (this->frame >> (8 * 0)) & 0xFF;
      offset += sizeof(this->frame);
      offset += this->target.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->type =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->type);
      this->frame =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->frame);
      offset += this->target.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "open_base/MovementGeneric"; };
    const char * getMD5(){ return "4524cf69d2ddd194d9c04f05478153fd"; };

  };

}
#endif
